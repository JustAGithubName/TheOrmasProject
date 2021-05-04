#include "stdafx.h"
#include "CreatePmtDlg.h"
#include "DataForm.h"



CreatePmtDlg::CreatePmtDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	targetEdit->setMaxLength(100);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePmtDlg::EditPayment);
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

		QObject::connect(okBtn, &QPushButton::released, this, &CreatePmtDlg::CreatePayment);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePmtDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreatePmtDlg::OpenUserDlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreatePmtDlg::OpenStatusDlg);
	QObject::connect(accBtn, &QPushButton::released, this, &CreatePmtDlg::OpenAccDlg);
	QObject::connect(subAccBtn, &QPushButton::released, this, &CreatePmtDlg::OpenSAccDlg);
	QObject::connect(accNumberEdit, &QLineEdit::textChanged, this, &CreatePmtDlg::AccTextChanged);
	QObject::connect(saNumberEdit, &QLineEdit::textChanged, this, &CreatePmtDlg::SATextChanged);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreatePmtDlg::TextEditChanged);
	QObject::connect(accountCmb, &QComboBox::currentTextChanged, this, &CreatePmtDlg::AccountIsChenged);
	QObject::connect(userEdit, &QLineEdit::textChanged, this, &CreatePmtDlg::UserIsChanged);
	InitComboBox();
}

CreatePmtDlg::~CreatePmtDlg()
{
	delete vInt;
	delete vDouble;
}

void CreatePmtDlg::SetID(int ID, QString childName)
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
			if (childName == QString("statusForm"))
			{
				statusEdit->setText(QString::number(ID));
				BusinessLayer::Status status;
				if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					statusPh->setText(status.GetName().c_str());
				}
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
		}
	}
}

void CreatePmtDlg::SetPaymentParams(QString pDate, double pValue, QString pTarget, int pUserID, int pCurrencyID, int pStatusID, 
	int pAccountID, int pSubaccountID, QString pWho, int cashboxAccID, int id)
{
	payment->SetDate(pDate.toUtf8().constData());
	payment->SetValue(pValue);
	payment->SetTarget(pTarget.toUtf8().constData());
	payment->SetUserID(pUserID);
	payment->SetCurrencyID(pCurrencyID);
	payment->SetStatusID(pStatusID);
	payment->SetAccountID(pAccountID);
	payment->SetSubaccountID(pSubaccountID);
	payment->SetWho(pWho.toUtf8().constData());
	payment->SetCashboxAccountID(cashboxAccID);
	payment->SetID(id);
}

void CreatePmtDlg::FillEditElements(QString pDate, double pValue, QString pTarget, int pUserID, int pCurrencyID, int pStatusID,
	int pAccountID, int pSubaccountID, QString pWho)
{
	accountCmb->setDisabled(true);
	dateEdit->setDateTime(QDateTime::fromString(pDate, "dd.MM.yyyy hh:mm"));
	valueEdit->setText(QString::number(pValue,'f',3));
	targetEdit->setText(pTarget);
	userEdit->setText(QString::number(pUserID));
	statusEdit->setText(QString::number(pStatusID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	accIDEdit->setText(QString::number(pAccountID));
	whoEdit->setText(pWho);
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pUserID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
	BusinessLayer::Subaccount sub;
	if (sub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pSubaccountID, errorMessage))
	{
		saNumberEdit->setText(sub.GetNumber().c_str());
	}
	BusinessLayer::Status status;
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pStatusID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
	BusinessLayer::Account acc;
	if (acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pAccountID, errorMessage))
	{
		accNumberEdit->setText(acc.GetNumber().c_str());
	}
}

bool CreatePmtDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPaymentParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 13)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 14)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 15)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 16)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 17)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 13)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 14)).toInt(),
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

void CreatePmtDlg::CreatePayment()
{
	errorMessage.clear();
	if ( 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty() && 0 != statusEdit->text().toInt()
		&& !whoEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		int cashboxAccID = GetCashboxAccountID();
		if (0 == cashboxAccID)
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("You have not rights to create payment")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		SetPaymentParams(dateEdit->text(), valueEdit->text().toDouble(), targetEdit->text(), userEdit->text().toInt(), 
			currencyCmb->currentData().toInt(), statusEdit->text().toInt(), accIDEdit->text().toInt(), saIDEdit->text().toInt(), 
			whoEdit->text(), cashboxAccID);
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePayment(payment, errorMessage))
		{
			if (!CrateCashboxTransaction(payment->GetID()))
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
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					BusinessLayer::User *user = new BusinessLayer::User;
					BusinessLayer::Status *status = new BusinessLayer::Status;
					if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetCurrencyID(), errorMessage) ||
						!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetStatusID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete currency;
						delete user;
						delete status;
						return;
					}
					if (userEdit->text().toInt() > 0)
					{
						if (!user->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetUserID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete currency;
							delete user;
							delete status;
							return;
						}
					}
					BusinessLayer::Subaccount subacc;
					if (saIDEdit->text().toInt() > 0)
					{
						if (!subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetSubaccountID(), errorMessage))
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

						if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							return;
						}
					}
					QList<QStandardItem*> paymentItem;
					paymentItem << new QStandardItem(QString::number(payment->GetID()))
						<< new QStandardItem(payment->GetDate().c_str());
					if (userEdit->text().toInt() > 0)
					{
						paymentItem << new QStandardItem(user->GetName().c_str())
							<< new QStandardItem(user->GetSurname().c_str())
							<< new QStandardItem(user->GetPhone().c_str());
					}
					else
					{
						paymentItem << new QStandardItem("")
							<< new QStandardItem("")
							<< new QStandardItem("");
					}
					paymentItem << new QStandardItem(QString::number(payment->GetValue(), 'f', 3))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(payment->GetTarget().c_str());
					if (accIDEdit->text().toInt() > 0)
					{
						paymentItem << new QStandardItem(account.GetNumber().c_str());
					}
					else
					{
						paymentItem << new QStandardItem("");
					}
					if (saIDEdit->text().toInt() > 0)
					{
						paymentItem << new QStandardItem(subacc.GetNumber().c_str());
					}
					else
					{
						paymentItem << new QStandardItem("");
					}
					paymentItem << new QStandardItem(payment->GetWho().c_str())
						<< new QStandardItem(status->GetName().c_str())
						<< new QStandardItem(QString::number(payment->GetUserID()))
						<< new QStandardItem(QString::number(payment->GetCurrencyID()))
						<< new QStandardItem(QString::number(payment->GetStatusID()))
						<< new QStandardItem(QString::number(payment->GetAccountID()))
						<< new QStandardItem(QString::number(payment->GetSubaccountID()))
						<< new QStandardItem(QString::number(payment->GetCashboxAccountID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(paymentItem);
					delete currency;
					delete user;
					delete status;
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
			QString(tr("Please fill user, value, date and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePmtDlg::EditPayment()
{
	errorMessage.clear();
	if (0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty() && !whoEdit->text().isEmpty() && 0 != statusEdit->text().toInt())
	{
		if (QString(payment->GetDate().c_str()) != dateEdit->text()
			|| payment->GetValue() != valueEdit->text().toDouble() || payment->GetCurrencyID() != currencyCmb->currentData().toInt()
			|| payment->GetStatusID() != statusEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetPaymentParams(dateEdit->text(), valueEdit->text().toDouble(), targetEdit->text(), userEdit->text().toInt(),
				currencyCmb->currentData().toInt(), statusEdit->text().toInt(), accIDEdit->text().toInt(), saIDEdit->text().toInt(),
				whoEdit->text(),payment->GetCashboxAccountID(), payment->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePayment(payment, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::User *user = new BusinessLayer::User;
						BusinessLayer::Status *status = new BusinessLayer::Status;
						if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetCurrencyID(), errorMessage) ||
							!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetStatusID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete currency;
							delete user;
							delete status;
							return;
						}
						if (userEdit->text().toInt() > 0)
						{
							if (!user->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetUserID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								delete currency;
								delete user;
								delete status;
								return;
							}
						}
						BusinessLayer::Subaccount subacc;
						if (saIDEdit->text().toInt() > 0)
						{
							if (!subacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetSubaccountID(), errorMessage))
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

							if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetAccountID(), errorMessage))
							{
								dialogBL->CancelTransaction(errorMessage);
								QMessageBox::information(NULL, QString(tr("Warning")),
									QString(tr(errorMessage.c_str())),
									QString(tr("Ok")));
								errorMessage.clear();
								return;
							}
						}
						itemModel->item(mIndex.row(), 1)->setText(payment->GetDate().c_str());
						if (userEdit->text().toInt() > 0)
						{
							itemModel->item(mIndex.row(), 2)->setText(user->GetName().c_str());
							itemModel->item(mIndex.row(), 3)->setText(user->GetSurname().c_str());
							itemModel->item(mIndex.row(), 4)->setText(user->GetPhone().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 2)->setText("");
							itemModel->item(mIndex.row(), 3)->setText("");
							itemModel->item(mIndex.row(), 4)->setText("");
						}
						itemModel->item(mIndex.row(), 5)->setText(QString::number(payment->GetValue(),'f',3));
						itemModel->item(mIndex.row(), 6)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(payment->GetTarget().c_str());
						if (accIDEdit->text().toInt() > 0)
						{
							itemModel->item(mIndex.row(), 8)->setText(account.GetNumber().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 8)->setText("");
						}
						if (saIDEdit->text().toInt() > 0)
						{
							itemModel->item(mIndex.row(), 9)->setText(subacc.GetNumber().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 9)->setText("");
						}
						itemModel->item(mIndex.row(), 10)->setText(payment->GetWho().c_str());
						itemModel->item(mIndex.row(), 11)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 12)->setText(QString::number(payment->GetUserID()));
						itemModel->item(mIndex.row(), 13)->setText(QString::number(payment->GetCurrencyID()));
						itemModel->item(mIndex.row(), 14)->setText(QString::number(payment->GetStatusID()));
						itemModel->item(mIndex.row(), 15)->setText(QString::number(payment->GetAccountID()));
						itemModel->item(mIndex.row(), 16)->setText(QString::number(payment->GetSubaccountID()));
						itemModel->item(mIndex.row(), 17)->setText(QString::number(payment->GetCashboxAccountID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete currency;
						delete user;
						delete status;
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
			QString(tr("Please fill user, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreatePmtDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePmtDlg::OpenUserDlg()
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

void CreatePmtDlg::OpenStatusDlg()
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

void CreatePmtDlg::OpenAccDlg()
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
		account.SetID(entryRouting.GetCreditAccountID());
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

void CreatePmtDlg::OpenSAccDlg()
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
		sabaccount.SetParentAccountID(entryRouting.GetCreditAccountID());
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


void CreatePmtDlg::InitComboBox()
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
		entryRouting.SetDebitAccountID(account.GetID());
		std::string filter = entryRouting.GenerateFilter(dialogBL->GetOrmasDal());
		std::vector<BusinessLayer::EntryRouting> entRoutVec = dialogBL->GetAllDataForClass<BusinessLayer::EntryRouting>(errorMessage, filter);
		accountCmb->addItem(tr("All"), 0);
		if (!entRoutVec.empty())
		{
			for (unsigned int i = 0; i < entRoutVec.size(); i++)
			{
				account.Clear();
				if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entRoutVec[i].GetCreditAccountID(), errorMessage))
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

int CreatePmtDlg::GetAccountIDFromCmb()
{
	BusinessLayer::Account account;
	BusinessLayer::EntryRouting entryRouting;
	if (entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
	{
		return entryRouting.GetCreditAccountID();
	}
	else
	{
		return 0;
	}
}

void CreatePmtDlg::SATextChanged()
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

void CreatePmtDlg::UserIsChanged()
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

void CreatePmtDlg::AccTextChanged()
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

void CreatePmtDlg::TextEditChanged()
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

void CreatePmtDlg::AccountIsChenged()
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

void CreatePmtDlg::SortTable(QTableView *table)
{
	BusinessLayer::EntryRouting entryRouting;
	if (!entryRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountCmb->currentData().toInt(), errorMessage))
		return;
	for (int i = 0; i < table->model()->rowCount(); i++)
	{
		QModelIndex index = table->model()->index(i, 11);
		if (index.data().toInt() == entryRouting.GetCreditAccountID())
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

bool CreatePmtDlg::CheckAccess()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return false;
	BusinessLayer::Status *status = new BusinessLayer::Status;
	if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payment->GetStatusID(), errorMessage))
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

int CreatePmtDlg::GetCashboxAccountID()
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

bool CreatePmtDlg::CrateCashboxTransaction(int paymentID)
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
			if (cTransaction.CreateCashboxTransaction(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox.GetID(), dialogBL->loggedUser->GetID(), accountant.GetID(), owner.GetID(), paymentID, 0, errorMessage))
				return true;
		}
	}
	return false;
}