#include "stdafx.h"
#include "CreateWdwDlg.h"
#include "DataForm.h"


CreateWdwDlg::CreateWdwDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	userEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	valueEdit->setMaxLength(17);
	targetEdit->setMaxLength(100);
	saIDEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateWdwDlg::EditWithdrawal);
	}
	else
	{
		subAccBtn->setDisabled(true);
		accBtn->setDisabled(true);
		userBtn->setDisabled(true);
		dateEdit->setDateTime(QDateTime::currentDateTime());

		BusinessLayer::Status *status = new BusinessLayer::Status();
		status->SetName("TO PAY");
		std::string statusFilter = dialogBL->GenerateFilter<BusinessLayer::Status>(status);
		std::vector<BusinessLayer::Status> statusVector = dialogBL->GetAllDataForClass<BusinessLayer::Status>(errorMessage, statusFilter);
		delete status;
		if (statusVector.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Status are empty please contact with Admin")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		statusEdit->setText(QString::number(statusVector.at(0).GetID()));
		statusPh->setText(statusVector.at(0).GetName().c_str());

		QObject::connect(okBtn, &QPushButton::released, this, &CreateWdwDlg::CreateWithdrawal);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateWdwDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreateWdwDlg::OpenUserDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateWdwDlg::TextEditChanged);
	QObject::connect(subAccBtn, &QPushButton::released, this, &CreateWdwDlg::OpenSAccDlg);
	QObject::connect(accBtn, &QPushButton::released, this, &CreateWdwDlg::OpenAccDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateWdwDlg::OpenStatusDlg);
	QObject::connect(saNumberEdit, &QLineEdit::textChanged, this, &CreateWdwDlg::SATextChanged);
	QObject::connect(accNumberEdit, &QLineEdit::textChanged, this, &CreateWdwDlg::AccTextChanged);
	QObject::connect(userEdit, &QLineEdit::textChanged, this, &CreateWdwDlg::UserIsChanged);
	QObject::connect(accountCmb, &QComboBox::currentTextChanged, this, &CreateWdwDlg::AccountIsChenged);
	InitComboBox();
}

CreateWdwDlg::~CreateWdwDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateWdwDlg::SetID(int ID, QString childName)
{
	if (0 != ID)
	{
		if (0 != childName.length())
		{
			this->hide();
			this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
			this->show();
			this->raise();
			this->activateWindow();
			QApplication::setActiveWindow(this);

			if (childName == QString("userForm"))
			{
				userEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					namePh->setText(user.GetName().c_str());
					surnamePh->setText(user.GetSurname().c_str());
					phonePh->setText(user.GetPhone().c_str());
					accountCmb->setDisabled(true);
					accIDEdit->setText(QString::number(GetAccountIDFromCmb()));
				}
				BusinessLayer::Balance balance;
				BusinessLayer::Subaccount subaccount;
				BusinessLayer::Currency currency;
				balance.SetUserID(ID);
				std::string filter = balance.GenerateFilter(dialogBL->GetOrmasDal());
				std::vector<BusinessLayer::BalanceView> balanceVector = dialogBL->GetAllDataForClass<BusinessLayer::BalanceView>(errorMessage, filter);
				if (0 < balanceVector.size())
				{
					for each (auto item in balanceVector)
					{
						subaccount.Clear();
						if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetSubaccountID(), errorMessage))
						{
							if (subaccount.GetParentAccountID() == GetAccountIDFromCmb())
							{
								balance.SetSubaccountID(subaccount.GetID());
							}
						}
					}
				}
				subaccount.Clear();
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance.GetSubaccountID(), errorMessage))
				{
					saIDEdit->setText(QString::number(subaccount.GetID()));
					saNumberEdit->setReadOnly(true);
					saNumberEdit->setText(subaccount.GetNumber().c_str());
					balanceEdit->setText(QString::number(subaccount.GetCurrentBalance()));
					if (currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount.GetCurrencyID(), errorMessage))
					{
						currencyNameEdit->setText(currency.GetName().c_str());
					}
				}
				
			}
			if (childName == QString("subaccountForm"))
			{
				saIDEdit->setText(QString::number(ID));
				BusinessLayer::Subaccount subaccount;
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					saNumberEdit->setReadOnly(true);
					saNumberEdit->setText(subaccount.GetNumber().c_str());
				}
				namePh->setText("");
				surnamePh->setText("");
				phonePh->setText("");
				userEdit->setText("");
			}
			if (childName == QString("accountForm"))
			{
				accIDEdit->setText(QString::number(ID));
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accNumberEdit->setReadOnly(true);
					accNumberEdit->setText(account.GetNumber().c_str());
				}
				namePh->setText("");
				surnamePh->setText("");
				phonePh->setText("");
				userEdit->setText("");
			}
			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
				BusinessLayer::Status status;
				if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					statusPh->setText(status.GetName().c_str());
				}
			}
		}
	}
}

void CreateWdwDlg::SetWithdrawalParams(QString wDate, double wValue, int wUserID, int wSubAccId, QString wTarget, int wCurrencyID, 
	int wStatusID, int wAccountID, QString wWho, int cashboxAccID, int id)
{
	withdrawal->SetDate(wDate.toUtf8().constData());
	withdrawal->SetValue(wValue);
	withdrawal->SetUserID(wUserID);
	withdrawal->SetSubaccountID(wSubAccId);
	withdrawal->SetTarget(wTarget.toUtf8().constData());
	withdrawal->SetCurrencyID(wCurrencyID);
	withdrawal->SetStatusID(wStatusID);
	withdrawal->SetAccountID(wAccountID);
	withdrawal->SetWho(wWho.toUtf8().constData());
	withdrawal->SetCashboxAccountID(cashboxAccID);
	withdrawal->SetID(id);
}

void CreateWdwDlg::FillEditElements(QString wDate, double wValue, int wUserID, int wSubAccId, QString wTarget, int wCurrencyID,
	int wStatusID, int wAccountID, QString wWho)
{
	accountCmb->setDisabled(true);
	dateEdit->setDateTime(QDateTime::fromString(wDate, "dd.MM.yyyy hh:mm"));
	valueEdit->setText(QString::number(wValue,'f',3));
	userEdit->setText(QString::number(wUserID));
	saIDEdit->setText(QString::number(wSubAccId));
	targetEdit->setText(wTarget);
	whoEdit->setText(wWho);
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(wCurrencyID)));
	accIDEdit->setText(QString::number(wAccountID));
	statusEdit->setText(QString::number(wStatusID));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wUserID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
	BusinessLayer::Subaccount sub;
	if (sub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wSubAccId, errorMessage))
	{
		saNumberEdit->setText(sub.GetNumber().c_str());
	}
	BusinessLayer::Account acc;
	if (acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wAccountID, errorMessage))
	{
		accNumberEdit->setText(acc.GetNumber().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), wStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateWdwDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetWithdrawalParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 14)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 13)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 15)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 16)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 17)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 14)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 13)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 15)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 16)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData());
		return CheckAccess();
	}
	else
	{
		return false;
	}
}

void CreateWdwDlg::CreateWithdrawal()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty() && !whoEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		int cashboxAccID = GetCashboxAccountID();
		if (0 == cashboxAccID)
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("You have not rights to create withdrawal")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		SetWithdrawalParams(dateEdit->text(), valueEdit->text().toDouble(), userEdit->text().toInt(), saIDEdit->text().toInt(),
			targetEdit->text(), currencyCmb->currentData().toInt(), statusEdit->text().toInt(), accIDEdit->text().toInt(), whoEdit->text(), cashboxAccID);
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateWithdrawal(withdrawal, errorMessage))
		{
			if (!CrateCashboxTransaction(withdrawal->GetID()))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Cannot create cashbox transaction!")),
					QString(tr("Ok")));
				errorMessage.clear();
				return;
			}
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Currency currency;
					if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
					BusinessLayer::User user;
					if (userEdit->text().toInt() >0)
					{
						if (!user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetUserID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
					}
					BusinessLayer::Subaccount subacc;
					if (saIDEdit->text().toInt() > 0)
					{
						if (!subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetSubaccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
					}
					BusinessLayer::Account account;
					if (accIDEdit->text().toInt() > 0)
					{
						
						if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
					}
					BusinessLayer::Status status;
					if (!status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						return;
					}
					QList<QStandardItem*> withdrawalItem;
					withdrawalItem << new QStandardItem(QString::number(withdrawal->GetID()))
						<< new QStandardItem(withdrawal->GetDate().c_str())
						<< new QStandardItem(QString::number(withdrawal->GetValue(),'f',3))
						<< new QStandardItem(currency.GetShortName().c_str());
					if (userEdit->text().isEmpty() || user.IsEmpty())
					{
						withdrawalItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					else
					{
						withdrawalItem << new QStandardItem(user.GetName().c_str())
							<< new QStandardItem(user.GetSurname().c_str())
							<< new QStandardItem(user.GetPhone().c_str());
					}
					withdrawalItem << new QStandardItem(status.GetName().c_str());
					if (accIDEdit->text().toInt() > 0)
					{
						withdrawalItem << new QStandardItem(account.GetNumber().c_str());
					}
					else
					{
						withdrawalItem << new QStandardItem("");
					}
					if (saIDEdit->text().toInt() > 0)
					{
						withdrawalItem << new QStandardItem(subacc.GetNumber().c_str());
					}
					else
					{
						withdrawalItem << new QStandardItem("");
					}
					withdrawalItem << new QStandardItem(withdrawal->GetWho().c_str())
						<< new QStandardItem(withdrawal->GetTarget().c_str())
						<< new QStandardItem(QString::number(withdrawal->GetUserID()))
						<< new QStandardItem(QString::number(withdrawal->GetCurrencyID()))
						<< new QStandardItem(QString::number(withdrawal->GetSubaccountID()))
						<< new QStandardItem(QString::number(withdrawal->GetStatusID()))
						<< new QStandardItem(QString::number(withdrawal->GetAccountID()))
						<< new QStandardItem(QString::number(withdrawal->GetCashboxAccountID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(withdrawalItem);
				}
			}
			if (!dialogBL->CommitTransaction(errorMessage))
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
			}
			
			Close();
		}
		else
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));

			errorMessage.clear();
		}

	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill employee or subaccout, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateWdwDlg::EditWithdrawal()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty() && !whoEdit->text().isEmpty())
	{
		if (QString(withdrawal->GetDate().c_str()) != dateEdit->text() || withdrawal->GetStatusID() != statusEdit->text().toInt() 
			|| withdrawal->GetValue() != valueEdit->text().toDouble() || withdrawal->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetWithdrawalParams(dateEdit->text(), valueEdit->text().toDouble(), userEdit->text().toInt(), saIDEdit->text().toInt(), targetEdit->text(), 
				currencyCmb->currentData().toInt(), statusEdit->text().toInt(), accIDEdit->text().toInt(), whoEdit->text(), withdrawal->GetCashboxAccountID(), withdrawal->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateWithdrawal(withdrawal, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Currency currency;
						if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
						BusinessLayer::User user;
						if (userEdit->text().toInt() >0)
						{
							if (!user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetUserID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								return;
							}
						}
						BusinessLayer::Subaccount subacc;
						if (saIDEdit->text().toInt() > 0)
						{
							if (!subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetSubaccountID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								return;
							}
						}
						BusinessLayer::Account account;
						if (accIDEdit->text().toInt() > 0)
						{

							if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetAccountID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								return;
							}
						}
						BusinessLayer::Status status;
						if (!status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
						itemModel->item(mIndex.row(), 1)->setText(withdrawal->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(withdrawal->GetValue(),'f',3));
						itemModel->item(mIndex.row(), 3)->setText(currency.GetShortName().c_str());
						if (userEdit->text().isEmpty() || user.IsEmpty())
						{
							itemModel->item(mIndex.row(), 4)->setText("");
							itemModel->item(mIndex.row(), 5)->setText("");
							itemModel->item(mIndex.row(), 6)->setText("");
						}
						else
						{
							itemModel->item(mIndex.row(), 4)->setText(user.GetName().c_str());
							itemModel->item(mIndex.row(), 5)->setText(user.GetSurname().c_str());
							itemModel->item(mIndex.row(), 6)->setText(user.GetPhone().c_str());
						}
						itemModel->item(mIndex.row(), 7)->setText(status.GetName().c_str());
						if (accIDEdit->text().toInt()>0)
						{
							itemModel->item(mIndex.row(), 8)->setText(account.GetNumber().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 8)->setText("");
						}
						if (saIDEdit->text().toInt()>0)
						{
							itemModel->item(mIndex.row(), 9)->setText(subacc.GetNumber().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 9)->setText("");
						}
						itemModel->item(mIndex.row(), 10)->setText(withdrawal->GetWho().c_str());
						itemModel->item(mIndex.row(), 11)->setText(withdrawal->GetTarget().c_str());
						itemModel->item(mIndex.row(), 12)->setText(QString::number(withdrawal->GetUserID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(withdrawal->GetCurrencyID()));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(withdrawal->GetSubaccountID()));
						itemModel->item(mIndex.row(), 15)->setText(QString::number(withdrawal->GetStatusID()));
						itemModel->item(mIndex.row(), 16)->setText(QString::number(withdrawal->GetAccountID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(withdrawal->GetCashboxAccountID()));
						emit itemModel->dataChanged(mIndex, mIndex);
					}
				}
				if (!dialogBL->CommitTransaction(errorMessage))
				{
					dialogBL->CancelTransaction(errorMessage);
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(tr(errorMessage.c_str())),
						QString(tr("Ok")));
				}
				
				Close();
			}
			else
			{
				dialogBL->CancelTransaction(errorMessage);
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr(errorMessage.c_str())),
					QString(tr("Ok")));
			}

		}
		else
		{
			Close();
		}
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please fill employee or subaccout, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateWdwDlg::Close()
{
	this->parentWidget()->close();
}

void CreateWdwDlg::OpenUserDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Users"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	std::string branchFilter = "";
	BusinessLayer::Account account10520;
	BusinessLayer::Account account11620;
	BusinessLayer::Account account22210;
	if (!account10520.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
		return;
	if (!account11620.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "11620", errorMessage))
		return;
	if (!account22210.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "22210", errorMessage))
		return;

	BusinessLayer::EntryRouting entryRouting;
	if (!entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
		return;

	if (account10520.GetID() == entryRouting.GetCreditAccountID() || account10520.GetID() == entryRouting.GetCreditAccountID()
		|| account10520.GetID() == entryRouting.GetCreditAccountID())
	{
		BusinessLayer::Branch branch;
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainForm->GetLoggedUser()->GetID(), errorMessage);
		if (0 < branchID)
		{
			branch.SetID(branchID);
			branchFilter = branch.GenerateFilter(dialogBL->GetOrmasDal());
		}
	}

	dForm->FillTable<BusinessLayer::UserExtendedView>(errorMessage, branchFilter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("userForm");
		dForm->QtConnect<BusinessLayer::UserExtendedView>();
		QMdiSubWindow *userWindow = new QMdiSubWindow;
		userWindow->setWidget(dForm);
		userWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(userWindow);
		userWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		SortTable(dForm->tableView);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All users are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateWdwDlg::OpenSAccDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Subccounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	std::string filter = "";
	BusinessLayer::Subaccount sabaccount;
	BusinessLayer::EntryRouting entryRouting;
	if (entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
	{
		sabaccount.SetParentAccountID(entryRouting.GetDebitAccountID());
		filter = sabaccount.GenerateFilter(dialogBL->GetOrmasDal());
	}
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage, filter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("subaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *dSAccountWindow = new QMdiSubWindow;
		dSAccountWindow->setWidget(dForm);
		dSAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(dSAccountWindow);
		dSAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->SetDecoration();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All subaccounts are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateWdwDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}

	BusinessLayer::ChartOfAccounts coAcc;
	BusinessLayer::Account account;
	BusinessLayer::Account account10110;
	BusinessLayer::EntryRouting entryRouting;
	if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10110", errorMessage))
	{
		std::string comboText = "";
		entryRouting.SetCreditAccountID(account.GetID());
		std::string filter = entryRouting.GenerateFilter(dialogBL->GetOrmasDal());
		std::vector<BusinessLayer::EntryRouting> entRoutVec = dialogBL->GetAllDataForClass<BusinessLayer::EntryRouting>(errorMessage, filter);
		accountCmb->addItem(tr("All"), 0);
		if (!entRoutVec.empty())
		{
			for (unsigned int i = 0; i < entRoutVec.size(); i++)
			{
				account.Clear();
				if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entRoutVec[i].GetDebitAccountID(), errorMessage))
					continue;
				coAcc.Clear();
				if (!coAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), account.GetNumber(), errorMessage))
					continue;
				comboText = "";
				comboText += account.GetNumber();
				comboText += " - ";
				comboText += coAcc.GetName();
				accountCmb->addItem(comboText.c_str(), QVariant(entRoutVec[i].GetID()));
			}
		}
		else
		{
			errorMessage = "";
		}
	}
}

void CreateWdwDlg::TextEditChanged()
{
	if (valueEdit->text().contains(","))
	{
		valueEdit->setText(valueEdit->text().replace(",", "."));
	}
	if (valueEdit->text().contains(".."))
	{
		valueEdit->setText(valueEdit->text().replace("..", "."));
	}
}

void CreateWdwDlg::AccountIsChenged()
{
	if (accountCmb->currentData().toInt() == 0)
	{
		targetEdit->setText("");
	}
	else
	{
		subAccBtn->setEnabled(true);
		accBtn->setEnabled(true);
		userBtn->setEnabled(true);
		BusinessLayer::EntryRouting entRouting;
		if (entRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
		{
			targetEdit->setText(entRouting.GetOperation().c_str());
		}
		else
		{
			targetEdit->setText("");
		}
	}
}

void CreateWdwDlg::OpenAccDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Accounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	std::string filter = "";
	BusinessLayer::Account account;
	BusinessLayer::EntryRouting entryRouting;
	if (entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
	{
		account.SetID(entryRouting.GetDebitAccountID());
		filter = account.GenerateFilter(dialogBL->GetOrmasDal());
	}
	dForm->FillTable<BusinessLayer::Account>(errorMessage, filter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *accountWindow = new QMdiSubWindow;
		accountWindow->setWidget(dForm);
		accountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accountWindow);
		accountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		dForm->tableView->setColumnHidden(2, true);
		dForm->tableView->setColumnHidden(3, true);
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accounts are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}

}

void CreateWdwDlg::OpenStatusDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Status"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);

	dForm->FillTable<BusinessLayer::Status>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("statusForm");
		dForm->QtConnect<BusinessLayer::Status>();
		QMdiSubWindow *statusWindow = new QMdiSubWindow;
		statusWindow->setWidget(dForm);
		statusWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(statusWindow);
		statusWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All statuses are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void CreateWdwDlg::AccTextChanged()
{
	if (accNumberEdit->text().length() == 5)
	{
		BusinessLayer::Account account;
		if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), accNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			accIDEdit->setText(QString::number(account.GetID()));
		}
		else
		{
			accIDEdit->setText("");
		}
	}
}
void CreateWdwDlg::SATextChanged()
{
	if (saNumberEdit->text().length() == 5 || saNumberEdit->text().length() == 6)
	{
		BusinessLayer::Account account;
		if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), saNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			saIDEdit->setText(QString::number(account.GetID()));
		}
		else
		{
			saIDEdit->setText("");
		}
	}
	else if (saNumberEdit->text().length() == 15)
	{
		BusinessLayer::Subaccount subaccount;
		if (subaccount.GetSubaccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), saNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			saIDEdit->setText(QString::number(subaccount.GetID()));
		}
		else
		{
			saIDEdit->setText("");
		}
	}
	else
	{
		saIDEdit->setText("");
	}
}

int CreateWdwDlg::GetAccountIDFromCmb()
{
	BusinessLayer::Account account;
	BusinessLayer::EntryRouting entryRouting;
	if (entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
	{
		return entryRouting.GetDebitAccountID();
	}
	else
	{
		return 0;
	}
}

void CreateWdwDlg::UserIsChanged()
{
	BusinessLayer::Balance balance;
	BusinessLayer::Subaccount suba;
	if (balance.GetBalanceByUserID(dialogBL->globalVar, dialogBL->GetOrmasDal(), userEdit->text().toInt(), errorMessage))
	{
		if (suba.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance.GetSubaccountID(), errorMessage))
		{
			saIDEdit->setText(QString::number(suba.GetID()));
			saNumberEdit->setText(suba.GetNumber().c_str());
		}
	}
}

void CreateWdwDlg::SortTable(QTableView *table)
{
	BusinessLayer::EntryRouting entryRouting;
	if (!entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
		return;
	for (int i = 0; i < table->model()->rowCount(); i++)
	{
		QModelIndex index = table->model()->index(i, 11);
		if (index.data().toInt() == entryRouting.GetDebitAccountID())
		{
			table->showRow(i);
			continue;
		}
		else
		{
			table->hideRow(i);
		}
	}
	errorMessage = "";
}

bool CreateWdwDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), withdrawal->GetStatusID(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		delete status;
		return false;
	}

	if (0 == status->GetName().compare("EXECUTED"))
	{
		if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
			mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
		{
			return true;
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("This document have an \"EXECUTED\" status. The document with \"EXECUTED\" status cannot be changed!")),
				QString(tr("Ok")));
			errorMessage.clear();
			delete status;
			return false;
		}
	}

	if (0 == status->GetName().compare("ERROR"))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("This document have an \"ERROR\" status. The document with \"ERROR\" status cannot be changed!")),
			QString(tr("Ok")));
		errorMessage.clear();
		delete status;
		return false;
	}

	return true;
}

int CreateWdwDlg::GetCashboxAccountID()
{
	BusinessLayer::Cashbox cashbox;
	BusinessLayer::CashboxEmployeeRelation ceRelation;
	if (ceRelation.GetCashboxEmployeeByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dialogBL->loggedUser->GetID(), errorMessage))
	{
		if (cashbox.GetCashboxByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ceRelation.GetCashboxID(), errorMessage))
		{
			return cashbox.GetSubaccountID();
		}
	}
	return 0;
}

bool CreateWdwDlg::CrateCashboxTransaction(int withdrawalID)
{
	BusinessLayer::Cashbox cashbox;
	BusinessLayer::CashboxEmployeeRelation ceRelation;
	if (ceRelation.GetCashboxEmployeeByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dialogBL->loggedUser->GetID(), errorMessage))
	{
		if (cashbox.GetCashboxByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ceRelation.GetCashboxID(), errorMessage))
		{
			BusinessLayer::Employee accountant;
			BusinessLayer::Employee owner;
			BusinessLayer::Role role;

			if (0 == role.GetRoleIDByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "CHIEF ACCOUNTANT", errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Connot find 'CHIEF ACCOUNTANT' role!")),
					QString(tr("Ok")));
				return false;
			}

			accountant.SetRoleID(role.GetID());
			std::string empFilter = accountant.GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::EmployeeView> vecEmpRep = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, empFilter);
			if (vecEmpRep.size() == 0)
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Connot find 'CHIEF ACCOUNTANT' employee!")),
					QString(tr("Ok")));
				return false;
			}
			else
			{
				accountant.SetID(vecEmpRep.at(0).GetID());
				accountant.SetName(vecEmpRep.at(0).GetName());
				accountant.SetSurname(vecEmpRep.at(0).GetSurname());
			}

			role.Clear();
			if (0 == role.GetRoleIDByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "DIRECTOR", errorMessage))
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Connot find 'OWNER' role!")),
					QString(tr("Ok")));
				return false;
			}

			owner.SetRoleID(role.GetID());
			std::string ownFilter = owner.GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::EmployeeView> vecOwnRep = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, ownFilter);
			if (vecOwnRep.size() == 0)
			{
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Connot find 'OWNER' employee!")),
					QString(tr("Ok")));
				return false;
			}
			else
			{
				owner.SetID(vecOwnRep.at(0).GetID());
				owner.SetName(vecOwnRep.at(0).GetName());
				owner.SetSurname(vecOwnRep.at(0).GetSurname());
			}

			BusinessLayer::CashboxTransaction cTransaction;
			if (cTransaction.CreateCashboxTransaction(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox.GetID(), dialogBL->loggedUser->GetID(), accountant.GetID(), owner.GetID(), 0, withdrawalID, errorMessage))
				return true;
		}
	}
	return false;
}