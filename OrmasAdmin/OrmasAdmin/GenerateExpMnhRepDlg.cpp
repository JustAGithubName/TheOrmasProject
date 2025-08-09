#include "stdafx.h"
#include "GenerateExpMnhRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include "DataForm.h"
/*
GenerateExpMnhRep::GenerateExpMnhRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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
	int coundOfDays;

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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateExpMnhRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateExpMnhRep::Close);
	QObject::connect(empBtn, &QPushButton::released, this, &GenerateExpMnhRep::OpenEmpDlg);
}

GenerateExpMnhRep::~GenerateExpMnhRep()
{

}

void GenerateExpMnhRep::SetID(int ID, QString childName)
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
				empEdit->setText(QString::number(ID));
				BusinessLayer::User user;
				if (user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					namePh->setText(user.GetName().c_str());
					surnamePh->setText(user.GetSurname().c_str());
				}
			}
		}
	}
}

class TotalTransportStart
{
public:
	int transportID = 0;
	int employeeID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalTransportStart(){};
	~TotalTransportStart(){};

	bool Clear(){
		transportID = 0;
		employeeID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};
};

class TotalTransportEnd
{
public:
	int transportID = 0;
	int employeeID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalTransportEnd(){};
	~TotalTransportEnd(){};

	bool Clear(){
		transportID = 0;
		employeeID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};
};

class TotalReturn
{
public:
	int day = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalReturn(){};
	~TotalReturn(){};

	bool Clear(){
		day = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};


	const TotalReturn& find(int fday, int fproductID, int femployeeID)
	{
		TotalReturn empty;
		if (day == fday)
			return *this;
		return empty;
	}
};

class TotalConsumeProductExec
{
public:
	int day = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalConsumeProductExec(){};
	~TotalConsumeProductExec(){};

	bool Clear(){
		day = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};


	const TotalConsumeProductExec& find(int fday, int fproductID, int femployeeID)
	{
		TotalConsumeProductExec empty;
		if (day == fday)
			return *this;
		return empty;
	}
};

class TotalConsumeProductRet
{
public:
	int day = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalConsumeProductRet(){};
	~TotalConsumeProductRet(){};

	bool Clear(){
		day = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};


	const TotalConsumeProductRet& find(int fday, int fproductID, int femployeeID)
	{
		TotalConsumeProductRet empty;
		if (day == fday)
			return *this;
		return empty;
	}
};

class TotalOrder
{
public:
	int day = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalOrder(){};
	~TotalOrder(){};

	bool Clear(){
		day = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};


	const TotalOrder& find(int fday, int fproductID, int femployeeID)
	{
		TotalOrder empty;
		if (day == fday)
			return *this;
		return empty;
	}
};

class TotalWriteOff
{
public:
	int day = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalWriteOff(){};
	~TotalWriteOff(){};

	bool Clear(){
		day = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};


	const TotalWriteOff& find(int fday, int fproductID, int femployeeID)
	{
		TotalWriteOff empty;
		if (day == fday)
			return *this;
		return empty;
	}
};

class TotalPayment
{
public:
	int day = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalPayment(){};
	~TotalPayment(){};

	bool Clear(){
		day = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};


	const TotalPayment& find(int fday, int fproductID, int femployeeID)
	{
		TotalPayment empty;
		if (day == fday)
			return *this;
		return empty;
	}
};

void GenerateExpMnhRep::Generate()
{
	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print expeditor monthly report"));
	QMdiSubWindow *generateExpMnhRepWindow = new QMdiSubWindow;
	generateExpMnhRepWindow->setWidget(docForm);
	generateExpMnhRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	generateExpMnhRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	mainForm->mdiArea->addSubWindow(generateExpMnhRepWindow);

	//read template
	QFile file;
	file.setFileName(":/docs/exp_month_rep.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find return report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	QString documentBody = "";
	QString tableBody = "";

	BusinessLayer::Status statusExec;
	if (!statusExec.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}

	BusinessLayer::Status statusToRet;
	if (!statusToRet.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "RETURN", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}

	BusinessLayer::Order order;
	BusinessLayer::OrderList orderList;
	std::string orderListFilter;
	std::map<int, double> productCount;
	std::map<int, double> productSum;
	std::map<int, std::string> clientMap;
	std::map<std::pair<int, int>, double> productClient;
	std::vector<BusinessLayer::OrderListView> vecOrderList;

	BusinessLayer::Return ret;
	BusinessLayer::ReturnList returnList;
	std::string returnListFilter;
	std::map<int, double> productCountRet;
	std::map<int, double> productSumRet;
	std::vector<BusinessLayer::ReturnListView> vecReturnList;

	BusinessLayer::WriteOff writeOff;
	BusinessLayer::WriteOffList writeOffList;
	std::string writeListFilter;
	std::map<int, double> productCountWriteOff;
	std::map<int, double> productSumWriteOff;
	std::vector<BusinessLayer::WriteOffListView> vecWriteOffList;

	BusinessLayer::Transport transport;
	BusinessLayer::TransportList transportList;
	BusinessLayer::TransportChangeLog tChangeLog;

	BusinessLayer::ConsumeProduct conProd;
	BusinessLayer::ConsumeProductList conProdList;
	std::string conProdListFilter;
	std::map<int, double> productCountCon;
	std::map<int, double> productSumCon;
	std::vector<BusinessLayer::ConsumeProductListView> vecConProdList;

	BusinessLayer::Payment paymet;
	std::string paymentFilter;
	std::map<int, double> paymentSum;
	std::vector<BusinessLayer::PaymentView> vecPayment;

	BusinessLayer::Product product;
	BusinessLayer::NetCost nCost;
	double sum = 0;
	double sumRet = 0;

	
	std::map<int, double> totalOrderSum;
	std::map<int, double> totalReturnSum;
	std::map<int, double> totalWriteOffSum;
	std::map<int, double> totalTransportSum;
	std::map<int, double> totalConsumeSum;
	std::map<int, double> totalPaymentSum;


	tableBody.clear();

	conProd.Clear();
	conProd.SetStatusID(statusExec.GetID());
	conProd.SetEmployeeID(empEdit->text().toInt());
	std::string consumeProd = conProd.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ConsumeProductView> vecConsume = dialogBL->GetAllDataForClass<BusinessLayer::ConsumeProductView>(errorMessage, consumeProd);

	order.Clear();
	order.SetStatusID(statusExec.GetID());
	order.SetEmployeeID(empEdit->text().toInt());
	std::string filter = order.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::OrderView> vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);

	ret.Clear();
	ret.SetStatusID(statusExec.GetID());
	ret.SetEmployeeID(empEdit->text().toInt());
	std::string filterRet = ret.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRet);

	ret.Clear();
	ret.SetStatusID(statusExec.GetID());
	ret.SetEmployeeID(empEdit->text().toInt());
	std::string filterRet = ret.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(errorMessage, filterRet);

	
	transport.Clear();
	std::vector<BusinessLayer::TransportListView> vecTrans;
	if (transport.GetTransportByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), empEdit->text().toInt(), errorMessage))
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
					tChangeLog.SetLogDate(fromDateEdit->text().toUtf8().constData());
					std::string filterTranLog = tChangeLog.GenerateFilterForDateLess(dialogBL->GetOrmasDal());
					std::vector<BusinessLayer::TransportChangeLog> vecTransLog = dialogBL->GetAllDataForClass<BusinessLayer::TransportChangeLog>(errorMessage, filterTranLog);
					if (vecTransLog.size() > 0)
					{
						//totalTransportLogCount.insert(std::pair<int, double>(listItem.GetProductID(), vecTransLog.at(0).GetCount()));
					}
					else
					{
						//totalTransportLogCount.insert(std::pair<int, double>(listItem.GetProductID(), 0));
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
			if (!expeditor.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), empEdit->text().toInt(), errorMessage))
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
				payment.SetStatusID(statusExec.GetID());
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
		BusinessLayer::PriceExtension priceExtension;
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
		double extensionValue = 0;
		for (std::map<int, std::string>::iterator clientIt = clientMap.begin(); clientIt != clientMap.end(); clientIt++)
		{
			clientSum = 0;

			tableBody += "<tr>";
			tableBody += "<td>" + QString(clientIt->second.c_str()) + "</td>";
			for (std::map<int, double>::iterator tranIt = totalTransportLogCount.begin(); tranIt != totalTransportLogCount.end(); tranIt++)
			{
				product.Clear();
				priceExtension.Clear();
				extensionValue = 0;
				if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), tranIt->first, errorMessage))
					continue;
				if (priceExtension.GetPriceExtensionByProductIDAndExpeditorID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetID(), empEdit->text().toInt(), errorMessage))
					extensionValue = priceExtension.GetValue();
				if (productClient.find(std::pair<int, int>(clientIt->first, tranIt->first)) != productClient.end())
				{
					tableBody += "<td>" + QString::number(productClient.find(std::pair<int, int>(clientIt->first, tranIt->first))->second) + "</td>";
					clientSum += productClient.find(std::pair<int, int>(clientIt->first, tranIt->first))->second*(product.GetPrice() + extensionValue);
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

	QDate currentDate = QDate::currentDate();
	reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
	reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);
	reportText.replace(QString("DocumentBodyPh"), documentBody, Qt::CaseInsensitive);
	reportText.replace(QString("ReportDatePh"), currentDate.toString("dd.MM.yyyy"), Qt::CaseInsensitive);
	reportText.replace(QString("UserNamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	reportText.replace(QString("UserSurnamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();

	Close();
}

void GenerateExpMnhRep::Close()
{
	this->parentWidget()->close();
}

void GenerateExpMnhRep::OpenEmpDlg()
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

*/