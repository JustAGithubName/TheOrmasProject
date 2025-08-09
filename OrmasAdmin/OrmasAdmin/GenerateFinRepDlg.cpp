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
	radioWidget->hide();
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
	dateMonthlyEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	dateYearlyEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateFinRep::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateFinRep::Close);
	QObject::connect(dateMonthlyEdit, &QDateEdit::dateChanged, this, &GenerateFinRep::ChangeRadio);
	QObject::connect(dateYearlyEdit, &QDateEdit::dateChanged, this, &GenerateFinRep::ChangeRadio);
	QObject::connect(fromDateEdit, &QDateEdit::dateChanged, this, &GenerateFinRep::ChangeRadio);
	QObject::connect(tillDateEdit, &QDateEdit::dateChanged, this, &GenerateFinRep::ChangeRadio);
}

GenerateFinRep::~GenerateFinRep()
{
	delete fReport;
}

void GenerateFinRep::Generate()
{
	if (radioPeriod->isChecked())
	{
		int count = CalculateMonthCount(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
		if (count == 0)
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Please select correct period! If you check for one month please use monthly report!")),
				QString(tr("Ok")));
		}
		QDate date;
		QDate nextDate;
		QString startDate="";
		QString endDate="";

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
		file.setFileName(":/docs/financial_report_period.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();

		QString monthHlder = "";
		
		QString chepter00Ph = "";
		QString chepter10Ph ="";
		QString chepter20Ph = "";
		QString chepter30Ph = "";
		QString chepter00100Ph = "";
		QString chepter40Ph = "";
		QString chepter41Ph = "";
		QString chepter50Ph = "";
		QString chepter51Ph = "";
		QString chepter60Ph = "";
		QString chepter70Ph = "";
		QString chepter80Ph = "";
		QString chepter90Ph = "";
		QString chepter100Ph = "";
		QString chepter110Ph = "";
		QString chepter120Ph = "";
		QString chepter130Ph = "";
		QString chepter140Ph = "";
		QString chepter150Ph = "";
		QString chepter160Ph = "";
		QString chepter170Ph = "";
		QString chepter180Ph = "";
		QString chepter190Ph = "";
		QString chepter200Ph = "";
		QString chepter210Ph = "";

		double sumChepter10Ph = 0;
		double sumChepter20Ph = 0;
		double sumChepter30Ph = 0;
		double sumChepter40Ph = 0;
		double sumChepter41Ph = 0;
		double sumChepter50Ph = 0;
		double sumChepter51Ph = 0;
		double sumChepter60Ph = 0;
		double sumChepter70Ph = 0;
		double sumChepter80Ph = 0;
		double sumChepter90Ph = 0;
		double sumChepter100Ph = 0;
		double sumChepter110Ph = 0;
		double sumChepter120Ph = 0;
		double sumChepter130Ph = 0;
		double sumChepter140Ph = 0;
		double sumChepter150Ph = 0;
		double sumChepter160Ph = 0;
		double sumChepter170Ph = 0;
		double sumChepter180Ph = 0;
		double sumChepter190Ph = 0;
		double sumChepter200Ph = 0;
		double sumChepter210Ph = 0;
		
		
		for (int i = 0; i < count; i++)
		{
			date = QDate::fromString(fromDateEdit->text().toUtf8().constData(), "MM.yyyy");
			
			if (i == 0)
			{
				if ((date.month() + i) / 12 < 1)
				{
					startDate = "01." + QString::number(date.month()) + "." + QString::number(date.year());
					endDate = QString::number(date.daysInMonth()) + "." + QString::number(date.month()) + "." + QString::number(date.year());
				}
				else
				{
					startDate = "01." + QString::number(12 - date.month()) + "." + QString::number(date.year());
					endDate = QString::number(date.daysInMonth()) + "." + QString::number(12 - date.month()) + "." + QString::number(date.year() *((date.month()+i) / 12));
				}
			}
			else
			{
				if ((date.month() + i) / 12 <= 1)
				{
					nextDate = QDate::fromString("01." + QString::number(date.month() + i) + "." + QString::number(date.year()), "dd.MM.yyyy");
				}
				else
				{
					nextDate = QDate::fromString("01." + QString::number(12 - nextDate.month()) + "." + QString::number(nextDate.year() *((nextDate.month() + i) / 12)), "dd.MM.yyyy");

				}
			    startDate = "01." + QString::number(nextDate.month()) + "." + QString::number(nextDate.year());
				endDate = QString::number(nextDate.daysInMonth()) + "." + QString::number(nextDate.month()) + "." + QString::number(nextDate.year());
				
			}
			
			QString fmDate = "";
			if (fmDate.isEmpty())
				fmDate = startDate;
			reportText.replace(QString("fromDatePh"), fmDate, Qt::CaseInsensitive);
			
			//CalculatePrevMonth(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), prevFromMonth, prevTillMonth);
			fReport->SetFromDate(startDate.toStdString());
			fReport->SetTillDate(endDate.toStdString());
			std::string filter = "";
			filter = fReport->GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::FinancialReport> vecFinRep;
			vecFinRep = dialogBL->GetAllDataForClass<BusinessLayer::FinancialReport>(errorMessage, filter);
			if (vecFinRep.size() == 0)
			{
				continue;
			}
			else
			{
				monthHlder += "<th><b>" + endDate + "</b></th>";
				//generating report
				if (vecFinRep.size() == 1)
				{
					double allIncome = 0;
					double allOperOut = 0;
					double operIncome = 0;
					double operOutIn = 0;
					
					
					for each (auto item in vecFinRep)
					{
						chepter00Ph += "<td></td>";
						chepter00100Ph += "<td></td>";
						
						chepter10Ph += "<td>" + QString::number(item.GetAccount44010()*(-1), 'f', 3) + "</td>";
						sumChepter10Ph += item.GetAccount44010()*(-1);
						
						chepter20Ph += "<td>"+QString::number(item.GetAccount55010(), 'f', 3)+"</td>";
						sumChepter20Ph += item.GetAccount55010();

						allIncome = item.GetAccount44010()*(-1) - item.GetAccount55010();
						chepter30Ph +="<td>"+ QString::number(allIncome, 'f', 3)+"</td>";
						sumChepter30Ph += allIncome;

						chepter40Ph +="<td>"+ QString::number(item.GetAccount552(), 'f', 3) + "</td>";
						sumChepter40Ph += item.GetAccount552();

						chepter41Ph +="<td>" + QString::number(item.GetAccount55270(), 'f', 3) +"</td>";
						sumChepter41Ph += item.GetAccount55270();

						chepter50Ph += "<td>" +QString::number(item.GetAccount553(), 'f', 3) + "</td>";
						sumChepter50Ph += item.GetAccount553();

						chepter51Ph += "<td>" + QString::number(item.GetAccount55321(), 'f', 3) + "</td>";
						sumChepter51Ph += item.GetAccount55321();

						allOperOut = item.GetAccount552() + item.GetAccount553();
						chepter60Ph += "<td>" + QString::number(allOperOut, 'f', 3) + "</td>";
						sumChepter60Ph += allOperOut;
						
						chepter70Ph += "<td>"+ QString::number(item.GetAccount44020_90() * (-1), 'f', 3)+ "</td>";
						sumChepter70Ph += item.GetAccount44020_90() * (-1);

						operIncome = allIncome - allOperOut - item.GetAccount44020_90();
						chepter80Ph += "<td>" + QString::number(operIncome, 'f', 3) + "</td>";
						sumChepter80Ph += operIncome;

						operOutIn = item.GetAccount66010_66110() + item.GetAccount66020_66120() + item.GetAccount66040_66140() +
							item.GetAccount66050_66150() + item.GetAccount66060_66160() + item.GetAccount66070_66170();
						chepter90Ph +="<td></td>";

						chepter100Ph += "<td>" + QString::number(item.GetAccount66010_66110()*(-1), 'f', 3) + "</td>";
						sumChepter100Ph += item.GetAccount66010_66110()*(-1);

						chepter110Ph += "<td>"+QString::number(item.GetAccount66020_66120()*(-1), 'f', 3) +"</td>";
						sumChepter110Ph += item.GetAccount66020_66120()*(-1);

						chepter120Ph +="<td>"+ QString::number(item.GetAccount66040_66140()*(-1), 'f', 3) +"</td>";
						sumChepter120Ph += item.GetAccount66040_66140()*(-1);
						
						chepter130Ph += "<td>"+ QString::number(item.GetAccount66050_66150()*(-1), 'f', 3) +"</td>";
						sumChepter130Ph += item.GetAccount66050_66150()*(-1);

						chepter140Ph += "<td>" + QString::number(item.GetAccount66060_66160()*(-1), 'f', 3) + "</td>";
						sumChepter140Ph += item.GetAccount66060_66160()*(-1);

						chepter150Ph +="<td>" + QString::number(item.GetAccount66130(), 'f', 3) + "</td>";
						sumChepter150Ph += item.GetAccount66130();

						chepter160Ph += "<td>" + QString::number(item.GetAccount66070_66170()*(-1), 'f', 3) + "</td>";
						sumChepter160Ph += item.GetAccount66070_66170()*(-1);

						chepter170Ph += "<td>" + QString::number(operOutIn*(-1), 'f', 3) + "</td>";
						sumChepter170Ph += operOutIn*(-1);
					
						chepter180Ph += "<td></td>"; 
						
						chepter190Ph += "<td>" + QString::number(operIncome + operOutIn*(-1), 'f', 3) + "</td>";
						sumChepter190Ph += operIncome + operOutIn*(-1);
						
						chepter200Ph += "<td></td>";  
						
						chepter210Ph += "<td>" + QString::number(operIncome + operOutIn*(-1), 'f', 3) + "</td>";
						sumChepter210Ph += operIncome + operOutIn*(-1);
					}

					
					
				}
				else
				{
					continue;
				}

			}
		}
		
		monthHlder += "<th><b>" + QString::fromWCharArray(L"Итого") + "</b></th>";
		chepter00100Ph += "<td></td>";
		chepter10Ph += "<td>" + QString::number(sumChepter10Ph, 'f', 3) + "</td>";
		chepter20Ph += "<td>" + QString::number(sumChepter20Ph, 'f', 3) + "</td>";
		chepter30Ph += "<td>" + QString::number(sumChepter30Ph, 'f', 3) + "</td>";
		chepter40Ph += "<td>" + QString::number(sumChepter40Ph, 'f', 3) + "</td>";
		chepter41Ph += "<td>" + QString::number(sumChepter41Ph, 'f', 3) + "</td>";
		chepter50Ph += "<td>" + QString::number(sumChepter50Ph, 'f', 3) + "</td>";
		chepter51Ph += "<td>" + QString::number(sumChepter51Ph, 'f', 3) + "</td>";
		chepter60Ph += "<td>" + QString::number(sumChepter60Ph, 'f', 3) + "</td>";
		chepter70Ph += "<td>" + QString::number(sumChepter70Ph, 'f', 3) + "</td>";
		chepter80Ph += "<td>" + QString::number(sumChepter80Ph, 'f', 3) + "</td>";
		chepter90Ph += "<td></td>";
		chepter100Ph += "<td>" + QString::number(sumChepter100Ph, 'f', 3) + "</td>";
		chepter110Ph += "<td>" + QString::number(sumChepter110Ph, 'f', 3) + "</td>";
		chepter120Ph += "<td>" + QString::number(sumChepter120Ph, 'f', 3) + "</td>";
		chepter130Ph += "<td>" + QString::number(sumChepter130Ph, 'f', 3) + "</td>";
		chepter140Ph += "<td>" + QString::number(sumChepter140Ph, 'f', 3) + "</td>";
		chepter150Ph += "<td>" + QString::number(sumChepter150Ph, 'f', 3) + "</td>";
		chepter160Ph += "<td>" + QString::number(sumChepter160Ph, 'f', 3) + "</td>";
		chepter170Ph += "<td>" + QString::number(sumChepter170Ph, 'f', 3) + "</td>";
		chepter180Ph += "<td></td>";
		chepter190Ph += "<td>" + QString::number(sumChepter190Ph, 'f', 3) + "</td>";
		chepter200Ph += "<td></td>";
		chepter210Ph += "<td>" + QString::number(sumChepter210Ph, 'f', 3) + "</td>";
		

		reportText.replace(QString("MonthPH"), monthHlder, Qt::CaseInsensitive);
		reportText.replace(QString("chepter00Ph"), chepter00Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter00100Ph"), chepter00100Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter10Ph"), chepter10Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter20Ph"), chepter20Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter30Ph"), chepter30Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter40Ph"), chepter40Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter41Ph"), chepter41Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter50Ph"), chepter50Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter51Ph"), chepter51Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter60Ph"), chepter60Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter70Ph"), chepter70Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter80Ph"), chepter80Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter90Ph"), chepter90Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter100Ph"), chepter100Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter110Ph"), chepter110Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter120Ph"), chepter120Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter130Ph"), chepter130Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter140Ph"), chepter140Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter150Ph"), chepter150Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter160Ph"), chepter160Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter170Ph"), chepter170Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter180Ph"), chepter180Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter190Ph"), chepter190Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter200Ph"), chepter200Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter210Ph"), chepter210Ph, Qt::CaseInsensitive);

		
		reportText.replace(QString("tillDatePh"), endDate, Qt::CaseInsensitive);
		docForm->webEngineView->setHtml(reportText);
		docForm->SetContent(reportText);
		docForm->webEngineView->show();
		docForm->show();
		Close();
	}
	else if (radioMon->isChecked())
	{
		QDate date;
		QDate nextDate;
		QString startDate = "";
		QString endDate = "";
		date = QDate::fromString(dateMonthlyEdit->text().toUtf8().constData(), "MM.yyyy");

		startDate = "01.";
		if (date.month() < 10)
			startDate += "0";
		startDate += QString::number(date.month()) + "." + QString::number(date.year());

		endDate = QString::number(date.daysInMonth());
		endDate += ".";
		if (date.month() < 10)
			endDate += "0";
		endDate += QString::number(date.month()) + "." + QString::number(date.year());
		

		CalculatePrevMonth(startDate.toStdString(), endDate.toStdString(), prevFromMonth, prevTillMonth);
		fReport->SetFromDate(startDate.toStdString());
		fReport->SetTillDate(endDate.toStdString());
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
			if (ownFormCbx->isChecked())
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
				file.setFileName(":/docs/financial_report_letterhead.html");
				if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				{
					QMessageBox::information(NULL, QString(tr("Info")),
						QString(tr("Cannot find report tamplate!")),
						QString(tr("Ok")));
					return;
				}
				QString reportText = QString::fromUtf8(file.readAll());
				
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
						reportText.replace(QString("percent20Ph"), QString::number(item.GetAccount55010() / item.GetAccount44010()*(-1)*100, 'f', 2), Qt::CaseInsensitive);
						reportText.replace(QString("chepter40Ph"), QString::number(item.GetAccount552(), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("percent40Ph"), QString::number(item.GetAccount552() / item.GetAccount44010()*(-1) * 100, 'f', 2), Qt::CaseInsensitive);
						reportText.replace(QString("chepter50Ph"), QString::number(item.GetAccount553(), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("percent50Ph"), QString::number(item.GetAccount553() / item.GetAccount44010()*(-1) * 100, 'f', 2), Qt::CaseInsensitive);
						allOperOut = item.GetAccount552() + item.GetAccount553();
						reportText.replace(QString("chepter70Ph"), QString::number(item.GetAccount44020_90() * (-1), 'f', 3), Qt::CaseInsensitive);
						operIncome = allIncome - allOperOut - item.GetAccount44020_90();
						reportText.replace(QString("chepter80Ph"), QString::number(operIncome, 'f', 3), Qt::CaseInsensitive);
						operOutIn = item.GetAccount66010_66110() + item.GetAccount66020_66120() + item.GetAccount66040_66140() +
							item.GetAccount66050_66150() + item.GetAccount66060_66160() + item.GetAccount66070_66170();
						reportText.replace(QString("percent80Ph"), QString::number(operIncome / item.GetAccount44010()*(-1) * 100, 'f', 2), Qt::CaseInsensitive);
						
						reportText.replace(QString("chepter110Ph"), QString::number(item.GetAccount66020_66120()*(-1), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter120Ph"), QString::number(item.GetAccount66040_66140()*(-1), 'f', 3), Qt::CaseInsensitive);
						
						reportText.replace(QString("chepter150Ph"), QString::number(item.GetAccount66130(), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter160Ph"), QString::number(item.GetAccount66070_66170()*(-1), 'f', 3), Qt::CaseInsensitive);
						
						reportText.replace(QString("chepter210Ph"), QString::number(operIncome + operOutIn*(-1), 'f', 3), Qt::CaseInsensitive);
					}
					
					docForm->webEngineView->setHtml(reportText);
					docForm->SetContent(reportText);
					docForm->webEngineView->show();
					docForm->show();
					Close();
				}
				else
				{
					QMessageBox::information(NULL, QString(tr("Info")),
						QString(tr("Cannot generate report for this period!")),
						QString(tr("Ok")));
				}
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
						reportText.replace(QString("chepter30Ph"), QString::number(allIncome, 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter40Ph"), QString::number(item.GetAccount552(), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter41Ph"), QString::number(item.GetAccount55270(), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter50Ph"), QString::number(item.GetAccount553(), 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter51Ph"), QString::number(item.GetAccount55321(), 'f', 3), Qt::CaseInsensitive);
						allOperOut = item.GetAccount552() + item.GetAccount553();
						reportText.replace(QString("chepter60Ph"), QString::number(allOperOut, 'f', 3), Qt::CaseInsensitive);
						reportText.replace(QString("chepter70Ph"), QString::number(item.GetAccount44020_90() * (-1), 'f', 3), Qt::CaseInsensitive);
						operIncome = allIncome - allOperOut - item.GetAccount44020_90();
						reportText.replace(QString("chepter80Ph"), QString::number(operIncome, 'f', 3), Qt::CaseInsensitive);
						operOutIn = item.GetAccount66010_66110() + item.GetAccount66020_66120() + item.GetAccount66040_66140() +
							item.GetAccount66050_66150() + item.GetAccount66060_66160() + item.GetAccount66070_66170();
						reportText.replace(QString("chepter90Ph"), "", Qt::CaseInsensitive);
						reportText.replace(QString("chepter100Ph"), QString::number(item.GetAccount66010_66110()*(-1), 'f', 3), Qt::CaseInsensitive);
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
					Close();
				}
				else
				{
					QMessageBox::information(NULL, QString(tr("Info")),
						QString(tr("Cannot generate report for this period!")),
						QString(tr("Ok")));
				}
			}
		}
	}
	else if (radioYear->isChecked())
	{
		
		QDate date;
		QDate nextDate;
		QString startDate = "";
		QString endDate = "";

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
		file.setFileName(":/docs/financial_report_period.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();

		QString monthHlder = "";

		QString chepter00Ph = "";
		QString chepter10Ph = "";
		QString chepter20Ph = "";
		QString chepter30Ph = "";
		QString chepter00100Ph = "";
		QString chepter40Ph = "";
		QString chepter41Ph = "";
		QString chepter50Ph = "";
		QString chepter51Ph = "";
		QString chepter60Ph = "";
		QString chepter70Ph = "";
		QString chepter80Ph = "";
		QString chepter90Ph = "";
		QString chepter100Ph = "";
		QString chepter110Ph = "";
		QString chepter120Ph = "";
		QString chepter130Ph = "";
		QString chepter140Ph = "";
		QString chepter150Ph = "";
		QString chepter160Ph = "";
		QString chepter170Ph = "";
		QString chepter180Ph = "";
		QString chepter190Ph = "";
		QString chepter200Ph = "";
		QString chepter210Ph = "";

		double sumChepter10Ph = 0;
		double sumChepter20Ph = 0;
		double sumChepter30Ph = 0;
		double sumChepter40Ph = 0;
		double sumChepter41Ph = 0;
		double sumChepter50Ph = 0;
		double sumChepter51Ph = 0;
		double sumChepter60Ph = 0;
		double sumChepter70Ph = 0;
		double sumChepter80Ph = 0;
		double sumChepter90Ph = 0;
		double sumChepter100Ph = 0;
		double sumChepter110Ph = 0;
		double sumChepter120Ph = 0;
		double sumChepter130Ph = 0;
		double sumChepter140Ph = 0;
		double sumChepter150Ph = 0;
		double sumChepter160Ph = 0;
		double sumChepter170Ph = 0;
		double sumChepter180Ph = 0;
		double sumChepter190Ph = 0;
		double sumChepter200Ph = 0;
		double sumChepter210Ph = 0;


		for (int i = 0; i < 12; i++)
		{
			date = QDate::fromString(dateYearlyEdit->text().toUtf8().constData(), "yyyy");

			if (i == 0)
			{
				if ((date.month() + i) / 12 < 1)
				{
					startDate = "01." + QString::number(date.month()) + "." + QString::number(date.year());
					endDate = QString::number(date.daysInMonth()) + "." + QString::number(date.month()) + "." + QString::number(date.year());
				}
				else
				{
					startDate = "01." + QString::number(12 - date.month()) + "." + QString::number(date.year());
					endDate = QString::number(date.daysInMonth()) + "." + QString::number(12 - date.month()) + "." + QString::number(date.year() *((date.month() + i) / 12));
				}
			}
			else
			{
				if ((date.month() + i) / 12 <= 1)
				{
					nextDate = QDate::fromString("01." + QString::number(date.month() + i) + "." + QString::number(date.year()), "dd.MM.yyyy");
				}
				else
				{
					nextDate = QDate::fromString("01." + QString::number(12 - nextDate.month()) + "." + QString::number(nextDate.year() *((nextDate.month() + i) / 12)), "dd.MM.yyyy");

				}
				startDate = "01." + QString::number(nextDate.month()) + "." + QString::number(nextDate.year());
				endDate = QString::number(nextDate.daysInMonth()) + "." + QString::number(nextDate.month()) + "." + QString::number(nextDate.year());
			}
			
			QString fmDate = "";
			if (fmDate.isEmpty())
				fmDate = startDate;
			reportText.replace(QString("fromDatePh"), fmDate, Qt::CaseInsensitive);

			//CalculatePrevMonth(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), prevFromMonth, prevTillMonth);
			fReport->SetFromDate(startDate.toStdString());
			fReport->SetTillDate(endDate.toStdString());
			std::string filter = "";
			filter = fReport->GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::FinancialReport> vecFinRep;
			vecFinRep = dialogBL->GetAllDataForClass<BusinessLayer::FinancialReport>(errorMessage, filter);
			if (vecFinRep.size() == 0)
			{
				continue;
			}
			else
			{
				monthHlder += "<th><b>" + endDate + "</b></th>";
				//generating report
				if (vecFinRep.size() == 1)
				{
					double allIncome = 0;
					double allOperOut = 0;
					double operIncome = 0;
					double operOutIn = 0;


					for each (auto item in vecFinRep)
					{
						chepter00Ph += "<td></td>";
						chepter00100Ph += "<td></td>";

						chepter10Ph += "<td>" + QString::number(item.GetAccount44010()*(-1), 'f', 3) + "</td>";
						sumChepter10Ph += item.GetAccount44010()*(-1);

						chepter20Ph += "<td>" + QString::number(item.GetAccount55010(), 'f', 3) + "</td>";
						sumChepter20Ph += item.GetAccount55010();

						allIncome = item.GetAccount44010()*(-1) - item.GetAccount55010();
						chepter30Ph += "<td>" + QString::number(allIncome, 'f', 3) + "</td>";
						sumChepter30Ph += allIncome;

						chepter40Ph += "<td>" + QString::number(item.GetAccount552(), 'f', 3) + "</td>";
						sumChepter40Ph += item.GetAccount552();

						chepter41Ph += "<td>" + QString::number(item.GetAccount55270(), 'f', 3) + "</td>";
						sumChepter41Ph += item.GetAccount55270();

						chepter50Ph += "<td>" + QString::number(item.GetAccount553(), 'f', 3) + "</td>";
						sumChepter50Ph += item.GetAccount553();

						chepter51Ph += "<td>" + QString::number(item.GetAccount55321(), 'f', 3) + "</td>";
						sumChepter51Ph += item.GetAccount55321();

						allOperOut = item.GetAccount552() + item.GetAccount553();
						chepter60Ph += "<td>" + QString::number(allOperOut, 'f', 3) + "</td>";
						sumChepter60Ph += allOperOut;

						chepter70Ph += "<td>" + QString::number(item.GetAccount44020_90() * (-1), 'f', 3) + "</td>";
						sumChepter70Ph += item.GetAccount44020_90() * (-1);

						operIncome = allIncome - allOperOut - item.GetAccount44020_90();
						chepter80Ph += "<td>" + QString::number(operIncome, 'f', 3) + "</td>";
						sumChepter80Ph += operIncome;

						operOutIn = item.GetAccount66010_66110() + item.GetAccount66020_66120() + item.GetAccount66040_66140() +
							item.GetAccount66050_66150() + item.GetAccount66060_66160() + item.GetAccount66070_66170();
						chepter90Ph += "<td></td>";

						chepter100Ph += "<td>" + QString::number(item.GetAccount66010_66110()*(-1), 'f', 3) + "</td>";
						sumChepter100Ph += item.GetAccount66010_66110()*(-1);

						chepter110Ph += "<td>" + QString::number(item.GetAccount66020_66120()*(-1), 'f', 3) + "</td>";
						sumChepter110Ph += item.GetAccount66020_66120()*(-1);

						chepter120Ph += "<td>" + QString::number(item.GetAccount66040_66140()*(-1), 'f', 3) + "</td>";
						sumChepter120Ph += item.GetAccount66040_66140()*(-1);

						chepter130Ph += "<td>" + QString::number(item.GetAccount66050_66150()*(-1), 'f', 3) + "</td>";
						sumChepter130Ph += item.GetAccount66050_66150()*(-1);

						chepter140Ph += "<td>" + QString::number(item.GetAccount66060_66160()*(-1), 'f', 3) + "</td>";
						sumChepter140Ph += item.GetAccount66060_66160()*(-1);

						chepter150Ph += "<td>" + QString::number(item.GetAccount66130(), 'f', 3) + "</td>";
						sumChepter150Ph += item.GetAccount66130();

						chepter160Ph += "<td>" + QString::number(item.GetAccount66070_66170()*(-1), 'f', 3) + "</td>";
						sumChepter160Ph += item.GetAccount66070_66170()*(-1);

						chepter170Ph += "<td>" + QString::number(operOutIn*(-1), 'f', 3) + "</td>";
						sumChepter170Ph += operOutIn*(-1);

						chepter180Ph += "<td></td>";

						chepter190Ph += "<td>" + QString::number(operIncome + operOutIn*(-1), 'f', 3) + "</td>";
						sumChepter190Ph += operIncome + operOutIn*(-1);

						chepter200Ph += "<td></td>";

						chepter210Ph += "<td>" + QString::number(operIncome + operOutIn*(-1), 'f', 3) + "</td>";
						sumChepter210Ph += operIncome + operOutIn*(-1);
					}



				}
				else
				{
					continue;
				}

			}
		}

		monthHlder += "<th><b>"+QString::fromWCharArray(L"Итого")+"</b></th>";
		chepter00100Ph += "<td></td>";
		chepter00Ph += "<td></td>";
		chepter10Ph += "<td>" + QString::number(sumChepter10Ph, 'f', 3) + "</td>";
		chepter20Ph += "<td>" + QString::number(sumChepter20Ph, 'f', 3) + "</td>";
		chepter30Ph += "<td>" + QString::number(sumChepter30Ph, 'f', 3) + "</td>";
		chepter40Ph += "<td>" + QString::number(sumChepter40Ph, 'f', 3) + "</td>";
		chepter41Ph += "<td>" + QString::number(sumChepter41Ph, 'f', 3) + "</td>";
		chepter50Ph += "<td>" + QString::number(sumChepter50Ph, 'f', 3) + "</td>";
		chepter51Ph += "<td>" + QString::number(sumChepter51Ph, 'f', 3) + "</td>";
		chepter60Ph += "<td>" + QString::number(sumChepter60Ph, 'f', 3) + "</td>";
		chepter70Ph += "<td>" + QString::number(sumChepter70Ph, 'f', 3) + "</td>";
		chepter80Ph += "<td>" + QString::number(sumChepter80Ph, 'f', 3) + "</td>";
		chepter90Ph += "<td></td>";
		chepter100Ph += "<td>" + QString::number(sumChepter100Ph, 'f', 3) + "</td>";
		chepter110Ph += "<td>" + QString::number(sumChepter110Ph, 'f', 3) + "</td>";
		chepter120Ph += "<td>" + QString::number(sumChepter120Ph, 'f', 3) + "</td>";
		chepter130Ph += "<td>" + QString::number(sumChepter130Ph, 'f', 3) + "</td>";
		chepter140Ph += "<td>" + QString::number(sumChepter140Ph, 'f', 3) + "</td>";
		chepter150Ph += "<td>" + QString::number(sumChepter150Ph, 'f', 3) + "</td>";
		chepter160Ph += "<td>" + QString::number(sumChepter160Ph, 'f', 3) + "</td>";
		chepter170Ph += "<td>" + QString::number(sumChepter170Ph, 'f', 3) + "</td>";
		chepter180Ph += "<td></td>";
		chepter190Ph += "<td>" + QString::number(sumChepter190Ph, 'f', 3) + "</td>";
		chepter200Ph += "<td></td>";
		chepter210Ph += "<td>" + QString::number(sumChepter210Ph, 'f', 3) + "</td>";



		reportText.replace(QString("MonthPH"), monthHlder, Qt::CaseInsensitive);
		reportText.replace(QString("chepter00Ph"), chepter00Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter00100Ph"), chepter00100Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter10Ph"), chepter10Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter20Ph"), chepter20Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter30Ph"), chepter30Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter40Ph"), chepter40Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter41Ph"), chepter41Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter50Ph"), chepter50Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter51Ph"), chepter51Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter60Ph"), chepter60Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter70Ph"), chepter70Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter80Ph"), chepter80Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter90Ph"), chepter90Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter100Ph"), chepter100Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter110Ph"), chepter110Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter120Ph"), chepter120Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter130Ph"), chepter130Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter140Ph"), chepter140Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter150Ph"), chepter150Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter160Ph"), chepter160Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter170Ph"), chepter170Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter180Ph"), chepter180Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter190Ph"), chepter190Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter200Ph"), chepter200Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter210Ph"), chepter210Ph, Qt::CaseInsensitive);


		reportText.replace(QString("tillDatePh"), endDate, Qt::CaseInsensitive);
		docForm->webEngineView->setHtml(reportText);
		docForm->SetContent(reportText);
		docForm->webEngineView->show();
		docForm->show();
		Close();
	}
	else
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Please select a period first!")),
			QString(tr("Ok")));
	}
	
}

void GenerateFinRep::Close()
{
	this->parentWidget()->close();
}

void GenerateFinRep::ChangeRadio()
{
	QDateEdit *senderObj = qobject_cast<QDateEdit *>(sender());
	if (senderObj != nullptr)
	{
		QString senderName = senderObj->objectName();
		if (senderName == "dateMonthlyEdit")
		{
			radioMon->setChecked(true);
			radioYear->setChecked(false);
			radioPeriod->setChecked(false);
		}
		else if (senderName == "dateYearlyEdit")
		{
			radioMon->setChecked(false);
			radioYear->setChecked(true);
			radioPeriod->setChecked(false);
		}
		else if (senderName == "fromDateEdit")
		{
			radioMon->setChecked(false);
			radioYear->setChecked(false);
			radioPeriod->setChecked(true);
		}
		else if (senderName == "tillDateEdit")
		{
			radioMon->setChecked(true);
			radioYear->setChecked(false);
			radioPeriod->setChecked(true);
		}
	}
}

void GenerateFinRep::CalculatePrevMonth(std::string fromMonth, std::string tilMonth, std::string& prevFromMonth, std::string& tillFromMonth)
{
	QDate startDate = QDate::fromString(QString(fromMonth.c_str()), "dd.MM.yyyy");
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

int GenerateFinRep::CalculateMonthCount(std::string fromMonth, std::string tilMonth)
{
	QDate startDate = QDate::fromString(fromMonth.c_str(), "MM.yyyy");
	QDate endDate = QDate::fromString(tilMonth.c_str(), "MM.yyyy");
	int sDay = startDate.day();
	int sMonth = startDate.month();
	int sYear = startDate.year();
	int eDay = endDate.day();
	int eMonth = endDate.month();
	int eYear = endDate.year();

	int count = 0;

	if (sYear == eYear)
	{
		count = eMonth - sMonth;
	}
	else
	{
		if (sYear > eYear || sMonth > eMonth)
		{
			return count;
		}
		count = (12 - sMonth + eMonth) * (eYear - sYear);
	}
	return count;

}
