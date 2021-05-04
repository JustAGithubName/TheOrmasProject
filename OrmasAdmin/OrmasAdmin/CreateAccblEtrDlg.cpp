#include "stdafx.h"
#include "CreateAccblEtrDlg.h"
#include "DataForm.h"



CreateAccblEtrDlg::CreateAccblEtrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	CreateAccblRepDlg *dataFormParent = (CreateAccblRepDlg *)this->parentForm;
	DataForm* dataForm = (DataForm *)dataFormParent->GetParentForm();
	mainForm = (MainForm *)dataForm->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	daIDEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	caIDEdit->setValidator(vInt);
	valueEdit->setMaxLength(17);
	daSubIDEdit->setValidator(vInt);
	caSubIDEdit->setValidator(vInt);
	deleteBtn->hide();
	daNumberEdit->setDisabled(true);
	caNumberEdit->setDisabled(true);

	int accountable = dataFormParent->employeeEdit->text().toInt();
	
	BusinessLayer::Subaccount subaccount;
	BusinessLayer::Subaccount sub;
	BusinessLayer::Account acc;
	BusinessLayer::Balance balance;
	BusinessLayer::User user;
	
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), accountable, errorMessage))
	{
		if (acc.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
		{
			balance.SetUserID(user.GetID());
			std::string filterBal = balance.GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::BalanceView> balVector = dialogBL->GetAllDataForClass<BusinessLayer::BalanceView>(errorMessage, filterBal);
			if (!balVector.empty())
			{
				for each (auto bal in balVector)
				{
					sub.Clear();
					if (sub.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), bal.GetSubaccountID(), errorMessage))
					{
						if (sub.GetParentAccountID() == acc.GetID())
							subaccount = sub;
					}
				}
			}
		}
		if (!subaccount.IsEmpty())
		{
			caIDEdit->setText(QString::number(subaccount.GetParentAccountID()));
			caSubIDEdit->setText(QString::number(subaccount.GetID()));
			caNumberEdit->setText(subaccount.GetNumber().c_str());
			caIDEdit->hide();
			caSubIDEdit->hide();
			caNumberEdit->hide();
			cAccBtn->hide();
			cSubAccBtn->hide();
			orLb_2->hide();
			caLb->hide();
			caNamePh->hide();
			caNameLb->hide();
		}
	}
	
	QObject::connect(addBtn, &QPushButton::released, this, &CreateAccblEtrDlg::CreateEntry);
	QObject::connect(deleteBtn, &QPushButton::released, this, &CreateAccblEtrDlg::DeleteEntry);
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAccblEtrDlg::Close);
	QObject::connect(dAccBtn, &QPushButton::released, this, &CreateAccblEtrDlg::OpenDAccDlg);
	QObject::connect(cAccBtn, &QPushButton::released, this, &CreateAccblEtrDlg::OpenCAccDlg);
	QObject::connect(dSubAccBtn, &QPushButton::released, this, &CreateAccblEtrDlg::OpenDSAccDlg);
	QObject::connect(cSubAccBtn, &QPushButton::released, this, &CreateAccblEtrDlg::OpenCSAccDlg);
	QObject::connect(daNumberEdit, &QLineEdit::textChanged, this, &CreateAccblEtrDlg::DATextChanged);
	QObject::connect(caNumberEdit, &QLineEdit::textChanged, this, &CreateAccblEtrDlg::CATextChanged);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateAccblEtrDlg::TextEditChanged);
	QObject::connect(routingCmb, &QComboBox::currentTextChanged, this, &CreateAccblEtrDlg::AccountIsChenged);
	QObject::connect(this, SIGNAL(IncrementEntryEditChanged(double)), dataFormParent, SLOT(IncrementEntrySum(double)));
	QObject::connect(this, SIGNAL(DecrementEntryEditChanged(double)), dataFormParent, SLOT(DecrementEntrySum(double)));
	InitComboBox();
}

CreateAccblEtrDlg::~CreateAccblEtrDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateAccblEtrDlg::SetID(int ID, QString childName)
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

			if (childName == QString("debitingAccountForm"))
			{
				daIDEdit->setText(QString::number(ID));
				daSubIDEdit->setText(QString::number(0));
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					daNumberEdit->setReadOnly(true);
					daNumberEdit->setText(account.GetNumber().c_str());
				}
			}
			if (childName == QString("creditingAccountForm"))
			{
				caIDEdit->setText(QString::number(ID));
				caSubIDEdit->setText(QString::number(0));
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					caNumberEdit->setReadOnly(true);
					caNumberEdit->setText(account.GetNumber().c_str());
				}
			}
			if (childName == QString("debitingSubaccountForm"))
			{
				daSubIDEdit->setText(QString::number(ID));
				daIDEdit->setText(QString::number(0));
				BusinessLayer::Subaccount subaccount;
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					daNumberEdit->setReadOnly(true);
					daNumberEdit->setText(subaccount.GetNumber().c_str());
				}
			}
			if (childName == QString("creditingSubaccountForm"))
			{
				caSubIDEdit->setText(QString::number(ID));
				daIDEdit->setText(QString::number(0));
				BusinessLayer::Subaccount subaccount;
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					caNumberEdit->setReadOnly(true);
					caNumberEdit->setText(subaccount.GetNumber().c_str());
				}
			}
		}
	}
}

void CreateAccblEtrDlg::SetEntryParams(int daID, int dasubID, double eValue, int caID, int casubID, int aDocID, int id)
{
	entry->SetDebitAccountID(daID);
	entry->SetDebitSubaccountID(dasubID);
	entry->SetValue(eValue);
	entry->SetCreditAccountID(caID);
	entry->SetCreditSubaccountID(casubID);
	entry->SetAccountableDocumentID(aDocID);
	entry->SetID(id);
}

void CreateAccblEtrDlg::FillEditElements(int daID, int dasubID, double eValue, int caID, int casubID, int aDocID)
{
	
	daIDEdit->setText(QString::number(daID));
	daSubIDEdit->setText(QString::number(dasubID));
	valueEdit->setText(QString::number(eValue));
	caIDEdit->setText(QString::number(caID));
	caSubIDEdit->setText(QString::number(casubID));
	BusinessLayer::Account account1;
	if (account1.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), daID, errorMessage))
	{
		daNumberEdit->setReadOnly(true);
		daNumberEdit->setText(account1.GetNumber().c_str());
	}
	BusinessLayer::Account account2;
	if (account2.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), caID, errorMessage))
	{
		caNumberEdit->setReadOnly(true);
		caNumberEdit->setText(account2.GetNumber().c_str());
	}
	BusinessLayer::Subaccount subaccount1;
	if (subaccount1.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dasubID, errorMessage))
	{
		daNumberEdit->setReadOnly(true);
		daNumberEdit->setText(subaccount1.GetNumber().c_str());
	}
	BusinessLayer::Subaccount subaccount2;
	if (subaccount2.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), casubID, errorMessage))
	{
		caNumberEdit->setReadOnly(true);
		caNumberEdit->setText(subaccount2.GetNumber().c_str());
	}
}

bool CreateAccblEtrDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetEntryParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAccblEtrDlg::CreateEntry()
{
	errorMessage.clear();
	if (0 != daIDEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && 0 != caIDEdit->text().toInt())
	{
		CreateAccblRepDlg *parentDataForm = (CreateAccblRepDlg*)parentForm;
		SetEntryParams(daIDEdit->text().toInt(), daSubIDEdit->text().toInt(), valueEdit->text().toDouble(), caIDEdit->text().toInt(), caSubIDEdit->text().toInt(),0);
		if (parentDataForm != nullptr)
		{
			QList<QStandardItem*> entryItem;
				entryItem << new QStandardItem(QString::number(entry->GetID()))
					<< new QStandardItem(QString::number(entry->GetDebitAccountID()))
					<< new QStandardItem(QString::number(entry->GetDebitSubaccountID()))
					<< new QStandardItem(QString::number(entry->GetValue(), 'f', 3))
					<< new QStandardItem(QString::number(entry->GetCreditAccountID()))
					<< new QStandardItem(QString::number(entry->GetCreditSubaccountID()))
					<< new QStandardItem(QString::number(entry->GetAccountableDocumentID()));
				
				QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->entryTableView->model();
				itemModel->appendRow(entryItem);

				emit IncrementEntryEditChanged(entry->GetValue());
			Close();
		}
		else
		{
			
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

void CreateAccblEtrDlg::DeleteEntry()
{
	int result = QMessageBox::question(this, QString(tr("Affirm")),
		QString(tr("Do you really want to delete these data? (WARNING! All data will be irretrievable lost)")),
		QString(tr("Yes")), QString(tr("No")));
	if (result == 1)
		return;
	std::string errorMessage = "";
	
	((CreateAccblRepDlg *)this->parent())->entryTableView->model()->removeRow(((CreateAccblRepDlg *)this->parent())->entryTableView->selectionModel()->currentIndex().row());
	
}

void CreateAccblEtrDlg::Close()
{
	this->parentWidget()->close();
}

void CreateAccblEtrDlg::OpenDAccDlg()
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
	dForm->FillTable<BusinessLayer::Account>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("debitingAccountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *dAccountWindow = new QMdiSubWindow;
		dAccountWindow->setWidget(dForm);
		dAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(dAccountWindow);
		dAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
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

void CreateAccblEtrDlg::OpenCAccDlg()
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
	dForm->FillTable<BusinessLayer::Account>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("creditingAccountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *cAccountWindow = new QMdiSubWindow;
		cAccountWindow->setWidget(dForm);
		cAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(cAccountWindow);
		cAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
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

void CreateAccblEtrDlg::OpenDSAccDlg()
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
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("debitingSubaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *dSAccountWindow = new QMdiSubWindow;
		dSAccountWindow->setWidget(dForm);
		dSAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(dSAccountWindow);
		dSAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
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

void CreateAccblEtrDlg::OpenCSAccDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Subaccounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("creditingSubaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *cSAccountWindow = new QMdiSubWindow;
		cSAccountWindow->setWidget(dForm);
		cSAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(cSAccountWindow);
		cSAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
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

void CreateAccblEtrDlg::DATextChanged()
{
	if (daNumberEdit->text().length() == 5 || daNumberEdit->text().length() == 6)
	{
		BusinessLayer::Account account;
		if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), daNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			daIDEdit->setText(QString::number(account.GetID()));
			if (account.GetName(dialogBL->GetOrmasDal()).c_str() != nullptr)
				daNamePh->setText(account.GetName(dialogBL->GetOrmasDal()).c_str());
		}
		else
		{
			daNamePh->setText(tr("Incorrect account number!"));
			daIDEdit->setText("");
		}
	}
	else if (daNumberEdit->text().length() == 15)
	{
		BusinessLayer::Subaccount subaccount;
		if (subaccount.GetSubaccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), daNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			daIDEdit->setText(QString::number(subaccount.GetID()));
			if (subaccount.GetName(dialogBL->GetOrmasDal()).c_str() != nullptr)
				daNamePh->setText(subaccount.GetName(dialogBL->GetOrmasDal()).c_str());
		}
		else
		{
			daNamePh->setText(tr("Incorrect account number!"));
			daIDEdit->setText("");
		}
	}
	else
	{
		daNamePh->setText("");
		daIDEdit->setText("");
	}
}

void CreateAccblEtrDlg::CATextChanged()
{
	if (caNumberEdit->text().length() == 5 || caNumberEdit->text().length() == 6)
	{
		BusinessLayer::Account account;
		if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), caNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			caIDEdit->setText(QString::number(account.GetID()));
			if (account.GetName(dialogBL->GetOrmasDal()).c_str() != nullptr)
				caNamePh->setText(account.GetName(dialogBL->GetOrmasDal()).c_str());
		}
		else
		{
			caNamePh->setText(tr("Incorrect account number!"));
			caIDEdit->setText("");
		}
	}
	else if (caNumberEdit->text().length() == 15)
	{
		BusinessLayer::Subaccount subaccount;
		if (subaccount.GetSubaccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), caNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			caIDEdit->setText(QString::number(subaccount.GetID()));
			if (subaccount.GetName(dialogBL->GetOrmasDal()).c_str() != nullptr)
				caNamePh->setText(subaccount.GetName(dialogBL->GetOrmasDal()).c_str());
		}
		else
		{
			caNamePh->setText(tr("Incorrect account number!"));
			caIDEdit->setText("");
		}
	}
	else
	{
		caNamePh->setText("");
		caIDEdit->setText("");
	}
}

void CreateAccblEtrDlg::TextEditChanged()
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

void CreateAccblEtrDlg::InitComboBox()
{
	BusinessLayer::Account account;
	BusinessLayer::Account account10110;
	BusinessLayer::EntryRouting entryRouting;
	if (!account10110.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10110", errorMessage))
	{
		return;
	}
	if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), "10520", errorMessage))
	{
		std::string comboText = "";
		entryRouting.SetCreditAccountID(account.GetID());
		std::string filter = entryRouting.GenerateFilter(dialogBL->GetOrmasDal());
		std::vector<BusinessLayer::EntryRouting> entRoutVec = dialogBL->GetAllDataForClass<BusinessLayer::EntryRouting>(errorMessage, filter);
		routingCmb->addItem(tr(""), 0);
		if (!entRoutVec.empty())
		{
			for (unsigned int i = 0; i < entRoutVec.size(); i++)
			{
				
				account.Clear();
				if (!account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entRoutVec[i].GetDebitAccountID(), errorMessage))
					continue;
				if (entRoutVec[i].GetDebitAccountID() != account10110.GetID())
				{
					comboText = "";
					comboText += account.GetNumber();
					comboText += " - ";
					comboText += entRoutVec[i].GetOperation();
					routingCmb->addItem(comboText.c_str(), QVariant(entRoutVec[i].GetID()));
				}
			}
		}
		else
		{
			errorMessage = "";
		}
	}
}

void CreateAccblEtrDlg::AccountIsChenged()
{
	if (routingCmb->currentData().toInt() == 0)
	{
		daIDEdit->setText("");
		daNumberEdit->setText("");
		daNamePh->setText("");
		dAccBtn->setDisabled(false);
		dSubAccBtn->setDisabled(false);
	}
	else
	{
		BusinessLayer::EntryRouting entRouting;
		BusinessLayer::ChartOfAccounts cao;
		BusinessLayer::Account acc;
		if (entRouting.GetEntryRoutingByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), routingCmb->currentData().toInt(), errorMessage))
		{
			if (acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entRouting.GetDebitAccountID(), errorMessage))
			{
				daIDEdit->setText(QString::number(acc.GetID()));
				daNumberEdit->setText(acc.GetNumber().c_str());
				if (cao.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), acc.GetNumber(), errorMessage))
				{
					daNamePh->setText(cao.GetName().c_str());
					dAccBtn->setDisabled(true);
					dSubAccBtn->setDisabled(true);
				}
			}
		}
	}
}