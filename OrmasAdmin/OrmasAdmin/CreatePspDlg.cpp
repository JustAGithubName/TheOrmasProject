#include "stdafx.h"
#include "CreatePspDlg.h"
#include "DataForm.h"



CreatePspDlg::CreatePspDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	salaryEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePspDlg::EditPayslip);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreatePspDlg::CreatePayslip);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreatePspDlg::Close);
	QObject::connect(salaryBtn, &QPushButton::released, this, &CreatePspDlg::OpenSlrDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreatePspDlg::TextEditChanged);
	InitComboBox();
}

CreatePspDlg::~CreatePspDlg()
{
	delete vInt;
	delete vDouble;
}

void CreatePspDlg::SetID(int ID, QString childName)
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

			if (childName == QString("salaryForm"))
			{
				salaryEdit->setText(QString::number(ID));
				BusinessLayer::Salary salary;
				if (salary.GetSalaryByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					BusinessLayer::User user;
					if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary.GetEmployeeID(), errorMessage))
					{
						namePh->setText(user.GetName().c_str());
						surnamePh->setText(user.GetSurname().c_str());
						phonePh->setText(user.GetPhone().c_str());
					}
					BusinessLayer::Currency currency;
					if (currency.GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary.GetCurrencyID(), errorMessage))
					{
						currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(currency.GetID())));
					}
				}
			}
		}
	}
}

void CreatePspDlg::SetPayslipParams(QString pDate, double pValue, int pSalaryID, int pCurrencyID, int id)
{
	payslip->SetDate(pDate.toUtf8().constData());
	payslip->SetValue(pValue);
	payslip->SetSalaryID(pSalaryID);
	payslip->SetCurrencyID(pCurrencyID);
	payslip->SetID(id);
}

void CreatePspDlg::FillEditElements(QString pDate, double pValue, int pSalaryID, int pCurrencyID)
{
	dateEdit->setDateTime(QDateTime::fromString(pDate, "dd.MM.yyyy hh:mm"));
	valueEdit->setText(QString::number(pValue));
	salaryEdit->setText(QString::number(pSalaryID));
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(pCurrencyID)));
	BusinessLayer::Salary salary;
	if (salary.GetSalaryByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), pSalaryID, errorMessage))
	{
		BusinessLayer::User user;
		if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary.GetEmployeeID(), errorMessage))
		{
			namePh->setText(user.GetName().c_str());
			surnamePh->setText(user.GetSurname().c_str());
			phonePh->setText(user.GetPhone().c_str());
		}
	}
}

bool CreatePspDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetPayslipParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 1)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 2)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toInt());
		return true;
	}
	else
	{
		return false;
	}
}

void CreatePspDlg::CreatePayslip()
{
	errorMessage.clear();
	if (0 != salaryEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetPayslipParams(dateEdit->text(), valueEdit->text().toDouble(), salaryEdit->text().toInt(), currencyCmb->currentData().toInt());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreatePayslip(payslip, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payslip->GetCurrencyID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete currency;
						return;
					}
					QList<QStandardItem*> payslipItem;
					payslipItem << new QStandardItem(QString::number(payslip->GetID()))
						<< new QStandardItem(payslip->GetDate().c_str())
						<< new QStandardItem(QString::number(payslip->GetValue()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(QString::number(payslip->GetSalaryID()))
						<< new QStandardItem(QString::number(payslip->GetCurrencyID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(payslipItem);
					delete currency;
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

void CreatePspDlg::EditPayslip()
{
	errorMessage.clear();
	if (0 != salaryEdit->text().toInt() && 0.0 != valueEdit->text().toDouble() && !currencyCmb->currentText().isEmpty()
		&& !dateEdit->text().isEmpty())
	{
		if (QString(payslip->GetDate().c_str()) != dateEdit->text() || payslip->GetSalaryID() != salaryEdit->text().toInt()
			|| payslip->GetValue() != valueEdit->text().toDouble() || payslip->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetPayslipParams(dateEdit->text(), valueEdit->text().toDouble(), salaryEdit->text().toInt(), currencyCmb->currentData().toInt(), payslip->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdatePayslip(payslip, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						if (!currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), payslip->GetCurrencyID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete currency;
							return;
						}
						
						itemModel->item(mIndex.row(), 1)->setText(payslip->GetDate().c_str());
						itemModel->item(mIndex.row(), 2)->setText(QString::number(payslip->GetValue()));
						itemModel->item(mIndex.row(), 3)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 4)->setText(QString::number(payslip->GetSalaryID()));
						itemModel->item(mIndex.row(), 5)->setText(QString::number(payslip->GetCurrencyID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete currency;
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

void CreatePspDlg::Close()
{
	this->parentWidget()->close();
}

void CreatePspDlg::OpenSlrDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Salaries"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SalaryView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("salaryForm");
		dForm->QtConnect<BusinessLayer::SalaryView>();
		QMdiSubWindow *salaryWindow = new QMdiSubWindow;
		salaryWindow->setWidget(dForm);
		salaryWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(salaryWindow);
		salaryWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
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

void CreatePspDlg::InitComboBox()
{
	std::vector<BusinessLayer::Currency> curVector = dialogBL->GetAllDataForClass<BusinessLayer::Currency>(errorMessage);
	if (!curVector.empty())
	{
		for (unsigned int i = 0; i < curVector.size(); i++)
		{
			if (curVector[i].GetMainTrade() == true)
				currencyCmb->addItem(curVector[i].GetShortName().c_str(), QVariant(curVector[i].GetID()));
		}
	}
}

void CreatePspDlg::TextEditChanged()
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
