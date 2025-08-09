#include "stdafx.h"
#include "GenerateRetRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include "DataForm.h"

GenerateRetRep::GenerateRetRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateRetRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateRetRep::Close);
	QObject::connect(empBtn, &QPushButton::released, this, &GenerateRetRep::OpenEmpDlg);
	QObject::connect(allCkb, &QCheckBox::released, this, &GenerateRetRep::CheckBoxChanged);
}

GenerateRetRep::~GenerateRetRep()
{

}

void GenerateRetRep::SetID(int ID, QString childName)
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

class TotalReturn
{
public:
	int warehouseID = 0;
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TotalReturn(){};
	~TotalReturn(){};

	bool Clear(){
		warehouseID = 0;
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};

	const TotalReturn& find(int productID, int userID, int warehouse)
	{

	}
};

class TableRowWarehouseExec
{
public:
	int warehouseID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TableRowWarehouseExec(){};
	~TableRowWarehouseExec(){};

	bool Clear(){
		warehouseID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};
};

class TableRowWarehouseToRet
{
public:
	int warehouseID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TableRowWarehouseToRet(){};
	~TableRowWarehouseToRet(){};

	bool Clear(){
		warehouseID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};
};

class TableRowEmployeeExec
{
public:
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TableRowEmployeeExec(){};
	~TableRowEmployeeExec(){};

	bool Clear(){
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};
};

class TableRowEmployeeToRet
{
public:
	int employeeID = 0;
	int productID = 0;
	int statusID = 0;
	double count = 0;
	double sum = 0;

	TableRowEmployeeToRet(){};
	~TableRowEmployeeToRet(){};

	bool Clear(){
		employeeID = 0;
		productID = 0;
		statusID = 0;
		count = 0;
		sum = 0;
		return true;
	};
};

void GenerateRetRep::Generate()
{
	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print return report"));
	QMdiSubWindow *generateRetRepWindow = new QMdiSubWindow;
	generateRetRepWindow->setWidget(docForm);
	generateRetRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	generateRetRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	mainForm->mdiArea->addSubWindow(generateRetRepWindow);

	//read template
	QFile file;
	file.setFileName(":/docs/return_rep.html");
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
	if (!statusToRet.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "TO RETURN", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}
	
	if (allCkb->isChecked() == false && empEdit->text().isEmpty())
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please select employee at first!")),
			QString(tr("Ok")));
		return;
	}
	


	std::map<int, double> retCount;
	std::map<int, double> retSum;
	std::map<int, double> toRetCount;
	std::map<int, double> toRetSum;

	BusinessLayer::WarehouseType wType;
	if (!wType.GetWarehouseTypeByCode(dialogBL->globalVar, dialogBL->GetOrmasDal(), "PRODUCT", errorMessage))
	{

		return;
	}

	 // select returned products
	BusinessLayer::Return retProducts;
	std::string filterRetrun = retProducts.GenerateFilterForRawPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toStdString(), tillDateEdit->text().toStdString());
	std::vector<BusinessLayer::ReturnView> vecReturn = dialogBL->GetAllDataForClass<BusinessLayer::ReturnView>(0, 0, errorMessage, filterRetrun);

	BusinessLayer::ReturnList returnList;
	std::vector<BusinessLayer::ReturnListView> vecReturnList;
	std::string filterRetrunList = "";
	std::deque<TotalReturn> deqReturn;
	TotalReturn totalReturn;

	std::deque<TableRowWarehouseExec> deqWarehouseExec;
	std::deque<TableRowWarehouseToRet> deqWarehouseToRet;
	std::deque<TableRowEmployeeExec> deqEmployeeExec;
	std::deque<TableRowEmployeeToRet> deqEmployeeToRet;


	
	BusinessLayer::Branch branch;
	BusinessLayer::Warehouse warehouse;
	int warehouseID = 0;

	TableRowWarehouseExec warehouseExec;
	TableRowWarehouseToRet warehouseToRet;
	TableRowEmployeeExec employeeExec;
	TableRowEmployeeToRet employeeToRet;

	std::vector<int> vecExecID;
	std::vector<int> vecToRetID;
	std::vector<int> vecEmpID; 
	std::vector<int> vecEmpToRetID;

	int execTotalCount=0;
	double execTotalSum=0;
	int toRetTotalCount = 0;
	double toRetTotalSum = 0;
	int empTotalCount = 0;
	double empTotalSum = 0;
	int retEmpTotalCount = 0;
	double retEmpTotalSum = 0;

	for each (auto item in vecReturn)
	{
		returnList.Clear();
		vecReturnList.clear();
		filterRetrunList.clear();
		returnList.SetReturnID(item.GetID());
		filterRetrunList = returnList.GenerateFilter(dialogBL->GetOrmasDal());
		vecReturnList = dialogBL->GetAllDataForClass<BusinessLayer::ReturnListView>(errorMessage, filterRetrunList);
		
		warehouseID = 0;
		warehouse.Clear();
		warehouseID = warehouse.GetWarehouseIDByUserIDAndTypeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetEmployeeID(), wType.GetID(), errorMessage);

		for each (auto listItem in vecReturnList)
		{
			totalReturn.Clear();
			totalReturn.employeeID = item.GetEmployeeID();
			totalReturn.warehouseID = warehouseID;
			totalReturn.productID = listItem.GetProductID();
			totalReturn.count = listItem.GetCount();
			totalReturn.sum = listItem.GetSum();
			totalReturn.statusID = item.GetStatusID();
			deqReturn.push_back(totalReturn);
		}
	}


	for each (auto itemReturn in deqReturn)
	{
		if (itemReturn.statusID == statusExec.GetID())
		{
			auto iteratorWE = std::find_if(deqWarehouseExec.begin(), deqWarehouseExec.end(), [&](TableRowWarehouseExec& tb){
				return (tb.productID == itemReturn.productID && tb.warehouseID == itemReturn.warehouseID);
			});
			if (iteratorWE != deqWarehouseExec.end())
			{
				(*iteratorWE).sum += itemReturn.sum;
				(*iteratorWE).count += itemReturn.count;
				if (std::find(vecExecID.begin(), vecExecID.end(), itemReturn.warehouseID) != vecExecID.end()) {

				}
				else {
					vecExecID.push_back(itemReturn.warehouseID);
				}
			}
			else
			{
				if (std::find(vecExecID.begin(), vecExecID.end(), itemReturn.warehouseID) != vecExecID.end()) {

				}
				else {
					vecExecID.push_back(itemReturn.warehouseID);
				}
				warehouseExec.Clear();
				warehouseExec.warehouseID = itemReturn.warehouseID;
				warehouseExec.productID = itemReturn.productID;
				warehouseExec.statusID = itemReturn.statusID;
				warehouseExec.count = itemReturn.count;
				warehouseExec.sum = itemReturn.sum;
				deqWarehouseExec.push_back(warehouseExec);
			}

			auto iteratorEE = std::find_if(deqEmployeeExec.begin(), deqEmployeeExec.end(), [&](TableRowEmployeeExec& tb){
				return (tb.productID == itemReturn.productID && tb.employeeID == itemReturn.employeeID);
			});
			if (iteratorEE != deqEmployeeExec.end())
			{
				if (std::find(vecEmpID.begin(), vecEmpID.end(), itemReturn.employeeID) != vecEmpID.end()) {

				}
				else {
					vecEmpID.push_back(itemReturn.employeeID);
				}
				(*iteratorEE).sum += itemReturn.sum;
				(*iteratorEE).count += itemReturn.count;
			}
			else
			{
				if (std::find(vecEmpID.begin(), vecEmpID.end(), itemReturn.employeeID) != vecEmpID.end()) {

				}
				else {
					vecEmpID.push_back(itemReturn.employeeID);
				}
				employeeExec.Clear();
				employeeExec.employeeID = itemReturn.employeeID;
				employeeExec.productID = itemReturn.productID;
				employeeExec.statusID = itemReturn.statusID;
				employeeExec.count = itemReturn.count;
				employeeExec.sum = itemReturn.sum;
				deqEmployeeExec.push_back(employeeExec);
			}
		}
		else if (itemReturn.statusID == statusToRet.GetID())
		{
			auto iteratorTR = std::find_if(deqWarehouseToRet.begin(), deqWarehouseToRet.end(), [&](TableRowWarehouseToRet& tb){
				return (tb.productID == itemReturn.productID && tb.warehouseID == itemReturn.warehouseID);
			});

			if (iteratorTR != deqWarehouseToRet.end())
			{
				if (std::find(vecToRetID.begin(), vecToRetID.end(), itemReturn.warehouseID) != vecToRetID.end()) {

				}
				else {
					vecToRetID.push_back(itemReturn.warehouseID);
				}
				(*iteratorTR).sum += itemReturn.sum;
				(*iteratorTR).count += itemReturn.count;
			}
			else
			{
				if (std::find(vecToRetID.begin(), vecToRetID.end(), itemReturn.warehouseID) != vecToRetID.end()) {

				}
				else {
					vecToRetID.push_back(itemReturn.warehouseID);
				}
				warehouseToRet.Clear();
				warehouseToRet.warehouseID = itemReturn.warehouseID;
				warehouseToRet.productID = itemReturn.productID;
				warehouseToRet.statusID = itemReturn.statusID;
				warehouseToRet.count = itemReturn.count;
				warehouseToRet.sum = itemReturn.sum;
				deqWarehouseToRet.push_back(warehouseToRet);
			}

			auto iteratorER = std::find_if(deqEmployeeToRet.begin(), deqEmployeeToRet.end(), [&](TableRowEmployeeToRet& tb){
				return (tb.productID == itemReturn.productID && tb.employeeID == itemReturn.employeeID);
			});
			if (iteratorER != deqEmployeeToRet.end())
			{
				if (std::find(vecEmpToRetID.begin(), vecEmpToRetID.end(), itemReturn.employeeID) != vecEmpToRetID.end()) {

				}
				else {
					vecEmpToRetID.push_back(itemReturn.employeeID);
				}
				(*iteratorER).sum += itemReturn.sum;
				(*iteratorER).count += itemReturn.count;
			}
			else
			{
				if (std::find(vecEmpToRetID.begin(), vecEmpToRetID.end(), itemReturn.employeeID) != vecEmpToRetID.end()) {

				}
				else {
					vecEmpToRetID.push_back(itemReturn.employeeID);
				}
				employeeToRet.Clear();
				employeeToRet.employeeID = itemReturn.employeeID;
				employeeToRet.productID = itemReturn.productID;
				employeeToRet.statusID = itemReturn.statusID;
				employeeToRet.count = itemReturn.count;
				employeeToRet.sum = itemReturn.sum;
				deqEmployeeToRet.push_back(employeeToRet);
			}
		}
	}


	if (allCkb->isChecked())
	{
		int counter = 0;
		BusinessLayer::Product product;
		std::map<int, std::string> productNameMap;
		warehouse.Clear();
		for each (int itemWareID in vecExecID)
		{
			execTotalCount = 0;
			execTotalSum = 0;
			warehouse.Clear();
			if (!warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemWareID, errorMessage))
				continue;
			tableBody += QString::fromWCharArray(L"Общее количечтво возврата на склад: ");
			tableBody += QString(warehouse.GetName().c_str());
			tableBody += "<br/>";

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";


			for each (auto itemExecList in deqWarehouseExec)
			{
				if (itemExecList.warehouseID == itemWareID)
				{
					counter++;
					if (productNameMap.find(itemExecList.productID) == productNameMap.end())
					{
						product.Clear();
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemExecList.productID, errorMessage))
						{
							productNameMap.insert(std::pair<int, std::string>(product.GetID(), product.GetName()));
						}
					}

					tableBody += "<tr><td><b>" + QString::number(counter) + "</b></td>";
					if (productNameMap.find(itemExecList.productID) != productNameMap.end())
					{
						tableBody += "<td><b>" + QString::fromStdString(productNameMap.find(itemExecList.productID)->second) + "</b></td>";
					}
					else
					{
						tableBody += "<td><b>" + QString::fromStdString("") + "</b></td>";
					}
					tableBody += "<td><b>" + QString::number(itemExecList.count) + "</b></td>";
					tableBody += "<td><b>" + QString::number(itemExecList.sum) + "</b></td></tr>";
					execTotalCount += itemExecList.count;
					execTotalSum += itemExecList.sum;
				}
			}

			tableBody += "<tr><td><b>" + QString::fromWCharArray(L"Суммарно") + "</b></td>";
			tableBody += "<td><b></b></td>";
			tableBody += "<td><b>" + QString::number(execTotalCount) + "</b></td>";
			tableBody += "<td><b>" + QString::number(execTotalSum, 'f', 3) + "</b></td></tr>";
			tableBody += "</table><br/>";
		}

		counter = 0;
		product.Clear();
		productNameMap.clear();
		warehouse.Clear();
		toRetTotalCount = 0;
		toRetTotalSum = 0;
		for each (int itemToWareID in vecToRetID)
		{
			toRetTotalCount = 0;
			toRetTotalSum = 0;
			warehouse.Clear();
			if (!warehouse.GetWarehouseByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemToWareID, errorMessage))
				continue;
			tableBody += QString::fromWCharArray(L"Общее количечтво к возврату на склад: ");
			tableBody += QString(warehouse.GetName().c_str());
			tableBody += "<br/>";

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";

			for each (auto itemExecList in deqWarehouseToRet)
			{
				if (itemExecList.warehouseID == itemToWareID)
				{
					counter++;
					if (productNameMap.find(itemExecList.productID) == productNameMap.end())
					{
						product.Clear();
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemExecList.productID, errorMessage))
						{
							productNameMap.insert(std::pair<int, std::string>(product.GetID(), product.GetName()));
						}
					}

					tableBody += "<tr><td><b>" + QString::number(counter) + "</b></td>";
					if (productNameMap.find(itemExecList.productID) != productNameMap.end())
					{
						tableBody += "<td><b>" + QString::fromStdString(productNameMap.find(itemExecList.productID)->second) + "</b></td>";
					}
					else
					{
						tableBody += "<td><b>" + QString::fromStdString("") + "</b></td>";
					}
					tableBody += "<td><b>" + QString::number(itemExecList.count) + "</b></td>";
					tableBody += "<td><b>" + QString::number(itemExecList.sum) + "</b></td></tr>";
					toRetTotalCount += itemExecList.count;
					toRetTotalSum += itemExecList.sum;
				}
			}

			tableBody += "<tr><td><b>" + QString::fromWCharArray(L"Суммарно") + "</b></td>";
			tableBody += "<td><b></b></td>";
			tableBody += "<td><b>" + QString::number(toRetTotalCount) + "</b></td>";
			tableBody += "<td><b>" + QString::number(toRetTotalSum, 'f', 3) + "</b></td></tr>";
			tableBody += "</table><br/>";
		}

		counter = 0;
		product.Clear();
		productNameMap.clear();
		BusinessLayer::Employee employee;

		empTotalCount = 0;
		empTotalSum = 0;

		for each (int itemEmp in vecEmpID)
		{
			empTotalCount = 0;
			empTotalSum = 0;
			employee.Clear();
			if (!employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemEmp, errorMessage))
				continue;
			tableBody += QString::fromWCharArray(L"Общее количечтво к возврату на склад по сотруднику: ");
			tableBody += QString(employee.GetName().c_str()) + QString(employee.GetSurname().c_str());
			tableBody += "<br/>";

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";

			for each (auto itemExecList in deqEmployeeExec)
			{
				if (itemExecList.employeeID == itemEmp)
				{
					counter++;
					if (productNameMap.find(itemExecList.productID) == productNameMap.end())
					{
						product.Clear();
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemExecList.productID, errorMessage))
						{
							productNameMap.insert(std::pair<int, std::string>(product.GetID(), product.GetName()));
						}
					}

					tableBody += "<tr><td><b>" + QString::number(counter) + "</b></td>";
					if (productNameMap.find(itemExecList.productID) != productNameMap.end())
					{
						tableBody += "<td><b>" + QString::fromStdString(productNameMap.find(itemExecList.productID)->second) + "</b></td>";
					}
					else
					{
						tableBody += "<td><b>" + QString::fromStdString("") + "</b></td>";
					}
					tableBody += "<td><b>" + QString::number(itemExecList.count) + "</b></td>";
					tableBody += "<td><b>" + QString::number(itemExecList.sum) + "</b></td></tr>";
					empTotalCount += itemExecList.count;
					empTotalSum += itemExecList.sum;
				}
			}

			tableBody += "<tr><td><b>" + QString::fromWCharArray(L"Суммарно") + "</b></td>";
			tableBody += "<td><b></b></td>";
			tableBody += "<td><b>" + QString::number(empTotalCount) + "</b></td>";
			tableBody += "<td><b>" + QString::number(empTotalSum, 'f', 3) + "</b></td></tr>";
			tableBody += "</table><br/>";
		}

		counter = 0;
		product.Clear();
		productNameMap.clear();
		employee.Clear();

		retEmpTotalCount = 0;
		retEmpTotalSum = 0;

		for each (int itemEmp in vecEmpToRetID)
		{
			retEmpTotalCount = 0;
			retEmpTotalSum = 0;
			employee.Clear();
			if (!employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemEmp, errorMessage))
				continue;
			tableBody += QString::fromWCharArray(L"Общее количечтво к возврату на склад по сотруднику: ");
			tableBody += QString(employee.GetName().c_str()) + QString(employee.GetSurname().c_str());
			tableBody += "<br/>";

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";

			for each (auto itemExecList in deqEmployeeToRet)
			{
				if (itemExecList.employeeID == itemEmp)
				{
					counter++;
					if (productNameMap.find(itemExecList.productID) == productNameMap.end())
					{
						product.Clear();
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemExecList.productID, errorMessage))
						{
							productNameMap.insert(std::pair<int, std::string>(product.GetID(), product.GetName()));
						}
					}

					tableBody += "<tr><td><b>" + QString::number(counter) + "</b></td>";
					if (productNameMap.find(itemExecList.productID) != productNameMap.end())
					{
						tableBody += "<td><b>" + QString::fromStdString(productNameMap.find(itemExecList.productID)->second) + "</b></td>";
					}
					else
					{
						tableBody += "<td><b>" + QString::fromStdString("") + "</b></td>";
					}
					tableBody += "<td><b>" + QString::number(itemExecList.count) + "</b></td>";
					tableBody += "<td><b>" + QString::number(itemExecList.sum) + "</b></td></tr>";
					retEmpTotalCount += itemExecList.count;
					retEmpTotalSum += itemExecList.sum;
				}
			}

			tableBody += "<tr><td><b>" + QString::fromWCharArray(L"Суммарно") + "</b></td>";
			tableBody += "<td><b></b></td>";
			tableBody += "<td><b>" + QString::number(retEmpTotalCount) + "</b></td>";
			tableBody += "<td><b>" + QString::number(retEmpTotalSum, 'f', 3) + "</b></td></tr>";
			tableBody += "</table><br/>";
		}
	}
	else
	{
		int counter = 0;
		BusinessLayer::Product product;
		std::map<int, std::string> productNameMap;
		counter = 0;
		product.Clear();
		productNameMap.clear();
		BusinessLayer::Employee employee;

		empTotalCount = 0;
		empTotalSum = 0;

		vecEmpID.clear();
		vecEmpID.push_back(empEdit->text().toInt());

		for each (int itemEmp in vecEmpID)
		{
			empTotalCount = 0;
			empTotalSum = 0;
			employee.Clear();
			if (!employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemEmp, errorMessage))
				continue;
			tableBody += QString::fromWCharArray(L"Общее количечтво к возврату на склад по сотруднику: ");
			tableBody += QString(employee.GetName().c_str()) + QString(employee.GetSurname().c_str());
			tableBody += "<br/>";

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";

			for each (auto itemExecList in deqEmployeeExec)
			{
				if (itemExecList.employeeID == itemEmp)
				{
					counter++;
					if (productNameMap.find(itemExecList.productID) == productNameMap.end())
					{
						product.Clear();
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemExecList.productID, errorMessage))
						{
							productNameMap.insert(std::pair<int, std::string>(product.GetID(), product.GetName()));
						}
					}

					tableBody += "<tr><td><b>" + QString::number(counter) + "</b></td>";
					if (productNameMap.find(itemExecList.productID) != productNameMap.end())
					{
						tableBody += "<td><b>" + QString::fromStdString(productNameMap.find(itemExecList.productID)->second) + "</b></td>";
					}
					else
					{
						tableBody += "<td><b>" + QString::fromStdString("") + "</b></td>";
					}
					tableBody += "<td><b>" + QString::number(itemExecList.count) + "</b></td>";
					tableBody += "<td><b>" + QString::number(itemExecList.sum) + "</b></td></tr>";
					empTotalCount += itemExecList.count;
					empTotalSum += itemExecList.sum;
				}
			}

			tableBody += "<tr><td><b>" + QString::fromWCharArray(L"Суммарно") + "</b></td>";
			tableBody += "<td><b></b></td>";
			tableBody += "<td><b>" + QString::number(empTotalCount) + "</b></td>";
			tableBody += "<td><b>" + QString::number(empTotalSum, 'f', 3) + "</b></td></tr>";
			tableBody += "</table><br/>";
		}

		counter = 0;
		product.Clear();
		productNameMap.clear();
		employee.Clear();

		retEmpTotalCount = 0;
		retEmpTotalSum = 0;
		
		vecEmpToRetID.clear();
		vecEmpToRetID.push_back(empEdit->text().toInt());

		for each (int itemEmp in vecEmpToRetID)
		{
			retEmpTotalCount = 0;
			retEmpTotalSum = 0;
			employee.Clear();
			if (!employee.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemEmp, errorMessage))
				continue;
			tableBody += QString::fromWCharArray(L"Общее количечтво к возврату на склад по сотруднику: ");
			tableBody += QString(employee.GetName().c_str()) + QString(employee.GetSurname().c_str());
			tableBody += "<br/>";

			tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
			tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";

			for each (auto itemExecList in deqEmployeeToRet)
			{
				if (itemExecList.employeeID == itemEmp)
				{
					counter++;
					if (productNameMap.find(itemExecList.productID) == productNameMap.end())
					{
						product.Clear();
						if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), itemExecList.productID, errorMessage))
						{
							productNameMap.insert(std::pair<int, std::string>(product.GetID(), product.GetName()));
						}
					}

					tableBody += "<tr><td><b>" + QString::number(counter) + "</b></td>";
					if (productNameMap.find(itemExecList.productID) != productNameMap.end())
					{
						tableBody += "<td><b>" + QString::fromStdString(productNameMap.find(itemExecList.productID)->second) + "</b></td>";
					}
					else
					{
						tableBody += "<td><b>" + QString::fromStdString("") + "</b></td>";
					}
					tableBody += "<td><b>" + QString::number(itemExecList.count) + "</b></td>";
					tableBody += "<td><b>" + QString::number(itemExecList.sum) + "</b></td></tr>";
					retEmpTotalCount += itemExecList.count;
					retEmpTotalSum += itemExecList.sum;
				}
			}

			tableBody += "<tr><td><b>" + QString::fromWCharArray(L"Суммарно") + "</b></td>";
			tableBody += "<td><b></b></td>";
			tableBody += "<td><b>" + QString::number(retEmpTotalCount) + "</b></td>";
			tableBody += "<td><b>" + QString::number(retEmpTotalSum, 'f', 3) + "</b></td></tr>";
			tableBody += "</table><br/>";
		}
	}

	documentBody += tableBody;

	QDate currentDate = QDate::currentDate();
	reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
	reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);
	reportText.replace(QString("TableBodyPh"), documentBody, Qt::CaseInsensitive);
	reportText.replace(QString("ReportDatePh"), currentDate.toString("dd.MM.yyyy"), Qt::CaseInsensitive);
	reportText.replace(QString("UserNamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	reportText.replace(QString("UserSurnamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
	
	Close();
}

void GenerateRetRep::Close()
{
	this->parentWidget()->close();
}

void GenerateRetRep::OpenEmpDlg()
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

void GenerateRetRep::CheckBoxChanged()
{
	if (allCkb->isChecked())
	{
		empEdit->setText("");
		namePh->setText("");
		surnamePh->setText("");
	}
}
