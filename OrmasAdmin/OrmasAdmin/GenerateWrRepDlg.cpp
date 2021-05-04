#include "stdafx.h"
#include "GenerateWrRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include "DataForm.h"

GenerateWrRep::GenerateWrRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateWrRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateWrRep::Close);
	InitComboBox();
}

GenerateWrRep::~GenerateWrRep()
{

}


void GenerateWrRep::Generate()
{
	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print warehouse report"));
	QMdiSubWindow *generateProfRepWindow = new QMdiSubWindow;
	generateProfRepWindow->setWidget(docForm);
	generateProfRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	generateProfRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	mainForm->mdiArea->addSubWindow(generateProfRepWindow);

	//read template
	QFile file;
	file.setFileName(":/docs/product_stock.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find sales report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	QString documentBody = "";
	QString tableBody = "";

	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "RECEIPTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}


	std::map<int, double> stockCount;
	std::map<int, double> stockSum;
	std::map<int, double> stockHistoryCount;
	std::map<int, double> stockHistorySum;


	BusinessLayer::Stock stock;
	stock.SetWarehouseID(warehouseCmb->currentData().toInt());
	std::string filterStock = stock.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::StockView> vecStock = dialogBL->GetAllDataForClass<BusinessLayer::StockView>(errorMessage, filterStock);


	std::vector<int> employeeIDList;
	BusinessLayer::Employee employee;
	BusinessLayer::WarehouseEmployeeRelation weRelation;
	employeeIDList = weRelation.GetEmployeeIDListByWarehouseID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseCmb->currentData().toInt());
	std::string empIDListFilter = employee.GenerateINFilterForEmployee(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeIDList);

	std::vector<int> userIDList;
	BusinessLayer::User user;
	BusinessLayer::WarehouseEmployeeRelation wuRelation;
	userIDList = wuRelation.GetEmployeeIDListByWarehouseID(dialogBL->globalVar, dialogBL->GetOrmasDal(), warehouseCmb->currentData().toInt());
	std::vector<std::string> filterList;
	std::string userIDListFilter = user.GenerateINFilter(dialogBL->globalVar, dialogBL->GetOrmasDal(), employeeIDList);
	
	// select stock transfers for warehouse
	filterList.clear();
	BusinessLayer::StockTransfer sOutTransfer;
	sOutTransfer.SetStatusID(status.GetID());
	std::string filterOutStockTra = sOutTransfer.GenerateFilter(dialogBL->GetOrmasDal());
	filterList.push_back(filterOutStockTra);
	filterList.push_back(userIDListFilter);
	filterOutStockTra = dialogBL->GetOrmasDal().ConcatenateFilters(filterList);
	std::vector<BusinessLayer::StockTransferView> vecStockOutTra = dialogBL->GetAllDataForClass<BusinessLayer::StockTransferView>(errorMessage, filterOutStockTra);


	tableBody += QString::fromWCharArray(L"ОС: ");
	tableBody += warehouseCmb->currentText();
	tableBody += "<br/>";

	tableBody += "<table width='100 % ' border = 1px  cellpadding=5 style='border-spacing:0px; '>";
	tableBody += "<th><b>" + QString::fromWCharArray(L"ID") + "</b></th>";
	tableBody += "<th><b>" + QString::fromWCharArray(L"Наименование продукта") + "</b></th>";
	tableBody += "<th><b>" + QString::fromWCharArray(L"Количество") + "</b></th>";
	tableBody += "<th><b>" + QString::fromWCharArray(L"Сумма") + "</b></th>";
	tableBody += "<th><b>" + QString::fromWCharArray(L"Валюта") + "</b></th>";
	tableBody += "<th><b>" + QString::fromWCharArray(L"Статус") + "</b></th>";
	
	std::map<int, double> stockOutTraCount;
	std::map<int, double> stockOutTraSum;
	double totalSum = 0;
	double totalCount = 0;

	if (vecStockOutTra.size() > 0)
	{
		BusinessLayer::StockTransferList stTraList;
		std::string stTraListFilter;
		std::vector<BusinessLayer::StockTransferListView> vecStTraList;

		for each (auto item in vecStockOutTra)
		{
			stTraList.Clear();
			stTraListFilter.clear();
			stTraList.SetStockTransferID(item.GetID());
			stTraListFilter = stTraList.GenerateFilter(dialogBL->GetOrmasDal());
			vecStTraList.clear();
			vecStTraList = dialogBL->GetAllDataForClass<BusinessLayer::StockTransferListView>(errorMessage, stTraListFilter);
			if (vecStTraList.size() > 0)
			{
				for each (auto listItem in vecStTraList)
				{
					if (stockOutTraCount.find(listItem.GetProductID()) != stockOutTraCount.end())
					{
						stockOutTraCount.find(listItem.GetProductID())->second = stockOutTraCount.find(listItem.GetProductID())->second + listItem.GetCount();
						stockOutTraSum.find(listItem.GetProductID())->second = stockOutTraSum.find(listItem.GetProductID())->second + listItem.GetSum();
					}
					else
					{
						stockOutTraCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
						stockOutTraSum.insert(std::make_pair(listItem.GetProductID(), listItem.GetSum()));
					}
				}
			}
		}
	}

	
	double transferSum = 0;
	double transferCount = 0;
	BusinessLayer::Product product;
	for each (auto mapItem in vecStock)
	{
		product.Clear();
		if (!product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapItem.GetProductID(), errorMessage))
			continue;
		if (stockOutTraCount.find(mapItem.GetProductID()) != stockOutTraCount.end())
		{
			transferCount = stockOutTraCount.find(mapItem.GetProductID())->second;
			transferSum = stockOutTraSum.find(mapItem.GetProductID())->second;
		}
		else
		{
			transferSum = 0;
			transferCount = 0;
		}
		tableBody += "<tr>";
		tableBody += "<td>" + QString::number(mapItem.GetID()) + "</td>";
		tableBody += "<td>" + QString(mapItem.GetProductName().c_str()) + "</td>";
		tableBody += "<td>" + QString::number(mapItem.GetCount() - transferCount, 'f', 3) + "</td>";
		tableBody += "<td>" + QString::number(mapItem.GetSum() - transferSum, 'f', 3) + "</td>";
		tableBody += "<td>" + QString(mapItem.GetCurrencyName().c_str()) + "</td>";
		tableBody += "<td>" + QString(mapItem.GetStatusName().c_str()) + "</td>";
		tableBody += "</tr>";
		totalCount += mapItem.GetCount() - transferCount;
		totalSum += mapItem.GetSum() - transferSum;
	}
	
	tableBody += "<tr>";
	tableBody += "<td>" + QString::fromWCharArray(L"Суммарно: ") + "</td>";
	tableBody += "<td></td>";
	tableBody += "<td>" + QString::number(totalCount, 'f', 3) + "</td>";
	tableBody += "<td>" + QString::number(totalSum, 'f', 3) + "</td>";
	tableBody += "<td></td>";
	tableBody += "<td></td>";
	tableBody += "</tr>";
	tableBody += "</table><br/><br/>";
	


	documentBody += tableBody;

	QDate currentDate = QDate::currentDate();
	reportText.replace(QString("fromDatePh"), currentDate.toString("dd.MM.yyyy"), Qt::CaseInsensitive);
	reportText.replace(QString("TablePh"), documentBody, Qt::CaseInsensitive);
	reportText.replace(QString("ReportDatePh"), currentDate.toString("dd.MM.yyyy"), Qt::CaseInsensitive);
	reportText.replace(QString("UserNamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	reportText.replace(QString("UserSurnamePh"), dialogBL->loggedUser->GetName().c_str(), Qt::CaseInsensitive);
	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();

	Close();
}

void GenerateWrRep::Close()
{
	this->parentWidget()->close();
}

void GenerateWrRep::InitComboBox()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	std::string filter = "";

	if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second ||
		mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("STOCK INSPECTOR")->second)
	{
		filter = "";
	}
	else
	{
		BusinessLayer::Subaccount subaccount;
		BusinessLayer::BranchSubaccountRelation bsRel;
		BusinessLayer::CompanyEmployeeRelation ceRel;
		int branchID = ceRel.GetBranchByEmployeeID(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), mainForm->GetLoggedUser()->GetID(), errorMessage);
		if (0 < branchID)
		{
			std::vector<int> subaccountIDVec = bsRel.GetSubaccountIDsbyBranchID(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), branchID, errorMessage);
			if (subaccountIDVec.size() > 0)
			{
				filter = subaccount.GenerateINFilter(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), subaccountIDVec);
			}
		}
	}
	BusinessLayer::WarehouseType type;
	BusinessLayer::Warehouse ware;
	if (!type.GetWarehouseTypeByCode(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "PRODUCT", errorMessage))
		return;
	ware.SetWarehouseTypeID(type.GetID());
	std::string filterWare = ware.GenerateFilter(mainForm->oBL->GetOrmasDal());
	std::vector<std::string> filterList;
	filterList.push_back(filterWare);
	filterList.push_back(filter);
	filter = mainForm->oBL->ConcatenateFilters(filterList);
	std::vector<BusinessLayer::WarehouseView> curWarehouse = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage, filter);
	if (!curWarehouse.empty())
	{
		for (unsigned int i = 0; i < curWarehouse.size(); i++)
		{
			warehouseCmb->addItem(curWarehouse[i].GetName().c_str(), QVariant(curWarehouse[i].GetID()));
		}
	}
}

