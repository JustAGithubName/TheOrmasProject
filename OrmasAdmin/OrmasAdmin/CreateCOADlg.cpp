#include "stdafx.h"
#include "CreateCOADlg.h"
#include "DataForm.h"



CreateCOADlg::CreateCOADlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vInt = new QIntValidator(0, 1000000000, this);
	numberEdit->setValidator(vInt);
	nameEdit->setMaxLength(150);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCOADlg::EditChartOfAccounts);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateCOADlg::CreateChartOfAccounts);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateCOADlg::Close);
	QObject::connect(accTypeBtn, &QPushButton::released, this, &CreateCOADlg::OpenAccTpDlg);
}

CreateCOADlg::~CreateCOADlg()
{
	delete vInt;
}

void CreateCOADlg::SetID(int ID, QString childName)
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

			if (childName == QString("accountTypeForm"))
			{
				accTypeEdit->setText(QString::number(ID));
				BusinessLayer::AccountType accType;
				if (accType.GetAccountTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accTypeNamePh->setText(accType.GetName().c_str());
				}
			}
		}
	}
}

void CreateCOADlg::SetChartOfAccountsParams(QString cName, QString cNumber, int atID, int id)
{
	chartOfAccounts->SetName(cName.toUtf8().constData());
	chartOfAccounts->SetNumber(cNumber.toUtf8().constData());
	chartOfAccounts->SetAccountTypeID(atID);
	chartOfAccounts->SetID(id);
}

void CreateCOADlg::FillEditElements(QString cName, QString cNumber, int atID)
{
	nameEdit->setText(cName);
	numberEdit->setText(cNumber);
	accTypeEdit->setText(QString::number(atID));
	BusinessLayer::AccountType accType;
	if (accType.GetAccountTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), atID, errorMessage))
	{
		accTypeNamePh->setText(accType.GetName().c_str());
	}
}

bool CreateCOADlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetChartOfAccountsParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateCOADlg::CreateChartOfAccounts()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !numberEdit->text().isEmpty() && 0 != accTypeEdit->text().toInt())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetChartOfAccountsParams(nameEdit->text(), numberEdit->text(), accTypeEdit->text().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateChartOfAccounts(chartOfAccounts, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::AccountType *accType = new BusinessLayer::AccountType();
					if (!accType->GetAccountTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccounts->GetAccountTypeID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete accType;
						return;
					}

					QList<QStandardItem*> chartOfAccountsItem;
					chartOfAccountsItem << new QStandardItem(QString::number(chartOfAccounts->GetID()))
						<< new QStandardItem(chartOfAccounts->GetNumber().c_str())
						<< new QStandardItem(chartOfAccounts->GetName().c_str())
						<< new QStandardItem(QString::number(chartOfAccounts->GetAccountTypeID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(chartOfAccountsItem);
					delete accType;
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

void CreateCOADlg::EditChartOfAccounts()
{
	errorMessage.clear();
	if (!nameEdit->text().isEmpty() && !numberEdit->text().isEmpty() && 0 != accTypeEdit->text().toInt())
	{
		if (QString(chartOfAccounts->GetName().c_str()) != nameEdit->text() || QString(chartOfAccounts->GetNumber().c_str()) != numberEdit->text()
			|| chartOfAccounts->GetAccountTypeID() != accTypeEdit->text().toDouble())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetChartOfAccountsParams(nameEdit->text(), numberEdit->text(), accTypeEdit->text().toInt(), chartOfAccounts->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateChartOfAccounts(chartOfAccounts, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::AccountType *accType = new BusinessLayer::AccountType();
						if (!accType->GetAccountTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), chartOfAccounts->GetAccountTypeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete accType;
							return;
						}

						itemModel->item(mIndex.row(), 1)->setText(chartOfAccounts->GetNumber().c_str());
						itemModel->item(mIndex.row(), 2)->setText(chartOfAccounts->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(accType->GetName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(chartOfAccounts->GetAccountTypeID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete accType;
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

void CreateCOADlg::Close()
{
	this->parentWidget()->close();
}

void CreateCOADlg::OpenAccTpDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Account types"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::AccountType>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountTypeForm");
		dForm->QtConnect<BusinessLayer::AccountType>();
		QMdiSubWindow *accTypeWindow = new QMdiSubWindow;
		accTypeWindow->setWidget(dForm);
		accTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(accTypeWindow);
		accTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All account types are shown");
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