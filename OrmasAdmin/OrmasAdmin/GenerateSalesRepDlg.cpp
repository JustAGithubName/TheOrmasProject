#include "stdafx.h"
#include "GenerateSalesRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"


GenerateSalesRep::GenerateSalesRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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
	std::string endDate;
	std::string reportingMonth;
	QDate pastMonthDate;
	int coundOfDays; //  = pastMonthDate.daysInMonth();

	if (day < 15 && month == 1)
	{
		startDate = "01.";
		startDate += std::to_string(12);
		startDate += ".";
		startDate += std::to_string(year - 1);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDays);
		endDate += ".";
		endDate += std::to_string(12);
		endDate += ".";
		endDate += std::to_string(year - 1);
		//previous month
		prevFromMonth = "01.";
		prevFromMonth += std::to_string(11);
		prevFromMonth += ".";
		prevFromMonth += std::to_string(year - 1);
		pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		prevTillMonth = std::to_string(coundOfDays);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(11);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(year - 1);
	}
	if (day > 15 && month == 1)
	{
		startDate = "01.";
		startDate += std::to_string(1);
		startDate += ".";
		startDate += std::to_string(year);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDays);
		endDate += ".";
		endDate += std::to_string(1);
		endDate += ".";
		endDate += std::to_string(year);
		//previous month
		prevFromMonth = "01.";
		prevFromMonth += std::to_string(12);
		prevFromMonth += ".";
		prevFromMonth += std::to_string(year - 1);
		pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		prevTillMonth = std::to_string(coundOfDays);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(12);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(year - 1);
	}
	if (day > 15 && month > 1)
	{
		startDate = "01.";
		startDate += std::to_string(month);
		startDate += ".";
		startDate += std::to_string(year);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDays);
		endDate += ".";
		endDate += std::to_string(month);
		endDate += ".";
		endDate += std::to_string(year);
		//previous month
		prevFromMonth = "01.";
		prevFromMonth += std::to_string(month - 1);
		prevFromMonth += ".";
		prevFromMonth += std::to_string(year);
		pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		prevTillMonth = std::to_string(coundOfDays);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(month - 1);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(year);
	}
	if (day < 15 && month > 1)
	{
		startDate = "01.";
		startDate += std::to_string(month - 1);
		startDate += ".";
		startDate += std::to_string(year);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDays);
		endDate += ".";
		endDate += std::to_string(month - 1);
		endDate += ".";
		endDate += std::to_string(year);
		//previous month
		if (month == 2)
		{
			prevFromMonth = "01.";
			prevFromMonth += std::to_string(12);
			prevFromMonth += ".";
			prevFromMonth += std::to_string(year - 1);
			pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
			coundOfDays = pastMonthDate.daysInMonth();
			prevTillMonth = std::to_string(coundOfDays);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(12);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(year - 1);
		}
		if (month > 2)
		{
			prevFromMonth = "01.";
			prevFromMonth += std::to_string(month - 2);
			prevFromMonth += ".";
			prevFromMonth += std::to_string(year);
			pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
			coundOfDays = pastMonthDate.daysInMonth();
			prevTillMonth = std::to_string(coundOfDays);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(month - 2);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(year);
		}
	}
	fromDateEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	tillDateEdit->setDate(QDate::fromString(endDate.c_str(), "dd.MM.yyyy"));

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateSalesRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateSalesRep::Close);
}

GenerateSalesRep::~GenerateSalesRep()
{
}

void GenerateSalesRep::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}

	BusinessLayer::Employee employee;
	BusinessLayer::Role role;
	role.SetName("EXPEDITOR");
	std::string filterRole = role.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::Role> vecRole = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, filterRole);
	if (vecRole.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with roles!")),
			QString(tr("Ok")));
		return;
	}

	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	std::string filter = "";

	if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
	{
		employee.SetRoleID(vecRole.at(0).GetID());
		filter = employee.GenerateFilter(dialogBL->GetOrmasDal());
	}
	else
	{
		BusinessLayer::Employee emp;
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), mainForm->GetLoggedUser()->GetID(), errorMessage);
		if (0 < branchID)
		{
			//get list of employees in branch
			ceRel.Clear();
			std::vector<int> empIDVec = ceRel.GetAllEmployeeIDByBranchID(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), branchID, errorMessage);
			std::string inEmployeeFilter= emp.GenerateINFilter(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), empIDVec);
			
			//get employees for specific role
			emp.SetRoleID(vecRole.at(0).GetID());
			std::string filterEmp = emp.GenerateFilter(dialogBL->GetOrmasDal());

			//marge filters
			std::vector<std::string> filterVec;
			filterVec.push_back(filterEmp);
			filterVec.push_back(inEmployeeFilter);
			filter = mainForm->oBL->ConcatenateFilters(filterVec);
		}
	}

	
	std::vector<BusinessLayer::EmployeeView> vecEmployee = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, filter);
	if (vecEmployee.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find any expeditor!")),
			QString(tr("Ok")));
		return;
	}
	else
	{
		DocForm *docForm = new DocForm(dialogBL, this);
		docForm->setAttribute(Qt::WA_DeleteOnClose);
		docForm->setWindowTitle(tr("Print sales report"));
		QMdiSubWindow *generateProfRepWindow = new QMdiSubWindow;
		generateProfRepWindow->setWidget(docForm);
		generateProfRepWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateProfRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateProfRepWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/sales.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find sales report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();

		BusinessLayer::Order order;
		BusinessLayer::OrderList orderList;
		std::string orderListFilter;
		std::map<int, double> productCount;
		std::map<int, double> productSum;
		std::vector<BusinessLayer::OrderListView> vecOrderList;

		BusinessLayer::Return ret;
		BusinessLayer::ReturnList returnList;
		std::string returnListFilter;
		std::map<int, double> productCountRet;
		std::map<int, double> productSumRet;
		std::vector<BusinessLayer::ReturnListView> vecReturnList;

		BusinessLayer::Product product;
		BusinessLayer::NetCost nCost;
		double sum = 0;
		double sumRet = 0;
		QString documentBody;
		QString tableBody;

		std::map<int, double> totalCount;
		std::map<int, double> totalSum;

		std::map<int, double> totalReturnCount;
		std::map<int, double> totalReturnSum;



		reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
		reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);

		if (!allSalesChb->isChecked())
		{
			for each (BusinessLayer::EmployeeView expeditor in vecEmployee)
			{
				tableBody.clear();

				ret.Clear();
				ret.SetStatusID(status.GetID());
				ret.SetEmployeeID(expeditor.GetID());
				std::string filterRet = ret.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
				std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRet);

				order.Clear();
				order.SetStatusID(status.GetID());
				order.SetEmployeeID(expeditor.GetID());
				std::string filter = order.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
				std::vector<BusinessLayer::OrderView> vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);
				if (vecOrder.size() == 0)
				{
					continue;
				}
				else
				{
					//generating report
					if (vecOrder.size() > 0)
					{
						productCount.clear();
						productSum.clear();
						productCountRet.clear();
						productSumRet.clear();
						sum = 0;
						sumRet = 0;
						tableBody += QString::fromWCharArray(L"Сотрудник: ");
						tableBody += expeditor.GetSurname().c_str();
						tableBody += " ";
						tableBody += expeditor.GetName().c_str();
						tableBody += "  ";
						tableBody += QString::fromWCharArray(L"Телефон: ");
						tableBody += expeditor.GetPhone().c_str();
						tableBody += "<br/>";

						tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px;'>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"ID продукта") + "</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта")+"</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Продажа количество") + "</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Продажа сумма") + "</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Возврат количество")+"</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Возврат сумма")+"</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Итого количество")+"</b></th>";
						tableBody += "<th><b>" + QString::fromWCharArray(L"Итого сумма")+"</b></th>";

						for each (auto item in vecOrder)
						{
							orderList.Clear();
							orderListFilter.clear();
							orderList.SetOrderID(item.GetID());
							orderListFilter = orderList.GenerateFilter(dialogBL->GetOrmasDal());
							vecOrderList.clear();
							vecOrderList = dialogBL->GetAllDataForClass<BusinessLayer::OrderListView>(errorMessage, orderListFilter);
							if (vecOrderList.size() > 0)
							{
								for each (auto listItem in vecOrderList)
								{
									if (productCount.find(listItem.GetProductID()) != productCount.end())
									{
										productCount.find(listItem.GetProductID())->second = productCount.find(listItem.GetProductID())->second + listItem.GetCount();
										productSum.find(listItem.GetProductID())->second = productSum.find(listItem.GetProductID())->second + listItem.GetSum();
									}
									else
									{
										productCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
										productSum.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
									}
								}
							}
						}

						for each (auto item in vecReturn)
						{
							returnList.Clear();
							returnListFilter.clear();
							returnList.SetReturnID(item.GetID());
							returnListFilter = returnList.GenerateFilter(dialogBL->GetOrmasDal());
							vecReturnList.clear();
							vecReturnList = dialogBL->GetAllDataForClass<BusinessLayer::ReturnListView>(errorMessage, returnListFilter);
							if (vecReturnList.size() > 0)
							{
								for each (auto listItem in vecReturnList)
								{
									if (productCountRet.find(listItem.GetProductID()) != productCountRet.end())
									{
										productCountRet.find(listItem.GetProductID())->second = productCountRet.find(listItem.GetProductID())->second + listItem.GetCount();
										productSumRet.find(listItem.GetProductID())->second = productSumRet.find(listItem.GetProductID())->second + listItem.GetSum();
									}
									else
									{
										productCountRet.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
										productSumRet.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
									}
								}
							}
						}


						if (productCount.size() != productSum.size())
						{
							QMessageBox::information(NULL, QString(tr("Info")),
								QString(tr("Calculation is failed. Please restart the report!")),
								QString(tr("Ok")));
							return;
						}

						for each (auto mapCountItem in productCount)
						{
							product.Clear();
							product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
							nCost.Clear();
							nCost.GetNetCostByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);

							if (productCountRet.find(mapCountItem.first) != productCountRet.end())
							{
								sumRet += productSumRet.find(mapCountItem.first)->second;
							}

							sum += productSum.find(mapCountItem.first)->second;
							tableBody += "<tr>";
							tableBody += "<td>" + QString::number(mapCountItem.first) + "</td>";
							tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
							tableBody += "<td>" + QString::number(mapCountItem.second) + "</td>";
							tableBody += "<td>" + QString::number(productSum.find(mapCountItem.first)->second, 'f', 3) + "</td>";
							if (productCountRet.find(mapCountItem.first) != productCountRet.end())
							{
								tableBody += "<td>" + QString::number(productCountRet.find(mapCountItem.first)->second) + "</td>";
							}
							else
							{
								tableBody += "<td> 0 </td>";
							}
							if (productCountRet.find(mapCountItem.first) != productCountRet.end())
							{
								tableBody += "<td>" + QString::number(productSumRet.find(mapCountItem.first)->second, 'f', 3) + "</td>";
							}
							else
							{
								tableBody += "<td> 0 </td>";
							}
							if (productCountRet.find(mapCountItem.first) != productCountRet.end())
							{
								tableBody += "<td>" + QString::number(mapCountItem.second - productCountRet.find(mapCountItem.first)->second) + "</td>";
							}
							else
							{
								tableBody += "<td>" + QString::number(mapCountItem.second) + "</td>";
							}
							if (productCountRet.find(mapCountItem.first) != productCountRet.end())
							{
								tableBody += "<td>" + QString::number(productSum.find(mapCountItem.first)->second - productSumRet.find(mapCountItem.first)->second) + "</td>";
							}
							else
							{
								tableBody += "<td>" + QString::number(productSum.find(mapCountItem.first)->second, 'f', 3) + "</td>";
							}


							tableBody += "</tr>";
						}

						BusinessLayer::Relation rel;
						BusinessLayer::User user;
						BusinessLayer::Payment payment;
						double sumCashier = 0;
						std::string filterCients = "";
						std::string filterPayments = "";
						std::string allFilters = "";
						std::vector<int> allClients;
						std::vector<BusinessLayer::PaymentView> allPaymens;
						std::vector<std::string> filterList;
						allClients.clear();
						allClients = rel.GetUser2IDByUser1ID(dialogBL->globalVar, dialogBL->GetOrmasDal(), expeditor.GetID(), errorMessage);
						if (allClients.size() > 0)
						{
							filterPayments.clear();
							payment.SetStatusID(status.GetID());
							filterPayments = payment.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toStdString(), tillDateEdit->text().toStdString());
							filterCients.clear();
							filterCients = user.GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), allClients);

							filterList.push_back(filterPayments);
							filterList.push_back(filterCients);
							allFilters.clear();
							allFilters = dialogBL->GetOrmasDal().ConcatenateFilters(filterList);
							allPaymens.clear();
							allPaymens = dialogBL->GetAllDataForClass<BusinessLayer::PaymentView>(errorMessage, allFilters);
							if (allPaymens.size() > 0)
							{
								for each (auto paymenyItem in allPaymens)
								{
									sumCashier += paymenyItem.GetValue();
								}
							}
						}
						tableBody += "<tr>";
						tableBody += "<td></td>";
						tableBody += "<td></td>";
						tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка") + "</td>";
						tableBody += "<td>" + QString::number(sum, 'f', 3) + "</td>";
						tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка с вычетом возврата") + "</td>";
						tableBody += "<td>" + QString::number(sum - sumRet, 'f', 3) + "</td>";
						tableBody += "<td>" + QString::fromWCharArray(L"Оплачено в кассу") + "</td>";
						tableBody += "<td>" + QString::number(sumCashier, 'f', 3) + "</td>";
						tableBody += "</tr>";
						tableBody += "</table>";
						

					}
					else
					{
						tableBody += "Нет данных!";
					}
				}
				BusinessLayer::Relation relation;
				relation.SetUser1ID(expeditor.GetID());
				std::string relFilter = relation.GenerateFilter(dialogBL->GetOrmasDal());
				std::vector<BusinessLayer::RelationView> relVec = dialogBL->GetAllDataForClass<BusinessLayer::RelationView>(errorMessage, relFilter);
				std::vector<int> clientIDVec;
				for each (auto relItem in relVec)
				{
					clientIDVec.push_back(relItem.GetUser2ID());
				}
				BusinessLayer::User user;
				std::string userINFilter = user.GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), clientIDVec);
				std::vector<BusinessLayer::BalanceView> balaceVec = dialogBL->GetAllDataForClass<BusinessLayer::BalanceView>(errorMessage, userINFilter);
				double clientBalance = 0;
				for each (auto balanceItem in balaceVec)
				{
					clientBalance += balanceItem.GetCurrentBalance();
				}
				tableBody += "<div>";
				tableBody += "<label>" + QString::fromWCharArray(L"Суммарная задолженность всех клиентов этого экспедитора:") + "</label>";
				tableBody += "<b>" + QString::number(clientBalance, 'f', 3) + "</b>";
				tableBody += "</div>";
				tableBody += "<br/><br/>";
				documentBody += tableBody;
			}
		}
		else
		{
			std::vector<int> employeeIDList;
			BusinessLayer::Employee employee;
			for each (BusinessLayer::EmployeeView expeditor in vecEmployee)
			{
				employeeIDList.push_back(expeditor.GetID());
			}
			std::string empIDListFilter = employee.GenerateINFilterForEmployee(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeIDList);
			
			ret.Clear();
			ret.SetStatusID(status.GetID());
			std::string filterRet = ret.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
			std::vector<std::string> filterList;
			filterList.push_back(filterRet);
			filterList.push_back(empIDListFilter);
			filterRet = dialogBL->GetOrmasDal().ConcatenateFilters(filterList);
			std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRet);
			
			order.Clear();
			order.SetStatusID(status.GetID());
			std::string filter = order.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
			std::vector<std::string> filterRetList;
			filterRetList.push_back(filter);
			filterRetList.push_back(empIDListFilter);
			filter = dialogBL->GetOrmasDal().ConcatenateFilters(filterRetList);
			std::vector<BusinessLayer::OrderView> vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);
			
			//generating report
			if (vecOrder.size() > 0)
			{
				for each (auto item in vecOrder)
				{
					orderList.Clear();
					orderListFilter.clear();
					orderList.SetOrderID(item.GetID());
					orderListFilter = orderList.GenerateFilter(dialogBL->GetOrmasDal());
					vecOrderList.clear();
					vecOrderList = dialogBL->GetAllDataForClass<BusinessLayer::OrderListView>(errorMessage, orderListFilter);
					if (vecOrderList.size() > 0)
					{
						for each (auto listItem in vecOrderList)
						{
							if (totalCount.find(listItem.GetProductID()) != totalCount.end())
							{
								totalCount.find(listItem.GetProductID())->second = totalCount.find(listItem.GetProductID())->second + listItem.GetCount();
								totalSum.find(listItem.GetProductID())->second = totalSum.find(listItem.GetProductID())->second + listItem.GetSum();
							}
							else
							{
								totalCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
								totalSum.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
							}
						}
					}
				}

				for each (auto item in vecReturn)
				{
					returnList.Clear();
					returnListFilter.clear();
					returnList.SetReturnID(item.GetID());
					returnListFilter = returnList.GenerateFilter(dialogBL->GetOrmasDal());
					vecReturnList.clear();
					vecReturnList = dialogBL->GetAllDataForClass<BusinessLayer::ReturnListView>(errorMessage, returnListFilter);
					if (vecReturnList.size() > 0)
					{
						for each (auto listItem in vecReturnList)
						{
							if (productCountRet.find(listItem.GetProductID()) != productCountRet.end())
							{
								productCountRet.find(listItem.GetProductID())->second = productCountRet.find(listItem.GetProductID())->second + listItem.GetCount();
								productSumRet.find(listItem.GetProductID())->second = productSumRet.find(listItem.GetProductID())->second + listItem.GetSum();
							}
							else
							{
								productCountRet.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
								productSumRet.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
							}
						}
					}
				}


				if (totalCount.size() != totalSum.size())
				{
					QMessageBox::information(NULL, QString(tr("Info")),
						QString(tr("Calculation is failed. Please restart the report!")),
						QString(tr("Ok")));
						return;
				}
				
				tableBody += "Суммарная продажа продуктов: ";

				tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"ID продукта") + "< / b>< / th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта")+"</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Продажа количество")+"</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Продажа сумма")+"</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Возврат количество")+"</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Возврат сумма")+"</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Итого количество")+"</b></th>";
				tableBody += "<th><b>" + QString::fromWCharArray(L"Итого сумма")+"</b></th>";
				for each (auto mapCountItem in totalCount)
				{
					product.Clear();
					product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
					nCost.Clear();
					nCost.GetNetCostByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
					
					if (totalReturnCount.find(mapCountItem.first) != totalReturnCount.end())
					{
						sumRet += totalReturnSum.find(mapCountItem.first)->second;
					}
					
					sum += totalSum.find(mapCountItem.first)->second;
					tableBody += "<tr>";
					tableBody += "<td>" + QString::number(mapCountItem.first) + "</td>";
					tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
					tableBody += "<td>" + QString::number(mapCountItem.second) + "</td>";
					tableBody += "<td>" + QString::number(totalSum.find(mapCountItem.first)->second, 'f', 3) + "</td>";
					if (totalReturnCount.find(mapCountItem.first) != totalReturnCount.end())
					{
						tableBody += "<td>" + QString::number(totalReturnCount.find(mapCountItem.first)->second) + "</td>";
					}
					else
					{
						tableBody += "<td> 0 </td>";
					}
					if (totalReturnCount.find(mapCountItem.first) != totalReturnCount.end())
					{
						tableBody += "<td>" + QString::number(totalReturnSum.find(mapCountItem.first)->second, 'f', 3) + "</td>";
					}
					else
					{
						tableBody += "<td> 0 </td>";
					}
					if (totalReturnCount.find(mapCountItem.first) != totalReturnCount.end())
					{
						tableBody += "<td>" + QString::number(mapCountItem.second - totalReturnCount.find(mapCountItem.first)->second) + "</td>";
					}
					else
					{
						tableBody += "<td>" + QString::number(mapCountItem.second) + "</td>";
					}
					if (totalReturnCount.find(mapCountItem.first) != totalReturnCount.end())
					{
						tableBody += "<td>" + QString::number(totalSum.find(mapCountItem.first)->second - totalReturnSum.find(mapCountItem.first)->second) + "</td>";
					}
					else
					{
						tableBody += "<td>" + QString::number(totalSum.find(mapCountItem.first)->second, 'f', 3) + "</td>";
					}
					
					tableBody += "</tr>";
				}

				tableBody += "<tr>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "<td></td>";
				tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка") + "</td>";
				tableBody += "<td>" + QString::number(sum, 'f', 3) + "</td>";
				tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка с вычетом возврата") + "</td>";
				tableBody += "<td>" + QString::number(sum - sumRet, 'f', 3) + "</td>";
				tableBody += "</tr>";
				tableBody += "</table>";
			

			}
			else
			{
				tableBody += "Нет данных!";
			}
			
			double clientBalance = 0;
			for each (auto expID in employeeIDList)
			{
				BusinessLayer::Relation relation;
				relation.SetUser1ID(expID);
				std::string relFilter = relation.GenerateFilter(dialogBL->GetOrmasDal());
				std::vector<BusinessLayer::RelationView> relVec = dialogBL->GetAllDataForClass<BusinessLayer::RelationView>(errorMessage, relFilter);
				std::vector<int> clientIDVec;
				for each (auto relItem in relVec)
				{
					clientIDVec.push_back(relItem.GetUser2ID());
				}
				BusinessLayer::User user;
				std::string userINFilter = user.GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), clientIDVec);
				std::vector<BusinessLayer::BalanceView> balaceVec = dialogBL->GetAllDataForClass<BusinessLayer::BalanceView>(errorMessage, userINFilter);
				
				for each (auto balanceItem in balaceVec)
				{
					clientBalance += balanceItem.GetCurrentBalance();
				}
				
			}
			tableBody += "<div>";
			tableBody += "<label>" + QString::fromWCharArray(L"Суммарная задолженность всех клиентов:") + "</label>";
			tableBody += "<b>" + QString::number(clientBalance, 'f', 3) + "</b>";
			tableBody += "</div>";
			tableBody += "<br/><br/>";
			documentBody += tableBody;
		}
		QDateTime currentDateTime = QDateTime::currentDateTime();
		reportText.replace(QString("DocumentBodyPh"), documentBody, Qt::CaseInsensitive);
		reportText.replace(QString("ReportDatePh"), currentDateTime.toString("dd.MM.yyyy hh:mm"), Qt::CaseInsensitive);
		reportText.replace(QString("UserNamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
		reportText.replace(QString("UserSurnamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
		docForm->webEngineView->setHtml(reportText);
		docForm->SetContent(reportText);
		docForm->webEngineView->show();
		docForm->show();
	}
	Close();
}

void GenerateSalesRep::Close()
{
	this->parentWidget()->close();
}
