#include "stdafx.h"
#include "CreateTmsDlg.h"
#include "DataForm.h"


CreateTmsDlg::CreateTmsDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
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
	workedTimeEdit->setValidator(vDouble);
	workedTimeEdit->setMaxLength(4);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateTmsDlg::EditTimesheet);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateTmsDlg::CreateTimesheet);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateTmsDlg::Close);
	QObject::connect(salaryBtn, &QPushButton::released, this, &CreateTmsDlg::OpenSlrDlg);
	QObject::connect(workedTimeEdit, &QLineEdit::textChanged, this, &CreateTmsDlg::TextEditChanged);
}

CreateTmsDlg::~CreateTmsDlg()
{
	delete vInt;
	delete vDouble;
}

void CreateTmsDlg::SetID(int ID, QString childName)
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
				}
			}
		}
	}
}

void CreateTmsDlg::SetTimesheetParams(int sID, double tWorkedTime, QString tDate, int id)
{
	timesheet->SetSalaryID(sID);
	timesheet->SetWorkedTime(tWorkedTime);
	timesheet->SetDate(tDate.toUtf8().constData());
	timesheet->SetID(id);
}

void CreateTmsDlg::FillEditElements(int sID, double tWorkedTime, QString tDate)
{
	salaryEdit->setText(QString::number(sID));
	workedTimeEdit->setText(QString::number(tWorkedTime));
	dateEdit->setDate(QDate::fromString(tDate, "dd.MM.yyyy"));
	BusinessLayer::Salary salary;
	if (salary.GetSalaryByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sID, errorMessage))
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

bool CreateTmsDlg::FillDlgElements(QTableView* pTable)
{
	QModelIndex mIndex = pTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetTimesheetParams(pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(pTable->model()->data(pTable->model()->index(mIndex.row(), 6)).toInt(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 5)).toDouble(),
			pTable->model()->data(pTable->model()->index(mIndex.row(), 4)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateTmsDlg::CreateTimesheet()
{
	errorMessage.clear();
	if (0 != salaryEdit->text().toInt() && 0.0 != workedTimeEdit->text().toDouble() && !dateEdit->text().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetTimesheetParams(salaryEdit->text().toInt(), workedTimeEdit->text().toDouble(), dateEdit->text());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateTimesheet(timesheet, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Salary *salary = new BusinessLayer::Salary;
					BusinessLayer::User *employee = new BusinessLayer::User;
					if (!salary->GetSalaryByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), timesheet->GetSalaryID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete salary;
						return;
					}

					if (!employee->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetEmployeeID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete employee;
						return;
					}


					QList<QStandardItem*> timesheetItem;
					timesheetItem << new QStandardItem(QString::number(timesheet->GetID()))
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(timesheet->GetDate().c_str())
						<< new QStandardItem(QString::number(timesheet->GetWorkedTime()))
						<< new QStandardItem(QString::number(timesheet->GetSalaryID()));
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(timesheetItem);
					delete salary;
					delete employee;
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

void CreateTmsDlg::EditTimesheet()
{
	errorMessage.clear();
	if (0 != salaryEdit->text().toInt() && 0.0 != workedTimeEdit->text().toDouble() && !dateEdit->text().isEmpty())
	{
		if (QString(timesheet->GetDate().c_str()) != dateEdit->text() || timesheet->GetSalaryID() != salaryEdit->text().toInt()
			|| timesheet->GetWorkedTime() != workedTimeEdit->text().toDouble())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetTimesheetParams(salaryEdit->text().toInt(), workedTimeEdit->text().toDouble(), dateEdit->text(), timesheet->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateTimesheet(timesheet, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Salary *salary = new BusinessLayer::Salary;
						BusinessLayer::User *employee = new BusinessLayer::User;
						if (!salary->GetSalaryByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), timesheet->GetSalaryID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete salary;
							return;
						}

						if (!employee->GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetEmployeeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							return;
						}

						
						itemModel->item(mIndex.row(), 1)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 2)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 4)->setText(timesheet->GetDate().c_str());
						itemModel->item(mIndex.row(), 5)->setText(QString::number(timesheet->GetWorkedTime()));
						itemModel->item(mIndex.row(), 6)->setText(QString::number(timesheet->GetSalaryID()));
						emit itemModel->dataChanged(mIndex, mIndex);
						delete employee;
						delete salary;
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

void CreateTmsDlg::Close()
{
	this->parentWidget()->close();
}

void CreateTmsDlg::OpenSlrDlg()
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
		QString message = tr("All salaries are shown");
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

void CreateTmsDlg::TextEditChanged()
{
	if (workedTimeEdit->text().contains(","))
	{
		workedTimeEdit->setText(workedTimeEdit->text().replace(",", "."));
	}
	if (workedTimeEdit->text().contains(".."))
	{
		workedTimeEdit->setText(workedTimeEdit->text().replace("..", "."));
	}
}