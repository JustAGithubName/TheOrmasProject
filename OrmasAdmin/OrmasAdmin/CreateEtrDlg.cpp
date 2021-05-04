#include "stdafx.h"
#include "CreateEtrDlg.h"
#include "DataForm.h"



CreateEtrDlg::CreateEtrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	daIDEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	caIDEdit->setValidator(vInt);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateEtrDlg::EditEntry);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateEtrDlg::CreateEntry);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateEtrDlg::Close);
	QObject::connect(dAccBtn, &QPushButton::released, this, &CreateEtrDlg::OpenDAccDlg);
	QObject::connect(cAccBtn, &QPushButton::released, this, &CreateEtrDlg::OpenCAccDlg);
	QObject::connect(dSubAccBtn, &QPushButton::released, this, &CreateEtrDlg::OpenDSAccDlg);
	QObject::connect(cSubAccBtn, &QPushButton::released, this, &CreateEtrDlg::OpenCSAccDlg);
	QObject::connect(daNumberEdit, &QLineEdit::textChanged, this, &CreateEtrDlg::DATextChanged);
	QObject::connect(caNumberEdit, &QLineEdit::textChanged, this, &CreateEtrDlg::CATextChanged);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateEtrDlg::TextEditChanged);
	QObject::connect(descriptionTextEdit, &QTextEdit::textChanged, this, &CreateEtrDlg::TextEditChanged);
}

CreateEtrDlg::~CreateEtrDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateEtrDlg::SetID(int ID, QString childName)
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
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					caNumberEdit->setReadOnly(true);
					caNumberEdit->setText(account.GetNumber().c_str());
				}
			}
			if (childName == QString("debitingSubaccountForm"))
			{
				daIDEdit->setText(QString::number(ID));
				BusinessLayer::Subaccount subaccount;
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					daNumberEdit->setReadOnly(true);
					daNumberEdit->setText(subaccount.GetNumber().c_str());
				}
			}
			if (childName == QString("creditingSubaccountForm"))
			{
				caIDEdit->setText(QString::number(ID));
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

void CreateEtrDlg::SetEntryParams(QString eDate, int daID, double eValue, int caID, QString eDescription, int id)
{
	entry->SetDate(eDate.toUtf8().constData());
	entry->SetDebitingAccountID(daID);
	entry->SetValue(eValue);
	entry->SetCreditingAccountID(caID);
	entry->SetDescription(eDescription.toUtf8().constData());
	entry->SetID(id);
}

void CreateEtrDlg::FillEditElements(QString eDate, int daID, double eValue, int caID, QString eDescription)
{
	dateEdit->setDate(QDate::fromString(eDate, "dd.MM.yyyy"));
	daIDEdit->setText(QString::number(daID));
	valueEdit->setText(QString::number(eValue));
	caIDEdit->setText(QString::number(caID));
	descriptionTextEdit->setText(eDescription);
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
	if (subaccount1.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), daID, errorMessage))
	{
		daNumberEdit->setReadOnly(true);
		daNumberEdit->setText(subaccount1.GetNumber().c_str());
	}
	BusinessLayer::Subaccount subaccount2;
	if (subaccount2.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), caID, errorMessage))
	{
		caNumberEdit->setReadOnly(true);
		caNumberEdit->setText(subaccount2.GetNumber().c_str());
	}
}

bool CreateEtrDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetEntryParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 7)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateEtrDlg::CreateEntry()
{
	errorMessage.clear();
	if (0 != daIDEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && 0 != caIDEdit->text().toInt()
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetEntryParams(dateEdit->text(), daIDEdit->text().toInt(), valueEdit->text().toDouble(), caIDEdit->text().toInt(), descriptionTextEdit->toPlainText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateEntry(entry, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Account *dAccount = new BusinessLayer::Account;
					BusinessLayer::Subaccount *dSAccount = new BusinessLayer::Subaccount;
					if (!dAccount->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetDebitingAccountID(), errorMessage)
						&& !dSAccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetDebitingAccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete dAccount;
						delete dSAccount;
						return;
					}
					BusinessLayer::Account *cAccount = new BusinessLayer::Account;
					BusinessLayer::Subaccount *cSAccount = new BusinessLayer::Subaccount;
					if (!cAccount->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetCreditingAccountID(), errorMessage)
						&& !cSAccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetCreditingAccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete dAccount;
						delete dSAccount;
						delete cAccount;
						delete cSAccount;
						return;
					}

					QList<QStandardItem*> entryItem;
					entryItem << new QStandardItem(QString::number(entry->GetID()))
						<< new QStandardItem(entry->GetDate().c_str());
					if (!dAccount->GetNumber().empty())
					{
						entryItem << new QStandardItem(dAccount->GetNumber().c_str());
					}
					else if (!dSAccount->GetNumber().empty())
					{
						entryItem << new QStandardItem(dSAccount->GetSubaccountParentNumber(dialogBL->GetOrmasDal()).c_str());
					}
					entryItem << new QStandardItem(QString::number(entry->GetValue(), 'f', 3));
					if (!cAccount->GetNumber().empty())
					{
						entryItem << new QStandardItem(cAccount->GetNumber().c_str());
					}
					else if (!cSAccount->GetNumber().empty())
					{
						entryItem << new QStandardItem(cSAccount->GetSubaccountParentNumber(dialogBL->GetOrmasDal()).c_str());
					}
					entryItem << new QStandardItem(QString::number(entry->GetDebitingAccountID()))
						<< new QStandardItem(QString::number(entry->GetCreditingAccountID()))
						<< new QStandardItem(entry->GetDescription().c_str());
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(entryItem);

					delete dAccount;
					delete dSAccount;
					delete cAccount;
					delete cSAccount;
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

void CreateEtrDlg::EditEntry()
{
	errorMessage.clear();
	if (0 != daIDEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && 0 != caIDEdit->text().toInt()
		&& !dateEdit->text().isEmpty())
	{
		if (QString(entry->GetDate().c_str()) != dateEdit->text() || entry->GetCreditingAccountID() != caIDEdit->text().toInt()
			|| entry->GetValue() != valueEdit->text().toDouble() || entry->GetDebitingAccountID() != daIDEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetEntryParams(dateEdit->text(), daIDEdit->text().toInt(), valueEdit->text().toDouble(), caIDEdit->text().toInt(), descriptionTextEdit->toPlainText(), entry->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateEntry(entry, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Account *dAccount = new BusinessLayer::Account;
						BusinessLayer::Subaccount *dSAccount = new BusinessLayer::Subaccount;
						if (!dAccount->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetDebitingAccountID(), errorMessage)
							&& !dSAccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetDebitingAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete dAccount;
							delete dSAccount;
							return;
						}
						BusinessLayer::Account *cAccount = new BusinessLayer::Account;
						BusinessLayer::Subaccount *cSAccount = new BusinessLayer::Subaccount;
						if (!cAccount->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetCreditingAccountID(), errorMessage)
							&& !cSAccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), entry->GetCreditingAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete dAccount;
							delete dSAccount;
							delete cAccount;
							delete cSAccount;
							return;
						}

						
						itemModel->item(mIndex.row(), 1)->setText(entry->GetDate().c_str());
						if (!dAccount->GetNumber().empty())
						{
							itemModel->item(mIndex.row(), 2)->setText(dAccount->GetNumber().c_str());
						}
						else if (!dSAccount->GetNumber().empty())
						{
							itemModel->item(mIndex.row(), 2)->setText(dSAccount->GetSubaccountParentNumber(dialogBL->GetOrmasDal()).c_str());
						}
						itemModel->item(mIndex.row(), 3)->setText(QString::number(entry->GetValue()));
						if (!cAccount->GetNumber().empty())
						{
							itemModel->item(mIndex.row(), 4)->setText(cAccount->GetNumber().c_str());
						}
						else if (!cSAccount->GetNumber().empty())
						{
							itemModel->item(mIndex.row(), 4)->setText(cSAccount->GetSubaccountParentNumber(dialogBL->GetOrmasDal()).c_str());
						}
						itemModel->item(mIndex.row(), 5)->setText(QString::number(entry->GetDebitingAccountID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(entry->GetCreditingAccountID()));
						itemModel->item(mIndex.row(), 7)->setText(entry->GetDescription().c_str());
						emit itemModel->dataChanged(mIndex, mIndex);
						delete dAccount;
						delete dSAccount;
						delete cAccount;
						delete cSAccount;
						
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

void CreateEtrDlg::Close()
{
	this->parentWidget()->close();
}

void CreateEtrDlg::OpenDAccDlg()
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

void CreateEtrDlg::OpenCAccDlg()
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

void CreateEtrDlg::OpenDSAccDlg()
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

void CreateEtrDlg::OpenCSAccDlg()
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

void CreateEtrDlg::DATextChanged()
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

void CreateEtrDlg::CATextChanged()
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

void CreateEtrDlg::TextEditChanged()
{
	if (valueEdit->text().contains(","))
	{
		valueEdit->setText(valueEdit->text().replace(",", "."));
	}
	if (valueEdit->text().contains(".."))
	{
		valueEdit->setText(valueEdit->text().replace("..", "."));
	}
	if (descriptionTextEdit->toPlainText().length()> 100) {
		descriptionTextEdit->setPlainText(descriptionTextEdit->toPlainText().left(descriptionTextEdit->toPlainText().length() - 1));
		descriptionTextEdit->moveCursor(QTextCursor::End);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Warning: no more then ")) + QString::number(100) + QString(tr(" characters in this field")),
			QString(tr("Ok")));
	}
}