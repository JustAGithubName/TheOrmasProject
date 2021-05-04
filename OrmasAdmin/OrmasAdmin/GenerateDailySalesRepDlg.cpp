#include "stdafx.h"
#include "GenerateDailySalesRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include "DataForm.h"

GenerateDailySalesRep::GenerateDailySalesRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();

	QDate currentDate = QDate::currentDate();
	forDateEdit->setDate(currentDate);

	vInt = new QIntValidator(0, 1000000000, this);
	employeeEdit->setValidator(vInt);

	

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateDailySalesRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateDailySalesRep::Close);
	QObject::connect(empButton, &QPushButton::released, this, &GenerateDailySalesRep::OpenEmpDlg);
}

GenerateDailySalesRep::~GenerateDailySalesRep()
{
	delete vInt;
}

void GenerateDailySalesRep::SetID(int ID, QString childName)
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
					empNamePh->setText(user.GetName().c_str());
					empSurnamePh->setText(user.GetSurname().c_str());
					empPhonePh->setText(user.GetPhone().c_str());
				}
			}
		}
	}
}

void GenerateDailySalesRep::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print daily sales report"));
	QMdiSubWindow *generateProfRepWindow = new QMdiSubWindow;
	generateProfRepWindow->setWidget(docForm);
	generateProfRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	generateProfRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	mainForm->mdiArea->addSubWindow(generateProfRepWindow);

	//read template
	QFile file;
	file.setFileName(":/docs/daily_sales.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find daily sales report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();

	BusinessLayer::Order order;
	BusinessLayer::OrderList orderList;
	std::string orderListFilter;
	std::map<int, double> productCount;
	std::map<int, double> productSum;
	std::map<int, std::string> clientMap;
	std::map<std::pair<int,int>, double> productClient;
	std::vector<BusinessLayer::OrderListView> vecOrderList;

	BusinessLayer::Return ret;
	BusinessLayer::ReturnList returnList;
	std::string returnListFilter;
	std::map<int, double> productCountRet;
	std::map<int, double> productSumRet;
	std::vector<BusinessLayer::ReturnListView> vecReturnList;

	BusinessLayer::Transport transport;
	BusinessLayer::TransportList transportList;
	BusinessLayer::TransportChangeLog tChangeLog;
	
	BusinessLayer::ConsumeProduct conProd;
	BusinessLayer::ConsumeProductList conProdList;
	std::string conProdListFilter;
	std::map<int, double> productCountCon;
	std::map<int, double> productSumCon;
	std::vector<BusinessLayer::ConsumeProductListView> vecConProdList;

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

	std::map<int, double> totalConsumeCount;
	std::map<int, double> totalConsumeSum;

	std::map<int, double> totalTransportCount;
	std::map<int, double> totalTransportLogCount;

	reportText.replace(QString("datePh"), forDateEdit->text(), Qt::CaseInsensitive);
	

	tableBody.clear();

	ret.Clear();
	ret.SetStatusID(status.GetID());
	ret.SetEmployeeID(employeeEdit->text().toInt());
	std::string filterRet = ret.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), forDateEdit->text().toUtf8().constData(), forDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRet);

	conProd.Clear();
	conProd.SetStatusID(status.GetID());
	conProd.SetEmployeeID(employeeEdit->text().toInt());
	std::string consumeProd = conProd.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), forDateEdit->text().toUtf8().constData(), forDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ConsumeProductView> vecConsume = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductView>(errorMessage, consumeProd);

	order.Clear();
	order.SetStatusID(status.GetID());
	order.SetEmployeeID(employeeEdit->text().toInt());
	std::string filter = order.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), forDateEdit->text().toUtf8().constData(), forDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::OrderView> vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);

	transport.Clear();
	std::vector<BusinessLayer::TransportListView> vecTrans;
	if (transport.GetTransportByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeEdit->text().toInt(), errorMessage))
	{
		transportList.Clear();
		transportList.SetTransportID(transport.GetID());
		std::string filterTran = transportList.GenerateFilter(dialogBL->GetOrmasDal());
		vecTrans = dialogBL->GetAllDataForClass<BusinessLayer::TransportListView>(errorMessage, filterTran);
	}

	if (vecOrder.size() == 0 || vecTrans.size() == 0)
	{
		tableBody += "Нет данных!";
	}
	else
	{
		//generating report
		if (vecOrder.size() > 0)
		{
			
			if (vecTrans.size() > 0)
			{
				for each (auto listItem in vecTrans)
				{
					tChangeLog.Clear();
					tChangeLog.SetTransportID(transport.GetID());
					tChangeLog.SetProductID(listItem.GetProductID());
					tChangeLog.SetLogDate(forDateEdit->text().toUtf8().constData());
					std::string filterTranLog = tChangeLog.GenerateFilterForDateLess(dialogBL->GetOrmasDal());
					std::vector<BusinessLayer::TransportChangeLog> vecTransLog = dialogBL->GetAllDataForClass<BusinessLayer::TransportChangeLog>(errorMessage, filterTranLog);
					if (vecTransLog.size() > 0)
					{
						totalTransportLogCount.insert(std::pair<int, double>(listItem.GetProductID(), vecTransLog.at(0).GetCount()));
					}
					else
					{
						totalTransportLogCount.insert(std::pair<int, double>(listItem.GetProductID(), 0));
					}
					filterTranLog.clear();
					vecTransLog.clear();
				}
			}

			for each (auto item in vecOrder)
			{
				clientMap.insert(std::pair<int, std::string>(item.GetClientID(), item.GetClientName() + " " + item.GetClientSurname() + " " + item.GetClientPhone()));
				//produt-count map
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
							sum += listItem.GetSum();
							productClient.insert(std::make_pair(std::make_pair(item.GetClientID(), listItem.GetProductID()), listItem.GetCount()));
						}
						else
						{
							productCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							productSum.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
							sum += listItem.GetSum();
							productClient.insert(std::make_pair(std::make_pair(item.GetClientID(), listItem.GetProductID()), listItem.GetCount()));
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

			for each (auto item in vecConsume)
			{
				conProdList.Clear();
				conProdListFilter.clear();
				conProdList.SetConsumeProductID(item.GetID());
				conProdListFilter = conProdList.GenerateFilter(dialogBL->GetOrmasDal());
				vecConProdList.clear();
				vecConProdList = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductListView>(errorMessage, conProdListFilter);
				if (vecConProdList.size() > 0)
				{
					for each (auto listItem in vecConProdList)
					{
						if (productCountCon.find(listItem.GetProductID()) != productCountCon.end())
						{
							productCountCon.find(listItem.GetProductID())->second = productCountCon.find(listItem.GetProductID())->second + listItem.GetCount();
							productSumCon.find(listItem.GetProductID())->second = productSumCon.find(listItem.GetProductID())->second + listItem.GetSum();
						}
						else
						{
							productCountCon.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							productSumCon.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
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


						
			BusinessLayer::Employee expeditor;
			if (!expeditor.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeEdit->text().toInt(), errorMessage))
				return;
		
			tableBody += QString::fromWCharArray(L"Сотрудник: ");
			tableBody += expeditor.GetSurname().c_str();
			tableBody += " ";
			tableBody += expeditor.GetName().c_str();
			tableBody += "  ";
			tableBody += QString::fromWCharArray(L"Телефон: ");
			tableBody += expeditor.GetPhone().c_str();
			tableBody += "<br/>";

			QString expeditorProfile = QString(expeditor.GetSurname().c_str());
			expeditorProfile += " ";
			expeditorProfile += QString(expeditor.GetName().c_str());
			reportText.replace(QString("ExpeditorPh"), expeditorProfile, Qt::CaseInsensitive);

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Остаток на начало") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Приход") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Расход") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Остаток на конец") + "</b></th>";

			
			double conCount = 0;
			double ordCount = 0;
			double tranCount = 0;
			for each (auto mapCountItem in totalTransportLogCount)
			{
				conCount = 0;
				ordCount = 0;
				tranCount = 0;
				product.Clear();
				product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
				nCost.Clear();
				nCost.GetNetCostByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);

				//sum += productSum.find(mapCountItem.first)->second;
				tableBody += "<tr>";
				tableBody += "<td>" + QString::number(mapCountItem.first) + "</td>";
				tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
				tableBody += "<td>" + QString::number(mapCountItem.second) + "</td>";
				
				if (productCountCon.find(mapCountItem.first) != productCountCon.end())
				{
					tableBody += "<td>" + QString::number(productCountCon.find(mapCountItem.first)->second) + "</td>";
				}
				else
				{
					tableBody += "<td> 0 </td>";
				}
				if (productCount.find(mapCountItem.first) != productCount.end())
				{
					tableBody += "<td>" + QString::number(productCount.find(mapCountItem.first)->second) + "</td>";
				}
				else
				{
					tableBody += "<td> 0 </td>";
				}
				if (productCountCon.size() > 0)
				{
					if (productCountCon.find(mapCountItem.first) != productCountCon.end())
					{
						conCount = productCountCon.find(mapCountItem.first)->second;
					}
					else
					{
						conCount = 0;
					}
				}
				if (productCount.size() > 0)
				{
					if (productCount.find(mapCountItem.first) != productCount.end())
					{
						ordCount = productCount.find(mapCountItem.first)->second;
					}
					else
					{
						ordCount = 0;
					}
				}
					
				tranCount = mapCountItem.second;
				tableBody += "<td>" + QString::number(tranCount + conCount - ordCount, 'f', 3) + "</td>";
				
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
				filterPayments = payment.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), forDateEdit->text().toStdString(), forDateEdit->text().toStdString());
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
			tableBody += "<td></td>";
			tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка") + "</td>";
			tableBody += "<td>" + QString::number(sum, 'f', 3) + "</td>";
			tableBody += "<td></td>";
			tableBody += "</tr>";
			tableBody += "</table>";
			tableBody += "<br/><br/>";

		}
		else
		{
			tableBody += "Нет данных!";
		}

		// market hash
		BusinessLayer::Client client;
		tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
		int mapCount = 0;
		tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";
		for each (auto mapCountItem in totalTransportLogCount)
		{
			product.Clear();
			product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
			tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>" + QString(product.GetName().c_str()) + "</div></b></th>";
			mapCount++;
		}
		tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Сумма") + "</div></b></th>";
		
		int productCounter = 1;
		double clientSum = 0;
		for (std::map<int, std::string>::iterator clientIt = clientMap.begin(); clientIt != clientMap.end(); clientIt++)
		{
			clientSum = 0;
			
			tableBody += "<tr>";
			tableBody += "<td>" + QString(clientIt->second.c_str()) + "</td>";
			for (std::map<int, double>::iterator tranIt = totalTransportLogCount.begin(); tranIt != totalTransportLogCount.end(); tranIt++)
			{
				product.Clear();
				if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), tranIt->first, errorMessage))
					continue;
				if (productClient.find(std::pair<int, int>(clientIt->first, tranIt->first)) != productClient.end())
				{
					tableBody += "<td>" + QString::number(productClient.find(std::pair<int, int>(clientIt->first, tranIt->first))->second) + "</td>";
					clientSum += productClient.find(std::pair<int, int>(clientIt->first, tranIt->first))->second*product.GetPrice();
				}
				else
				{
					tableBody += "<td></td>";
				}
				productCounter++;
			}
			if (clientSum>0)
				tableBody += "<td>" + QString::number(clientSum) + "</td>";
			tableBody += "</tr>";
		}

		tableBody += "</table>";
	}
	documentBody += tableBody;


	QDateTime currentDateTime = QDateTime::currentDateTime();
	reportText.replace(QString("DocumentBodyPh"), documentBody, Qt::CaseInsensitive);
	reportText.replace(QString("DateReportPh"), currentDateTime.toString("dd.MM.yyyy hh:mm"), Qt::CaseInsensitive);
	reportText.replace(QString("UserNamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	reportText.replace(QString("UserSurnamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();

	Close();
}

void GenerateDailySalesRep::Close()
{
	this->parentWidget()->close();
}

void GenerateDailySalesRep::OpenEmpDlg()
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

	BusinessLayer::Role *role = new BusinessLayer::Role();
	role->SetName("EXPEDITOR");
	std::string roleFilter = dialogBL->GenerateFilter<BusinessLayer::Role>(role);
	std::vector<BusinessLayer::Role> roleVector = dialogBL->GetAllDataForClass<BusinessLayer::Role>(errorMessage, roleFilter);

	if (roleVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not define the role for this employee!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	BusinessLayer::Employee *employee = new BusinessLayer::Employee();
	employee->SetRoleID(roleVector.at(0).GetID());
	std::string employeeFilter = dialogBL->GenerateFilter<BusinessLayer::Employee>(employee);
	std::vector<BusinessLayer::EmployeeView> employeeVector = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
	if (employeeVector.size() == 0)
	{
		delete role;
		QString message = tr("Sorry could not find employee with \"expeditor\" role!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(message),
			QString(tr("Ok")));
		errorMessage = "";
		return;
	}

	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(dialogBL->globalVar, dialogBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	std::string filter = "";

	if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
	{
		filter = "";
	}
	else
	{
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mainForm->GetLoggedUser()->GetID(), errorMessage);
		if (0 < branchID)
		{
			BusinessLayer::Employee employee;
			std::vector<int> empID = ceRel.GetAllEmployeeIDByBranchID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branchID, errorMessage);
			if (empID.size() > 0)
			{
				filter = employee.GenerateINFilterForEmployee(dialogBL->globalVar, dialogBL->GetOrmasDal(), empID);
			}
		}
	}

	std::vector<std::string> empFilterVec;
	empFilterVec.push_back(employeeFilter);
	empFilterVec.push_back(filter);

	employeeFilter = dialogBL->ConcatenateFilters(empFilterVec);

	dForm->FillTable<BusinessLayer::EmployeeView>(errorMessage, employeeFilter);
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

