#include "stdafx.h"
#include "ClcWagesDlg.h"
#include "DataForm.h"

#include <map>


ClcWagesDlg::ClcWagesDlg(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();

	QDate currentDate = QDate::currentDate();
	int day = currentDate.day();
	int month = currentDate.month();
	int year = currentDate.year();

	std::string startDate;
	/*std::string endDate;

	std::string pastMonth;
	pastMonth = std::to_string(year);
	pastMonth += "-";
	pastMonth += std::to_string(month - 1);
	pastMonth += "-01";
	QDate pastMonthDate = (QDate::fromString(pastMonth.c_str(), "dd.MM.yyyy"));
	int coundOfDays = pastMonthDate.daysInMonth();

	

	if (day < 15 && month == 1)
	{
		startDate = std::to_string(year - 1);
		startDate += "-";
		startDate += std::to_string(month - 1);
		startDate += "-01";
		endDate += std::to_string(year - 1);
	}
	if (day > 15 && month == 1)
	{
		startDate = std::to_string(year - 1);
		startDate += "-";
		startDate += std::to_string(month);
		startDate += "-01";
	}
	if (day > 15 && month > 1)
	{
		startDate = std::to_string(year);
		startDate += "-";
		startDate += std::to_string(month);
		startDate += "-01";
	}
	if (day < 15 && month > 1)
	{
		startDate = std::to_string(year);
		startDate += "-";
		startDate += std::to_string(month - 1);
		startDate += "-01";
	}*/

	startDate = std::to_string(year);
	startDate += "-";
	startDate += std::to_string(month);
	startDate += "-01";
	endDateEdit->setDate(QDate::currentDate());
	startDateEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	if (employeeChkBox->isChecked())
	{
		employeeEdit->setText("");
		singleEmployeeWidget->setVisible(false);
	}
	else
	{
		singleEmployeeWidget->setVisible(true);
	}
	QObject::connect(okBtn, &QPushButton::released, this, &ClcWagesDlg::Calculate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &ClcWagesDlg::Close);
	QObject::connect(employeeBtn, &QPushButton::released, this, &ClcWagesDlg::OpenEmpDlg);
	QObject::connect(employeeChkBox, &QCheckBox::stateChanged, this, &ClcWagesDlg::ChangeState);
}

ClcWagesDlg::~ClcWagesDlg()
{
	
}

void ClcWagesDlg::SetID(int ID, QString childName)
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
			}
		}
	}
}


void ClcWagesDlg::Calculate()
{
	/*if (employeeChkBox->isChecked())
	{
		QProgressDialog progressDialog(this);
		std::vector<BusinessLayer::EmployeeView> employeeVector = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage);
		if (employeeVector.size() > 0)
		{
			progressDialog.setRange(0, employeeVector.size());
			progressDialog.setWindowFlags(Qt::FramelessWindowHint);
			int i = 0;
			
			BusinessLayer::Salary salary;
			std::string salaryFilter;
			std::vector<BusinessLayer::SalaryView> salaryVector;
			std::map<std::string, int> salaryTypeMap = BusinessLayer::SalaryType::GetSalaryTypesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
			std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
			BusinessLayer::Payslip payslip;
			BusinessLayer::Order order;
			std::string orderFilter;
			std::vector<BusinessLayer::OrderView> orderVector;

			for each (auto employeeItem in employeeVector)
			{
				progressDialog.setValue(i);

				if (!employeeItem.IsEmpty())
				{
					errorMessage = "";
					salary.Clear();
					salary.SetEmployeeID(employeeItem.GetID());
					salaryFilter = salary.GenerateFilter(dialogBL->GetOrmasDal());
					salaryVector.clear();
					salaryVector = dialogBL->GetAllDataForClass<BusinessLayer::SalaryView>(errorMessage, salaryFilter);
					if (errorMessage.empty())
					{
						if (1 <= salaryVector.size())
						{
							if (salaryTypeMap.size() > 0 && statusMap.size() > 0)
							{
								for each (auto salaryItem in salaryVector)
								{
									try
									{
										if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("FIXED")->second)
										{
											payslip.Clear();
											payslip.SetDate(dialogBL->GetOrmasDal().GetSystemDateTime());
											payslip.SetSalaryID(salaryItem.GetID());
											payslip.SetCurrencyID(salaryItem.GetCurrencyID());
											payslip.SetValue(salaryItem.GetValue());
											payslip.CreatePayslip(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
										}
										if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("PERCENT")->second)
										{
											order.Clear();
											order.SetEmployeeID(salary.GetEmployeeID());
											order.SetStatusID(statusMap.find("EXECUTED")->second);
											orderFilter = order.GenerateFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), startDateEdit->text().toUtf8().constData(),
												endDateEdit->text().toUtf8().constData());
											orderVector.clear();
											orderVector = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, orderFilter);
											sum = 0;
											if (orderVector.size() > 0)
											{
												for each (auto item in orderVector)
												{
													sum += sum + item.GetSum();
												}
											}
											if (sum > 0)
											{
												payslip.Clear();
												payslip.SetDate(dialogBL->GetOrmasDal().GetSystemDateTime());
												payslip.SetSalaryID(salaryItem.GetID());
												payslip.SetCurrencyID(salaryItem.GetCurrencyID());
												payslip.SetValue(sum);
												payslip.CreatePayslip(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
											}
										}
									}
									catch (...)
									{
									}
								}
							}
						}
					}
				}
				progressDialog.setValue(i);
				i++;
			}
		}
		QMessageBox::information(NULL, QString(tr("Info")),
		QString("For all employees a wages were calculated!"),
		QString(tr("Ok")));
		Close();
	}
	else
	{
		if (0 != employeeEdit->text().toInt())
		{
			BusinessLayer::Employee employee;
			employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeEdit->text().toInt(), errorMessage);
			if (!employee.IsEmpty())
			{
				errorMessage = "";
				BusinessLayer::Salary salary;
				salary.SetEmployeeID(employee.GetID());
				std::string filter = salary.GenerateFilter(dialogBL->GetOrmasDal());
				std::vector<BusinessLayer::SalaryView> salaryVector = dialogBL->GetAllDataForClass<BusinessLayer::SalaryView>(errorMessage, filter);
				if (errorMessage.empty())
				{
					if (0 == salaryVector.size())
					{
						errorMessage = "Please check the salary parameters for employee: "  + employee.GetSurname() + ", " + employee.GetName() + ". These employee has not any salary options";
						QMessageBox::information(NULL, QString(tr("Warning")),
							QString(errorMessage.c_str()),
							QString(tr("Ok")));
						errorMessage.clear();
					}
					if (1 <= salaryVector.size())
					{
						std::map<std::string, int> salaryTypeMap = BusinessLayer::SalaryType::GetSalaryTypesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
						std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
						if (salaryTypeMap.size() > 0 && statusMap.size() > 0)
						{
							for each (auto salaryItem in salaryVector)
							{
								try
								{
									if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("FIXED")->second)
									{
										BusinessLayer::Payslip payslip;
										payslip.SetDate(dialogBL->GetOrmasDal().GetSystemDateTime());
										payslip.SetSalaryID(salaryItem.GetID());
										payslip.SetCurrencyID(salaryItem.GetCurrencyID());
										payslip.SetValue(salaryItem.GetValue());
										payslip.CreatePayslip(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
									}
									if (salaryItem.GetSalaryTypeID() == salaryTypeMap.find("PERCENT")->second)
									{
										BusinessLayer::Order order;
										order.SetEmployeeID(salary.GetEmployeeID());
										order.SetStatusID(statusMap.find("EXECUTED")->second);
										std::string filter = order.GenerateFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), startDateEdit->text().toUtf8().constData(),
											endDateEdit->text().toUtf8().constData());
										std::vector<BusinessLayer::OrderView> orderVector = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);
										sum = 0;
										if (orderVector.size() > 0)
										{
											for each (auto item in orderVector)
											{
												sum += sum + item.GetSum();
											}
										}
										if (sum > 0)
										{
											BusinessLayer::Payslip payslip;
											payslip.SetDate(dialogBL->GetOrmasDal().GetSystemDateTime());
											payslip.SetSalaryID(salaryItem.GetID());
											payslip.SetCurrencyID(salaryItem.GetCurrencyID());
											payslip.SetValue(sum);
											payslip.CreatePayslip(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
										}
									}
								}
								catch (...)
								{
								}
							}
						}
					}
				}
				else
				{
					QMessageBox::information(NULL, QString(tr("Warning")),
						QString(errorMessage.c_str()),
						QString(tr("Ok")));
					errorMessage.clear();
				}
			}			
		}
	}*/
}

void ClcWagesDlg::ChangeState()
{
	if (employeeChkBox->isChecked())
	{
		employeeEdit->setText("");
		singleEmployeeWidget->setVisible(false);
	}
	else
	{
		singleEmployeeWidget->setVisible(true);
	}
}

void ClcWagesDlg::Close()
{
	this->parentWidget()->close();
}

void ClcWagesDlg::OpenEmpDlg()
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