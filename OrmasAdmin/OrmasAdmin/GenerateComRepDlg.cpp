#include "stdafx.h"
#include "GenerateComRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"


GenerateComRep::GenerateComRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateComRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateComRep::Close);
}

GenerateComRep::~GenerateComRep()
{
}

void GenerateComRep::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::WarehouseType wType;
	if (!wType.GetWarehouseTypeByCode(dialogBL->globalVar, dialogBL->GetOrmasDal(), "PRODUCT", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with warehouse!")),
			QString(tr("Ok")));
		return;
	}
	
	BusinessLayer::Warehouse warehouse;
	warehouse.SetWarehouseTypeID(wType.GetID());
	std::string filterWarehouse = warehouse.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::WarehouseView> vecWarehouse = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage, filterWarehouse);

	

	BusinessLayer::Transport transport;
	std::string filterTransport = transport.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::TransportView> vecTransport = dialogBL->GetAllDataForClass<BusinessLayer::TransportView>(errorMessage, filterTransport);
	if (vecTransport.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find any transport for this period!")),
			QString(tr("Ok")));
		return;
	}

	BusinessLayer::TransportHistory sTransport;
	sTransport.SetTillDate(tillDateEdit->text().toUtf8().constData());
	std::string filterTransportHis = sTransport.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::TransportHistory> vecTransportHis = dialogBL->GetAllDataForClass<BusinessLayer::TransportHistory>(errorMessage, filterTransportHis);


	BusinessLayer::Production production;
	std::string filter = production.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::Production> vecProdn = dialogBL->GetAllDataForClass<BusinessLayer::Production>(errorMessage, filter);
	if (vecProdn.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find any production document for this period!")),
			QString(tr("Ok")));
		return;
	}

	if (vecProdn.size() > 0 )
	{
		DocForm *docForm = new DocForm(dialogBL, this);
		docForm->setAttribute(Qt::WA_DeleteOnClose);
		docForm->setWindowTitle(tr("Print common report"));
		QMdiSubWindow *generateComRepWindow = new QMdiSubWindow;
		generateComRepWindow->setWidget(docForm);
		generateComRepWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateComRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateComRepWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/common_report.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find Comification report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();
		//generating report
		std::map<int, double> prodnProductCount;
		std::map<int, double> orderProductCount;
		std::map<int, double> stockProductCount;
		std::map<int, double> stockHistoryCount;
		std::map<int, double> transportProductCount;
		std::map<int, double> transportHistoryCount;

		if (vecProdn.size() > 0)
		{
			BusinessLayer::ProductionList productionList;
			std::string prodnListFilter;
			std::vector<BusinessLayer::ProductionListView> vecProdnList;

			for each (auto item in vecProdn)
			{
				productionList.Clear();
				prodnListFilter.clear();
				productionList.SetProductionID(item.GetID());
				prodnListFilter = productionList.GenerateFilter(dialogBL->GetOrmasDal());
				vecProdnList.clear();
				vecProdnList = dialogBL->GetAllDataForClass<BusinessLayer::ProductionListView>(errorMessage, prodnListFilter);
				if (vecProdnList.size() > 0)
				{
					for each (auto listItem in vecProdnList)
					{
						if (prodnProductCount.find(listItem.GetProductID()) != prodnProductCount.end())
						{
							prodnProductCount.find(listItem.GetProductID())->second = prodnProductCount.find(listItem.GetProductID())->second + listItem.GetCount();
						}
						else
						{
							prodnProductCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
						}
					}
				}
			}

			if (vecTransportHis.size() > 0)
			{
				for each (auto item in vecTransportHis)
				{
					if (transportHistoryCount.find(item.GetProductID()) != transportHistoryCount.end())
					{
						transportHistoryCount.find(item.GetProductID())->second = transportHistoryCount.find(item.GetProductID())->second + item.GetCount();
					}
					else
					{
						transportHistoryCount.insert(std::make_pair(item.GetProductID(), item.GetCount()));
					}
				}
			}

			if (vecTransport.size() > 0)
			{
				BusinessLayer::TransportList cTransportList;
				std::string cTransportListFilter;
				std::vector<BusinessLayer::TransportListView> vecTransportList;
				for each (auto item in vecTransport)
				{
					vecTransportList.clear();
					cTransportListFilter.clear();
					cTransportList.SetTransportID(item.GetID());
					cTransportListFilter = cTransportList.GenerateFilter(dialogBL->GetOrmasDal());
					vecTransportList.clear();
					vecTransportList = dialogBL->GetAllDataForClass<BusinessLayer::TransportListView>(errorMessage, cTransportListFilter);
					if (vecTransportList.size() > 0)
					{
						for each (auto listItem in vecTransportList)
						{
							if (transportProductCount.find(listItem.GetProductID()) != transportProductCount.end())
							{
								transportProductCount.find(listItem.GetProductID())->second = transportProductCount.find(listItem.GetProductID())->second + listItem.GetCount();
							}
							else
							{
								transportProductCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							}
						}
					}
				}
			}

			BusinessLayer::Product product;
			BusinessLayer::Measure measure;

			reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
			reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);
			double sum = 0;
			double difSum = 0;
			double prodSum = 0;
			QString producedTableBody;
			for each (auto producedProduct in prodnProductCount)
			{
				product.Clear();
				product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), producedProduct.first, errorMessage);
				producedTableBody += "<tr>";
				producedTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(producedProduct.first) + "</td>";
				producedTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
				producedTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(producedProduct.second) + "</td>";
				producedTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(product.GetPrice()) + "</td>";
				producedTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(producedProduct.second * product.GetPrice()) + "</td>";
				producedTableBody += "</tr>";
				prodSum += producedProduct.second * product.GetPrice();
			}
			reportText.replace(QString("ProductTableBodyPh"), producedTableBody, Qt::CaseInsensitive);

			QString orderTableBody = "";
			
			// Order tables
			
			BusinessLayer::Branch branches;
			std::vector<BusinessLayer::Branch> vecBranch = dialogBL->GetAllDataForClass<BusinessLayer::Branch>(errorMessage);
			if (vecBranch.size() == 0)
			{
				QMessageBox::information(NULL, QString(tr("Info")),
					QString(tr("Cannot find any branch in production for this period!")),
					QString(tr("Ok")));
				return;
			}
			
			BusinessLayer::Order prOrder;
			std::vector<BusinessLayer::OrderView> vecOrder;
			BusinessLayer::CompanyEmployeeRelation crel;
			BusinessLayer::Employee emp;
			std::vector<int> empIDVec;
			std::string inFilter;
			std::vector<std::string> listFilter;
			std::string filterprOrder;

			for each (auto branch in vecBranch)
			{
				listFilter.clear();
				empIDVec.clear();
				inFilter.clear();
				filterprOrder.clear();

				crel.Clear();
				empIDVec = crel.GetAllEmployeeIDByBranchID(dialogBL->globalVar, dialogBL->GetOrmasDal(), branch.GetID(), errorMessage);
				if (empIDVec.size() <= 1)
					continue;
				inFilter = emp.GenerateINFilterForEmployee(dialogBL->globalVar, dialogBL->GetOrmasDal(), empIDVec);
				
				prOrder.Clear();
				vecOrder.clear();
				prOrder.SetStatusID(status.GetID());
				filterprOrder = prOrder.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
				listFilter.push_back(inFilter);
				listFilter.push_back(filterprOrder);
				filterprOrder = dialogBL->GetOrmasDal().ConcatenateFilters(listFilter);
				vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filterprOrder);
				
				if (vecOrder.size() > 0)
				{

					BusinessLayer::OrderList cOrdList;
					std::string cOrdListFilter;
					std::vector<BusinessLayer::OrderListView> vecOrdList;
					for each (auto item in vecOrder)
					{
						vecOrdList.clear();
						cOrdListFilter.clear();
						cOrdList.SetOrderID(item.GetID());
						cOrdListFilter = cOrdList.GenerateFilter(dialogBL->GetOrmasDal());
						vecOrdList.clear();
						vecOrdList = dialogBL->GetAllDataForClass<BusinessLayer::OrderListView>(errorMessage, cOrdListFilter);
						if (vecOrdList.size() > 0)
						{
							for each (auto listItem in vecOrdList)
							{
								if (orderProductCount.find(listItem.GetProductID()) != orderProductCount.end())
								{
									orderProductCount.find(listItem.GetProductID())->second = orderProductCount.find(listItem.GetProductID())->second + listItem.GetCount();
								}
								else
								{
									orderProductCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
								}
							}
						}
					}



					orderTableBody += "<h3>" + QString::fromLocal8Bit("Филиал: ");
					orderTableBody += branch.GetName().c_str();
					orderTableBody += "</h3>";
					orderTableBody += "<h4>" + QString::fromLocal8Bit("Продано продукции за отчетный период") + "</h4> ";
					orderTableBody += "<table style = 'width:800px; border: 1px solid black;font-size:12px; border-collapse: collapse;'>";
					orderTableBody += "<th>" + QString::fromLocal8Bit("ID продукта") + "</th>";
					orderTableBody += "<th>" + QString::fromLocal8Bit("Наименование продукта") + "</th>";
					orderTableBody += "<th>" + QString::fromLocal8Bit("Количество") + "</th>";
					orderTableBody += "<th>" + QString::fromLocal8Bit("Цена продукта") + "</ h>";
					orderTableBody += "<th>" + QString::fromLocal8Bit("Сумма") + "</th> ";
					orderTableBody += "<br/>";
					double oprodSum = 0;
					for each (auto orderProduct in orderProductCount)
					{
						product.Clear();
						product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), orderProduct.first, errorMessage);
						orderTableBody += "<tr>";
						orderTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(orderProduct.first) + "</td>";
						orderTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
						orderTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(orderProduct.second) + "</td>";
						orderTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(product.GetPrice()) + "</td>";
						orderTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(orderProduct.second * product.GetPrice()) + "</td>";
						orderTableBody += "</tr>";
						oprodSum += orderProduct.second * product.GetPrice();
					}
					orderTableBody += "<tr>";
					orderTableBody += "<td style = 'border: 1px solid black; text-align: center;'></td> ";
					orderTableBody += "<td style = 'border: 1px solid black; text-align: center;'></td> ";
					orderTableBody += "<td style = 'border: 1px solid black; text-align: center;'></td> ";
					orderTableBody += "<td style = 'border: 1px solid black; text-align: center;'>" + QString::fromLocal8Bit("Продано на сумму") + "</td> ";
					orderTableBody += "<td style = 'border: 1px solid black; text-align: center;'>";
					orderTableBody += QString::number(oprodSum, 'f',3);
					orderTableBody += "</td> \
									  																																																																												</tr> \
																																																																																																																																																																														</table><br/><br>";
					oprodSum = 0;
					orderProductCount.clear();
				}
			}
			reportText.replace(QString("SaleProductBodyPh"), orderTableBody, Qt::CaseInsensitive);
			
			double sprodSum = 0;
			QString stoclTableBody;
			QString totalStockTableBody;
			if (vecWarehouse.size() > 0)
			{
				for each (auto ware in vecWarehouse)
				{

					stoclTableBody += "<h3>" + QString::fromLocal8Bit("Склад: ");
					stoclTableBody += ware.GetName().c_str();
					stoclTableBody += "</h3>";
					stoclTableBody += "<h3>" + QString::fromLocal8Bit("Остаток на складе на конец периода") + "</h3>";
					stoclTableBody += "<table style = 'width:800px; border: 1px solid black;font-size:12px; border-collapse: collapse;'>";
					stoclTableBody += "<th>" + QString::fromLocal8Bit("ID продукта") + "</th> ";
					stoclTableBody += "<th>" + QString::fromLocal8Bit("Наименование продукта") + "</th> ";
					stoclTableBody += "<th>" + QString::fromLocal8Bit("Количество") + "</th> ";
					stoclTableBody += "<th>" + QString::fromLocal8Bit("Цена продукта") + "</th> ";
					stoclTableBody += "<th>" + QString::fromLocal8Bit("Сумма") + "</th>";
					BusinessLayer::StockView stockView;
					stockView.SetWarehouseID(ware.GetID());
					std::string filterStock = stockView.GenerateFilter(dialogBL->GetOrmasDal());
					std::vector<BusinessLayer::StockView> vecStock = dialogBL->GetAllDataForClass<BusinessLayer::StockView>(errorMessage, filterStock);


					BusinessLayer::StockHistoryView sHistory;
					sHistory.SetWarehouseID(ware.GetID());
					sHistory.SetHistoryDate(tillDateEdit->text().toUtf8().constData());
					std::string filterHistory = sHistory.GenerateFilter(dialogBL->GetOrmasDal());
					std::vector<BusinessLayer::StockHistoryView> vecHistory = dialogBL->GetAllDataForClass<BusinessLayer::StockHistoryView>(errorMessage, filterHistory);

					if (vecHistory.size() > 0)
					{
						for each (auto item in vecHistory)
						{
							if (stockHistoryCount.find(item.GetProductID()) != stockHistoryCount.end())
							{
								stockHistoryCount.find(item.GetProductID())->second = stockHistoryCount.find(item.GetProductID())->second + item.GetCount();
							}
							else
							{
								stockHistoryCount.insert(std::make_pair(item.GetProductID(), item.GetCount()));
							}
						}
					}
					else if (vecStock.size() > 0)
					{
						for each (auto item in vecStock)
						{
							if (stockProductCount.find(item.GetProductID()) != stockProductCount.end())
							{
								stockProductCount.find(item.GetProductID())->second = stockProductCount.find(item.GetProductID())->second + item.GetCount();
							}
							else
							{
								stockProductCount.insert(std::make_pair(item.GetProductID(), item.GetCount()));
							}
						}
					}

					if (stockHistoryCount.size() > 0)
					{
						for each (auto stockProduct in stockHistoryCount)
						{
							product.Clear();
							product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stockProduct.first, errorMessage);
							stoclTableBody += "<tr>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(stockProduct.first) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(stockProduct.second) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(product.GetPrice()) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(stockProduct.second * product.GetPrice()) + "</td>";
							stoclTableBody += "</tr>";
							sprodSum += stockProduct.second * product.GetPrice();
						}
					}
					else
					{
						for each (auto stockProduct in stockProductCount)
						{
							product.Clear();
							product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), stockProduct.first, errorMessage);
							stoclTableBody += "<tr>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(stockProduct.first) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(stockProduct.second) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(product.GetPrice()) + "</td>";
							stoclTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(stockProduct.second * product.GetPrice()) + "</td>";
							stoclTableBody += "</tr>";
							sprodSum += stockProduct.second * product.GetPrice();
						}

					}
					stoclTableBody += "<tr>";
					stoclTableBody += "<td style = 'border: 1px solid black; text-align: center;'></td> ";
					stoclTableBody += "<td style = 'border: 1px solid black; text-align: center;'></td> ";
					stoclTableBody += "<td style = 'border: 1px solid black; text-align: center;'></td> ";
					stoclTableBody += "<td style = 'border: 1px solid black; text-align: center;'>" + QString::fromLocal8Bit("Остаток на сумму") + "</td> ";
					stoclTableBody += "<td style = 'border: 1px solid black; text-align: center;'>";
					stoclTableBody += QString::number(sprodSum, 'f', 3);
					stoclTableBody += "</td> </table><br/>";
					if (sprodSum > 0)
						totalStockTableBody += stoclTableBody;
					stoclTableBody.clear();
					sprodSum = 0;
					stockHistoryCount.clear();
					stockProductCount.clear();
				}
			}
			reportText.replace(QString("StockPh"), totalStockTableBody, Qt::CaseInsensitive);
			
			
			double tprodSum = 0;
			QString transportTableBody;
			if (transportHistoryCount.size() > 0)
			{
				for each (auto transportProduct in transportHistoryCount)
				{
					if (transportProduct.second > 0)
					{

						product.Clear();
						product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transportProduct.first, errorMessage);
						transportTableBody += "<tr>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(transportProduct.first) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(transportProduct.second) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(product.GetPrice()) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(transportProduct.second * product.GetPrice()) + "</td>";
						transportTableBody += "</tr>";
						tprodSum += transportProduct.second * product.GetPrice();
					}
				}
			}
			else
			{
				for each (auto transportProduct in transportProductCount)
				{
					if (transportProduct.second > 0)
					{
						product.Clear();
						product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), transportProduct.first, errorMessage);
						transportTableBody += "<tr>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(transportProduct.first) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(transportProduct.second) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(product.GetPrice()) + "</td>";
						transportTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(transportProduct.second * product.GetPrice()) + "</td>";
						transportTableBody += "</tr>";
						tprodSum += transportProduct.second * product.GetPrice();
					}
				}
				
			}
			reportText.replace(QString("TransportPh"), transportTableBody, Qt::CaseInsensitive);


			reportText.replace(QString("SumPh"), QString::number(difSum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("AllSummPh"), QString::number(sum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("AllProdPh"), QString::number(prodSum, 'f', 3), Qt::CaseInsensitive);
			
			reportText.replace(QString("AllStocksPh"), QString::number(sprodSum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("AllTransportsPh"), QString::number(tprodSum, 'f', 3), Qt::CaseInsensitive);

			docForm->webEngineView->setHtml(reportText);
			docForm->SetContent(reportText);
			docForm->webEngineView->show();
			docForm->show();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot generate report for this period!")),
				QString(tr("Ok")));
		}
	}
	Close();
}

void GenerateComRep::Close()
{
	this->parentWidget()->close();
}

