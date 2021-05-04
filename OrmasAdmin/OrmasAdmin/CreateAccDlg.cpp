#include "stdafx.h"
#include "CreateAccDlg.h"
#include "DataForm.h"


CreateAccDlg::CreateAccDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	startBalanceEdit->setValidator(vDouble);
	currentBalanceEdit->setValidator(vDouble);
	startBalanceEdit->setMaxLength(17);
	currentBalanceEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAccDlg::EditAccount);
	}
	else
	{
		QObject::connect(okBtn, &QPushButton::released, this, &CreateAccDlg::CreateAccount);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateAccDlg::Close);
	QObject::connect(chartOfAccBtn, &QPushButton::released, this, &CreateAccDlg::OpenCOADlg);
	QObject::connect(startBalanceEdit, &QLineEdit::textChanged, this, &CreateAccDlg::TextEditChanged);
	QObject::connect(currentBalanceEdit, &QLineEdit::textChanged, this, &CreateAccDlg::TextEditChanged);
}

CreateAccDlg::~CreateAccDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateAccDlg::SetID(int ID, QString childName)
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
				BusinessLayer::ChartOfAccounts coAcc;
				if (coAcc.GetChartOfAccountsByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					numberEdit->setText(coAcc.GetNumber().c_str());
					accNamePh->setText(coAcc.GetName().c_str());
				}
			}
		}
	}
}

void CreateAccDlg::SetAccountParams(QString aNumber, double aStartBalance, double aCurrentBalance, int id)
{
	account->SetNumber(aNumber.toUtf8().constData());
	account->SetStartBalance(aStartBalance);
	account->SetCurrentBalance(aCurrentBalance);
	account->SetID(id);
}

void CreateAccDlg::FillEditElements(QString aNumber, double aStartBalance, double aCurrentBalance)
{
	numberEdit->setText(aNumber);
	startBalanceEdit->setText(QString::number(aStartBalance, 'f', 3));
	currentBalanceEdit->setText(QString::number(aCurrentBalance, 'f', 3));
	BusinessLayer::ChartOfAccounts aoAcc;
	if (aoAcc.GetChartOfAccountsByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), aNumber.toUtf8().constData(), errorMessage))
	{
		
		chartOfAccEdit->setText(QString::number(aoAcc.GetID()));
		accNamePh->setText(aoAcc.GetName().c_str());
		
	}
}

bool CreateAccDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetAccountParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 3)).toDouble());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateAccDlg::CreateAccount()
{
	errorMessage.clear();
	if (!numberEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetAccountParams(numberEdit->text(), startBalanceEdit->text().toDouble(), currentBalanceEdit->text().toDouble());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateAccount(account, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					QList<QStandardItem*> accountItem;
					accountItem << new QStandardItem(QString::number(account->GetID()))
						<< new QStandardItem(account->GetNumber().c_str())
						<< new QStandardItem(QString::number(account->GetStartBalance(), 'f', 3))
						<< new QStandardItem(QString::number(account->GetCurrentBalance(), 'f', 3));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(accountItem);
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

void CreateAccDlg::EditAccount()
{
	errorMessage.clear();
	if (!numberEdit->text().isEmpty())
	{
		if (QString(account->GetNumber().c_str()) != numberEdit->text()	|| account->GetStartBalance() != startBalanceEdit->text().toDouble()
			|| account->GetCurrentBalance() != currentBalanceEdit->text().toDouble())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetAccountParams(numberEdit->text(), startBalanceEdit->text().toDouble(), currentBalanceEdit->text().toDouble(),
				 account->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateAccount(account, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						itemModel->item(mIndex.row(), 1)->setText(account->GetNumber().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(account->GetStartBalance(), 'f', 3));
						itemModel->item(mIndex.row(), 3)->setText(QString::number(account->GetCurrentBalance(), 'f', 3));
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
			QString(tr("Please fill all fields!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateAccDlg::Close()
{
	this->parentWidget()->close();
}

void CreateAccDlg::OpenCOADlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Chart of accounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::ChartOfAccountsView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("chartOfAccountForm");
		dForm->QtConnect<BusinessLayer::ChartOfAccountsView>();
		QMdiSubWindow *coAccWindow = new QMdiSubWindow;
		coAccWindow->setWidget(dForm);
		coAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(coAccWindow);
		coAccWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("Chart of accounts are shown");
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

void CreateAccDlg::TextEditChanged()
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

