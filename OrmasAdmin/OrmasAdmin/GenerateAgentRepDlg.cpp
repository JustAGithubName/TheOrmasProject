#include "stdafx.h"
#include "GenerateAgentRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include "DataForm.h"

GenerateAgentRep::GenerateAgentRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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
			if (month > 11)
			{
				prevFromMonth = "01.";
			}
			else
			{
				prevFromMonth = "01.0";
			}
			prevFromMonth += std::to_string(month - 2);
			prevFromMonth += ".";
			prevFromMonth += std::to_string(year);
			pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
			coundOfDays = pastMonthDate.daysInMonth();
			prevTillMonth = std::to_string(coundOfDays);
			if (month > 11)
			{
				prevTillMonth += ".";
			}
			else
			{
				prevTillMonth += ".0";
			}
			prevTillMonth += std::to_string(month - 2);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(year);
		}
	}
	fromDateEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	tillDateEdit->setDate(QDate::fromString(endDate.c_str(), "dd.MM.yyyy"));

	vInt = new QIntValidator(0, 1000000000, this);
	employeeEdit->setValidator(vInt);



	QObject::connect(okBtn, &QPushButton::released, this, &GenerateAgentRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateAgentRep::Close);
	QObject::connect(empButton, &QPushButton::released, this, &GenerateAgentRep::OpenEmpDlg);
}

GenerateAgentRep::~GenerateAgentRep()
{
	delete vInt;
}

void GenerateAgentRep::SetID(int ID, QString childName)
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

void GenerateAgentRep::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}

	BusinessLayer::Status statusRet;
	if (!statusRet.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "RETURN", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}

	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print monthly sales report"));
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

	std::vector<int> clientID;
	BusinessLayer::Relation relation;
	clientID = relation.GetUser2IDByUser1ID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeEdit->text().toInt(), errorMessage);
	BusinessLayer::User user;
	std::string clientFilter = user.GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), clientID);

	BusinessLayer::Payment payment;

	BusinessLayer::Order order;
	BusinessLayer::OrderList orderList;
	std::string orderListFilter;
	std::map<int, double> productCount;
	std::map<int, double> productSum;
	std::vector<BusinessLayer::OrderListView> vecOrderList;
	std::map<int, std::string> orderDateMap;
	std::map<std::pair< std::string, int>, double> productOrderMap;

	BusinessLayer::Order orderRet;
	BusinessLayer::OrderList orderListRet;
	std::string orderRetListFilter;
	std::map<int, double> productRetCount;
	std::map<int, double> productRetSum;
	std::vector<BusinessLayer::OrderListView> vecOrderListRet;
	std::map<int, std::string> orderRetDateMap;
	std::map<std::pair< std::string, int>, double> productRetOrderMap;


	BusinessLayer::Return ret;
	BusinessLayer::ReturnList returnList;
	std::string returnListFilter;
	std::map<int, double> productCountRet;
	std::map<int, double> productSumRet;
	std::vector<BusinessLayer::ReturnListView> vecReturnList;
	std::map<int, std::string> returnDateMap;
	std::map<std::pair< std::string, int>, double> productReturnMap;

	BusinessLayer::Return retRet;
	BusinessLayer::ReturnList returnListRet;
	std::string returnListFilterRet;
	std::map<int, double> productRetCountRet;
	std::map<int, double> productRetSumRet;
	std::vector<BusinessLayer::ReturnListView> vecReturnListRet;
	std::map<int, std::string> returnRetDateMap;
	std::map<std::pair< std::string, int>, double> productReturnRetMap;

	BusinessLayer::ConsumeProduct consume;
	BusinessLayer::ConsumeProductList consumeList;
	std::string consumeListFilter;
	std::map<int, double> productCountCon;
	std::map<int, double> productSumCon;
	std::vector<BusinessLayer::ConsumeProductListView> vecConsumeList;
	std::map<int, std::string> consumeDateMap;
	std::map<std::pair< std::string, int>, double> productConsumeMap;

	BusinessLayer::ConsumeProduct consumeRet;
	BusinessLayer::ConsumeProductList consumeListRet;
	std::string consumeListFilterRet;
	std::map<int, double> productRetCountCon;
	std::map<int, double> productRetSumCon;
	std::vector<BusinessLayer::ConsumeProductListView> vecConsumeListRet;
	std::map<int, std::string> consumeRetDateMap;
	std::map<std::pair< std::string, int>, double> productRetConsumeMap;


	BusinessLayer::TransportHistory startHistory;
	BusinessLayer::TransportHistory endHistory;
	std::string historyFilter;
	std::map<int, double> productCountStart;
	std::map<int, double> productSumStart;
	std::map<int, double> productCountEnd;
	std::map<int, double> productSumEnd;
	std::vector<BusinessLayer::TransportHistory> vecStartHisList;
	std::vector<BusinessLayer::TransportHistory> vecEndHisList;

	BusinessLayer::Transport transport;
	BusinessLayer::TransportList transportList;
	std::vector<BusinessLayer::TransportListView> vecTranList;
	std::map<int, double> productIDCycle;

	BusinessLayer::Client client;
	std::vector<BusinessLayer::ClientView> vecClientView;
	std::map<int, std::string> clientInfoMap;

	BusinessLayer::Product product;
	BusinessLayer::NetCost nCost;
	double sum = 0;
	double sumRet = 0;
	QString documentBody;
	QString tableBody;

	std::map<int, double> totalCount;
	std::map<int, double> totalSum;

	std::map<int, double> debt;
	std::map<int, double> cred;

	std::map<int, double> totalReturnCount;
	std::map<int, double> totalReturnSum;

	reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
	reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);

	tableBody.clear();

	ret.Clear();
	ret.SetStatusID(status.GetID());
	ret.SetEmployeeID(employeeEdit->text().toInt());
	std::string filterRet = ret.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRet);

	retRet.Clear();
	retRet.SetStatusID(statusRet.GetID());
	retRet.SetEmployeeID(employeeEdit->text().toInt());
	std::string filterRetRet = retRet.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ReturnView> vecReturnRet = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRetRet);

	order.Clear();
	order.SetStatusID(status.GetID());
	order.SetEmployeeID(employeeEdit->text().toInt());
	std::string filter = order.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::OrderView> vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);

	orderRet.Clear();
	orderRet.SetStatusID(statusRet.GetID());
	orderRet.SetEmployeeID(employeeEdit->text().toInt());
	std::string filterOrdRet = orderRet.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::OrderView> vecOrderRet = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filterOrdRet);

	consume.Clear();
	consume.SetStatusID(status.GetID());
	consume.SetEmployeeID(employeeEdit->text().toInt());
	std::string filterCon = consume.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ConsumeProductView> vecConsume = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductView>(errorMessage, filterCon);

	consumeRet.Clear();
	consumeRet.SetStatusID(statusRet.GetID());
	consumeRet.SetEmployeeID(employeeEdit->text().toInt());
	std::string filterConRet = consumeRet.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ConsumeProductView> vecConsumeRet = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductView>(errorMessage, filterConRet);

	payment.Clear();
	payment.SetStatusID(status.GetID());
	std::string filterforPayment = payment.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<std::string> filterList;
	filterList.push_back(clientFilter);
	filterList.push_back(filterforPayment);
	filterforPayment = dialogBL->GetOrmasDal().ConcatenateFilters(filterList);
	std::vector<BusinessLayer::PaymentView> vecPaymet = dialogBL->GetAllDataForClass<BusinessLayer::PaymentView>(errorMessage, filterforPayment);

	
	vecClientView = dialogBL->GetAllDataForClass<BusinessLayer::ClientView>(errorMessage, clientFilter);


	std::string prevMonthStart;
	std::string prevMonthEnd;
	CalculatePrevMonth(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), prevMonthStart, prevMonthEnd);

	transport.Clear();
	if (transport.GetTransportByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeEdit->text().toInt(), errorMessage))
	{
		startHistory.Clear();
		startHistory.SetTransportID(transport.GetID());
		startHistory.SetFromDate(prevMonthEnd);
		std::string filterTranStart = startHistory.GenerateFilter(dialogBL->GetOrmasDal());
		vecStartHisList = dialogBL->GetAllDataForClass<BusinessLayer::TransportHistory>(errorMessage, filterTranStart);

		endHistory.Clear();
		endHistory.SetTransportID(transport.GetID());
		endHistory.SetTillDate(tillDateEdit->text().toStdString());
		std::string filterTranEnd = endHistory.GenerateFilter(dialogBL->GetOrmasDal());
		vecEndHisList = dialogBL->GetAllDataForClass<BusinessLayer::TransportHistory>(errorMessage, filterTranEnd);

		transportList.Clear();
		transportList.SetTransportID(transport.GetID());
		std::string filterTranList = transportList.GenerateFilter(dialogBL->GetOrmasDal());
		vecTranList = dialogBL->GetAllDataForClass<BusinessLayer::TransportListView>(errorMessage, filterTranList);
	}

	
	if (vecOrder.size() == 0 && vecConsume.size() == 0 && vecStartHisList.size() == 0)
	{
		tableBody += "Нет данных!";
	}
	else
	{
		BusinessLayer::Employee expeditor;
		if (!expeditor.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeEdit->text().toInt(), errorMessage))
			return;
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

		tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
		tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
		tableBody += "<th><b>" + QString::fromWCharArray(L"В транспорте на начало") + "</b></th>";
		tableBody += "<th><b>" + QString::fromWCharArray(L"Приход") + "</b></th>";
		tableBody += "<th><b>" + QString::fromWCharArray(L"Расход") + "</b></th>";
		tableBody += "<th><b>" + QString::fromWCharArray(L"В транспорте на конец") + "</b></th>";

		if (vecClientView.size() > 0)
		{
			for each (auto cl in vecClientView)
			{
				if (clientInfoMap.find(cl.GetID()) != clientInfoMap.end())
				{
					
				}
				else
				{
					std::string user;
					user = cl.GetName().c_str();
					user += " ";
					user += cl.GetSurname().c_str();
					user += " ";
					user += cl.GetPhone().c_str();
					clientInfoMap.insert(std::make_pair(cl.GetID(), user));
				}

			}
		}

		if (vecTranList.size() > 0)
		{
			for each (auto item in vecTranList)
			{
				if (productIDCycle.find(item.GetProductID()) != productIDCycle.end())
				{
					productIDCycle.find(item.GetProductID())->second = productIDCycle.find(item.GetProductID())->second + item.GetCount();
				}
				else
				{
					productIDCycle.insert(std::make_pair(item.GetProductID(), item.GetCount()));
				}

			}
		}

		if (vecStartHisList.size() > 0)
		{
			for each (auto item in vecStartHisList)
			{
				if (productCountStart.find(item.GetProductID()) != productCountStart.end())
				{
					productCountStart.find(item.GetProductID())->second = productCountStart.find(item.GetProductID())->second + item.GetCount();
					productSumStart.find(item.GetProductID())->second = productSumStart.find(item.GetProductID())->second + item.GetSum();
				}
				else
				{
					productCountStart.insert(std::make_pair(item.GetProductID(), item.GetCount()));
					productSumStart.insert(std::make_pair(item.GetProductID(), item.GetSum()));
				}

			}
		}
		
		if (vecEndHisList.size() > 0)
		{
			for each (auto item in vecEndHisList)
			{
				if (productCountEnd.find(item.GetProductID()) != productCountEnd.end())
				{
					productCountEnd.find(item.GetProductID())->second = productCountEnd.find(item.GetProductID())->second + item.GetCount();
					productSumEnd.find(item.GetProductID())->second = productSumEnd.find(item.GetProductID())->second + item.GetSum();
				}
				else
				{
					productCountEnd.insert(std::make_pair(item.GetProductID(), item.GetCount()));
					productSumEnd.insert(std::make_pair(item.GetProductID(), item.GetSum()));
				}

			}
		}

		if (vecOrder.size() > 0)
		{
			for each (auto item in vecOrder)
			{
				orderDateMap.insert(std::make_pair(item.GetID(), item.GetDate()));
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
						if (productOrderMap.find(std::make_pair(item.GetDate(), listItem.GetProductID())) != productOrderMap.end())
						{
							productOrderMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second = productOrderMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second + listItem.GetCount();
						}
						else
						{
							productOrderMap.insert(std::make_pair(std::make_pair(item.GetDate(), listItem.GetProductID()), listItem.GetCount()));
						}
					}
				}
				if (debt.find(item.GetClientID()) != debt.end())
				{
					debt.find(item.GetClientID())->second = debt.find(item.GetClientID())->second + item.GetSum();
				}
				else
				{
					debt.insert(std::make_pair(item.GetClientID(), item.GetSum()));
				}
			}
		}

		if (vecOrderRet.size() > 0)
		{
			for each (auto item in vecOrderRet)
			{
				orderRetDateMap.insert(std::make_pair(item.GetID(), item.GetDate()));
				orderList.Clear();
				orderListFilter.clear();
				orderList.SetOrderID(item.GetID());
				orderListFilter = orderList.GenerateFilter(dialogBL->GetOrmasDal());
				vecOrderListRet.clear();
				vecOrderListRet = dialogBL->GetAllDataForClass<BusinessLayer::OrderListView>(errorMessage, orderListFilter);
				if (vecOrderListRet.size() > 0)
				{
					for each (auto listItem in vecOrderListRet)
					{
						if (productRetCount.find(listItem.GetProductID()) != productRetCount.end())
						{
							productRetCount.find(listItem.GetProductID())->second = productRetCount.find(listItem.GetProductID())->second + listItem.GetCount();
							productRetSum.find(listItem.GetProductID())->second = productRetSum.find(listItem.GetProductID())->second + listItem.GetSum();
						}
						else
						{
							productRetCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							productRetSum.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
						}
						if (productRetOrderMap.find(std::make_pair(item.GetDate(), listItem.GetProductID())) != productRetOrderMap.end())
						{
							productRetOrderMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second = productRetOrderMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second + listItem.GetCount();
						}
						else
						{
							productRetOrderMap.insert(std::make_pair(std::make_pair(item.GetDate(), listItem.GetProductID()), listItem.GetCount()));
						}
					}
				}
				
			}
		}

		if (vecConsume.size() > 0)
		{
			for each (auto item in vecConsume)
			{
				consumeDateMap.insert(std::make_pair(item.GetID(), item.GetDate()));
				consumeList.Clear();
				consumeListFilter.clear();
				consumeList.SetConsumeProductID(item.GetID());
				consumeListFilter = consumeList.GenerateFilter(dialogBL->GetOrmasDal());
				vecConsumeList.clear();
				vecConsumeList = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductListView>(errorMessage, consumeListFilter);
				if (vecConsumeList.size() > 0)
				{
					for each (auto listItem in vecConsumeList)
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

						if (productConsumeMap.find(std::make_pair(item.GetDate(), listItem.GetProductID())) != productConsumeMap.end())
						{
							productConsumeMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second = productConsumeMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second + listItem.GetCount();
						}
						else
						{
							productConsumeMap.insert(std::make_pair(std::make_pair(item.GetDate(), listItem.GetProductID()), listItem.GetCount()));
						}
					}
				}
			}
		}
		if (vecConsumeRet.size() > 0)
		{
			for each (auto item in vecConsumeRet)
			{
				consumeRetDateMap.insert(std::make_pair(item.GetID(), item.GetDate()));
				consumeList.Clear();
				consumeListFilter.clear();
				consumeList.SetConsumeProductID(item.GetID());
				consumeListFilter = consumeList.GenerateFilter(dialogBL->GetOrmasDal());
				vecConsumeListRet.clear();
				vecConsumeListRet = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductListView>(errorMessage, consumeListFilter);
				if (vecConsumeListRet.size() > 0)
				{
					for each (auto listItem in vecConsumeListRet)
					{
						if (productRetCountCon.find(listItem.GetProductID()) != productRetCountCon.end())
						{
							productRetCountCon.find(listItem.GetProductID())->second = productRetCountCon.find(listItem.GetProductID())->second + listItem.GetCount();
							productRetSumCon.find(listItem.GetProductID())->second = productRetSumCon.find(listItem.GetProductID())->second + listItem.GetSum();
						}
						else
						{
							productRetCountCon.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							productRetSumCon.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
						}
						if (productRetConsumeMap.find(std::make_pair(item.GetDate(), listItem.GetProductID())) != productRetConsumeMap.end())
						{
							productRetConsumeMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second = productRetConsumeMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second + listItem.GetCount();
						}
						else
						{
							productRetConsumeMap.insert(std::make_pair(std::make_pair(item.GetDate(), listItem.GetProductID()), listItem.GetCount()));
						}
					}
				}
			}
		}

		if (vecReturn.size() > 0)
		{
			for each (auto item in vecReturn)
			{
				returnDateMap.insert(std::make_pair(item.GetID(), item.GetDate()));
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
						if (productReturnMap.find(std::make_pair(item.GetDate(), listItem.GetProductID())) != productReturnMap.end())
						{
							productReturnMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second = productReturnMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second + listItem.GetCount();
						}
						else
						{
							productReturnMap.insert(std::make_pair(std::make_pair(item.GetDate(), listItem.GetProductID()), listItem.GetCount()));
						}
					}
				}
				if (cred.find(item.GetClientID()) != cred.end())
				{
					cred.find(item.GetClientID())->second = cred.find(item.GetClientID())->second + item.GetSum();
				}
				else
				{
					cred.insert(std::make_pair(item.GetClientID(), item.GetSum()));
				}
			}
		}

		if (vecReturnRet.size() > 0)
		{
			for each (auto item in vecReturnRet)
			{
				returnRetDateMap.insert(std::make_pair(item.GetID(), item.GetDate()));
				returnList.Clear();
				returnListFilter.clear();
				returnList.SetReturnID(item.GetID());
				returnListFilter = returnList.GenerateFilter(dialogBL->GetOrmasDal());
				vecReturnListRet.clear();
				vecReturnListRet = dialogBL->GetAllDataForClass<BusinessLayer::ReturnListView>(errorMessage, returnListFilter);
				if (vecReturnListRet.size() > 0)
				{
					for each (auto listItem in vecReturnListRet)
					{
						if (productRetCountRet.find(listItem.GetProductID()) != productRetCountRet.end())
						{
							productRetCountRet.find(listItem.GetProductID())->second = productRetCountRet.find(listItem.GetProductID())->second + listItem.GetCount();
							productRetSumRet.find(listItem.GetProductID())->second = productRetSumRet.find(listItem.GetProductID())->second + listItem.GetSum();
						}
						else
						{
							productRetCountRet.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							productRetSumRet.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
						}
						if (productReturnRetMap.find(std::make_pair(item.GetDate(), listItem.GetProductID())) != productReturnRetMap.end())
						{
							productReturnRetMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second = productReturnRetMap.find(std::make_pair(item.GetDate(), listItem.GetProductID()))->second + listItem.GetCount();
						}
						else
						{
							productReturnRetMap.insert(std::make_pair(std::make_pair(item.GetDate(), listItem.GetProductID()), listItem.GetCount()));
						}
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

		for each (auto mapCountItem in productIDCycle)
		{
			product.Clear();
			product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
			nCost.Clear();
			nCost.GetNetCostByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);

			if (productCountRet.find(mapCountItem.first) != productCountRet.end())
			{
				sumRet += productSumRet.find(mapCountItem.first)->second;
			}

			if (productCount.find(mapCountItem.first) != productCount.end())
			{
				sum += productSum.find(mapCountItem.first)->second;
			}
			tableBody += "<tr>";
			tableBody += "<td>" + QString(product.GetName().c_str()) + "</td>";
			if (productCountStart.find(mapCountItem.first) != productCountStart.end())
			{
				tableBody += "<td>" + QString::number(productCountStart.find(mapCountItem.first)->second) + "</td>";
			}
			else
			{
				tableBody += "<td> 0 </td>";
			}
			if (productCountCon.find(mapCountItem.first) != productCountCon.end())
			{
				tableBody += "<td>" + QString::number(productCountCon.find(mapCountItem.first)->second, 'f', 3) + "</td>";
			}
			else
			{
				tableBody += "<td> 0 </td>";
			}
			if (productCount.find(mapCountItem.first) != productCount.end())
			{
				tableBody += "<td>" + QString::number(productCount.find(mapCountItem.first)->second, 'f', 3) + "</td>";
			}
			else
			{
				tableBody += "<td> 0 </td>";
			}
			if (productCountEnd.find(mapCountItem.first) != productCountEnd.end())
			{
				tableBody += "<td>" + QString::number(productCountEnd.find(mapCountItem.first)->second, 'f', 3) + "</td>";
			}
			else
			{
				tableBody += "<td> 0 </td>";
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
			filterPayments = payment.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toStdString(), fromDateEdit->text().toStdString());
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
		tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка") + "</td>";
		tableBody += "<td><b>" + QString::number(sum, 'f', 3) + "</b></td>";
		tableBody += "<td>" + QString::fromWCharArray(L"Вся выручка с вычетом возврата") + "</td>";
		tableBody += "<td><b>" + QString::number(sum - sumRet, 'f', 3) + "</b></td>";
		tableBody += "</tr>";
		tableBody += "</table>";
		tableBody += "<br/><br/>";
	}

	//consume out
	BusinessLayer::ConsumeProduct conProd;
	tableBody += QString::fromWCharArray(L"Поступление товара из склада");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата создания") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата исполнения") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Количество") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сотрудник склада") + "</div></b></th>";
	QString username;
	for each (auto consumeItem  in vecConsume)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(consumeItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(consumeItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString(consumeItem.GetExecutionDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(consumeItem.GetCount()) + "</td>";
		tableBody += "<td>" + QString(consumeItem.GetStatusName().c_str()) + "</td>";
		username = consumeItem.GetStockEmployeeName().c_str();
		username += " ";
		username += consumeItem.GetStockEmployeeSurname().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
	}
	tableBody += "</table><br/><br/>";
	
	// consume hash
	conProd.Clear();
	tableBody += QString::fromWCharArray(L"Поступление товара по наименованию и количеству");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Дата") + "</div></b></th>";
	for each (auto mapCountItem in productCountCon)
	{
		product.Clear();
		product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
		tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>" + QString(product.GetName().c_str()) + "</div></b></th>";
		
	}
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Общее количество") + "</div></b></th>";

	int productCounter = 1;
	double clientSum = 0;
	for (std::map<int, std::string>::iterator dateIt = consumeDateMap.begin(); dateIt != consumeDateMap.end(); dateIt++)
	{
		clientSum = 0;

		tableBody += "<tr>";
		tableBody += "<td>" + QString(dateIt->second.c_str()) + "</td>";
		for (std::map<int, double>::iterator conIt = productCountCon.begin(); conIt != productCountCon.end(); conIt++)
		{
			product.Clear();
			if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), conIt->first, errorMessage))
				continue;
			if (productConsumeMap.find(std::pair<std::string, int>(dateIt->second, conIt->first)) != productConsumeMap.end())
			{
				tableBody += "<td>" + QString::number(productConsumeMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second) + "</td>";
				clientSum += productConsumeMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second;
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
	
	tableBody += "</table><br/><br/>";

	//consume return
	
	tableBody += QString::fromWCharArray(L"Возврат товара на склад");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата создания") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата исполнения") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Количество") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сотрудник склада") + "</div></b></th>";
	username.clear();
	for each (auto consumeItem  in vecConsumeRet)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(consumeItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(consumeItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString(consumeItem.GetExecutionDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(consumeItem.GetCount()) + "</td>";
		tableBody += "<td>" + QString(consumeItem.GetStatusName().c_str()) + "</td>";
		username = consumeItem.GetStockEmployeeName().c_str();
		username += " ";
		username += consumeItem.GetStockEmployeeSurname().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
	}
	tableBody += "</table><br/><br/>";

	// consume hash return
	conProd.Clear();
	tableBody += QString::fromWCharArray(L"Возврат товара по наименованию и количеству");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Дата") + "</div></b></th>";
	for each (auto mapCountItem in productRetCountCon)
	{
		product.Clear();
		product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
		tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>" + QString(product.GetName().c_str()) + "</div></b></th>";
		
	}
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Общее количество") + "</div></b></th>";

	
	for (std::map<int, std::string>::iterator dateIt = consumeRetDateMap.begin(); dateIt != consumeRetDateMap.end(); dateIt++)
	{
		clientSum = 0;

		tableBody += "<tr>";
		tableBody += "<td>" + QString(dateIt->second.c_str()) + "</td>";
		for (std::map<int, double>::iterator conIt = productRetCountCon.begin(); conIt != productRetCountCon.end(); conIt++)
		{
			product.Clear();
			if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), conIt->first, errorMessage))
				continue;
			if (productRetConsumeMap.find(std::pair<std::string, int>(dateIt->second, conIt->first)) != productRetConsumeMap.end())
			{
				tableBody += "<td>" + QString::number(productRetConsumeMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second) + "</td>";
				clientSum += productRetConsumeMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second;
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

	tableBody += "</table><br/><br/>";

	//order
	BusinessLayer::Order saleOrder;
	tableBody += QString::fromWCharArray(L"Продажа товара из транспорта");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата создания") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата исполнения") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Количество") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сумма") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";
	
	username.clear();
	for each (auto orderItem  in vecOrder)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(orderItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(orderItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString(orderItem.GetExecutionDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(orderItem.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(orderItem.GetSum()) + "</td>";
		tableBody += "<td>" + QString(orderItem.GetStatusName().c_str()) + "</td>";
		username = orderItem.GetClientName().c_str();
		username += " ";
		username += orderItem.GetClientSurname().c_str();
		username += " ";
		username += orderItem.GetClientPhone().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
	}
	tableBody += "</table><br/><br/>";

	// order hash
	saleOrder.Clear();
	tableBody += QString::fromWCharArray(L"Продажа товара по наименованию и количеству");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Дата") + "</div></b></th>";
	for each (auto mapCountItem in productCount)
	{
		product.Clear();
		if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage))
			continue;
		tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>";
		tableBody += QString(product.GetName().c_str());
		tableBody += "</div></b></th>";
	}
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Общее количество") + "</div></b></th>";

	productCounter = 1;
	clientSum = 0;
	std::string currentDate = "";
	for (std::map<int, std::string>::iterator dateIt = orderDateMap.begin(); dateIt != orderDateMap.end(); dateIt++)
	{
		clientSum = 0;
		if (currentDate == dateIt->second.c_str())
		{
			continue;
		}
		else
		{
			currentDate = dateIt->second.c_str();
		}

		tableBody += "<tr>";
		tableBody += "<td>" + QString(dateIt->second.c_str()) + "</td>";
		
		for (std::map<int, double>::iterator conIt = productCount.begin(); conIt != productCount.end(); conIt++)
		{
			product.Clear();
			if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), conIt->first, errorMessage))
				continue;
			if (productOrderMap.find(std::pair<std::string, int>(dateIt->second, conIt->first)) != productOrderMap.end())
			{
				tableBody += "<td>" + QString::number(productOrderMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second) + "</td>";
				clientSum += productOrderMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second;
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

	tableBody += "</table><br/><br/>";

	//order return
	
	tableBody += QString::fromWCharArray(L"Отмена проданных товаров, возврат на транспорт");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата создания") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата исполнения") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Количество") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сумма") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";

	username.clear();
	for each (auto orderItem  in vecOrderRet)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(orderItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(orderItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString(orderItem.GetExecutionDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(orderItem.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(orderItem.GetSum()) + "</td>";
		tableBody += "<td>" + QString(orderItem.GetStatusName().c_str()) + "</td>";
		username = orderItem.GetClientName().c_str();
		username += " ";
		username += orderItem.GetClientSurname().c_str();
		username += " ";
		username += orderItem.GetClientPhone().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
	}
	tableBody += "</table><br/><br/>";

	// order return hash
	saleOrder.Clear();
	tableBody += QString::fromWCharArray(L"Отмена продажи по наименованию и количеству товара");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";

	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Дата") + "</div></b></th>";
	for each (auto mapCountItem in productRetCount)
	{
		product.Clear();
		product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
		tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>" + QString(product.GetName().c_str()) + "</div></b></th>";

	}
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Общее количество") + "</div></b></th>";

	productCounter = 1;
	clientSum = 0;
	currentDate.clear();
	for (std::map<int, std::string>::iterator dateIt = orderRetDateMap.begin(); dateIt != orderRetDateMap.end(); dateIt++)
	{
		clientSum = 0;
		if (currentDate == dateIt->second.c_str())
		{
			continue;
		}
		else
		{
			currentDate = dateIt->second.c_str();
		}

		tableBody += "<tr>";
		tableBody += "<td>" + QString(dateIt->second.c_str()) + "</td>";

		for (std::map<int, double>::iterator conIt = productRetCount.begin(); conIt != productRetCount.end(); conIt++)
		{
			product.Clear();
			if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), conIt->first, errorMessage))
				continue;
			if (productRetOrderMap.find(std::pair<std::string, int>(dateIt->second, conIt->first)) != productRetOrderMap.end())
			{
				tableBody += "<td>" + QString::number(productRetOrderMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second) + "</td>";
				clientSum += productRetOrderMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second;
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

	tableBody += "</table><br/><br/>";

	//return

	tableBody += QString::fromWCharArray(L"Возврат от клиента на склад");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата создания") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата исполнения") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Количество") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сумма") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";

	username.clear();
	for each (auto returnItem  in vecReturn)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(returnItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(returnItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString(returnItem.GetExecutionDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(returnItem.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(returnItem.GetSum()) + "</td>";
		tableBody += "<td>" + QString(returnItem.GetStatusName().c_str()) + "</td>";
		username = returnItem.GetClientName().c_str();
		username += " ";
		username += returnItem.GetClientSurname().c_str();
		username += " ";
		username += returnItem.GetClientPhone().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
	}
	tableBody += "</table><br/><br/>";

	// return hash
	saleOrder.Clear();
	tableBody += QString::fromWCharArray(L"Возврат от клиента по наименованию и количеству товара");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";

	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Дата") + "</div></b></th>";
	for each (auto mapCountItem in productCountRet)
	{
		product.Clear();
		product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
		tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>" + QString(product.GetName().c_str()) + "</div></b></th>";

	}
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Общее количество") + "</div></b></th>";

	productCounter = 1;
	clientSum = 0;
	currentDate.clear();
	for (std::map<int, std::string>::iterator dateIt = returnDateMap.begin(); dateIt != returnDateMap.end(); dateIt++)
	{
		clientSum = 0;
		if (currentDate == dateIt->second.c_str())
		{
			continue;
		}
		else
		{
			currentDate = dateIt->second.c_str();
		}

		tableBody += "<tr>";
		tableBody += "<td>" + QString(dateIt->second.c_str()) + "</td>";

		for (std::map<int, double>::iterator conIt = productCountRet.begin(); conIt != productCountRet.end(); conIt++)
		{
			product.Clear();
			if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), conIt->first, errorMessage))
				continue;
			if (productReturnMap.find(std::pair<std::string, int>(dateIt->second, conIt->first)) != productReturnMap.end())
			{
				tableBody += "<td>" + QString::number(productReturnMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second) + "</td>";
				clientSum += productReturnMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second;
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

	tableBody += "</table><br/><br/>";

	//return ret

	tableBody += QString::fromWCharArray(L"Отмена возврата от клиента");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата создания") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата исполнения") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Количество") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сумма") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";

	username.clear();
	for each (auto returnItem  in vecReturnRet)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(returnItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(returnItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString(returnItem.GetExecutionDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(returnItem.GetCount()) + "</td>";
		tableBody += "<td>" + QString::number(returnItem.GetSum()) + "</td>";
		tableBody += "<td>" + QString(returnItem.GetStatusName().c_str()) + "</td>";
		username = returnItem.GetClientName().c_str();
		username += " ";
		username += returnItem.GetClientSurname().c_str();
		username += " ";
		username += returnItem.GetClientPhone().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
	}
	tableBody += "</table><br/><br/>";

	//return return hash
	saleOrder.Clear();
	tableBody += QString::fromWCharArray(L"Отмена возврата от клиента по наименованию и количеству товара");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";

	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Дата") + "</div></b></th>";
	for each (auto mapCountItem in productRetCountRet)
	{
		product.Clear();
		product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage);
		tableBody += "<th style='height:300px; vertical-align:bottom;text-align:center;'><b><div style='transform: rotate(-90deg); max-width:20px; white-space:nowrap;'>" + QString(product.GetName().c_str()) + "</div></b></th>";
	}
	tableBody += "<th><b><div style='transform: rotate(-90deg);'>" + QString::fromWCharArray(L"Общее количество") + "</div></b></th>";

	productCounter = 1;
	clientSum = 0;
	currentDate.clear();
	for (std::map<int, std::string>::iterator dateIt = returnRetDateMap.begin(); dateIt != returnRetDateMap.end(); dateIt++)
	{
		clientSum = 0;
		if (currentDate == dateIt->second.c_str())
		{
			continue;
		}
		else
		{
			currentDate = dateIt->second.c_str();
		}

		tableBody += "<tr>";
		tableBody += "<td>" + QString(dateIt->second.c_str()) + "</td>";

		for (std::map<int, double>::iterator conIt = productRetCountRet.begin(); conIt != productRetCountRet.end(); conIt++)
		{
			product.Clear();
			if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), conIt->first, errorMessage))
				continue;
			if (productReturnRetMap.find(std::pair<std::string, int>(dateIt->second, conIt->first)) != productReturnRetMap.end())
			{
				tableBody += "<td>" + QString::number(productReturnRetMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second) + "</td>";
				clientSum += productReturnRetMap.find(std::pair<std::string, int>(dateIt->second, conIt->first))->second;
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

	tableBody += "</table><br/><br/>";

	//payment

	tableBody += QString::fromWCharArray(L"Оплата клиента");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"ID") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Дата оплаты") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Сумма") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Статус") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";

	username.clear();
	std::vector<int> subID;
	std::map<int, double> paymentMap;
	std::map<int, int> clientSubID;
	std::map<int, double> startBalValue;
	std::map<int, double> endBalValue;
	for each (auto paymentItem  in vecPaymet)
	{
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(paymentItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(paymentItem.GetDate().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(paymentItem.GetValue()) + "</td>";
		tableBody += "<td>" + QString(paymentItem.GetStatusName().c_str()) + "</td>";
		username = paymentItem.GetUsername().c_str();
		username += " ";
		username += paymentItem.GetUserSurname().c_str();
		username += " ";
		username += paymentItem.GetUserPhone().c_str();
		tableBody += "<td>" + username + "</td>";
		tableBody += "</tr>";
		subID.push_back(paymentItem.GetSubaccountID());
	
		if (paymentMap.find(paymentItem.GetUserID()) != paymentMap.end())
		{
			paymentMap.find(paymentItem.GetUserID())->second = paymentMap.find(paymentItem.GetUserID())->second + paymentItem.GetValue();
		}
		else
		{
			paymentMap.insert(std::make_pair(paymentItem.GetUserID(), paymentItem.GetValue()));
		}
		clientSubID.insert(std::make_pair(paymentItem.GetUserID(), paymentItem.GetSubaccountID()));
	}
	tableBody += "</table><br/><br/>";

	//payment hash
	BusinessLayer::SubaccountHistory sHistoryStart;
	BusinessLayer::SubaccountHistory sHistoryEnd;
	BusinessLayer::Subaccount subaccount;
	
	std::string filterSub = subaccount.GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), subID);
	sHistoryStart.SetTillDate(prevMonthEnd);
	std::string filterHis = sHistoryStart.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<std::string> filterLists;
	filterLists.push_back(filterSub);
	filterLists.push_back(filterHis);
	filterHis = dialogBL->GetOrmasDal().ConcatenateFilters(filterLists);
	std::vector<BusinessLayer::SubaccountHistory> vecBalanceStart = dialogBL->GetAllDataForClass<BusinessLayer::SubaccountHistory>(errorMessage, filterHis);

	filterLists.clear();
	filterHis.clear();
	sHistoryEnd.SetTillDate(tillDateEdit->text().toStdString());
	filterHis = sHistoryEnd.GenerateFilter(dialogBL->GetOrmasDal());
	filterLists.push_back(filterSub);
	filterLists.push_back(filterHis);
	filterHis = dialogBL->GetOrmasDal().ConcatenateFilters(filterLists);
	std::vector<BusinessLayer::SubaccountHistory> vecBalanceEnd = dialogBL->GetAllDataForClass<BusinessLayer::SubaccountHistory>(errorMessage, filterHis);

	if (vecBalanceStart.size() > 0)
	{
		for each (auto item in vecBalanceStart)
		{
			
			if (startBalValue.find(item.GetSubaccountID()) != startBalValue.end())
			{
				startBalValue.find(item.GetSubaccountID())->second = startBalValue.find(item.GetSubaccountID())->second + item.GetCurrentBalance();
			}
			else
			{
				startBalValue.insert(std::make_pair(item.GetSubaccountID(), item.GetCurrentBalance()));
			}

		}
	}

	if (vecBalanceEnd.size() > 0)
	{
		for each (auto item in vecBalanceEnd)
		{

			if (endBalValue.find(item.GetSubaccountID()) != endBalValue.end())
			{
				endBalValue.find(item.GetSubaccountID())->second = endBalValue.find(item.GetSubaccountID())->second + item.GetCurrentBalance();
			}
			else
			{
				endBalValue.insert(std::make_pair(item.GetSubaccountID(), item.GetCurrentBalance()));
			}

		}
	}

	tableBody += QString::fromWCharArray(L"Суммарная заделжность/оплата клиентов");
	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Клиент") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Осаток на начало") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Задолженность") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Оплачено") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"Осаток на конец") + "</div></b></th>";
	
	double sratSum = 0;
	double paymentSum = 0;
	double debtSum = 0;
	double endSum = 0;
	double creds = 0;
	for each  (int ID in clientID)
	{
		tableBody += "<tr>";
		if (clientInfoMap.find(ID) != clientInfoMap.end())
		{
			tableBody += "<td>" + QString(clientInfoMap.find(ID)->second.c_str()) + "</td>";
		}
		else
		{
			tableBody += "<td> </td>";
		}
		if (clientSubID.find(ID) != clientSubID.end())
		{
			if (startBalValue.find(clientSubID.find(ID)->second) != startBalValue.end())
			{
				tableBody += "<td>" + QString::number(startBalValue.find(clientSubID.find(ID)->second)->second) + "</td>";
				sratSum += startBalValue.find(clientSubID.find(ID)->second)->second;
			}
			else
			{
				tableBody += "<td>0</td>";
			}
		}
		else
		{
			tableBody += "<td>0</td>";
		}
		if (debt.find(ID) != debt.end())
		{
			if (cred.find(ID) != cred.end())
			{
				creds = cred.find(ID)->second;
			}
			else
			{
				creds = 0;
			}
			tableBody += "<td>" + QString::number(debt.find(ID)->second - creds) + "</td>";
			debtSum += debt.find(ID)->second - creds;
		}
		else
		{
			tableBody += "<td>0</td>";
		}
		if (paymentMap.find(ID) != paymentMap.end())
		{
			tableBody += "<td>" + QString::number(paymentMap.find(ID)->second) + "</td>";
			paymentSum += paymentMap.find(ID)->second;
		}
		else
		{
			tableBody += "<td>0</td>";
		}
		if (clientSubID.find(ID) != clientSubID.end())
		{
			if (endBalValue.find(clientSubID.find(ID)->second) != endBalValue.end())
			{
				tableBody += "<td>" + QString::number(endBalValue.find(clientSubID.find(ID)->second)->second) + "</td>";
				endSum += endBalValue.find(clientSubID.find(ID)->second)->second;
			}
			else
			{
				tableBody += "<td>0</td>";
			}
		}
		else
		{
			tableBody += "<td>0</td>";
		}
		
		
		tableBody += "</tr>";
	}
	tableBody += "<th><b><div '>" + QString::fromWCharArray(L"По всем клиентам") + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::number(sratSum) + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::number(debtSum) + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::number(paymentSum) + "</div></b></th>";
	tableBody += "<th><b><div '>" + QString::number(endSum) + "</div></b></th>";
	tableBody += "</table><br/><br/>";

	documentBody += tableBody;



	reportText.replace(QString("DocumentBodyPh"), documentBody, Qt::CaseInsensitive);
	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();

	Close();
}

void GenerateAgentRep::Close()
{
	this->parentWidget()->close();
}

void GenerateAgentRep::OpenEmpDlg()
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

void GenerateAgentRep::CalculatePrevMonth(std::string fromMonth, std::string tilMonth, std::string& prevFromMonth, std::string& tillFromMonth)
{
	QDate startDate = QDate::fromString(fromMonth.c_str(), "dd.MM.yyyy");
	int day = startDate.day();
	int month = startDate.month();
	int year = startDate.year();

	if (month == 1)
	{
		prevFromMonth = "01.";
		prevFromMonth += std::to_string(12);
		prevFromMonth += ".";
		prevFromMonth += std::to_string(year - 1);
	}
	else
	{
		prevFromMonth = "01.";
		if (month < 11)
		{
			prevFromMonth += "0";
			prevFromMonth += std::to_string(month - 1);
		}
		else
		{
			prevFromMonth += std::to_string(month - 1);
		}

		prevFromMonth += ".";
		prevFromMonth += std::to_string(year);
	}
	QDate pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
	int coundOfDays = pastMonthDate.daysInMonth();
	day = pastMonthDate.day();
	month = pastMonthDate.month();
	year = pastMonthDate.year();
	tillFromMonth = std::to_string(coundOfDays);
	if (month < 10)
	{
		tillFromMonth += ".";
		tillFromMonth += "0";
		tillFromMonth += std::to_string(month);
	}
	else
	{
		tillFromMonth += ".";
		tillFromMonth += std::to_string(month);
	}
	tillFromMonth += ".";
	tillFromMonth += std::to_string(year);

}