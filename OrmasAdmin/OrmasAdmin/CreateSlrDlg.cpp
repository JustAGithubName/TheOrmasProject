#include "stdafx.h"
#include "CreateSlrDlg.h"
#include "DataForm.h"



CreateSlrDlg::CreateSlrDlg(BusinessLayer::OrmasBL *ormasBL, bool updateFlag, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	DataForm *dataFormParent = (DataForm *)this->parentForm;
	mainForm = (MainForm *)dataFormParent->GetParent();
	vDouble = new QDoubleValidator(0.00, 1000000000.00, 3, this);
	vInt = new QIntValidator(0, 1000000000, this);
	bonusCmb->addItem("false");
	bonusCmb->addItem("true");
	employeeEdit->setValidator(vInt);
	valueEdit->setValidator(vDouble);
	valueEdit->setMaxLength(17);
	if (true == updateFlag)
	{
		DataForm *parentDataForm = (DataForm*)parentForm;
		itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
		mIndex = parentDataForm->tableView->selectionModel()->currentIndex();
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSlrDlg::EditSalary);
	}
	else
	{
		dateEdit->setDateTime(QDateTime::currentDateTime());
		QObject::connect(okBtn, &QPushButton::released, this, &CreateSlrDlg::CreateSalary);
	}
	QObject::connect(cancelBtn, &QPushButton::released, this, &CreateSlrDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &CreateSlrDlg::OpenEmpDlg);
	QObject::connect(slrTypeBtn, &QPushButton::released, this, &CreateSlrDlg::OpenSlrTypeDlg);
	QObject::connect(valueEdit, &QLineEdit::textChanged, this, &CreateSlrDlg::TextEditChanged);
	InitComboBox();
}

CreateSlrDlg::~CreateSlrDlg()
{
	delete vDouble;
	delete vInt;
}


void CreateSlrDlg::SetID(int ID, QString childName)
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

			if (childName == QString("employeeForm"))
			{
				employeeEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					namePh->setText(user.GetName().c_str());
					surnamePh->setText(user.GetSurname().c_str());
					phonePh->setText(user.GetPhone().c_str());
				}
			}
			if (childName == QString("slrTypeForm"))
			{
				salaryTypeEdit->setText(QString::number(ID));
				BusinessLayer::SalaryType salaryType;
				if (salaryType.GetSalaryTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					salaryTypeNamePh->setText(salaryType.GetName().c_str());
				}
			}
		}
	}
}

void CreateSlrDlg::SetSalaryParams(int sEmployeeID, double sValue, int sCurrencyID, int sSalaryTypeID, QString sDate, QString sBonus, int id)
{
	salary->SetEmployeeID(sEmployeeID);
	salary->SetValue(sValue);
	salary->SetCurrencyID(sCurrencyID);
	salary->SetSalaryTypeID(sSalaryTypeID);
	salary->SetDate(sDate.toUtf8().constData());
	salary->SetIsBonus(sBonus == "true" ? true : false);
	salary->SetID(id);
}

void CreateSlrDlg::FillEditElements(int sEmployeeID, double sValue, int sCurrencyID, int sSalaryTypeID, QString sDate, QString sBonus)
{
	employeeEdit->setText(QString::number(sEmployeeID));
	valueEdit->setText(QString::number(sValue));
	salaryTypeEdit->setText(QString::number(sSalaryTypeID));
	dateEdit->setDateTime(QDateTime::fromString(sDate, "dd.MM.yyyy hh:mm"));
	int index = bonusCmb->findText(sBonus);
	bonusCmb->setCurrentIndex(index);
	currencyCmb->setCurrentIndex(currencyCmb->findData(QVariant(sCurrencyID)));
	BusinessLayer::User user;
	if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sEmployeeID, errorMessage))
	{
		namePh->setText(user.GetName().c_str());
		surnamePh->setText(user.GetSurname().c_str());
		phonePh->setText(user.GetPhone().c_str());
	}
	BusinessLayer::SalaryType salaryType;
	if (salaryType.GetSalaryTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), sSalaryTypeID, errorMessage))
	{
		salaryTypeNamePh->setText(salaryType.GetName().c_str());
	}
}

bool CreateSlrDlg::FillDlgElements(QTableView* sTable)
{
	QModelIndex mIndex = sTable->selectionModel()->currentIndex();
	if (mIndex.row() >= 0)
	{
		SetSalaryParams(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 6)).toDouble(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 9)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 10)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 0)).toInt());
		FillEditElements(sTable->model()->data(sTable->model()->index(mIndex.row(), 1)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 6)).toDouble(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 9)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 10)).toInt(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 5)).toString().toUtf8().constData(),
			sTable->model()->data(sTable->model()->index(mIndex.row(), 11)).toString().toUtf8().constData());
		return true;
	}
	else
	{
		return false;
	}
}

void CreateSlrDlg::CreateSalary()
{
	errorMessage.clear();
	if (!(0 != employeeEdit->text().toInt() || 0.0 != valueEdit->text().toDouble() || !currencyCmb->currentText().isEmpty()
		|| dateEdit->text().isEmpty()) || 0 != salaryTypeEdit->text().toInt() || bonusCmb->currentText().isEmpty())
	{
		DataForm *parentDataForm = (DataForm*) parentForm;
		SetSalaryParams(employeeEdit->text().toInt(), valueEdit->text().toDouble(), currencyCmb->currentData().toInt(), salaryTypeEdit->text().toInt(), dateEdit->text(), bonusCmb->currentText());
		dialogBL->StartIsolatedTransaction(errorMessage);
		if (dialogBL->CreateSalary(salary, errorMessage))
		{
			if (parentDataForm != nullptr)
			{
				if (!parentDataForm->IsClosed())
				{
					BusinessLayer::Employee *employee = new BusinessLayer::Employee();
					BusinessLayer::Currency *currency = new BusinessLayer::Currency;
					BusinessLayer::SalaryType *salaryType = new BusinessLayer::SalaryType;
					if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetEmployeeID(), errorMessage)
						|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetCurrencyID(), errorMessage)
						|| !salaryType->GetSalaryTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetSalaryTypeID(), errorMessage))
					{
						dialogBL->CancelTransaction(errorMessage);
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(tr(errorMessage.c_str())),
							QString(tr("Ok")));
						errorMessage.clear();
						delete employee;
						delete currency;
						delete salaryType;
						return;
					}

					QList<QStandardItem*> salaryItem;
					salaryItem << new QStandardItem(QString::number(salary->GetID()))
						<< new QStandardItem(QString::number(salary->GetEmployeeID()))
						<< new QStandardItem(employee->GetName().c_str())
						<< new QStandardItem(employee->GetSurname().c_str())
						<< new QStandardItem(employee->GetPhone().c_str())
						<< new QStandardItem(salary->GetDate().c_str())
						<< new QStandardItem(QString::number(salary->GetValue()))
						<< new QStandardItem(currency->GetShortName().c_str())
						<< new QStandardItem(salaryType->GetName().c_str())
						<< new QStandardItem(QString::number(salary->GetCurrencyID()))
						<< new QStandardItem(QString::number(salary->GetSalaryTypeID()))
						<< new QStandardItem(salary->GetIsBonus() ? "true" : "false");
					QStandardItemModel *itemModel = (QStandardItemModel *)parentDataForm->tableView->model();
					itemModel->appendRow(salaryItem);
					delete employee;
					delete currency;
					delete salaryType;
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
			QString(tr("Please fill employee, value, date and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateSlrDlg::EditSalary()
{
	errorMessage.clear();
	if (!(0 != employeeEdit->text().toInt() || 0.0 != valueEdit->text().toDouble() || !currencyCmb->currentText().isEmpty()
		|| dateEdit->text().isEmpty()) || 0 != salaryTypeEdit->text().toInt() || bonusCmb->currentText().isEmpty())
	{
		if (QString(salary->GetDate().c_str()) != dateEdit->text() || salary->GetEmployeeID() != employeeEdit->text().toInt()
			|| salary->GetValue() != valueEdit->text().toDouble() || salary->GetCurrencyID() != currencyCmb->currentData().toInt())
		{
			DataForm *parentDataForm = (DataForm*) parentForm;
			SetSalaryParams(employeeEdit->text().toInt(), valueEdit->text().toDouble(), currencyCmb->currentData().toInt(), salaryTypeEdit->text().toInt(), dateEdit->text(), bonusCmb->currentText(), salary->GetID());
			dialogBL->StartIsolatedTransaction(errorMessage);
			if (dialogBL->UpdateSalary(salary, errorMessage))
			{
				if (parentDataForm != nullptr)
				{
					if (!parentDataForm->IsClosed())
					{
						BusinessLayer::Employee *employee = new BusinessLayer::Employee();
						BusinessLayer::Currency *currency = new BusinessLayer::Currency;
						BusinessLayer::SalaryType *salaryType = new BusinessLayer::SalaryType;
						if (!employee->GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetEmployeeID(), errorMessage)
							|| !currency->GetCurrencyByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetCurrencyID(), errorMessage)
							|| !salaryType->GetSalaryTypeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), salary->GetSalaryTypeID(), errorMessage))
						{
							dialogBL->CancelTransaction(errorMessage);
							QMessageBox::information(NULL, QString(tr("Warning")),
								QString(tr(errorMessage.c_str())),
								QString(tr("Ok")));
							errorMessage.clear();
							delete employee;
							delete currency;
							delete salaryType;
							return;
						}

						
						itemModel->item(mIndex.row(), 1)->setText(QString::number(salary->GetEmployeeID()));
						itemModel->item(mIndex.row(), 2)->setText(employee->GetName().c_str());
						itemModel->item(mIndex.row(), 3)->setText(employee->GetSurname().c_str());
						itemModel->item(mIndex.row(), 4)->setText(employee->GetPhone().c_str());
						itemModel->item(mIndex.row(), 5)->setText(salary->GetDate().c_str());
						itemModel->item(mIndex.row(), 6)->setText(QString::number(salary->GetValue()));
						itemModel->item(mIndex.row(), 7)->setText(currency->GetShortName().c_str());
						itemModel->item(mIndex.row(), 8)->setText(salaryType->GetName().c_str());
						itemModel->item(mIndex.row(), 9)->setText(QString::number(salary->GetCurrencyID()));
						itemModel->item(mIndex.row(), 10)->setText(QString::number(salary->GetSalaryTypeID()));
						itemModel->item(mIndex.row(), 11)->setText(salary->GetIsBonus() ? "true" : "false");
						emit itemModel->dataChanged(mIndex, mIndex);
						delete employee;
						delete currency;
						delete salaryType;
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
			QString(tr("Please fill employee, value and currency!")),
			QString(tr("Ok")));
	}
	errorMessage.clear();
}

void CreateSlrDlg::Close()
{
	this->parentWidget()->close();
}

void CreateSlrDlg::OpenEmpDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Employees"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("employeeForm");
		dForm->QtConnect<BusinessLayer::EmployeeView>();
		QMdiSubWindow *employeeWindow = new QMdiSubWindow;
		employeeWindow->setWidget(dForm);
		employeeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(employeeWindow);
		employeeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->HideSomeRow();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All employees are shown");
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

void CreateSlrDlg::OpenSlrTypeDlg()
{
	this->hide();
	this->setModal(false);
	this->show();
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Salary type"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SalaryType>(errorMessage);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("slrTypeForm");
		dForm->QtConnect<BusinessLayer::SalaryType>();
		QMdiSubWindow *slrTypeWindow = new QMdiSubWindow;
		slrTypeWindow->setWidget(dForm);
		slrTypeWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(slrTypeWindow);
		slrTypeWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All salary types are shown");
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

void CreateSlrDlg::InitComboBox()
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

void CreateSlrDlg::TextEditChanged()
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