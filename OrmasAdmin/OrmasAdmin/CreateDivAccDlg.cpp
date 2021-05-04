#include "stdafx.h"

#include "CreateDivAccDlg.h"
#include "DataForm.h"

#include <map>

CreateDivAccDlg::CreateDivAccDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	//setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	codeEdit->setMaxLength(30);

	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateDivAccDlg::EditDivisionAccount);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateDivAccDlg::CreateDivisionAccount);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateDivAccDlg::Close);
	QObject::connect(accountBtn, &QPushButton::released, this, &CreateDivAccDlg::OpenAccDlg);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	InitComboBox();
}

CreateDivAccDlg::~CreateDivAccDlg()
{
	delete vInt;
	emit CloseCreatedForms();

}

void CreateDivAccDlg::SetDivisionAccountParams(int divID, int accID, QString dCode, int id)
{
	divisionAccount->SetDivisionID(divID);
	divisionAccount->SetAccountID(accID);
	divisionAccount->SetCode(dCode.toUtf8().constData());
	divisionAccount->SetID(id);
}

void CreateDivAccDlg::FillEditElements(int divID, int accID, QString dCode)
{
	divisionCmb->setCurrentIndex(divisionCmb->findData(QVariant(divID)));
	accountEdit->setText(QString::number(accID));
	codeEdit->setText(dCode);
}

void CreateDivAccDlg::SetID(int ID, QString childName)
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
		}
	}
}

bool CreateDivAccDlg::FillDlgElements(QTableView* cTable)
{
	QModelIndex mIndex = cTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetDivisionAccountParams(cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(cTable->model()->data(cTable->model()->index(mIndex.row(), 5)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 6)).toInt(),
			cTable->model()->data(cTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateDivAccDlg::CreateDivisionAccount()
{
	errorMessage.clear();
	if (!codeEdit->text().isEmpty()
		&& 0 != accountEdit->text().toInt() && !divisionCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		SetDivisionAccountParams(divisionCmb->currentData().toInt(), accountEdit->text().toInt(), codeEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateDivisionAccountRelation(divisionAccount, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Account *account = new BusinessLayer::Account;
					if (!account->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), divisionAccount->GetAccountID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete account;
						return;
					}
					BusinessLayer::ChartOfAccounts *coAcc = new BusinessLayer::ChartOfAccounts;
					if (!coAcc->GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), account->GetNumber(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete account;
						delete coAcc;
						return;
					}
					BusinessLayer::Division *division = new BusinessLayer::Division;
					if (!division->GetDivisionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), divisionAccount->GetDivisionID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete account;
						delete division;
						delete coAcc;
						return;
					}
					QList<QStandardItem*> DivisionAccountItem;
					DivisionAccountItem << new QStandardItem(QString::number(divisionAccount->GetID()))
						<< new QStandardItem(division->GetName().c_str())
						<< new QStandardItem(account->GetNumber().c_str())
						<< new QStandardItem(coAcc->GetName().c_str())
						<< new QStandardItem(divisionAccount->GetCode().c_str())
						<< new QStandardItem(QString::number(divisionAccount->GetDivisionID()))
						<< new QStandardItem(QString::number(divisionAccount->GetAccountID()));

					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(DivisionAccountItem);

					delete division;
					delete account;
					delete coAcc;
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
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr("Please recheck all fields, especially product list!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateDivAccDlg::EditDivisionAccount()
{
	errorMessage.clear();
	if (!codeEdit->text().isEmpty()
		&& 0 != accountEdit->text().toInt() && !divisionCmb->currentText().isEmpty())
	{
		if (QString(divisionAccount->GetCode().c_str()) != codeEdit->text() ||
			divisionAccount->GetAccountID() != accountEdit->text().toInt() ||
			divisionAccount->GetDivisionID() != divisionCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*)parentForm;
			SetDivisionAccountParams(divisionCmb->currentData().toInt(), accountEdit->text().toInt(), codeEdit->text(), divisionAccount->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateDivisionAccountRelation(divisionAccount, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Account *account = new BusinessLayer::Account;
						if (!account->GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), divisionAccount->GetAccountID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete account;
							return;
						}
						BusinessLayer::ChartOfAccounts *coAcc = new BusinessLayer::ChartOfAccounts;
						if (!coAcc->GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), account->GetNumber(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete account;
							delete coAcc;
							return;
						}
						BusinessLayer::Division *division = new BusinessLayer::Division;
						if (!division->GetDivisionByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), divisionAccount->GetDivisionID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete account;
							delete division;
							delete coAcc;
							return;
						}
						//updating DivisionAccount data
						itemModel->item(mIndex.row(), 1)->setText(division->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(account->GetNumber().c_str());
						itemModel->item(mIndex.row(), 3)->setText(coAcc->GetName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(divisionAccount->GetCode().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(divisionAccount->GetDivisionID()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(divisionAccount->GetAccountID()));

						emit itemModel->dataChanged(mIndex, mIndex);
						delete division;
						delete account;
						delete coAcc;
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
			QString(tr("Please recheck all fields, all of them must be filled!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateDivAccDlg::Close()
{
	dialogBL->CancelTransaction(errorMessage);
	this->parentWidget()->close();
}

void CreateDivAccDlg::OpenAccDlg()
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

void CreateDivAccDlg::InitComboBox()
{
	std::vector<BusinessLayer::Division> curDivision = dialogBL->GetAllDataForClass<BusinessLayer::Division>(errorMessage);
	if (!curDivision.empty())
	{
		for (unsigned int i = 0; i < curDivision.size(); i++)
		{
			divisionCmb->addItem(curDivision[i].GetName().c_str(), QVariant(curDivision[i].GetID()));
		}
	}
}

