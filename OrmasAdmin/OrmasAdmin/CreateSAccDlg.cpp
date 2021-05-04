#include "stdafx.h"
#include "CreateSAccDlg.h"
#include "DataForm.h"


CreateSAccDlg::CreateSAccDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(-1000000000.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	numberEdit->setMaxLength(20);
	statusEdit->setValidator(vInt);
	startBalanceEdit->setValidator(vDouble);
	currentBalanceEdit->setValidator(vDouble);
	startBalanceEdit->setMaxLength(17);
	currentBalanceEdit->setMaxLength(17);
	openedDateEdit->setDate(QDate::currentDate());
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSAccDlg::EditSubaccount);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSAccDlg::CreateSubaccount);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateSAccDlg::Close);
	QObject::connect(chartOfAccBtn, &QPushButton::released, this, &CreateSAccDlg::OpenCOADlg);
	QObject::connect(statusBtn, &QPushButton::released, this, &CreateSAccDlg::OpenStsDlg);
	QObject::connect(startBalanceEdit, &QLineEdit::textChanged, this, &CreateSAccDlg::TextEditChanged);
	QObject::connect(currentBalanceEdit, &QLineEdit::textChanged, this, &CreateSAccDlg::TextEditChanged);
	QObject::connect(chartOfAccEdit, &QLineEdit::textChanged, this, &CreateSAccDlg::GenerateNumber);
	QObject::connect(currencyCmb, &QComboBox::currentTextChanged, this, &CreateSAccDlg::GenerateNumber);
	InitComboBox();
}

CreateSAccDlg::~CreateSAccDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateSAccDlg::SetID(int ID, QString childName)
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

			if (childName == QString("chartOfAccountForm"))
			{
				chartOfAccEdit->setText(QString::number(ID));
				BusinessLayer::ChartOfAccounts coSAcc;
				if (coSAcc.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accNamePh->setText(coSAcc.GetName().c_str());
				}
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

void CreateSAccDlg::SetSubaccountParams(QString aNumber, double aStartBalance, double aCurrentBalance, int cID, int sID,
	QString aOpenedDate, QString aClosedDate, QString aDetails, int id)
{
	subaccount->SetNumber(aNumber.toUtf8().constData());
	subaccount->SetStartBalance(aStartBalance);
	subaccount->SetCurrentBalance(aCurrentBalance);
	subaccount->SetCurrencyID(cID);
	subaccount->SetStatusID(sID);
	subaccount->SetOpenedDate(aOpenedDate.toUtf8().constData());
	subaccount->SetClosedDate(aClosedDate.toUtf8().constData());
	subaccount->SetDetails(aDetails.toUtf8().constData());
	subaccount->SetID(id);
}

void CreateSAccDlg::FillEditElements(QString aNumber, double aStartBalance, double aCurrentBalance, int cID, int sID,
	QString aOpenedDate, QString aClosedDate, QString aDetails)
{
	numberEdit->setText(aNumber);
	startBalanceEdit->setText(QString::number(aStartBalance));
	currentBalanceEdit->setText(QString::number(aCurrentBalance));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(cID)));
	statusEdit->setText(QString::number(sID));
	openedDateEdit->setDate(QDate::fromString(aOpenedDate, "dd.MM.yyyy"));
	detailsEdit->setText(aDetails);
	BusinessLayer::ChartOfAccounts aoSAcc;
	BusinessLayer::Status status;
	if (aoSAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), aNumber.left(5).toUtf8().constData(), errorMessage))
	{
		chartOfAccEdit->setText(QString::number(aoSAcc.GetID()));
		accNamePh->setText(aoSAcc.GetName().c_str());
	}
	if (status.GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sID, errorMessage))
	{
		statusPh->setText(status.GetName().c_str());
	}
}

bool CreateSAccDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetSubaccountParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 8)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 9)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 10)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 12)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateSAccDlg::CreateSubaccount()
{
	errorMessage.clear();
	if (!numberEdit->text().isEmpty() && !currencyCmb->currentText().isEmpty() &&
		!openedDateEdit->text().isEmpty() && 0 != statusEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;

		SetSubaccountParams(numberEdit->text(), startBalanceEdit->text().toDouble(), currentBalanceEdit->text().toDouble(), 
			currencyCmb->currentData().toInt(), statusEdit->text().toInt(), 
			openedDateEdit->text(), "", detailsEdit->text());
		subaccount->SetParentAccountID(parentAccID);
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateSubaccount(subaccount, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::ChartOfAccounts *coSAcc = new BusinessLayer::ChartOfAccounts;
					if (!coSAcc->GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccEdit->text().toInt(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete coSAcc;
						return;
					}

					BusinessLayer::Status *status = new BusinessLayer::Status;
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					BusinessLayer::Account *account = new BusinessLayer::Account;
					if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount->GetStatusID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount->GetCurrencyID(), errorMessage)
						|| !account->GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), coSAcc->GetNumber(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete currency;
						delete status;
						delete account;
						delete coSAcc;
						return;
					}
					QList<QStandardItem*> SAccountItem;
					SAccountItem << new QStandardItem(QString::number(subaccount->GetID()))
						<< new QStandardItem(QString::number(account->GetID()))
						<< new QStandardItem(account->GetNumber().c_str())
						<< new QStandardItem(subaccount->GetNumber().c_str())
						<< new QStandardItem(QString::number(subaccount->GetStartBalance()))
						<< new QStandardItem(QString::number(subaccount->GetCurrentBalance()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(status->GetName().c_str())
						<< new QStandardItem(QString::number(subaccount->GetCurrencyID()))
						<< new QStandardItem(QString::number(subaccount->GetStatusID()))
						<< new QStandardItem(subaccount->GetOpenedDate().c_str())
						<< new QStandardItem(subaccount->GetClosedDate().c_str())
						<< new QStandardItem(subaccount->GetDetails().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(SAccountItem);
					delete currency;
					delete status;
					delete account;
					delete coSAcc;
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateSAccDlg::EditSubaccount()
{
	errorMessage.clear();
	if (!numberEdit->text().isEmpty() && !currencyCmb->currentText().isEmpty() &&
		!openedDateEdit->text().isEmpty() && 0 != statusEdit->text().toInt())
	{
		if (QString(subaccount->GetNumber().c_str()) != numberEdit->text() || subaccount->GetStartBalance() != startBalanceEdit->text().toDouble()
			|| subaccount->GetCurrentBalance() != currentBalanceEdit->text().toDouble() || subaccount->GetCurrencyID() != currencyCmb->currentData().toInt()
			|| subaccount->GetStatusID() != statusEdit->text().toInt() || QString(subaccount->GetOpenedDate().c_str()) != openedDateEdit->text()
			|| QString(subaccount->GetDetails().c_str()) != detailsEdit->text())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetSubaccountParams(numberEdit->text(), startBalanceEdit->text().toDouble(), currentBalanceEdit->text().toDouble(),
				currencyCmb->currentData().toInt(), statusEdit->text().toInt(),
				openedDateEdit->text(), "", detailsEdit->text(), subaccount->GetID());
			int parAccID = GetParentAccNumber(numberEdit->text().toStdString());
			if (0 == parAccID)
				return;
			subaccount->SetParentAccountID(parAccID);
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateSubaccount(subaccount, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::ChartOfAccounts *coSAcc = new BusinessLayer::ChartOfAccounts;
						if (!coSAcc->GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccEdit->text().toInt(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete coSAcc;
							return;
						}

						BusinessLayer::Status *status = new BusinessLayer::Status;
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::Account *account = new BusinessLayer::Account;
						if (!status->GetStatusByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount->GetStatusID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount->GetCurrencyID(), errorMessage)
							|| !account->GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), coSAcc->GetNumber(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete currency;
							delete status;
							delete account;
							delete coSAcc;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(QString::number(account->GetID()));
						itemModel->item(mIndex.row(), 2)->setText(account->GetNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(subaccount->GetNumber().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(subaccount->GetStartBalance()));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(subaccount->GetCurrentBalance()));
						itemModel->item(mIndex.row(), 6)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 7)->setText(status->GetName().c_str());
						itemModel->item(mIndex.row(), 8)->setText(QString::number(subaccount->GetCurrencyID()));
						itemModel->item(mIndex.row(), 9)->setText(QString::number(subaccount->GetStatusID()));
						itemModel->item(mIndex.row(), 10)->setText(subaccount->GetOpenedDate().c_str());
						itemModel->item(mIndex.row(), 11)->setText(subaccount->GetClosedDate().c_str());
						itemModel->item(mIndex.row(), 12)->setText(subaccount->GetDetails().c_str());
						emit itemModel->dataChanged(mIndex, mIndex);
						delete currency;
						delete status;
						delete account;
						delete coSAcc;
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateSAccDlg::Close()
{
	this->parentWidget()->close();
}

void CreateSAccDlg::OpenStsDlg()
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
		QString message = tr("All status are shown");
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

void CreateSAccDlg::OpenCOADlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Chart of Accounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ChartOfAccountsView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("chartOfAccountForm");
		dForm->QtConnect<BusinessLayer::ChartOfAccountsView>();
		QMdiSubWindow *coSAccWindow = new QMdiSubWindow;
		coSAccWindow->setWidget(dForm);
		coSAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(coSAccWindow);
		coSAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("Chart of Accounts are shown");
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

void CreateSAccDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreateSAccDlg::TextEditChanged()
{
	if (startBalanceEdit->text().contains(","))
	{
		startBalanceEdit->setText(startBalanceEdit->text().replace(",", "."));
	}
	if (startBalanceEdit->text().contains(".."))
	{
		startBalanceEdit->setText(startBalanceEdit->text().replace("..", "."));
	}
	if (currentBalanceEdit->text().contains(","))
	{
		currentBalanceEdit->setText(currentBalanceEdit->text().replace(",", "."));
	}
	if (currentBalanceEdit->text().contains(".."))
	{
		currentBalanceEdit->setText(currentBalanceEdit->text().replace("..", "."));
	}
}

void CreateSAccDlg::GenerateNumber()
{
	BusinessLayer::ChartOfAccounts coAcc;
	BusinessLayer::Account account;
	BusinessLayer::Currency currency;
	if (chartOfAccEdit->text().toInt() == 0 || chartOfAccEdit->text().isEmpty())
		return;
	if (!coAcc.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccEdit->text().toInt(), errorMessage))
		return;
	std::string number = coAcc.GetNumber();

	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), coAcc.GetNumber(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currencyCmb->currentData().toInt(), errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return;
	}
	number.append(std::to_string(currency.GetCode()));
	std::string genAccRawNumber = subaccount->GenerateRawNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (genAccRawNumber.empty())
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot generate account number! Please contact with Administrator!")),
			QString(tr("Ok")));
		Close();
	}
	number.append(genAccRawNumber);
	parentAccID = account.GetID();
	numberEdit->setText(number.c_str());
}

int CreateSAccDlg::GetParentAccNumber(std::string subNumber)
{
	std::string parentNumber = subNumber.substr(0, 5);
	BusinessLayer::Account account;
	if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), parentNumber, errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage.clear();
		return 0;
	}
	return account.GetID();
}


