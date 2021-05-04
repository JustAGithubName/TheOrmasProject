#include "stdafx.h"
#include "CreateCARDlg.h"
#include "DataForm.h"



CreateCARDlg::CreateCARDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	accountEdit->setValidator(vInt);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCARDlg::EditCompanyAccount);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCARDlg::CreateCompanyAccount);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCARDlg::Close);
	QObject::connect(accountBtn, &QPushButton::released, this, &CreateCARDlg::OpenAccDlg);
	InitComboBox();
}

CreateCARDlg::~CreateCARDlg()
{
	delete vInt;
}


void CreateCARDlg::SetID(int ID, QString childName)
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

			if (childName == QString("accountForm"))
			{
				accountEdit->setText(QString::number(ID));
			}
			BusinessLayer::Account account;
			if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
			{
				numberPh->setText(account.GetNumber().c_str());
			}
		}
	}
}


void CreateCARDlg::SetCompanyAccountParams(int caCompanyID, int caAccountID, int id)
{
	companyAccount->SetCompanyID(caCompanyID);
	companyAccount->SetAccountID(caAccountID);
	companyAccount->SetID(id);
}

void CreateCARDlg::FillEditElements(int caCompanyID, int caAccountID)
{
	accountEdit->setText(QString::number(caAccountID));
	companyCmb->setCurrentIndex(companyCmb->findData(QVariant(caAccountID)));
	BusinessLayer::Account account;
	if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), caAccountID, errorMessage))
	{
		numberPh->setText(account.GetNumber().c_str());
	}
}

bool CreateCARDlg::FillDlgElements(QTableView* aTable)
{
	QModelIndex mIndex = aTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetCompanyAccountParams(aTable->model()->data(aTable->model()->index(mIndex.row(), 3)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 4)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(aTable->model()->data(aTable->model()->index(mIndex.row(), 3)).toInt(),
			aTable->model()->data(aTable->model()->index(mIndex.row(), 4)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCARDlg::CreateCompanyAccount()
{
	errorMessage.clear();
	if (!companyCmb->currentText().isEmpty() && 0 != accountEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetCompanyAccountParams(companyCmb->currentData().toInt(), accountEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateCompanyAccountRelation(companyAccount, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Company *company = new BusinessLayer::Company();
					BusinessLayer::Account *account = new BusinessLayer::Account();
					if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyAccount->GetCompanyID(), errorMessage)
						|| !account->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyAccount->GetAccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));

						errorMessage.clear();
						delete company;
						delete account;
						return;
					}
					QList<QStandardItem*> companyAccountItem;
					companyAccountItem << new QStandardItem(QString::number(companyAccount->GetID()))
						<< new QStandardItem(company->GetName().c_str())
						<< new QStandardItem(account->GetNumber().c_str())
						<< new QStandardItem(QString::number(companyAccount->GetCompanyID()))
						<< new QStandardItem(QString::number(companyAccount->GetAccountID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(companyAccountItem);
					
					delete company;
					delete account;
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
			QString(tr("Please fill company, account fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCARDlg::EditCompanyAccount()
{
	errorMessage.clear();
	if (!companyCmb->currentText().isEmpty() && 0 != accountEdit->text().toInt())
	{
		if (companyAccount->GetCompanyID() != companyCmb->currentData().toInt() || companyAccount->GetAccountID() != accountEdit->text().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetCompanyAccountParams(companyCmb->currentData().toInt(), accountEdit->text().toInt(), companyAccount->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateCompanyAccountRelation(companyAccount, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Company *company = new BusinessLayer::Company();
						BusinessLayer::Account *account = new BusinessLayer::Account();
						if (!company->GetCompanyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyAccount->GetCompanyID(), errorMessage)
							|| !account->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), companyAccount->GetAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));

							errorMessage.clear();
							delete company;
							delete account;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(company->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(account->GetNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(QString::number(companyAccount->GetCompanyID()));
						itemModel->item(mIndex.row(), 4)->setText(QString::number(companyAccount->GetAccountID()));
						emit itemModel->dataChanged(mIndex, mIndex);
				
						delete company;
						delete account;
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
			QString(tr("Please enter role and Company-account item!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateCARDlg::Close()
{
	this->parentWidget()->close();
}

void CreateCARDlg::OpenAccDlg()
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
		dForm->setObjectName("accountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *accountWindow = new QMdiSubWindow;
		accountWindow->setWidget(dForm);
		accountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accountWindow);
		accountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
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


void CreateCARDlg::InitComboBox()
{
	std::vector<BusinessLayer::Company> comVector = dialogBL->GetAllDataForClass<BusinessLayer::Company>(errorMessage);
	if (!comVector.empty())
	{
		for (unsigned int i = 0; i < comVector.size(); i++)
		{
			companyCmb->addItem(comVector[i].GetName().c_str(), QVariant(comVector[i].GetID()));
		}
	}
}