#include "stdafx.h"
#include "GenerateSpecRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"


GenerateSpecRep::GenerateSpecRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateSpecRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateSpecRep::Close);
}

GenerateSpecRep::~GenerateSpecRep()
{
}

void GenerateSpecRep::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please contact with administrator, you have same troubles with statuses!")),
			QString(tr("Ok")));
		return;
	}
	BusinessLayer::ProductionConsumeRaw prRaw;
	prRaw.SetStatusID(status.GetID());
	std::string filterprRaw = prRaw.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
	std::vector<BusinessLayer::ProductionConsumeRawView> vecConRaw = dialogBL->GetAllDataForClass<BusinessLayer::ProductionConsumeRawView>(errorMessage, filterprRaw);
	if (vecConRaw.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find any consumption raw in production for this period!")),
			QString(tr("Ok")));
		return;
	}

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
	else
	{
		DocForm *docForm = new DocForm(dialogBL, this);
		docForm->setAttribute(Qt::WA_DeleteOnClose);
		docForm->setWindowTitle(tr("Print specification report"));
		QMdiSubWindow *generateSpecRepWindow = new QMdiSubWindow;
		generateSpecRepWindow->setWidget(docForm);
		generateSpecRepWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateSpecRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateSpecRepWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/spec_consume_report.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find specification report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();
		//generating report
		std::map<int, double> prodnProductCount;
		std::map<int, double> consumeProductCount;
		std::map<int, double> specProductCount;

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


			if (vecConRaw.size() > 0)
			{
				BusinessLayer::ProductionConsumeRawList cRawList;
				std::string cRawListFilter;
				std::vector<BusinessLayer::ProductionConsumeRawListView> vecCRawList;
				for each (auto item in vecConRaw)
				{
					cRawList.Clear();
					cRawListFilter.clear();
					cRawList.SetProductionConsumeRawID(item.GetID());
					cRawListFilter = cRawList.GenerateFilter(dialogBL->GetOrmasDal());
					vecCRawList.clear();
					vecCRawList = dialogBL->GetAllDataForClass<BusinessLayer::ProductionConsumeRawListView>(errorMessage, cRawListFilter);
					if (vecCRawList.size() > 0)
					{
						for each (auto listItem in vecCRawList)
						{
							if (consumeProductCount.find(listItem.GetProductID()) != consumeProductCount.end())
							{
								consumeProductCount.find(listItem.GetProductID())->second = consumeProductCount.find(listItem.GetProductID())->second + listItem.GetCount();
							}
							else
							{
								consumeProductCount.insert(std::make_pair(listItem.GetProductID(), listItem.GetCount()));
							}
						}
					}
				}
			}

			BusinessLayer::Specification specification;
			BusinessLayer::SpecificationList specList;
			std::vector<BusinessLayer::SpecificationListView> vecSpecList;
			std::string specFilter;

			for each (auto product in prodnProductCount)
			{
				specification.Clear();
				if (!specification.GetSpecificationByProductID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.first, errorMessage))
				{
					QMessageBox::information(NULL, QString(tr("Info")),
						QString(tr("This product does't have specification! Cannot print it")),
						QString(tr("Ok")));
					return;
				}
				specFilter.clear();
				specList.Clear();
				specList.SetSpecificationID(specification.GetID());
				specFilter = specList.GenerateFilter(dialogBL->GetOrmasDal());
				vecSpecList.clear();
				vecSpecList = dialogBL->GetAllDataForClass<BusinessLayer::SpecificationListView>(errorMessage, specFilter);
				if (vecSpecList.size() > 0)
				{
					for each (auto specItem in vecSpecList)
					{
						if (specProductCount.find(specItem.GetProductID()) != specProductCount.end())
						{
							specProductCount.find(specItem.GetProductID())->second = specProductCount.find(specItem.GetProductID())->second + (specItem.GetCount() * product.second);
						}
						else
						{
							specProductCount.insert(std::make_pair(specItem.GetProductID(), (specItem.GetCount() * product.second)));
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

			QString specTableBody;
			for each (auto specProduct in specProductCount)
			{
				product.Clear();
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), specProduct.first, errorMessage))
				{
					measure.Clear();
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
					{
						specTableBody += "<tr>";
						specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
						specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(specProduct.second) + "</td>";
						specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
						if (consumeProductCount.find(product.GetID()) != consumeProductCount.end())
						{
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(consumeProductCount.find(product.GetID())->second) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(consumeProductCount.find(product.GetID())->second - specProduct.second) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number((consumeProductCount.find(product.GetID())->second - specProduct.second) * product.GetPrice()) + "</td>";
							difSum += (consumeProductCount.find(product.GetID())->second - specProduct.second) * product.GetPrice();
							sum += consumeProductCount.find(product.GetID())->second * product.GetPrice();
						}
						else
						{
							specTableBody += "<td style='border: 1px solid black; text - align: center; '> 0 </td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(specProduct.second * -1) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(specProduct.second * -1 * product.GetPrice()) + "</td>";
							difSum += specProduct.second * -1 * product.GetPrice();
						}
					}
				}
			}
			for each (auto consumedProduct in consumeProductCount)
			{
				product.Clear();
				if (product.GetProductByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), consumedProduct.first, errorMessage))
				{
					measure.Clear();
					if (measure.GetMeasureByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), product.GetMeasureID(), errorMessage))
					{
						if (specProductCount.find(product.GetID()) == specProductCount.end())
						{

							specTableBody += "<tr>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(product.GetName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '> 0 </td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(consumedProduct.second) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(consumedProduct.second) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString(measure.GetShortName().c_str()) + "</td>";
							specTableBody += "<td style='border: 1px solid black; text - align: center; '>" + QString::number(consumedProduct.second * product.GetPrice()) + "</td>";
							difSum += consumedProduct.second * product.GetPrice();
							sum += consumedProduct.second * product.GetPrice();
						}
					}
				}
			}
			reportText.replace(QString("SpecTableBodyPh"), specTableBody, Qt::CaseInsensitive);
			reportText.replace(QString("SumPh"), QString::number(difSum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("AllSummPh"), QString::number(sum, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("AllProdPh"), QString::number(prodSum,'f', 3), Qt::CaseInsensitive);

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

void GenerateSpecRep::Close()
{
	this->parentWidget()->close();
}

