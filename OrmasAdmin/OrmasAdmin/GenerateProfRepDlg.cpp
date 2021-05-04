#include "stdafx.h"
#include "GenerateProfRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"
#include <map>


GenerateProfRep::GenerateProfRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateProfRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateProfRep::Close);
}

GenerateProfRep::~GenerateProfRep()
{
}

void GenerateProfRep::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::Order order;
	order.SetStatusID(status.GetID());
	std::string filter = order.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::OrderView> vecOrder = dialogBL->GetAllDataForClass<BusinessLayer::OrderView>(errorMessage, filter);
	if (vecOrder.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find any order for this period!")),
			QString(tr("Ok")));
		return;
	}
	else
	{
		DocForm *docForm = new DocForm(dialogBL, this);
		docForm->setAttribute(Qt::WA_DeleteOnClose);
		docForm->setWindowTitle(tr("Print products profitability report"));
		QMdiSubWindow *generateProfRepWindow = new QMdiSubWindow;
		generateProfRepWindow->setWidget(docForm);
		generateProfRepWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateProfRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateProfRepWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/profitability.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find profitability report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();
		//generating report
		if (vecOrder.size() > 0)
		{
			BusinessLayer::OrderList orderList;
			std::string orderListFilter;
			std::map<int, double> productCount;
			std::map<int, double> productSum;
			std::vector<BusinessLayer::OrderListView> vecOrderList;
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

			BusinessLayer::Product product;
			BusinessLayer::NetCost nCost;
			if (productCount.size() != productSum.size())
			{
				QMessageBox::information(NULL, QString(tr("Info")),
					QString(tr("Calculation is failed. Please restart the report!")),
					QString(tr("Ok")));
				return;
			}
			reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
			reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);
			double sum = 0;
			double netSum = 0;
			double negSum = 0;
			QString tableBody;
			for each (auto mapCountItem in productCount)
			{
				product.Clear();
				nCost.Clear();
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage) &&
					nCost.GetNetCostByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), mapCountItem.first, errorMessage))
				{
					sum += productSum.find(mapCountItem.first)->second;
					netSum += nCost.GetValue()*mapCountItem.second;
					if (productSum.find(mapCountItem.first)->second - nCost.GetValue()*mapCountItem.second < 0)
						negSum += productSum.find(mapCountItem.first)->second - nCost.GetValue()*mapCountItem.second;

					tableBody += "<tr>";
					tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(mapCountItem.first) + "</td>";
					tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
					tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(mapCountItem.second , 'f', 3) + "</td>";
					tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(nCost.GetValue()*mapCountItem.second, 'f', 3) + "</td>";
					tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(productSum.find(mapCountItem.first)->second, 'f', 3) + "</td>";
					tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number((productSum.find(mapCountItem.first)->second - nCost.GetValue()*mapCountItem.second), 'f', 3) + "</td>";
					tableBody += "</tr>";
				}
			}

			tableBody += "<tr>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::fromWCharArray(L"Вся выручка")+"</td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(sum, 'f', 3) + "</td>";
			tableBody += "</tr>";

			tableBody += "<tr>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::fromWCharArray(L"Сумма себестоимости по всем продуктам")+"</td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(netSum, 'f', 3) + "</td>";
			tableBody += "</tr>";

			tableBody += "<tr>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '></td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::fromWCharArray(L"Сумма убыточной реализации")+"</td>";
			tableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(negSum,'f',3) + "</td>";
			tableBody += "</tr>";

			reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
			docForm->webEngineView->setHtml(reportText);
			docForm->SetContent(reportText);
			docForm->webEngineView->show();
			docForm->show();
		}
		else
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Report is empty! Cannot print it")),
				QString(tr("Ok")));
			return;
		}
	}
	Close();
}

void GenerateProfRep::Close()
{
	this->parentWidget()->close();
}
