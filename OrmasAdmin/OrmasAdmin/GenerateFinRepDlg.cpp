#include "stdafx.h"
#include "GenerateFinRepDlg.h"
#include "MainForm.h"
#include "DocForm.h"


GenerateFinRep::GenerateFinRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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
		prevFromMonth += std::to_string(year-1);
		pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		prevTillMonth = std::to_string(coundOfDays);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(12);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(year-1);
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
		prevFromMonth += std::to_string(month-1);
		prevFromMonth += ".";
		prevFromMonth += std::to_string(year);
		pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		prevTillMonth = std::to_string(coundOfDays);
		prevTillMonth += ".";
		prevTillMonth += std::to_string(month-1);
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
			prevFromMonth += std::to_string(year-1);
			pastMonthDate = (QDate::fromString(prevFromMonth.c_str(), "dd.MM.yyyy"));
			coundOfDays = pastMonthDate.daysInMonth();
			prevTillMonth = std::to_string(coundOfDays);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(12);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(year-1);
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
			prevFromMonth += std::to_string(month-2);
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
			prevTillMonth += std::to_string(month-2);
			prevTillMonth += ".";
			prevTillMonth += std::to_string(year);
		}
	}
	fromDateEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	tillDateEdit->setDate(QDate::fromString(endDate.c_str(), "dd.MM.yyyy"));

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateFinRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateFinRep::Close);
}

GenerateFinRep::~GenerateFinRep()
{
	delete fReport;
}

void GenerateFinRep::Generate()
{
	CalculatePrevMonth(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), prevFromMonth, prevTillMonth);
	fReport->SetFromDate(fromDateEdit->text().toUtf8().constData());
	fReport->SetTillDate(tillDateEdit->text().toUtf8().constData());
	std::string filter = fReport->GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::FinancialReport> vecFinRep = dialogBL->GetAllDataForClass<BusinessLayer::FinancialReport>(errorMessage, filter);
	if (vecFinRep.size() == 0)
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report for this period!")),
			QString(tr("Ok")));
	}
	else
	{
		DocForm *docForm = new DocForm(dialogBL, this);
		docForm->setAttribute(Qt::WA_DeleteOnClose);
		docForm->setWindowTitle(tr("Print financial report"));
		QMdiSubWindow *generateFinRepWindow = new QMdiSubWindow;
		generateFinRepWindow->setWidget(docForm);
		generateFinRepWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateFinRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateFinRepWindow);
		
		//read template
		QFile file;
		file.setFileName(":/docs/financial_report.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();
		//generating report
		if (vecFinRep.size() == 1)
		{
			double allIncome = 0;
			double allOperOut = 0;
			double operIncome = 0;
			double operOutIn = 0;
			for each (auto item in vecFinRep)
			{
				reportText.replace(QString("fromDatePh"), fromDateEdit->text(), Qt::CaseInsensitive);
				reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);
				reportText.replace(QString("chepter10Ph"), QString::number(item.GetAccount44010()*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter20Ph"), QString::number(item.GetAccount55010(), 'f', 3), Qt::CaseInsensitive);
				allIncome = item.GetAccount44010()*(-1) - item.GetAccount55010();
				reportText.replace(QString("chepter30Ph"), QString::number(allIncome ,'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter40Ph"), QString::number(item.GetAccount552() ,'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter41Ph"), QString::number(item.GetAccount55270() ,'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter50Ph"), QString::number(item.GetAccount553() ,'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter51Ph"), QString::number(item.GetAccount55321() ,'f', 3), Qt::CaseInsensitive);
				allOperOut = item.GetAccount552() + item.GetAccount553();
				reportText.replace(QString("chepter60Ph"), QString::number(allOperOut, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter70Ph"), QString::number(item.GetAccount44020_90() * (-1),'f', 3), Qt::CaseInsensitive);
				operIncome = allIncome - allOperOut - item.GetAccount44020_90();
				reportText.replace(QString("chepter80Ph"), QString::number(operIncome, 'f', 3), Qt::CaseInsensitive);
				operOutIn = item.GetAccount66010_66110() + item.GetAccount66020_66120() + item.GetAccount66040_66140() +
					item.GetAccount66050_66150() + item.GetAccount66060_66160() + item.GetAccount66070_66170();
				reportText.replace(QString("chepter90Ph"), "", Qt::CaseInsensitive);
				reportText.replace(QString("chepter100Ph"), QString::number(item.GetAccount66010_66110()*(-1) ,'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter110Ph"), QString::number(item.GetAccount66020_66120()*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter120Ph"), QString::number(item.GetAccount66040_66140()*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter130Ph"), QString::number(item.GetAccount66050_66150()*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter140Ph"), QString::number(item.GetAccount66060_66160()*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter150Ph"), QString::number(item.GetAccount66130(), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter160Ph"), QString::number(item.GetAccount66070_66170()*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter170Ph"), QString::number(operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter180Ph"), "", Qt::CaseInsensitive);
				reportText.replace(QString("chepter190Ph"), QString::number(operIncome + operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepter200Ph"), "", Qt::CaseInsensitive);
				reportText.replace(QString("chepter210Ph"), QString::number(operIncome + operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
			}

			BusinessLayer::FinancialReport prevFinRep;
			prevFinRep.SetFromDate(prevFromMonth);
			prevFinRep.SetTillDate(prevTillMonth);
			std::string filterPrev = prevFinRep.GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::FinancialReport> vecPrevFinRep = dialogBL->GetAllDataForClass<BusinessLayer::FinancialReport>(errorMessage, filterPrev);
			if (vecPrevFinRep.size() == 0)
			{
				reportText.replace(QString("chepterprev10Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev20Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev30Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev40Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev41Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev50Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev51Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev60Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev70Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev80Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev90Ph"), "", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev100Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev110Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev120Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev130Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev140Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev150Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev160Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev170Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev180Ph"), "", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev190Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev200Ph"), "", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev210Ph"), "0", Qt::CaseInsensitive);
			}
			if (vecPrevFinRep.size() == 1)
			{
				for each (auto item in vecPrevFinRep)
				{
					reportText.replace(QString("chepterprev10Ph"), QString::number(item.GetAccount44010()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev20Ph"), QString::number(item.GetAccount55010(), 'f', 3), Qt::CaseInsensitive);
					allIncome = item.GetAccount44010()*(-1) - item.GetAccount55010();
					reportText.replace(QString("chepterprev30Ph"), QString::number(allIncome, 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev40Ph"), QString::number(item.GetAccount552(), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev41Ph"), QString::number(item.GetAccount55270(), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev50Ph"), QString::number(item.GetAccount553(), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev51Ph"), QString::number(item.GetAccount55321(), 'f', 3), Qt::CaseInsensitive);
					allOperOut = item.GetAccount552() + item.GetAccount553();
					reportText.replace(QString("chepterprev60Ph"), QString::number(allOperOut, 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev70Ph"), QString::number(item.GetAccount44020_90() * (-1), 'f', 3), Qt::CaseInsensitive);
					operIncome = allIncome - allOperOut - item.GetAccount44020_90();
					reportText.replace(QString("chepterprev80Ph"), QString::number(operIncome, 'f', 3), Qt::CaseInsensitive);
					operOutIn = item.GetAccount66010_66110() + item.GetAccount66020_66120() + item.GetAccount66040_66140() +
						item.GetAccount66050_66150() + item.GetAccount66060_66160() + item.GetAccount66070_66170();
					reportText.replace(QString("chepterprev90Ph"), "", Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev100Ph"), QString::number(item.GetAccount66010_66110()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev110Ph"), QString::number(item.GetAccount66020_66120()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev120Ph"), QString::number(item.GetAccount66040_66140()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev130Ph"), QString::number(item.GetAccount66050_66150()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev140Ph"), QString::number(item.GetAccount66060_66160()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev150Ph"), QString::number(item.GetAccount66130(), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev160Ph"), QString::number(item.GetAccount66070_66170()*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev170Ph"), QString::number(operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev180Ph"), "", Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev190Ph"), QString::number(operIncome + operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev200Ph"), "", Qt::CaseInsensitive);
					reportText.replace(QString("chepterprev210Ph"), QString::number(operIncome + operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
				}
			}
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
		Close();
	}
}

void GenerateFinRep::Close()
{
	this->parentWidget()->close();
}

void GenerateFinRep::CalculatePrevMonth(std::string fromMonth, std::string tilMonth, std::string& prevFromMonth, std::string& tillFromMonth)
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
	tillFromMonth += ".";
	if (month < 11)
	{
		tillFromMonth += "0";
		tillFromMonth += std::to_string(month);
	}
	else
	{
		tillFromMonth += std::to_string(month);
	}
	tillFromMonth += ".";
	tillFromMonth += std::to_string(year);

}
