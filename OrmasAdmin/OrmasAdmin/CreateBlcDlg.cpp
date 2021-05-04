#include "stdafx.h"
#include "CreateBlcDlg.h"
#include "DataForm.h"



CreateBlcDlg::CreateBlcDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	userEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBlcDlg::EditBalance);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateBlcDlg::CreateBalance);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateBlcDlg::Close);
	QObject::connect(userBtn, &QPushButton::released, this, &CreateBlcDlg::OpenUserDlg);
}

CreateBlcDlg::~CreateBlcDlg()
{
	delete vInt;
}

void CreateBlcDlg::SetID(int ID, QString childName)
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
				}
			}
		}
	}
}

void CreateBlcDlg::SetBalanceParams(int bUserID, int bSubccountID, int id)
{
	balance->SetUserID(bUserID);
	balance->SetSubaccountID(bSubccountID);
	balance->SetID(id);
}

void CreateBlcDlg::FillEditElements(int bUserID, int bAccountID)
{
	userEdit->setText(QString::number(bUserID));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), bUserID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
}

bool CreateBlcDlg::FillDlgElements(QTableView* bTable)
{
	QModelIndex mIndex = bTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetBalanceParams(bTable->model()->data(bTable->model()->index(mIndex.row(), 5)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 6)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(bTable->model()->data(bTable->model()->index(mIndex.row(), 5)).toInt(),
			bTable->model()->data(bTable->model()->index(mIndex.row(), 6)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateBlcDlg::CreateBalance()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt())
	{
		dialogBL->StartIsolatedTransaction(errorMessage);
		int subaccountID = CreateSubaccount();
		if (0 == subaccountID)
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Cannot create account for this user. Please contact with Administrator!")),
				QString(tr("Ok")));
			errorMessage.clear();
			return;
		}
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetBalanceParams(userEdit->text().toInt(), subaccountID);
		
		if (dialogBL->CreateBalance(balance, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> balanceItem;
					BusinessLayer::User *user = new BusinessLayer::User();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					BusinessLayer::Subaccount *subaccount = new BusinessLayer::Subaccount;
					if (!user->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance->GetUserID(), errorMessage) ||
						subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance->GetSubaccountID(), errorMessage) ||
						currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete user;
						delete currency;
						delete subaccount;
						return;
					}

					balanceItem << new QStandardItem(QString::number(balance->GetID()));

					if (0 != balance->GetUserID())
					{
						balanceItem << new QStandardItem(user->GetName().c_str())
							<< new QStandardItem(user->GetSurname().c_str());
					}
					else
					{
						balanceItem << new QStandardItem("")
							<< new QStandardItem("");
					}

					balanceItem << new QStandardItem(subaccount->GetNumber().c_str())
						<< new QStandardItem(QString::number(subaccount->GetCurrentBalance()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(balance->GetUserID()))
						<< new QStandardItem(QString::number(balance->GetSubaccountID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(balanceItem);

					delete user;
					delete currency;
					delete subaccount;
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
			QString(tr("Please select user!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateBlcDlg::EditBalance()
{
	errorMessage.clear();
	if (0 != userEdit->text().toInt())
	{
		if (balance->GetUserID() != userEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetBalanceParams(userEdit->text().toInt(), balance->GetSubaccountID(), balance->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateBalance(balance, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::User *user = new BusinessLayer::User();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::Subaccount *subaccount = new BusinessLayer::Subaccount;
						if (!user->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance->GetUserID(), errorMessage) ||
							subaccount->GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance->GetSubaccountID(), errorMessage) ||
							currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), subaccount->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete user;
							delete currency;
							delete subaccount;
							return;
						}

						if (0 != balance->GetUserID())
						{
							itemModel->item(mIndex.row(), 1)->setText(user->GetName().c_str());
							itemModel->item(mIndex.row(), 2)->setText(user->GetSurname().c_str());
						}
						else
						{
							itemModel->item(mIndex.row(), 1)->setText("");
							itemModel->item(mIndex.row(), 2)->setText("");
						}

						itemModel->item(mIndex.row(), 3)->setText(subaccount->GetNumber().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(subaccount->GetCurrentBalance()));
						itemModel->item(mIndex.row(), 5)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 6)->setText(QString::number(balance->GetUserID()));
						itemModel->item(mIndex.row(), 7)->setText(QString::number(balance->GetSubaccountID()));
						emit itemModel->dataChanged(mIndex, mIndex);

						delete user;
						delete currency;
						delete subaccount;
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
			QString(tr("Please select user")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateBlcDlg::Close()
{
	this->parentWidget()->close();
}

void CreateBlcDlg::OpenUserDlg()
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
	dForm->FillTable<BusinessLayer::UserView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("userForm");
		dForm->QtConnect<BusinessLayer::UserView>();
		QMdiSubWindow *userWindow = new QMdiSubWindow;
		userWindow->setWidget(dForm);
		userWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(userWindow);
		userWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
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

int CreateBlcDlg::CreateSubaccount()
{
	BusinessLayer::Currency currency;
	std::string number = "";
	std::string genAccRawNumber = "";
	int currID = currency.GetMainTradeCurrencyID(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 != currID)
	{
		BusinessLayer::Status status;
		if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "OPEN", errorMessage))
			return 0;
		if (!currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), currID, errorMessage))
			return 0;
		BusinessLayer::Subaccount subaccount;
		BusinessLayer::Account account;
		if (!account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), std::to_string(10410), errorMessage))
		{
			return 0;
		}
		number = std::to_string(10410);
		number.append(std::to_string(currency.GetCode()));
		genAccRawNumber = subaccount.GenerateRawNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
		if (genAccRawNumber.empty())
			return 0;
		number.append(genAccRawNumber);
		subaccount.SetParentAccountID(account.GetID());
		subaccount.SetNumber(number);
		subaccount.SetStartBalance(0.0);
		subaccount.SetCurrentBalance(0.0);
		subaccount.SetCurrencyID(currID);
		subaccount.SetStatusID(status.GetID());
		subaccount.SetOpenedDate(dialogBL->GetOrmasDal().GetSystemDate());
		subaccount.SetClosedDate("");
		subaccount.SetDetails("Generated by system");

		if (!subaccount.CreateSubaccount(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage))
			return 0;
		return subaccount.GetID();
	}
	return 0;
}
