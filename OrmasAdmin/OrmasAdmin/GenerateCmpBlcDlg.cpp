#include "stdafx.h"
#include "GenerateCmpBlcDlg.h"
#include "MainForm.h"
#include "DocForm.h"


GenerateCmpBlc::GenerateCmpBlc(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
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
			pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
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
			pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
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
	dateMonthlyEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	dateYearlyEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateCmpBlc::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateCmpBlc::Close);
	QObject::connect(dateMonthlyEdit, &QDateEdit::dateChanged, this, &GenerateCmpBlc::ChangeRadio);
	QObject::connect(dateYearlyEdit, &QDateEdit::dateChanged, this, &GenerateCmpBlc::ChangeRadio);
	QObject::connect(fromDateEdit, &QDateEdit::dateChanged, this, &GenerateCmpBlc::ChangeRadio);
	QObject::connect(tillDateEdit, &QDateEdit::dateChanged, this, &GenerateCmpBlc::ChangeRadio);
}

GenerateCmpBlc::~GenerateCmpBlc()
{
	delete aHistory;
}

void GenerateCmpBlc::Generate()
{
	
	if (radioMon->isChecked())
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
	//aHistory->SetFromDate(fromDateEdit->text().toUtf8().constData());
		aHistory->SetTillDate(endDate.toStdString());
	std::string filter = aHistory->GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::AccountHistory> vecCmpBlc = dialogBL->GetAllDataForClass<BusinessLayer::AccountHistory>(errorMessage, filter);
	if (vecCmpBlc.size() == 0)
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
		QMdiSubWindow *generateOneAccWindow = new QMdiSubWindow;
		generateOneAccWindow->setWidget(docForm);
		generateOneAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateOneAccWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateOneAccWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/company_balance.html");
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Cannot find report tamplate!")),
				QString(tr("Ok")));
			return;
		}
		QString reportText = file.readAll();
		//generating report
		if (vecCmpBlc.size() > 1)
		{
			double chepter33Ph = 0;
			double chepter53Ph = 0;
			double chepter54Ph = 0;
			double chepter71Ph = 0;
			double chepter99Ph = 0;
			double chepter199Ph = 0;
			double chepter100Ph = 0;
			double chepter110Ph = 0;
			double chepter130Ph = 0;
			double chepter121Ph = 0;
			double chepter131Ph = 0;
			double chepter133Ph = 0;
			double chepter259Ph = 0;
			double chepter203Ph = 0;
			double chepter222Ph = 0;
			double chepter224Ph = 0;
			double chepter234Ph = 0;
			double chepter298Ph = 0;
			double chepter261Ph = 0;
			double chepter262Ph = 0;
			double chepter264Ph = 0;
			double chepter313Ph = 0;
			double chepter315Ph = 0;
			double chepter339Ph = 0;
			

			for each (auto item in vecCmpBlc)
			{
				reportText.replace(QString("tillDatePh"), endDate, Qt::CaseInsensitive);
				//Оборотные активы
				if (0 == item.GetNumber().compare("10100"))
				{
					chepter99Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter10Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10200"))
				{
					chepter99Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter20Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10300"))
				{
					chepter99Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter30Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10310"))
					reportText.replace(QString("chepter31Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10320"))
					reportText.replace(QString("chepter32Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10330") || 0 == item.GetNumber().compare("10340"))
				{
					chepter33Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("10350"))
					reportText.replace(QString("chepter34Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10360"))
					reportText.replace(QString("chepter35Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10400"))
				{
					chepter99Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter40Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10410"))
					reportText.replace(QString("chepter41Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10420"))
					reportText.replace(QString("chepter42Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10430"))
					reportText.replace(QString("chepter43Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10500"))
				{
					chepter99Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter50Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10510"))
					reportText.replace(QString("chepter51Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10520"))
					reportText.replace(QString("chepter52Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10530") || 0 == item.GetNumber().compare("10540"))
				{
					chepter53Ph += item.GetCurrentBalance();
				}	
				if (0 == item.GetNumber().compare("10550") || 0 == item.GetNumber().compare("10560"))
				{
					chepter54Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("10570"))
					reportText.replace(QString("chepter55Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10580"))
					reportText.replace(QString("chepter56Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10590"))
					reportText.replace(QString("chepter59Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10600"))
				{
					chepter99Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter60Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10700"))
				{
					chepter99Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter70Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10710") || 0 == item.GetNumber().compare("10711") || 0 == item.GetNumber().compare("10712") ||
					0 == item.GetNumber().compare("10713") || 0 == item.GetNumber().compare("10714") || 0 == item.GetNumber().compare("10715") || 
					0 == item.GetNumber().compare("10716") || 0 == item.GetNumber().compare("10717") || 0 == item.GetNumber().compare("10718") || 
					0 == item.GetNumber().compare("10719"))
				{
					chepter71Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("10720"))
					reportText.replace(QString("chepter72Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10730"))
					reportText.replace(QString("chepter73Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10740"))
					reportText.replace(QString("chepter74Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10742"))
					reportText.replace(QString("chepter742Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10750"))
					reportText.replace(QString("chepter75Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10760"))
					reportText.replace(QString("chepter76Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10770"))
					reportText.replace(QString("chepter77Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10780"))
					reportText.replace(QString("chepter78Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10790"))
					reportText.replace(QString("chepter79Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10800"))
				{
					chepter99Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter80Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10810"))
					reportText.replace(QString("chepter81Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10820"))
					reportText.replace(QString("chepter82Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10830"))
					reportText.replace(QString("chepter83Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10900"))
				{
					chepter99Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter90Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("10910"))
					reportText.replace(QString("chepter91Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10920"))
					reportText.replace(QString("chepter92Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("10930"))
					reportText.replace(QString("chepter93Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				
				
				
				//Внеоборотные активы
				
				if (0 == item.GetNumber().compare("11000"))
				{
					chepter100Ph = item.GetCurrentBalance(); 
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter100Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11010"))
					reportText.replace(QString("chepter101Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11020"))
					reportText.replace(QString("chepter102Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11030"))
					reportText.replace(QString("chepter103Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11040"))
					reportText.replace(QString("chepter104Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11050"))
					reportText.replace(QString("chepter105Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11060"))
					reportText.replace(QString("chepter106Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11070"))
					reportText.replace(QString("chepter107Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11080"))
					reportText.replace(QString("chepter108Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11090"))
					reportText.replace(QString("chepter109Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11100"))
				{
					chepter110Ph = item.GetCurrentBalance(); 
					reportText.replace(QString("chepter110Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				
				if (0 == item.GetNumber().compare("11200"))
				{
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter120Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11210") || 0 == item.GetNumber().compare("11220"))
				{
					chepter121Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("11290"))
					reportText.replace(QString("chepter122Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11300"))
				{
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter130Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11310") || 0 == item.GetNumber().compare("11320") || 0 == item.GetNumber().compare("11330") 
					|| 0 == item.GetNumber().compare("11340") || 0 == item.GetNumber().compare("11350") || 0 == item.GetNumber().compare("11360"))
				{
					chepter131Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("11370"))
					reportText.replace(QString("chepter132Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11390"))
					reportText.replace(QString("chepter133Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11400"))
				{
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter140Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11410"))
					reportText.replace(QString("chepter141Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11420"))
					reportText.replace(QString("chepter142Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11430"))
					reportText.replace(QString("chepter143Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11440"))
					reportText.replace(QString("chepter144Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11450"))
					reportText.replace(QString("chepter145Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11460"))
					reportText.replace(QString("chepter146Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11500"))
				{
					chepter199Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter150Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11510"))
					reportText.replace(QString("chepter151Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11520"))
					reportText.replace(QString("chepter152Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11600"))
				{
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter160Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11610"))
					reportText.replace(QString("chepter161Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11620"))
					reportText.replace(QString("chepter162Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11630"))
					reportText.replace(QString("chepter163Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11640"))
					reportText.replace(QString("chepter164Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11650"))
					reportText.replace(QString("chepter165Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11660"))
					reportText.replace(QString("chepter166Ph"), QString::number(item.GetCurrentBalance()), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11700"))
				{
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter170Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11800"))
				{
					chepter199Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter180Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("11810"))
					reportText.replace(QString("chepter181Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11820"))
					reportText.replace(QString("chepter182Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11830"))
					reportText.replace(QString("chepter183Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11840"))
					reportText.replace(QString("chepter184Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("11900"))
				{
					chepter199Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter190Ph"), QString::number(item.GetCurrentBalance() , 'f' ,3), Qt::CaseInsensitive);
				}
				
				
				//Краткосрочные обязательства
				if (0 == item.GetNumber().compare("22000"))
				{
					chepter259Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter200Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22010"))
					reportText.replace(QString("chepter201Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22020"))
					reportText.replace(QString("chepter202Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22030") || 0 == item.GetNumber().compare("22040"))
				{
					chepter203Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22100"))
				{
					chepter259Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter210Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22110"))
					reportText.replace(QString("chepter211Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22120"))
					reportText.replace(QString("chepter212Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22130"))
					reportText.replace(QString("chepter213Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22140"))
					reportText.replace(QString("chepter214Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22200"))
				{
					chepter259Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter220Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22210"))
					reportText.replace(QString("chepter221Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22220") || 0 == item.GetNumber().compare("22230"))
				{
					chepter222Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22240"))
					reportText.replace(QString("chepter223Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22250") || 0 == item.GetNumber().compare("22260"))
				{
					chepter224Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22270"))
					reportText.replace(QString("chepter225Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22300"))
				{
					chepter259Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter230Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22310"))
					reportText.replace(QString("chepter231Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22320"))
					reportText.replace(QString("chepter232Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22330"))
					reportText.replace(QString("chepter233Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22340") || 0 == item.GetNumber().compare("22350")
					|| 0 == item.GetNumber().compare("22360") || 0 == item.GetNumber().compare("22370"))
				{
					chepter234Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22400"))
				{
					chepter259Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter240Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22500"))
				{
					chepter259Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter250Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22510"))
					reportText.replace(QString("chepter251Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22520"))
					reportText.replace(QString("chepter252Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22530"))
					reportText.replace(QString("chepter253Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				

				//Долгосрочные обязательства
				if (0 == item.GetNumber().compare("22600"))
				{
					chepter298Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter260Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22610") || 0 == item.GetNumber().compare("22640"))
				{
					chepter261Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22620") || 0 == item.GetNumber().compare("22630"))
				{
					chepter262Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22650"))
					reportText.replace(QString("chepter263Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("22660") || 0 == item.GetNumber().compare("22670"))
				{
					chepter264Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("22700"))
				{
					chepter298Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter270Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("22800"))
				{
					chepter298Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter280Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				

				//Собственный капитал
				if (0 == item.GetNumber().compare("33000"))
				{
					chepter339Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter300Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("33010"))
					reportText.replace(QString("chepter301Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("33020"))
					reportText.replace(QString("chepter302Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("33030"))
					reportText.replace(QString("chepter303Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("33090"))
					reportText.replace(QString("chepter304Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("33100"))
				{
					chepter339Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter310Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("33110"))
					reportText.replace(QString("chepter311Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("33120") || 0 == item.GetNumber().compare("33130"))
				{
					chepter313Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("33140"))
					reportText.replace(QString("chepter314Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				if (0 == item.GetNumber().compare("33150") || 0 == item.GetNumber().compare("33160"))
				{
					chepter315Ph += item.GetCurrentBalance();
				}
				if (0 == item.GetNumber().compare("33200"))
				{
					chepter339Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter320Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("33300"))
				{
					chepter339Ph += item.GetCurrentBalance();
					reportText.replace(QString("chepter330Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				if (0 == item.GetNumber().compare("33400"))
				{
					chepter339Ph += item.GetCurrentBalance(); 
					reportText.replace(QString("chepter340Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
				}
				
			}
			reportText.replace(QString("chepter33Ph"), QString::number(chepter33Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter53Ph"), QString::number(chepter53Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter54Ph"), QString::number(chepter54Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter71Ph"), QString::number(chepter71Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter121Ph"), QString::number(chepter121Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter131Ph"), QString::number(chepter131Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter203Ph"), QString::number(chepter203Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter222Ph"), QString::number(chepter222Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter224Ph"), QString::number(chepter224Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter234Ph"), QString::number(chepter234Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter261Ph"), QString::number(chepter261Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter262Ph"), QString::number(chepter262Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter264Ph"), QString::number(chepter264Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter313Ph"), QString::number(chepter313Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter315Ph"), QString::number(chepter315Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			//итоги
			reportText.replace(QString("chepter99Ph"), QString::number(chepter99Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter119Ph"), QString::number(chepter100Ph + chepter110Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter199Ph"), QString::number(chepter199Ph + chepter110Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter1000Ph"), QString::number(chepter99Ph + chepter199Ph + chepter110Ph, 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter259Ph"), QString::number(chepter259Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter298Ph"), QString::number(chepter298Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter299Ph"), QString::number((chepter259Ph + chepter298Ph)*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter339Ph"), QString::number(chepter339Ph*(-1), 'f', 3), Qt::CaseInsensitive);
			reportText.replace(QString("chepter399Ph"), QString::number((chepter339Ph + chepter259Ph + chepter298Ph)*(-1), 'f', 3), Qt::CaseInsensitive);

			chepter33Ph = 0;
			chepter53Ph = 0;
			chepter54Ph = 0;
			chepter71Ph = 0;
			chepter99Ph = 0;
			chepter199Ph = 0;
			chepter100Ph = 0;
			chepter110Ph = 0;
			chepter130Ph = 0;
			chepter121Ph = 0;
			chepter131Ph = 0;
			chepter133Ph = 0;
			chepter259Ph = 0;
			chepter203Ph = 0;
			chepter222Ph = 0;
			chepter224Ph = 0;
			chepter234Ph = 0;
			chepter298Ph = 0;
			chepter261Ph = 0;
			chepter262Ph = 0;
			chepter264Ph = 0;
			chepter313Ph = 0;
			chepter315Ph = 0;
			chepter339Ph = 0;
			
			BusinessLayer::AccountHistory prevCmpBlc;
			//prevCmpBlc.SetFromDate(prevFromMonth);
			prevCmpBlc.SetTillDate(prevTillMonth);
			std::string filterPrev = prevCmpBlc.GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::AccountHistory> vecPrevFinRep = dialogBL->GetAllDataForClass<BusinessLayer::AccountHistory>(errorMessage, filterPrev);
			if (vecPrevFinRep.size() == 0)
			{
				
				reportText.replace(QString("chepterprev10Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev20Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev30Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev31Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev32Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev34Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev35Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev40Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev41Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev42Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev43Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev50Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev51Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev52Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev55Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev56Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev59Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev60Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev70Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev72Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev73Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev74Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev742Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev75Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev76Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev77Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev78Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev79Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev80Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev81Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev82Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev83Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev90Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev91Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev92Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev93Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev99Ph"), "0", Qt::CaseInsensitive);

				//Внеоборотные активы
				reportText.replace(QString("chepterprev100Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev101Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev102Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev103Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev104Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev105Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev106Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev107Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev108Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev109Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev110Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev119Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev120Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev122Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev130Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev132Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev133Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev140Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev141Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev142Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev143Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev144Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev145Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev146Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev150Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev151Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev152Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev160Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev161Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev162Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev163Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev164Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev165Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev166Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev170Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev180Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev181Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev182Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev183Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev184Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev190Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev199Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev1000Ph"), "0", Qt::CaseInsensitive);

				//Краткосрочные обязательства
				reportText.replace(QString("chepterprev200Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev201Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev202Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev210Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev211Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev212Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev213Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev214Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev220Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev221Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev223Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev225Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev230Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev231Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev232Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev233Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev240Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev250Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev251Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev252Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev253Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev259Ph"), "0", Qt::CaseInsensitive);

				//Долгосрочные обязательства
				reportText.replace(QString("chepterprev260Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev263Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev270Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev280Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev298Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev299Ph"), "0", Qt::CaseInsensitive);

				//Собственный капитал
				reportText.replace(QString("chepterprev300Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev301Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev302Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev303Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev304Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev310Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev311Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev314Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev320Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev330Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev340Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev339Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev399Ph"), "0", Qt::CaseInsensitive);

				reportText.replace(QString("chepterprev33Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev53Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev54Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev71Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev121Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev131Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev203Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev222Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev224Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev234Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev261Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev262Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev264Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev313Ph"), "0", Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev315Ph"), "0", Qt::CaseInsensitive);
			}
			if (vecPrevFinRep.size() > 1)
			{
				for each (auto item in vecPrevFinRep)
				{
					//Оборотные активы
					if (0 == item.GetNumber().compare("10100"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev10Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10200"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev20Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10300"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev30Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10310"))
						reportText.replace(QString("chepterprev31Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10320"))
						reportText.replace(QString("chepterprev32Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10330") || 0 == item.GetNumber().compare("10340"))
					{
						chepter33Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("10350"))
						reportText.replace(QString("chepterprev34Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10360"))
						reportText.replace(QString("chepterprev35Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10400"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev40Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10410"))
						reportText.replace(QString("chepterprev41Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10420"))
						reportText.replace(QString("chepterprev42Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10430"))
						reportText.replace(QString("chepterprev43Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10500"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev50Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10510"))
						reportText.replace(QString("chepterprev51Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10520"))
						reportText.replace(QString("chepterprev52Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10530") || 0 == item.GetNumber().compare("10540"))
					{
						chepter53Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("10550") || 0 == item.GetNumber().compare("10560"))
					{
						chepter54Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("10570"))
						reportText.replace(QString("chepterprev55Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10580"))
						reportText.replace(QString("chepterprev56Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10590"))
						reportText.replace(QString("chepterprev59Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10600"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev60Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10700"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev70Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10710") || 0 == item.GetNumber().compare("10711") || 0 == item.GetNumber().compare("10712") ||
						0 == item.GetNumber().compare("10713") || 0 == item.GetNumber().compare("10714") || 0 == item.GetNumber().compare("10715") ||
						0 == item.GetNumber().compare("10716") || 0 == item.GetNumber().compare("10717") || 0 == item.GetNumber().compare("10718") ||
						0 == item.GetNumber().compare("10719"))
					{
						chepter71Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("10720"))
						reportText.replace(QString("chepterprev72Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10730"))
						reportText.replace(QString("chepterprev73Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10740"))
						reportText.replace(QString("chepterprev74Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10742"))
						reportText.replace(QString("chepterprev742Ph"), QString::number(item.GetCurrentBalance(), 'f', 3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10750"))
						reportText.replace(QString("chepterprev75Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10760"))
						reportText.replace(QString("chepterprev76Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10770"))
						reportText.replace(QString("chepterprev77Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10780"))
						reportText.replace(QString("chepterprev78Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10790"))
						reportText.replace(QString("chepterprev79Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10800"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev80Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10810"))
						reportText.replace(QString("chepterprev81Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10820"))
						reportText.replace(QString("chepterprev82Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10830"))
						reportText.replace(QString("chepterprev83Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10900"))
					{
						chepter99Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev90Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("10910"))
						reportText.replace(QString("chepterprev91Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10920"))
						reportText.replace(QString("chepterprev92Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("10930"))
						reportText.replace(QString("chepterprev93Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);



					//Внеоборотные активы

					if (0 == item.GetNumber().compare("11000"))
					{
						chepter100Ph = item.GetCurrentBalance();
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev100Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11010"))
						reportText.replace(QString("chepterprev101Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11020"))
						reportText.replace(QString("chepterprev102Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11030"))
						reportText.replace(QString("chepterprev103Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11040"))
						reportText.replace(QString("chepterprev104Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11050"))
						reportText.replace(QString("chepterprev105Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11060"))
						reportText.replace(QString("chepterprev106Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11070"))
						reportText.replace(QString("chepterprev107Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11080"))
						reportText.replace(QString("chepterprev108Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11090"))
						reportText.replace(QString("chepterprev109Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11100"))
					{
						chepter110Ph = item.GetCurrentBalance();
						reportText.replace(QString("chepterprev110Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}

					if (0 == item.GetNumber().compare("11200"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev120Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11210") || 0 == item.GetNumber().compare("11220"))
					{
						chepter121Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("11290"))
						reportText.replace(QString("chepterprev122Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11300"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev130Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11310") || 0 == item.GetNumber().compare("11320") || 0 == item.GetNumber().compare("11330")
						|| 0 == item.GetNumber().compare("11340") || 0 == item.GetNumber().compare("11350") || 0 == item.GetNumber().compare("11360"))
					{
						chepter131Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("11370"))
						reportText.replace(QString("chepterprev132Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11390"))
						reportText.replace(QString("chepterprev133Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11400"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev140Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11410"))
						reportText.replace(QString("chepterprev141Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11420"))
						reportText.replace(QString("chepterprev142Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11430"))
						reportText.replace(QString("chepterprev143Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11440"))
						reportText.replace(QString("chepterprev144Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11450"))
						reportText.replace(QString("chepterprev145Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11460"))
						reportText.replace(QString("chepterprev146Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11500"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev150Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11510"))
						reportText.replace(QString("chepterprev151Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11520"))
						reportText.replace(QString("chepterprev152Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11600"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev160Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11610"))
						reportText.replace(QString("chepterprev161Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11620"))
						reportText.replace(QString("chepterprev162Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11630"))
						reportText.replace(QString("chepterprev163Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11640"))
						reportText.replace(QString("chepterprev164Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11650"))
						reportText.replace(QString("chepterprev165Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11660"))
						reportText.replace(QString("chepterprev166Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11700"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev170Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11800"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev180Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("11810"))
						reportText.replace(QString("chepterprev181Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11820"))
						reportText.replace(QString("chepterprev182Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11830"))
						reportText.replace(QString("chepterprev183Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11840"))
						reportText.replace(QString("chepterprev184Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("11900"))
					{
						chepter199Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev190Ph"), QString::number(item.GetCurrentBalance(), 'f' ,3), Qt::CaseInsensitive);
					}


					//Краткосрочные обязательства
					if (0 == item.GetNumber().compare("22000"))
					{
						chepter259Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev200Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22010"))
						reportText.replace(QString("chepterprev201Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22020"))
						reportText.replace(QString("chepterprev202Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22030") || 0 == item.GetNumber().compare("22040"))
					{
						chepter203Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22100"))
					{
						chepter259Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev210Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22110"))
						reportText.replace(QString("chepterprev211Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22120"))
						reportText.replace(QString("chepterprev212Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22130"))
						reportText.replace(QString("chepterprev213Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22140"))
						reportText.replace(QString("chepterprev214Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22200"))
					{
						chepter259Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev220Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22210"))
						reportText.replace(QString("chepterprev221Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22220") || 0 == item.GetNumber().compare("22230"))
					{
						chepter222Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22240"))
						reportText.replace(QString("chepterprev223Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22250") || 0 == item.GetNumber().compare("22260"))
					{
						chepter224Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22270"))
						reportText.replace(QString("chepterprev225Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22300"))
					{
						chepter259Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev230Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22310"))
						reportText.replace(QString("chepterprev231Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22320"))
						reportText.replace(QString("chepterprev232Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22330"))
						reportText.replace(QString("chepterprev233Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22340") || 0 == item.GetNumber().compare("22350")
						|| 0 == item.GetNumber().compare("22360") || 0 == item.GetNumber().compare("22370"))
					{
						chepter234Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22400"))
					{
						chepter259Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev240Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22500"))
					{
						chepter259Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev250Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22510"))
						reportText.replace(QString("chepterprev251Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22520"))
						reportText.replace(QString("chepterprev252Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22530"))
						reportText.replace(QString("chepterprev253Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);


					//Долгосрочные обязательства
					if (0 == item.GetNumber().compare("22600"))
					{
						chepter298Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev260Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22610") || 0 == item.GetNumber().compare("22640"))
					{
						chepter261Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22620") || 0 == item.GetNumber().compare("22630"))
					{
						chepter262Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22650"))
						reportText.replace(QString("chepterprev263Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("22660") || 0 == item.GetNumber().compare("22670"))
					{
						chepter264Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("22700"))
					{
						chepter298Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev270Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("22800"))
					{
						chepter298Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev280Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}


					//Собственный капитал
					if (0 == item.GetNumber().compare("33000"))
					{
						chepter339Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev300Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("33010"))
						reportText.replace(QString("chepterprev301Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("33020"))
						reportText.replace(QString("chepterprev302Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("33030"))
						reportText.replace(QString("chepterprev303Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("33090"))
						reportText.replace(QString("chepterprev304Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("33100"))
					{
						chepter339Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev310Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("33110"))
						reportText.replace(QString("chepterprev311Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("33120") || 0 == item.GetNumber().compare("33130"))
					{
						chepter313Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("33140"))
						reportText.replace(QString("chepterprev314Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					if (0 == item.GetNumber().compare("33150") || 0 == item.GetNumber().compare("33160"))
					{
						chepter315Ph += item.GetCurrentBalance();
					}
					if (0 == item.GetNumber().compare("33200"))
					{
						chepter339Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev320Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("33300"))
					{
						chepter339Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev330Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}
					if (0 == item.GetNumber().compare("33400"))
					{
						chepter339Ph += item.GetCurrentBalance();
						reportText.replace(QString("chepterprev340Ph"), QString::number(item.GetCurrentBalance()*(-1) , 'f' ,3), Qt::CaseInsensitive);
					}

				}
				reportText.replace(QString("chepterprev33Ph"), QString::number(chepter33Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev53Ph"), QString::number(chepter53Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev54Ph"), QString::number(chepter54Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev71Ph"), QString::number(chepter71Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev121Ph"), QString::number(chepter121Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev131Ph"), QString::number(chepter131Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev203Ph"), QString::number(chepter203Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev222Ph"), QString::number(chepter222Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev224Ph"), QString::number(chepter224Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev234Ph"), QString::number(chepter234Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev261Ph"), QString::number(chepter261Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev262Ph"), QString::number(chepter262Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev264Ph"), QString::number(chepter264Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev313Ph"), QString::number(chepter313Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev315Ph"), QString::number(chepter315Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				//итоги
				reportText.replace(QString("chepterprev99Ph"), QString::number(chepter99Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev119Ph"), QString::number(chepter100Ph + chepter110Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev199Ph"), QString::number(chepter199Ph + chepter110Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev1000Ph"), QString::number(chepter99Ph + chepter199Ph + chepter110Ph, 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev259Ph"), QString::number(chepter259Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev298Ph"), QString::number(chepter298Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev299Ph"), QString::number((chepter259Ph + chepter298Ph)*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev339Ph"), QString::number(chepter339Ph*(-1), 'f', 3), Qt::CaseInsensitive);
				reportText.replace(QString("chepterprev399Ph"), QString::number((chepter339Ph + chepter259Ph + chepter298Ph)*(-1), 'f', 3), Qt::CaseInsensitive);
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
	else if (radioPeriod->isChecked())
	{

		QDate date;
		QDate nextDate;
		QString startDate = "";
		QString endDate = "";

		int count = CalculateMonthCount(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData());
		if (count == 0)
		{
			QMessageBox::information(NULL, QString(tr("Info")),
				QString(tr("Please select correct period! If you check for one month please use monthly report!")),
				QString(tr("Ok")));
		}


		DocForm *docForm = new DocForm(dialogBL, this);
		docForm->setAttribute(Qt::WA_DeleteOnClose);
		docForm->setWindowTitle(tr("Print financial report"));
		QMdiSubWindow *generateOneAccWindow = new QMdiSubWindow;
		generateOneAccWindow->setWidget(docForm);
		generateOneAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateOneAccWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateOneAccWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/company_balance_period.html");
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
		QString chepter31Ph = "";
		QString chepter32Ph = "";
		QString chepter33Ph = "";
		QString chepter34Ph = "";
		QString chepter35Ph = "";
		QString chepter40Ph = "";
		QString chepter41Ph = "";
		QString chepter42Ph = "";
		QString chepter43Ph = "";
		QString chepter50Ph = "";
		QString chepter51Ph = "";
		QString chepter52Ph = "";
		QString chepter53Ph = "";
		QString chepter54Ph = "";
		QString chepter55Ph = "";
		QString chepter56Ph = "";
		QString chepter59Ph = "";
		QString chepter60Ph = "";
		QString chepter70Ph = "";
		QString chepter71Ph = "";
		QString chepter72Ph = "";
		QString chepter73Ph = "";
		QString chepter74Ph = "";
		QString chepter742Ph = "";
		QString chepter75Ph = "";
		QString chepter76Ph = "";
		QString chepter77Ph = "";
		QString chepter78Ph = "";
		QString chepter79Ph = "";
		QString chepter80Ph = "";
		QString chepter81Ph = "";
		QString chepter82Ph = "";
		QString chepter83Ph = "";
		QString chepter90Ph = "";
		QString chepter91Ph = "";
		QString chepter92Ph = "";
		QString chepter93Ph = "";
		QString chepter99Ph = "";
		QString chepter100Ph = "";
		QString chepter101Ph = "";
		QString chepter102Ph = "";
		QString chepter103Ph = "";
		QString chepter104Ph = "";
		QString chepter105Ph = "";
		QString chepter106Ph = "";
		QString chepter107Ph = "";
		QString chepter108Ph = "";
		QString chepter109Ph = "";
		QString chepter110Ph = "";
		QString chepter119Ph = "";
		QString chepter120Ph = "";
		QString chepter121Ph = "";
		QString chepter122Ph = "";
		QString chepter130Ph = "";
		QString chepter131Ph = "";
		QString chepter132Ph = ""; 
		QString chepter133Ph = "";
		QString chepter140Ph = "";
		QString chepter141Ph = "";
		QString chepter142Ph = "";
		QString chepter143Ph = "";
		QString chepter144Ph = "";
		QString chepter145Ph = "";
		QString chepter146Ph = "";
		QString chepter150Ph = "";
		QString chepter151Ph = "";
		QString chepter152Ph = "";
		QString chepter160Ph = "";
		QString chepter161Ph = "";
		QString chepter162Ph = "";
		QString chepter163Ph = "";
		QString chepter164Ph = "";
		QString chepter165Ph = "";
		QString chepter166Ph = "";
		QString chepter170Ph = "";
		QString chepter180Ph = "";
		QString chepter181Ph = "";
		QString chepter182Ph = "";
		QString chepter183Ph = "";
		QString chepter184Ph = "";
		QString chepter190Ph = "";
		QString chepter199Ph = "";
		QString chepter1000Ph = "";
		QString chepter200Ph = "";
		QString chepter201Ph = "";
		QString chepter202Ph = "";
		QString chepter203Ph = "";
		QString chepter210Ph = "";
		QString chepter211Ph = "";
		QString chepter212Ph = "";
		QString chepter213Ph = "";
		QString chepter214Ph = "";
		QString chepter220Ph = "";
		QString chepter221Ph = "";
		QString chepter222Ph = "";
		QString chepter223Ph = "";
		QString chepter224Ph = "";
		QString chepter225Ph = "";
		QString chepter230Ph = "";
		QString chepter231Ph = "";
		QString chepter232Ph = "";
		QString chepter233Ph = "";
		QString chepter234Ph = "";
		QString chepter240Ph = "";
		QString chepter250Ph = "";
		QString chepter251Ph = "";
		QString chepter252Ph = "";
		QString chepter253Ph = "";
		QString chepter259Ph = "";
		QString chepter260Ph = "";
		QString chepter261Ph = "";
		QString chepter262Ph = "";
		QString chepter263Ph = "";
		QString chepter264Ph = "";
		QString chepter270Ph = "";
		QString chepter280Ph = "";
		QString chepter290Ph = "";
		QString chepter298Ph = "";
		QString chepter299Ph = "";
		QString chepter300Ph = "";
		QString chepter301Ph = "";
		QString chepter302Ph = "";
		QString chepter303Ph = "";
		QString chepter304Ph = "";
		QString chepter310Ph = "";
		QString chepter311Ph = "";
		QString chepter313Ph = "";
		QString chepter314Ph = "";
		QString chepter315Ph = "";
		QString chepter320Ph = "";
		QString chepter330Ph = "";
		QString chepter340Ph = "";
		QString chepter339Ph = "";
		QString chepter399Ph = "";

		double sumChepter00Ph = 0;
		double sumChepter10Ph = 0;
		double sumChepter20Ph = 0;
		double sumChepter30Ph = 0;
		double sumChepter31Ph = 0;
		double sumChepter32Ph = 0;
		double sumChepter33Ph = 0;
		double sumChepter34Ph = 0;
		double sumChepter35Ph = 0;
		double sumChepter40Ph = 0;
		double sumChepter41Ph = 0;
		double sumChepter42Ph = 0;
		double sumChepter43Ph = 0;
		double sumChepter50Ph = 0;
		double sumChepter51Ph = 0;
		double sumChepter52Ph = 0;
		double sumChepter53Ph = 0;
		double sumChepter54Ph = 0;
		double sumChepter55Ph = 0;
		double sumChepter56Ph = 0;
		double sumChepter59Ph = 0;
		double sumChepter60Ph = 0;
		double sumChepter70Ph = 0;
		double sumChepter71Ph = 0;
		double sumChepter72Ph = 0;
		double sumChepter73Ph = 0;
		double sumChepter74Ph = 0;
		double sumChepter742Ph = 0;
		double sumChepter75Ph = 0;
		double sumChepter76Ph = 0;
		double sumChepter77Ph = 0;
		double sumChepter78Ph = 0;
		double sumChepter79Ph = 0;
		double sumChepter80Ph = 0;
		double sumChepter81Ph = 0;
		double sumChepter82Ph = 0;
		double sumChepter83Ph = 0;
		double sumChepter90Ph = 0;
		double sumChepter91Ph = 0;
		double sumChepter92Ph = 0;
		double sumChepter93Ph = 0;
		double sumChepter99Ph = 0;
		double sumChepter100Ph = 0;
		double sumChepter101Ph = 0;
		double sumChepter102Ph = 0;
		double sumChepter103Ph = 0;
		double sumChepter104Ph = 0;
		double sumChepter105Ph = 0;
		double sumChepter106Ph = 0;
		double sumChepter107Ph = 0;
		double sumChepter108Ph = 0;
		double sumChepter109Ph = 0;
		double sumChepter110Ph = 0;
		double sumChepter119Ph = 0;
		double sumChepter120Ph = 0;
		double sumChepter121Ph = 0;
		double sumChepter122Ph = 0;
		double sumChepter130Ph = 0;
		double sumChepter131Ph = 0;
		double sumChepter132Ph = 0;
		double sumChepter133Ph = 0;
		double sumChepter140Ph = 0;
		double sumChepter141Ph = 0;
		double sumChepter142Ph = 0;
		double sumChepter143Ph = 0;
		double sumChepter144Ph = 0;
		double sumChepter145Ph = 0;
		double sumChepter146Ph = 0;
		double sumChepter150Ph = 0;
		double sumChepter151Ph = 0;
		double sumChepter152Ph = 0;
		double sumChepter160Ph = 0;
		double sumChepter161Ph = 0;
		double sumChepter162Ph = 0;
		double sumChepter163Ph = 0;
		double sumChepter164Ph = 0;
		double sumChepter165Ph = 0;
		double sumChepter166Ph = 0;
		double sumChepter170Ph = 0;
		double sumChepter180Ph = 0;
		double sumChepter181Ph = 0;
		double sumChepter182Ph = 0;
		double sumChepter183Ph = 0;
		double sumChepter184Ph = 0;
		double sumChepter190Ph = 0;
		double sumChepter199Ph = 0;
		double sumChepter1000Ph = 0;
		double sumChepter200Ph = 0;
		double sumChepter201Ph = 0;
		double sumChepter202Ph = 0;
		double sumChepter203Ph = 0;
		double sumChepter210Ph = 0;
		double sumChepter211Ph = 0;
		double sumChepter212Ph = 0;
		double sumChepter213Ph = 0;
		double sumChepter214Ph = 0;
		double sumChepter220Ph = 0;
		double sumChepter221Ph = 0;
		double sumChepter222Ph = 0;
		double sumChepter223Ph = 0;
		double sumChepter224Ph = 0;
		double sumChepter225Ph = 0;
		double sumChepter230Ph = 0;
		double sumChepter231Ph = 0;
		double sumChepter232Ph = 0;
		double sumChepter233Ph = 0;
		double sumChepter234Ph = 0;
		double sumChepter240Ph = 0;
		double sumChepter250Ph = 0;
		double sumChepter251Ph = 0;
		double sumChepter252Ph = 0;
		double sumChepter253Ph = 0;
		double sumChepter259Ph = 0;
		double sumChepter260Ph = 0;
		double sumChepter261Ph = 0;
		double sumChepter262Ph = 0;
		double sumChepter263Ph = 0;
		double sumChepter264Ph = 0;
		double sumChepter270Ph = 0;
		double sumChepter280Ph = 0;
		double sumChepter290Ph = 0;
		double sumChepter298Ph = 0;
		double sumChepter299Ph = 0;
		double sumChepter300Ph = 0;
		double sumChepter301Ph = 0;
		double sumChepter302Ph = 0;
		double sumChepter303Ph = 0;
		double sumChepter304Ph = 0;
		double sumChepter310Ph = 0;
		double sumChepter311Ph = 0;
		double sumChepter313Ph = 0;
		double sumChepter314Ph = 0;
		double sumChepter315Ph = 0;
		double sumChepter320Ph = 0;
		double sumChepter330Ph = 0;
		double sumChepter340Ph = 0;
		double sumChepter339Ph = 0;
		double sumChepter399Ph = 0;


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



			CalculatePrevMonth(startDate.toStdString(), endDate.toStdString(), prevFromMonth, prevTillMonth);
			//aHistory->SetFromDate(fromDateEdit->text().toUtf8().constData());
			aHistory->SetTillDate(endDate.toStdString());
			std::string filter = "";
			filter = aHistory->GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::AccountHistory> vecCmpBlc;
			vecCmpBlc = dialogBL->GetAllDataForClass<BusinessLayer::AccountHistory>(errorMessage, filter);
			if (vecCmpBlc.size() == 0)
			{
				QMessageBox::information(NULL, QString(tr("Info")),
					QString(tr("Cannot find report for this period!")),
					QString(tr("Ok")));
			}
			else
			{
				monthHlder += "<th><b>" + endDate + "</b></th>";
				//generating report
				if (vecCmpBlc.size() > 1)
				{
					double sChepter33Ph = 0;
					double sChepter53Ph = 0;
					double sChepter54Ph = 0;
					double sChepter71Ph = 0;
					double sChepter99Ph = 0;
					double sChepter199Ph = 0;
					double sChepter100Ph = 0;
					double sChepter110Ph = 0;
					double sChepter130Ph = 0;
					double sChepter121Ph = 0;
					double sChepter131Ph = 0;
					double sChepter133Ph = 0;
					double sChepter259Ph = 0;
					double sChepter203Ph = 0;
					double sChepter222Ph = 0;
					double sChepter224Ph = 0;
					double sChepter234Ph = 0;
					double sChepter298Ph = 0;
					double sChepter261Ph = 0;
					double sChepter262Ph = 0;
					double sChepter264Ph = 0;
					double sChepter313Ph = 0;
					double sChepter315Ph = 0;
					double sChepter339Ph = 0;

					chepter00Ph += "<td></td>";
					for each (auto item in vecCmpBlc)
					{
						
						
						
						//Оборотные активы
						if (0 == item.GetNumber().compare("10100"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter10Ph+="<td>" + QString::number(item.GetCurrentBalance(), 'f', 3)+"</td>";
							sumChepter10Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10200"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter20Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter20Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10300"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter30Ph +="<td>"+QString::number(item.GetCurrentBalance(), 'f', 3)+"</td>";
							sumChepter30Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10310"))
						{
							chepter31Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter31Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10320"))
						{
							chepter32Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter32Ph += item.GetCurrentBalance();
						}

						if (0 == item.GetNumber().compare("10330") || 0 == item.GetNumber().compare("10340"))
						{
							sChepter33Ph += item.GetCurrentBalance();
							sumChepter33Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10350"))
						{
							chepter34Ph += "<td> " + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter34Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10360"))
						{
							chepter35Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter35Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10400"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter40Ph +="<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter40Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10410"))
						{
							sumChepter41Ph += item.GetCurrentBalance();
							chepter41Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10420"))
						{
							sumChepter42Ph += item.GetCurrentBalance();
							chepter42Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10430"))
						{
							sumChepter43Ph += item.GetCurrentBalance();
							chepter43Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10500"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter50Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter50Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10510"))
						{
							sumChepter51Ph += item.GetCurrentBalance();
							chepter51Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10520"))
						{
							sumChepter52Ph += item.GetCurrentBalance();
							chepter52Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10530") || 0 == item.GetNumber().compare("10540"))
						{
							sChepter53Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10550") || 0 == item.GetNumber().compare("10560"))
						{
							sChepter54Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10570"))
						{
							chepter55Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter55Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10580"))
						{
							chepter56Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter56Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10590"))
						{
							sumChepter59Ph += item.GetCurrentBalance();
							chepter59Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10600"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter60Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter60Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10700"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter70Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter70Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10710") || 0 == item.GetNumber().compare("10711") || 0 == item.GetNumber().compare("10712") ||
							0 == item.GetNumber().compare("10713") || 0 == item.GetNumber().compare("10714") || 0 == item.GetNumber().compare("10715") ||
							0 == item.GetNumber().compare("10716") || 0 == item.GetNumber().compare("10717") || 0 == item.GetNumber().compare("10718") ||
							0 == item.GetNumber().compare("10719"))
						{
							sChepter71Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10720"))
						{
							sumChepter72Ph += item.GetCurrentBalance();
							chepter72Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10730"))
						{
							sumChepter73Ph += item.GetCurrentBalance();
							chepter73Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10740"))
						{
							sumChepter74Ph += item.GetCurrentBalance();
							chepter74Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10742"))
						{
							sumChepter74Ph += item.GetCurrentBalance();
							chepter742Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10750"))
						{
							sumChepter75Ph += item.GetCurrentBalance();
							chepter75Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10760"))
						{
							sumChepter76Ph += item.GetCurrentBalance();
							chepter76Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10770"))
						{
							sumChepter77Ph += item.GetCurrentBalance();
							chepter77Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10780"))
						{
							sumChepter78Ph += item.GetCurrentBalance();
							chepter78Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10790"))
						{
							sumChepter79Ph += item.GetCurrentBalance();
							chepter79Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10800"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter80Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter80Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10810"))
						{
							sumChepter81Ph += item.GetCurrentBalance();
							chepter81Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10820"))
						{
							sumChepter82Ph += item.GetCurrentBalance();
							chepter82Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10830"))
						{
							sumChepter83Ph += item.GetCurrentBalance();
							chepter83Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10900"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter90Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter90Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10910"))
						{
							sumChepter91Ph += item.GetCurrentBalance();
							chepter91Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10920"))
						{
							sumChepter92Ph += item.GetCurrentBalance();
							chepter92Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10930"))
						{
							sumChepter93Ph += item.GetCurrentBalance();
							chepter93Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}



						//Внеоборотные активы

						if (0 == item.GetNumber().compare("11000"))
						{
							sChepter100Ph = item.GetCurrentBalance();
							sChepter199Ph += item.GetCurrentBalance();
							chepter100Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter100Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11010"))
						{
							sumChepter101Ph += item.GetCurrentBalance();
							chepter101Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11020"))
						{
							sumChepter102Ph += item.GetCurrentBalance();
							chepter102Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11030"))
						{
							sumChepter103Ph += item.GetCurrentBalance();
							chepter103Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11040"))
						{
							sumChepter104Ph += item.GetCurrentBalance();
							chepter104Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11050"))
						{
							sumChepter105Ph += item.GetCurrentBalance();
							chepter105Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11060"))
						{
							sumChepter106Ph += item.GetCurrentBalance();
							chepter106Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11070"))
						{
							sumChepter107Ph += item.GetCurrentBalance();
							chepter107Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11080"))
						{
							sumChepter108Ph += item.GetCurrentBalance();
							chepter108Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11090"))
						{
							sumChepter109Ph += item.GetCurrentBalance();
							chepter109Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11100"))
						{
							sChepter110Ph = item.GetCurrentBalance();
							chepter110Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter110Ph += item.GetCurrentBalance();
						}

						if (0 == item.GetNumber().compare("11200"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter120Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter120Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11210") || 0 == item.GetNumber().compare("11220"))
						{
							sChepter121Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11290"))
						{
							sumChepter122Ph += item.GetCurrentBalance();
							chepter122Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11300"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter130Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter130Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11310") || 0 == item.GetNumber().compare("11320") || 0 == item.GetNumber().compare("11330")
							|| 0 == item.GetNumber().compare("11340") || 0 == item.GetNumber().compare("11350") || 0 == item.GetNumber().compare("11360"))
						{
							sChepter131Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11370"))
						{
							sumChepter132Ph += item.GetCurrentBalance();
							chepter132Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11390"))
						{
							sumChepter133Ph += item.GetCurrentBalance();
							chepter133Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11400"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter140Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter140Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11410"))
						{
							sumChepter141Ph += item.GetCurrentBalance();
							chepter141Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11420"))
						{
							sumChepter142Ph += item.GetCurrentBalance();
							chepter142Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11430"))
						{
							sumChepter143Ph += item.GetCurrentBalance();
							chepter143Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11440"))
						{
							sumChepter144Ph += item.GetCurrentBalance();
							chepter144Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11450"))
						{
							sumChepter145Ph += item.GetCurrentBalance();
							chepter145Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11460"))
						{
							sumChepter146Ph += item.GetCurrentBalance();
							chepter146Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11500"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter150Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter150Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11510"))
						{
							sumChepter151Ph += item.GetCurrentBalance();
							chepter151Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11520"))
						{
							sumChepter152Ph += item.GetCurrentBalance();
							chepter152Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11600"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter160Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter160Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11610"))
						{
							sumChepter161Ph += item.GetCurrentBalance();
							chepter161Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11620"))
						{
							sumChepter162Ph += item.GetCurrentBalance();
							chepter162Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11630"))
						{
							sumChepter163Ph += item.GetCurrentBalance();
							chepter163Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11640"))
						{
							sumChepter164Ph += item.GetCurrentBalance();
							chepter164Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11650"))
						{
							sumChepter165Ph += item.GetCurrentBalance();
							chepter165Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11660"))
						{
							sumChepter166Ph += item.GetCurrentBalance();
							chepter166Ph += "<td>" + QString::number(item.GetCurrentBalance()) + "</td>";
						}
						if (0 == item.GetNumber().compare("11700"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter170Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter170Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11800"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter180Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter180Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11810"))
						{
							sumChepter181Ph += item.GetCurrentBalance();
							chepter181Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11820"))
						{
							sumChepter182Ph += item.GetCurrentBalance();
							chepter182Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11830"))
						{
							sumChepter183Ph += item.GetCurrentBalance();
							chepter183Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11840"))
						{
							sumChepter184Ph += item.GetCurrentBalance();
							chepter184Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11900"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter190Ph+= "<td>" +QString::number(item.GetCurrentBalance(), 'f', 3)+ "</td>";
							sumChepter190Ph += item.GetCurrentBalance();
						}


						//Краткосрочные обязательства
						if (0 == item.GetNumber().compare("22000"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter200Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter200Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22010"))
						{
							sumChepter201Ph += item.GetCurrentBalance()*(-1);
							chepter201Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22020"))
						{
							sumChepter202Ph += item.GetCurrentBalance()*(-1);
							chepter202Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22030") || 0 == item.GetNumber().compare("22040"))
						{
							sChepter203Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22100"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter210Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter210Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22110"))
						{
							sumChepter211Ph += item.GetCurrentBalance()*(-1);
							chepter211Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22120"))
						{
							sumChepter212Ph += item.GetCurrentBalance()*(-1);
							chepter212Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22130"))
						{
							sumChepter213Ph += item.GetCurrentBalance()*(-1);
							chepter213Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22140"))
						{
							sumChepter214Ph += item.GetCurrentBalance()*(-1);
							chepter214Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22200"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter220Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter220Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22210"))
						{
							sumChepter221Ph += item.GetCurrentBalance()*(-1);
							chepter221Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22220") || 0 == item.GetNumber().compare("22230"))
						{
							sChepter222Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22240"))
						{
							sumChepter223Ph += item.GetCurrentBalance()*(-1);
							chepter223Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22250") || 0 == item.GetNumber().compare("22260"))
						{
							sChepter224Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22270"))
						{
							sumChepter225Ph += item.GetCurrentBalance()*(-1);
							chepter225Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22300"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter230Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter230Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22310"))
						{
							sumChepter231Ph += item.GetCurrentBalance()*(-1);
							chepter231Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22320"))
						{
							sumChepter232Ph += item.GetCurrentBalance()*(-1);
							chepter232Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22330"))
						{
							sumChepter233Ph += item.GetCurrentBalance()*(-1);
							chepter233Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22340") || 0 == item.GetNumber().compare("22350")
							|| 0 == item.GetNumber().compare("22360") || 0 == item.GetNumber().compare("22370"))
						{
							sChepter234Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22400"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter240Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter240Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22500"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter250Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter250Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22510"))
						{
							sumChepter251Ph += item.GetCurrentBalance()*(-1);
							chepter251Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22520"))
						{
							sumChepter252Ph += item.GetCurrentBalance()*(-1);
							chepter252Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22530"))
						{
							sumChepter253Ph += item.GetCurrentBalance()*(-1);
							chepter253Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}


						//Долгосрочные обязательства
						if (0 == item.GetNumber().compare("22600"))
						{
							sChepter298Ph += item.GetCurrentBalance();
							chepter260Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter260Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22610") || 0 == item.GetNumber().compare("22640"))
						{
							sChepter261Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22620") || 0 == item.GetNumber().compare("22630"))
						{
							sChepter262Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22650"))
						{
							sumChepter263Ph += item.GetCurrentBalance()*(-1);
							chepter263Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22660") || 0 == item.GetNumber().compare("22670"))
						{
							sChepter264Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22700"))
						{
							sChepter298Ph += item.GetCurrentBalance();
							chepter270Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter270Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22800"))
						{
							sChepter298Ph += item.GetCurrentBalance();
							chepter280Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter280Ph += item.GetCurrentBalance()*(-1);
						}


						//Собственный капитал
						if (0 == item.GetNumber().compare("33000"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter300Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter300Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33010"))
						{
							sumChepter301Ph += item.GetCurrentBalance()*(-1);
							chepter301Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33020"))
						{
							sumChepter302Ph += item.GetCurrentBalance()*(-1);
							chepter302Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33030"))
						{
							sumChepter303Ph += item.GetCurrentBalance()*(-1);
							chepter303Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33090"))
						{
							sumChepter304Ph += item.GetCurrentBalance()*(-1);
							chepter304Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33100"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter310Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter310Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33110"))
						{
							sumChepter311Ph += item.GetCurrentBalance()*(-1);
							chepter311Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33120") || 0 == item.GetNumber().compare("33130"))
						{
							sChepter313Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("33140"))
						{
							sumChepter314Ph += item.GetCurrentBalance()*(-1);
							chepter314Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33150") || 0 == item.GetNumber().compare("33160"))
						{
							sChepter315Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("33200"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter320Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter320Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33300"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter330Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter330Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33400"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter340Ph+= "<td>" +QString::number(item.GetCurrentBalance()*(-1), 'f', 3)+ "</td>";
							sumChepter340Ph += item.GetCurrentBalance()*(-1);
						}

					}
					
					chepter33Ph+= "<td>" +QString::number(sChepter33Ph, 'f', 3)+ "</td>";
					sumChepter33Ph += sChepter33Ph;
					chepter53Ph+= "<td>" +QString::number(sChepter53Ph, 'f', 3)+ "</td>";
					sumChepter33Ph += sChepter53Ph;
					chepter54Ph+= "<td>" +QString::number(sChepter54Ph, 'f', 3)+ "</td>";
					sumChepter54Ph += sChepter54Ph;
					chepter71Ph+= "<td>" +QString::number(sChepter71Ph, 'f', 3)+ "</td>";
					sumChepter71Ph += sChepter71Ph;
					chepter121Ph+= "<td>" +QString::number(sChepter121Ph, 'f', 3)+ "</td>";
					sumChepter121Ph += sChepter121Ph;
					chepter131Ph+= "<td>" +QString::number(sChepter131Ph, 'f', 3)+ "</td>";
					sumChepter131Ph += sChepter131Ph;
					chepter203Ph+= "<td>" +QString::number(sChepter203Ph*(-1), 'f', 3)+ "</td>";
					sumChepter203Ph += sChepter203Ph*(-1);
					chepter222Ph+= "<td>" +QString::number(sChepter222Ph*(-1), 'f', 3)+ "</td>";
					sumChepter222Ph += sChepter222Ph*(-1);
					chepter224Ph+= "<td>" +QString::number(sChepter224Ph*(-1), 'f', 3)+ "</td>";
					sumChepter224Ph += sChepter224Ph*(-1);
					chepter234Ph+= "<td>" +QString::number(sChepter234Ph*(-1), 'f', 3)+ "</td>";
					sumChepter234Ph += sChepter234Ph*(-1);
					chepter261Ph+= "<td>" +QString::number(sChepter261Ph*(-1), 'f', 3)+ "</td>";
					sumChepter261Ph += sChepter261Ph*(-1);
					chepter262Ph+= "<td>" +QString::number(sChepter262Ph*(-1), 'f', 3)+ "</td>";
					sumChepter262Ph += sChepter262Ph*(-1);
					chepter264Ph+= "<td>" +QString::number(sChepter264Ph*(-1), 'f', 3)+ "</td>";
					sumChepter264Ph += sChepter264Ph*(-1);
					chepter313Ph+= "<td>" +QString::number(sChepter313Ph*(-1), 'f', 3)+ "</td>";
					sumChepter313Ph += sChepter313Ph*(-1);
					chepter315Ph+= "<td>" +QString::number(sChepter315Ph*(-1), 'f', 3)+ "</td>";
					sumChepter315Ph += sChepter315Ph*(-1);
					//итоги
					chepter99Ph+= "<td>" +QString::number(sChepter99Ph, 'f', 3)+ "</td>";
					sumChepter99Ph += sChepter99Ph;
					chepter119Ph+= "<td>" +QString::number(sChepter100Ph + sChepter110Ph, 'f', 3)+ "</td>";
					sumChepter119Ph += sChepter100Ph + sChepter110Ph;
					chepter199Ph+= "<td>" +QString::number(sChepter199Ph + sChepter110Ph, 'f', 3)+ "</td>";
					sumChepter199Ph += sChepter199Ph + sChepter110Ph;
					chepter1000Ph+= "<td>" +QString::number(sChepter99Ph + sChepter199Ph + sChepter110Ph, 'f', 3)+ "</td>";
					sumChepter1000Ph += sChepter99Ph + sChepter199Ph + sChepter110Ph;
					chepter259Ph+= "<td>" +QString::number(sChepter259Ph*(-1), 'f', 3)+ "</td>";
					sumChepter259Ph += sChepter259Ph*(-1);
					chepter298Ph+= "<td>" +QString::number(sChepter298Ph*(-1), 'f', 3)+ "</td>";
					sumChepter298Ph += sChepter298Ph*(-1);
					chepter299Ph+= "<td>" +QString::number((sChepter259Ph + sChepter298Ph)*(-1), 'f', 3)+ "</td>";
					sumChepter299Ph += (sChepter259Ph + sChepter298Ph)*(-1);
					chepter339Ph+= "<td>" +QString::number(sChepter339Ph*(-1), 'f', 3)+ "</td>";
					sumChepter339Ph += sChepter339Ph*(-1);
					chepter399Ph+= "<td>" +QString::number((sChepter339Ph + sChepter259Ph + sChepter298Ph)*(-1), 'f', 3)+ "</td>";
					sumChepter399Ph += (sChepter339Ph + sChepter259Ph + sChepter298Ph)*(-1);

				}

				
			}
		}

		/*monthHlder += "<th><b>" + QString::fromWCharArray(L"Итого") + "</b></th>";
		chepter10Ph += "<td>" + QString::number(sumChepter10Ph, 'f', 3) + "</td>";
		chepter20Ph += "<td>" + QString::number(sumChepter20Ph, 'f', 3) + "</td>";
		chepter30Ph += "<td>" + QString::number(sumChepter30Ph, 'f', 3) + "</td>";
		chepter31Ph += "<td>" + QString::number(sumChepter31Ph, 'f', 3) + "</td>";
		chepter32Ph += "<td>" + QString::number(sumChepter32Ph, 'f', 3) + "</td>";
		chepter33Ph += "<td>" + QString::number(sumChepter33Ph, 'f', 3) + "</td>";
		chepter34Ph += "<td>" + QString::number(sumChepter34Ph, 'f', 3) + "</td>";
		chepter35Ph += "<td>" + QString::number(sumChepter35Ph, 'f', 3) + "</td>";
		chepter40Ph += "<td>" + QString::number(sumChepter40Ph, 'f', 3) + "</td>";
		chepter41Ph += "<td>" + QString::number(sumChepter41Ph, 'f', 3) + "</td>";
		chepter42Ph += "<td>" + QString::number(sumChepter42Ph, 'f', 3) + "</td>";
		chepter43Ph += "<td>" + QString::number(sumChepter43Ph, 'f', 3) + "</td>";
		chepter50Ph += "<td>" + QString::number(sumChepter50Ph, 'f', 3) + "</td>";
		chepter51Ph += "<td>" + QString::number(sumChepter51Ph, 'f', 3) + "</td>";
		chepter52Ph += "<td>" + QString::number(sumChepter52Ph, 'f', 3) + "</td>";
		chepter53Ph += "<td>" + QString::number(sumChepter53Ph, 'f', 3) + "</td>";
		chepter54Ph += "<td>" + QString::number(sumChepter54Ph, 'f', 3) + "</td>";
		chepter55Ph += "<td>" + QString::number(sumChepter55Ph, 'f', 3) + "</td>";
		chepter56Ph += "<td>" + QString::number(sumChepter56Ph, 'f', 3) + "</td>";
		chepter59Ph += "<td>" + QString::number(sumChepter59Ph, 'f', 3) + "</td>";
		chepter60Ph += "<td>" + QString::number(sumChepter60Ph, 'f', 3) + "</td>";
		chepter70Ph += "<td>" + QString::number(sumChepter70Ph, 'f', 3) + "</td>";
		chepter71Ph += "<td>" + QString::number(sumChepter71Ph, 'f', 3) + "</td>";
		chepter72Ph += "<td>" + QString::number(sumChepter72Ph, 'f', 3) + "</td>";
		chepter73Ph += "<td>" + QString::number(sumChepter73Ph, 'f', 3) + "</td>";
		chepter74Ph += "<td>" + QString::number(sumChepter74Ph, 'f', 3) + "</td>";
		chepter742Ph += "<td>" + QString::number(sumChepter742Ph, 'f', 3) + "</td>";
		chepter75Ph += "<td>" + QString::number(sumChepter75Ph, 'f', 3) + "</td>";
		chepter76Ph += "<td>" + QString::number(sumChepter76Ph, 'f', 3) + "</td>";
		chepter77Ph += "<td>" + QString::number(sumChepter77Ph, 'f', 3) + "</td>";
		chepter78Ph += "<td>" + QString::number(sumChepter78Ph, 'f', 3) + "</td>";
		chepter79Ph += "<td>" + QString::number(sumChepter79Ph, 'f', 3) + "</td>";
		chepter80Ph += "<td>" + QString::number(sumChepter80Ph, 'f', 3) + "</td>";
		chepter81Ph += "<td>" + QString::number(sumChepter81Ph, 'f', 3) + "</td>";
		chepter82Ph += "<td>" + QString::number(sumChepter82Ph, 'f', 3) + "</td>";
		chepter83Ph += "<td>" + QString::number(sumChepter83Ph, 'f', 3) + "</td>";
		chepter90Ph += "<td>" + QString::number(sumChepter90Ph, 'f', 3) + "</td>";
		chepter91Ph += "<td>" + QString::number(sumChepter91Ph, 'f', 3) + "</td>";
		chepter92Ph += "<td>" + QString::number(sumChepter92Ph, 'f', 3) + "</td>";
		chepter93Ph += "<td>" + QString::number(sumChepter93Ph, 'f', 3) + "</td>";
		chepter99Ph += "<td>" + QString::number(sumChepter99Ph, 'f', 3) + "</td>";
		chepter100Ph += "<td>" + QString::number(sumChepter100Ph, 'f', 3) + "</td>";
		chepter101Ph += "<td>" + QString::number(sumChepter101Ph, 'f', 3) + "</td>";
		chepter102Ph += "<td>" + QString::number(sumChepter102Ph, 'f', 3) + "</td>";
		chepter103Ph += "<td>" + QString::number(sumChepter103Ph, 'f', 3) + "</td>";
		chepter104Ph += "<td>" + QString::number(sumChepter104Ph, 'f', 3) + "</td>";
		chepter105Ph += "<td>" + QString::number(sumChepter105Ph, 'f', 3) + "</td>";
		chepter106Ph += "<td>" + QString::number(sumChepter106Ph, 'f', 3) + "</td>";
		chepter107Ph += "<td>" + QString::number(sumChepter107Ph, 'f', 3) + "</td>";
		chepter108Ph += "<td>" + QString::number(sumChepter108Ph, 'f', 3) + "</td>";
		chepter109Ph += "<td>" + QString::number(sumChepter109Ph, 'f', 3) + "</td>";
		chepter110Ph += "<td>" + QString::number(sumChepter110Ph, 'f', 3) + "</td>";
		chepter119Ph += "<td>" + QString::number(sumChepter119Ph, 'f', 3) + "</td>";
		chepter120Ph += "<td>" + QString::number(sumChepter120Ph, 'f', 3) + "</td>";
		chepter121Ph += "<td>" + QString::number(sumChepter121Ph, 'f', 3) + "</td>";
		chepter122Ph += "<td>" + QString::number(sumChepter122Ph, 'f', 3) + "</td>";
		chepter130Ph += "<td>" + QString::number(sumChepter130Ph, 'f', 3) + "</td>";
		chepter131Ph += "<td>" + QString::number(sumChepter131Ph, 'f', 3) + "</td>";
		chepter132Ph += "<td>" + QString::number(sumChepter132Ph, 'f', 3) + "</td>";
		chepter133Ph += "<td>" + QString::number(sumChepter133Ph, 'f', 3) + "</td>";
		chepter140Ph += "<td>" + QString::number(sumChepter140Ph, 'f', 3) + "</td>";
		chepter141Ph += "<td>" + QString::number(sumChepter141Ph, 'f', 3) + "</td>";
		chepter142Ph += "<td>" + QString::number(sumChepter142Ph, 'f', 3) + "</td>";
		chepter143Ph += "<td>" + QString::number(sumChepter143Ph, 'f', 3) + "</td>";
		chepter144Ph += "<td>" + QString::number(sumChepter144Ph, 'f', 3) + "</td>";
		chepter145Ph += "<td>" + QString::number(sumChepter145Ph, 'f', 3) + "</td>";
		chepter146Ph += "<td>" + QString::number(sumChepter146Ph, 'f', 3) + "</td>";
		chepter150Ph += "<td>" + QString::number(sumChepter150Ph, 'f', 3) + "</td>";
		chepter151Ph += "<td>" + QString::number(sumChepter151Ph, 'f', 3) + "</td>";
		chepter152Ph += "<td>" + QString::number(sumChepter152Ph, 'f', 3) + "</td>";
		chepter160Ph += "<td>" + QString::number(sumChepter160Ph, 'f', 3) + "</td>";
		chepter161Ph += "<td>" + QString::number(sumChepter161Ph, 'f', 3) + "</td>";
		chepter162Ph += "<td>" + QString::number(sumChepter162Ph, 'f', 3) + "</td>";
		chepter163Ph += "<td>" + QString::number(sumChepter163Ph, 'f', 3) + "</td>";
		chepter164Ph += "<td>" + QString::number(sumChepter164Ph, 'f', 3) + "</td>";
		chepter165Ph += "<td>" + QString::number(sumChepter165Ph, 'f', 3) + "</td>";
		chepter166Ph += "<td>" + QString::number(sumChepter166Ph, 'f', 3) + "</td>";
		chepter170Ph += "<td>" + QString::number(sumChepter170Ph, 'f', 3) + "</td>";
		chepter180Ph += "<td>" + QString::number(sumChepter180Ph, 'f', 3) + "</td>";
		chepter181Ph += "<td>" + QString::number(sumChepter181Ph, 'f', 3) + "</td>";
		chepter182Ph += "<td>" + QString::number(sumChepter182Ph, 'f', 3) + "</td>";
		chepter183Ph += "<td>" + QString::number(sumChepter183Ph, 'f', 3) + "</td>";
		chepter184Ph += "<td>" + QString::number(sumChepter184Ph, 'f', 3) + "</td>";
		chepter190Ph += "<td>" + QString::number(sumChepter190Ph, 'f', 3) + "</td>";
		chepter199Ph += "<td>" + QString::number(sumChepter199Ph, 'f', 3) + "</td>";
		chepter1000Ph += "<td>" + QString::number(sumChepter1000Ph, 'f', 3) + "</td>";
		chepter200Ph += "<td>" + QString::number(sumChepter200Ph, 'f', 3) + "</td>";
		chepter201Ph += "<td>" + QString::number(sumChepter201Ph, 'f', 3) + "</td>";
		chepter202Ph += "<td>" + QString::number(sumChepter202Ph, 'f', 3) + "</td>";
		chepter203Ph += "<td>" + QString::number(sumChepter203Ph, 'f', 3) + "</td>";
		chepter210Ph += "<td>" + QString::number(sumChepter210Ph, 'f', 3) + "</td>";
		chepter211Ph += "<td>" + QString::number(sumChepter211Ph, 'f', 3) + "</td>";
		chepter212Ph += "<td>" + QString::number(sumChepter212Ph, 'f', 3) + "</td>";
		chepter213Ph += "<td>" + QString::number(sumChepter213Ph, 'f', 3) + "</td>";
		chepter214Ph += "<td>" + QString::number(sumChepter214Ph, 'f', 3) + "</td>";
		chepter220Ph += "<td>" + QString::number(sumChepter220Ph, 'f', 3) + "</td>";
		chepter221Ph += "<td>" + QString::number(sumChepter221Ph, 'f', 3) + "</td>";
		chepter222Ph += "<td>" + QString::number(sumChepter222Ph, 'f', 3) + "</td>";
		chepter223Ph += "<td>" + QString::number(sumChepter223Ph, 'f', 3) + "</td>";
		chepter224Ph += "<td>" + QString::number(sumChepter224Ph, 'f', 3) + "</td>";
		chepter225Ph += "<td>" + QString::number(sumChepter225Ph, 'f', 3) + "</td>";
		chepter230Ph += "<td>" + QString::number(sumChepter230Ph, 'f', 3) + "</td>";
		chepter231Ph += "<td>" + QString::number(sumChepter231Ph, 'f', 3) + "</td>";
		chepter232Ph += "<td>" + QString::number(sumChepter232Ph, 'f', 3) + "</td>";
		chepter233Ph += "<td>" + QString::number(sumChepter233Ph, 'f', 3) + "</td>";
		chepter234Ph += "<td>" + QString::number(sumChepter234Ph, 'f', 3) + "</td>";
		chepter240Ph += "<td>" + QString::number(sumChepter240Ph, 'f', 3) + "</td>";
		chepter250Ph += "<td>" + QString::number(sumChepter250Ph, 'f', 3) + "</td>";
		chepter251Ph += "<td>" + QString::number(sumChepter251Ph, 'f', 3) + "</td>";
		chepter252Ph += "<td>" + QString::number(sumChepter252Ph, 'f', 3) + "</td>";
		chepter253Ph += "<td>" + QString::number(sumChepter253Ph, 'f', 3) + "</td>";
		chepter259Ph += "<td>" + QString::number(sumChepter259Ph, 'f', 3) + "</td>";
		chepter260Ph += "<td>" + QString::number(sumChepter260Ph, 'f', 3) + "</td>";
		chepter261Ph += "<td>" + QString::number(sumChepter261Ph, 'f', 3) + "</td>";
		chepter262Ph += "<td>" + QString::number(sumChepter262Ph, 'f', 3) + "</td>";
		chepter263Ph += "<td>" + QString::number(sumChepter263Ph, 'f', 3) + "</td>";
		chepter264Ph += "<td>" + QString::number(sumChepter264Ph, 'f', 3) + "</td>";
		chepter270Ph += "<td>" + QString::number(sumChepter270Ph, 'f', 3) + "</td>";
		chepter280Ph += "<td>" + QString::number(sumChepter280Ph, 'f', 3) + "</td>";
		chepter290Ph += "<td>" + QString::number(sumChepter290Ph, 'f', 3) + "</td>";
		chepter298Ph += "<td>" + QString::number(sumChepter298Ph, 'f', 3) + "</td>";
		chepter299Ph += "<td>" + QString::number(sumChepter299Ph, 'f', 3) + "</td>";
		chepter300Ph += "<td>" + QString::number(sumChepter300Ph, 'f', 3) + "</td>";
		chepter301Ph += "<td>" + QString::number(sumChepter301Ph, 'f', 3) + "</td>";
		chepter302Ph += "<td>" + QString::number(sumChepter302Ph, 'f', 3) + "</td>";
		chepter303Ph += "<td>" + QString::number(sumChepter303Ph, 'f', 3) + "</td>";
		chepter304Ph += "<td>" + QString::number(sumChepter304Ph, 'f', 3) + "</td>";
		chepter310Ph += "<td>" + QString::number(sumChepter310Ph, 'f', 3) + "</td>";
		chepter311Ph += "<td>" + QString::number(sumChepter311Ph, 'f', 3) + "</td>";
		chepter313Ph += "<td>" + QString::number(sumChepter313Ph, 'f', 3) + "</td>";
		chepter314Ph += "<td>" + QString::number(sumChepter314Ph, 'f', 3) + "</td>";
		chepter315Ph += "<td>" + QString::number(sumChepter315Ph, 'f', 3) + "</td>";
		chepter320Ph += "<td>" + QString::number(sumChepter320Ph, 'f', 3) + "</td>";
		chepter330Ph += "<td>" + QString::number(sumChepter330Ph, 'f', 3) + "</td>";
		chepter340Ph += "<td>" + QString::number(sumChepter340Ph, 'f', 3) + "</td>";
		chepter339Ph += "<td>" + QString::number(sumChepter339Ph, 'f', 3) + "</td>";
		chepter399Ph += "<td>" + QString::number(sumChepter399Ph, 'f', 3) + "</td>";*/

		
		reportText.replace(QString("tillDatePh"), endDate, Qt::CaseInsensitive);
		reportText.replace(QString("MonthPH"), monthHlder, Qt::CaseInsensitive);
		reportText.replace(QString("chepter00Ph"), chepter00Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter10Ph"), chepter10Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter20Ph"), chepter20Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter30Ph"), chepter30Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter31Ph"), chepter31Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter32Ph"), chepter32Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter33Ph"), chepter33Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter34Ph"), chepter34Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter35Ph"), chepter35Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter40Ph"), chepter40Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter41Ph"), chepter41Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter42Ph"), chepter42Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter43Ph"), chepter43Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter50Ph"), chepter50Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter51Ph"), chepter51Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter52Ph"), chepter52Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter53Ph"), chepter53Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter54Ph"), chepter54Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter55Ph"), chepter55Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter56Ph"), chepter56Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter59Ph"), chepter59Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter60Ph"), chepter60Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter70Ph"), chepter70Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter71Ph"), chepter71Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter72Ph"), chepter72Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter73Ph"), chepter73Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter74Ph"), chepter74Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter742Ph"), chepter742Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter75Ph"), chepter75Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter76Ph"), chepter76Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter77Ph"), chepter77Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter78Ph"), chepter78Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter79Ph"), chepter79Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter80Ph"), chepter80Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter81Ph"), chepter81Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter82Ph"), chepter82Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter83Ph"), chepter83Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter90Ph"), chepter90Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter91Ph"), chepter91Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter92Ph"), chepter92Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter93Ph"), chepter93Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter99Ph"), chepter93Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter100Ph"), chepter100Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter101Ph"), chepter101Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter102Ph"), chepter102Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter103Ph"), chepter103Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter104Ph"), chepter104Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter105Ph"), chepter105Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter106Ph"), chepter106Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter107Ph"), chepter107Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter108Ph"), chepter108Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter109Ph"), chepter109Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter110Ph"), chepter110Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter119Ph"), chepter119Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter120Ph"), chepter120Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter121Ph"), chepter121Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter122Ph"), chepter122Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter130Ph"), chepter130Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter131Ph"), chepter131Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter132Ph"), chepter132Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter133Ph"), chepter133Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter140Ph"), chepter140Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter141Ph"), chepter141Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter142Ph"), chepter142Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter143Ph"), chepter143Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter144Ph"), chepter144Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter145Ph"), chepter145Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter146Ph"), chepter146Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter150Ph"), chepter150Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter151Ph"), chepter151Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter152Ph"), chepter152Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter160Ph"), chepter160Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter161Ph"), chepter161Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter162Ph"), chepter162Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter163Ph"), chepter163Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter164Ph"), chepter164Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter165Ph"), chepter165Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter166Ph"), chepter166Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter170Ph"), chepter170Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter180Ph"), chepter180Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter181Ph"), chepter181Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter182Ph"), chepter182Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter183Ph"), chepter183Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter184Ph"), chepter184Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter190Ph"), chepter190Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter199Ph"), chepter199Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter1000Ph"), chepter1000Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter200Ph"), chepter200Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter201Ph"), chepter201Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter202Ph"), chepter202Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter203Ph"), chepter203Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter210Ph"), chepter210Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter211Ph"), chepter211Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter212Ph"), chepter212Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter213Ph"), chepter213Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter214Ph"), chepter214Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter220Ph"), chepter220Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter221Ph"), chepter221Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter222Ph"), chepter222Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter223Ph"), chepter223Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter224Ph"), chepter224Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter225Ph"), chepter225Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter230Ph"), chepter230Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter231Ph"), chepter231Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter232Ph"), chepter232Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter233Ph"), chepter233Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter234Ph"), chepter234Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter240Ph"), chepter240Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter250Ph"), chepter250Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter251Ph"), chepter251Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter252Ph"), chepter252Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter253Ph"), chepter253Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter259Ph"), chepter259Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter260Ph"), chepter260Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter261Ph"), chepter261Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter262Ph"), chepter262Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter263Ph"), chepter263Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter264Ph"), chepter264Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter270Ph"), chepter270Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter280Ph"), chepter280Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter290Ph"), chepter290Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter298Ph"), chepter298Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter299Ph"), chepter299Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter300Ph"), chepter300Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter301Ph"), chepter301Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter302Ph"), chepter302Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter303Ph"), chepter303Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter304Ph"), chepter304Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter310Ph"), chepter310Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter311Ph"), chepter311Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter313Ph"), chepter313Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter314Ph"), chepter314Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter315Ph"), chepter315Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter320Ph"), chepter320Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter330Ph"), chepter330Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter340Ph"), chepter340Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter339Ph"), chepter339Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter399Ph"), chepter399Ph, Qt::CaseInsensitive);

		docForm->webEngineView->setHtml(reportText);
		docForm->SetContent(reportText);
		docForm->webEngineView->show();
		docForm->show();
		Close();

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
		QMdiSubWindow *generateOneAccWindow = new QMdiSubWindow;
		generateOneAccWindow->setWidget(docForm);
		generateOneAccWindow->setAttribute(Qt::WA_DeleteOnClose);
		generateOneAccWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
		mainForm->mdiArea->addSubWindow(generateOneAccWindow);

		//read template
		QFile file;
		file.setFileName(":/docs/company_balance_period.html");
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
		QString chepter31Ph = "";
		QString chepter32Ph = "";
		QString chepter33Ph = "";
		QString chepter34Ph = "";
		QString chepter35Ph = "";
		QString chepter40Ph = "";
		QString chepter41Ph = "";
		QString chepter42Ph = "";
		QString chepter43Ph = "";
		QString chepter50Ph = "";
		QString chepter51Ph = "";
		QString chepter52Ph = "";
		QString chepter53Ph = "";
		QString chepter54Ph = "";
		QString chepter55Ph = "";
		QString chepter56Ph = "";
		QString chepter59Ph = "";
		QString chepter60Ph = "";
		QString chepter70Ph = "";
		QString chepter71Ph = "";
		QString chepter72Ph = "";
		QString chepter73Ph = "";
		QString chepter74Ph = "";
		QString chepter742Ph = "";
		QString chepter75Ph = "";
		QString chepter76Ph = "";
		QString chepter77Ph = "";
		QString chepter78Ph = "";
		QString chepter79Ph = "";
		QString chepter80Ph = "";
		QString chepter81Ph = "";
		QString chepter82Ph = "";
		QString chepter83Ph = "";
		QString chepter90Ph = "";
		QString chepter91Ph = "";
		QString chepter92Ph = "";
		QString chepter93Ph = "";
		QString chepter99Ph = "";
		QString chepter100Ph = "";
		QString chepter101Ph = "";
		QString chepter102Ph = "";
		QString chepter103Ph = "";
		QString chepter104Ph = "";
		QString chepter105Ph = "";
		QString chepter106Ph = "";
		QString chepter107Ph = "";
		QString chepter108Ph = "";
		QString chepter109Ph = "";
		QString chepter110Ph = "";
		QString chepter119Ph = "";
		QString chepter120Ph = "";
		QString chepter121Ph = "";
		QString chepter122Ph = "";
		QString chepter130Ph = "";
		QString chepter131Ph = "";
		QString chepter132Ph = "";
		QString chepter133Ph = "";
		QString chepter140Ph = "";
		QString chepter141Ph = "";
		QString chepter142Ph = "";
		QString chepter143Ph = "";
		QString chepter144Ph = "";
		QString chepter145Ph = "";
		QString chepter146Ph = "";
		QString chepter150Ph = "";
		QString chepter151Ph = "";
		QString chepter152Ph = "";
		QString chepter160Ph = "";
		QString chepter161Ph = "";
		QString chepter162Ph = "";
		QString chepter163Ph = "";
		QString chepter164Ph = "";
		QString chepter165Ph = "";
		QString chepter166Ph = "";
		QString chepter170Ph = "";
		QString chepter180Ph = "";
		QString chepter181Ph = "";
		QString chepter182Ph = "";
		QString chepter183Ph = "";
		QString chepter184Ph = "";
		QString chepter190Ph = "";
		QString chepter199Ph = "";
		QString chepter1000Ph = "";
		QString chepter200Ph = "";
		QString chepter201Ph = "";
		QString chepter202Ph = "";
		QString chepter203Ph = "";
		QString chepter210Ph = "";
		QString chepter211Ph = "";
		QString chepter212Ph = "";
		QString chepter213Ph = "";
		QString chepter214Ph = "";
		QString chepter220Ph = "";
		QString chepter221Ph = "";
		QString chepter222Ph = "";
		QString chepter223Ph = "";
		QString chepter224Ph = "";
		QString chepter225Ph = "";
		QString chepter230Ph = "";
		QString chepter231Ph = "";
		QString chepter232Ph = "";
		QString chepter233Ph = "";
		QString chepter234Ph = "";
		QString chepter240Ph = "";
		QString chepter250Ph = "";
		QString chepter251Ph = "";
		QString chepter252Ph = "";
		QString chepter253Ph = "";
		QString chepter259Ph = "";
		QString chepter260Ph = "";
		QString chepter261Ph = "";
		QString chepter262Ph = "";
		QString chepter263Ph = "";
		QString chepter264Ph = "";
		QString chepter270Ph = "";
		QString chepter280Ph = "";
		QString chepter290Ph = "";
		QString chepter298Ph = "";
		QString chepter299Ph = "";
		QString chepter300Ph = "";
		QString chepter301Ph = "";
		QString chepter302Ph = "";
		QString chepter303Ph = "";
		QString chepter304Ph = "";
		QString chepter310Ph = "";
		QString chepter311Ph = "";
		QString chepter313Ph = "";
		QString chepter314Ph = "";
		QString chepter315Ph = "";
		QString chepter320Ph = "";
		QString chepter330Ph = "";
		QString chepter340Ph = "";
		QString chepter339Ph = "";
		QString chepter399Ph = "";

		double sumChepter00Ph = 0;
		double sumChepter10Ph = 0;
		double sumChepter20Ph = 0;
		double sumChepter30Ph = 0;
		double sumChepter31Ph = 0;
		double sumChepter32Ph = 0;
		double sumChepter33Ph = 0;
		double sumChepter34Ph = 0;
		double sumChepter35Ph = 0;
		double sumChepter40Ph = 0;
		double sumChepter41Ph = 0;
		double sumChepter42Ph = 0;
		double sumChepter43Ph = 0;
		double sumChepter50Ph = 0;
		double sumChepter51Ph = 0;
		double sumChepter52Ph = 0;
		double sumChepter53Ph = 0;
		double sumChepter54Ph = 0;
		double sumChepter55Ph = 0;
		double sumChepter56Ph = 0;
		double sumChepter59Ph = 0;
		double sumChepter60Ph = 0;
		double sumChepter70Ph = 0;
		double sumChepter71Ph = 0;
		double sumChepter72Ph = 0;
		double sumChepter73Ph = 0;
		double sumChepter74Ph = 0;
		double sumChepter742Ph = 0;
		double sumChepter75Ph = 0;
		double sumChepter76Ph = 0;
		double sumChepter77Ph = 0;
		double sumChepter78Ph = 0;
		double sumChepter79Ph = 0;
		double sumChepter80Ph = 0;
		double sumChepter81Ph = 0;
		double sumChepter82Ph = 0;
		double sumChepter83Ph = 0;
		double sumChepter90Ph = 0;
		double sumChepter91Ph = 0;
		double sumChepter92Ph = 0;
		double sumChepter93Ph = 0;
		double sumChepter99Ph = 0;
		double sumChepter100Ph = 0;
		double sumChepter101Ph = 0;
		double sumChepter102Ph = 0;
		double sumChepter103Ph = 0;
		double sumChepter104Ph = 0;
		double sumChepter105Ph = 0;
		double sumChepter106Ph = 0;
		double sumChepter107Ph = 0;
		double sumChepter108Ph = 0;
		double sumChepter109Ph = 0;
		double sumChepter110Ph = 0;
		double sumChepter119Ph = 0;
		double sumChepter120Ph = 0;
		double sumChepter121Ph = 0;
		double sumChepter122Ph = 0;
		double sumChepter130Ph = 0;
		double sumChepter131Ph = 0;
		double sumChepter132Ph = 0;
		double sumChepter133Ph = 0;
		double sumChepter140Ph = 0;
		double sumChepter141Ph = 0;
		double sumChepter142Ph = 0;
		double sumChepter143Ph = 0;
		double sumChepter144Ph = 0;
		double sumChepter145Ph = 0;
		double sumChepter146Ph = 0;
		double sumChepter150Ph = 0;
		double sumChepter151Ph = 0;
		double sumChepter152Ph = 0;
		double sumChepter160Ph = 0;
		double sumChepter161Ph = 0;
		double sumChepter162Ph = 0;
		double sumChepter163Ph = 0;
		double sumChepter164Ph = 0;
		double sumChepter165Ph = 0;
		double sumChepter166Ph = 0;
		double sumChepter170Ph = 0;
		double sumChepter180Ph = 0;
		double sumChepter181Ph = 0;
		double sumChepter182Ph = 0;
		double sumChepter183Ph = 0;
		double sumChepter184Ph = 0;
		double sumChepter190Ph = 0;
		double sumChepter199Ph = 0;
		double sumChepter1000Ph = 0;
		double sumChepter200Ph = 0;
		double sumChepter201Ph = 0;
		double sumChepter202Ph = 0;
		double sumChepter203Ph = 0;
		double sumChepter210Ph = 0;
		double sumChepter211Ph = 0;
		double sumChepter212Ph = 0;
		double sumChepter213Ph = 0;
		double sumChepter214Ph = 0;
		double sumChepter220Ph = 0;
		double sumChepter221Ph = 0;
		double sumChepter222Ph = 0;
		double sumChepter223Ph = 0;
		double sumChepter224Ph = 0;
		double sumChepter225Ph = 0;
		double sumChepter230Ph = 0;
		double sumChepter231Ph = 0;
		double sumChepter232Ph = 0;
		double sumChepter233Ph = 0;
		double sumChepter234Ph = 0;
		double sumChepter240Ph = 0;
		double sumChepter250Ph = 0;
		double sumChepter251Ph = 0;
		double sumChepter252Ph = 0;
		double sumChepter253Ph = 0;
		double sumChepter259Ph = 0;
		double sumChepter260Ph = 0;
		double sumChepter261Ph = 0;
		double sumChepter262Ph = 0;
		double sumChepter263Ph = 0;
		double sumChepter264Ph = 0;
		double sumChepter270Ph = 0;
		double sumChepter280Ph = 0;
		double sumChepter290Ph = 0;
		double sumChepter298Ph = 0;
		double sumChepter299Ph = 0;
		double sumChepter300Ph = 0;
		double sumChepter301Ph = 0;
		double sumChepter302Ph = 0;
		double sumChepter303Ph = 0;
		double sumChepter304Ph = 0;
		double sumChepter310Ph = 0;
		double sumChepter311Ph = 0;
		double sumChepter313Ph = 0;
		double sumChepter314Ph = 0;
		double sumChepter315Ph = 0;
		double sumChepter320Ph = 0;
		double sumChepter330Ph = 0;
		double sumChepter340Ph = 0;
		double sumChepter339Ph = 0;
		double sumChepter399Ph = 0;


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



			CalculatePrevMonth(startDate.toStdString(), endDate.toStdString(), prevFromMonth, prevTillMonth);
			//aHistory->SetFromDate(fromDateEdit->text().toUtf8().constData());
			aHistory->SetTillDate(endDate.toStdString());
			std::string filter = "";
			filter = aHistory->GenerateFilter(dialogBL->GetOrmasDal());
			std::vector<BusinessLayer::AccountHistory> vecCmpBlc;
			vecCmpBlc = dialogBL->GetAllDataForClass<BusinessLayer::AccountHistory>(errorMessage, filter);
			if (vecCmpBlc.size() == 0)
			{
				QMessageBox::information(NULL, QString(tr("Info")),
					QString(tr("Cannot find report for this period!")),
					QString(tr("Ok")));
			}
			else
			{
				monthHlder += "<th><b>" + endDate + "</b></th>";
				//generating report
				if (vecCmpBlc.size() > 1)
				{
					double sChepter33Ph = 0;
					double sChepter53Ph = 0;
					double sChepter54Ph = 0;
					double sChepter71Ph = 0;
					double sChepter99Ph = 0;
					double sChepter199Ph = 0;
					double sChepter100Ph = 0;
					double sChepter110Ph = 0;
					double sChepter130Ph = 0;
					double sChepter121Ph = 0;
					double sChepter131Ph = 0;
					double sChepter133Ph = 0;
					double sChepter259Ph = 0;
					double sChepter203Ph = 0;
					double sChepter222Ph = 0;
					double sChepter224Ph = 0;
					double sChepter234Ph = 0;
					double sChepter298Ph = 0;
					double sChepter261Ph = 0;
					double sChepter262Ph = 0;
					double sChepter264Ph = 0;
					double sChepter313Ph = 0;
					double sChepter315Ph = 0;
					double sChepter339Ph = 0;

					chepter00Ph += "<td></td>";
					for each (auto item in vecCmpBlc)
					{



						//Оборотные активы
						if (0 == item.GetNumber().compare("10100"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter10Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter10Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10200"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter20Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter20Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10300"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter30Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter30Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10310"))
						{
							chepter31Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter31Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10320"))
						{
							chepter32Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter32Ph += item.GetCurrentBalance();
						}

						if (0 == item.GetNumber().compare("10330") || 0 == item.GetNumber().compare("10340"))
						{
							sChepter33Ph += item.GetCurrentBalance();
							sumChepter33Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10350"))
						{
							chepter34Ph += "<td> " + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter34Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10360"))
						{
							chepter35Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter35Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10400"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter40Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter40Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10410"))
						{
							sumChepter41Ph += item.GetCurrentBalance();
							chepter41Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10420"))
						{
							sumChepter42Ph += item.GetCurrentBalance();
							chepter42Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10430"))
						{
							sumChepter43Ph += item.GetCurrentBalance();
							chepter43Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10500"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter50Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter50Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10510"))
						{
							sumChepter51Ph += item.GetCurrentBalance();
							chepter51Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10520"))
						{
							sumChepter52Ph += item.GetCurrentBalance();
							chepter52Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10530") || 0 == item.GetNumber().compare("10540"))
						{
							sChepter53Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10550") || 0 == item.GetNumber().compare("10560"))
						{
							sChepter54Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10570"))
						{
							chepter55Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter55Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10580"))
						{
							chepter56Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter56Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10590"))
						{
							sumChepter59Ph += item.GetCurrentBalance();
							chepter59Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10600"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter60Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter60Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10700"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter70Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter70Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10710") || 0 == item.GetNumber().compare("10711") || 0 == item.GetNumber().compare("10712") ||
							0 == item.GetNumber().compare("10713") || 0 == item.GetNumber().compare("10714") || 0 == item.GetNumber().compare("10715") ||
							0 == item.GetNumber().compare("10716") || 0 == item.GetNumber().compare("10717") || 0 == item.GetNumber().compare("10718") ||
							0 == item.GetNumber().compare("10719"))
						{
							sChepter71Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10720"))
						{
							sumChepter72Ph += item.GetCurrentBalance();
							chepter72Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10730"))
						{
							sumChepter73Ph += item.GetCurrentBalance();
							chepter73Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10740"))
						{
							sumChepter74Ph += item.GetCurrentBalance();
							chepter74Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10742"))
						{
							sumChepter74Ph += item.GetCurrentBalance();
							chepter742Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10750"))
						{
							sumChepter75Ph += item.GetCurrentBalance();
							chepter75Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10760"))
						{
							sumChepter76Ph += item.GetCurrentBalance();
							chepter76Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10770"))
						{
							sumChepter77Ph += item.GetCurrentBalance();
							chepter77Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10780"))
						{
							sumChepter78Ph += item.GetCurrentBalance();
							chepter78Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10790"))
						{
							sumChepter79Ph += item.GetCurrentBalance();
							chepter79Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10800"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter80Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter80Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10810"))
						{
							sumChepter81Ph += item.GetCurrentBalance();
							chepter81Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10820"))
						{
							sumChepter82Ph += item.GetCurrentBalance();
							chepter82Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10830"))
						{
							sumChepter83Ph += item.GetCurrentBalance();
							chepter83Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10900"))
						{
							sChepter99Ph += item.GetCurrentBalance();
							chepter90Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter90Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("10910"))
						{
							sumChepter91Ph += item.GetCurrentBalance();
							chepter91Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10920"))
						{
							sumChepter92Ph += item.GetCurrentBalance();
							chepter92Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("10930"))
						{
							sumChepter93Ph += item.GetCurrentBalance();
							chepter93Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}



						//Внеоборотные активы

						if (0 == item.GetNumber().compare("11000"))
						{
							sChepter100Ph = item.GetCurrentBalance();
							sChepter199Ph += item.GetCurrentBalance();
							chepter100Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter100Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11010"))
						{
							sumChepter101Ph += item.GetCurrentBalance();
							chepter101Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11020"))
						{
							sumChepter102Ph += item.GetCurrentBalance();
							chepter102Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11030"))
						{
							sumChepter103Ph += item.GetCurrentBalance();
							chepter103Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11040"))
						{
							sumChepter104Ph += item.GetCurrentBalance();
							chepter104Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11050"))
						{
							sumChepter105Ph += item.GetCurrentBalance();
							chepter105Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11060"))
						{
							sumChepter106Ph += item.GetCurrentBalance();
							chepter106Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11070"))
						{
							sumChepter107Ph += item.GetCurrentBalance();
							chepter107Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11080"))
						{
							sumChepter108Ph += item.GetCurrentBalance();
							chepter108Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11090"))
						{
							sumChepter109Ph += item.GetCurrentBalance();
							chepter109Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11100"))
						{
							sChepter110Ph = item.GetCurrentBalance();
							chepter110Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter110Ph += item.GetCurrentBalance();
						}

						if (0 == item.GetNumber().compare("11200"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter120Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter120Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11210") || 0 == item.GetNumber().compare("11220"))
						{
							sChepter121Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11290"))
						{
							sumChepter122Ph += item.GetCurrentBalance();
							chepter122Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11300"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter130Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter130Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11310") || 0 == item.GetNumber().compare("11320") || 0 == item.GetNumber().compare("11330")
							|| 0 == item.GetNumber().compare("11340") || 0 == item.GetNumber().compare("11350") || 0 == item.GetNumber().compare("11360"))
						{
							sChepter131Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11370"))
						{
							sumChepter132Ph += item.GetCurrentBalance();
							chepter132Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11390"))
						{
							sumChepter133Ph += item.GetCurrentBalance();
							chepter133Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11400"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter140Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter140Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11410"))
						{
							sumChepter141Ph += item.GetCurrentBalance();
							chepter141Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11420"))
						{
							sumChepter142Ph += item.GetCurrentBalance();
							chepter142Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11430"))
						{
							sumChepter143Ph += item.GetCurrentBalance();
							chepter143Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11440"))
						{
							sumChepter144Ph += item.GetCurrentBalance();
							chepter144Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11450"))
						{
							sumChepter145Ph += item.GetCurrentBalance();
							chepter145Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11460"))
						{
							sumChepter146Ph += item.GetCurrentBalance();
							chepter146Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11500"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter150Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter150Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11510"))
						{
							sumChepter151Ph += item.GetCurrentBalance();
							chepter151Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11520"))
						{
							sumChepter152Ph += item.GetCurrentBalance();
							chepter152Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11600"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter160Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter160Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11610"))
						{
							sumChepter161Ph += item.GetCurrentBalance();
							chepter161Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11620"))
						{
							sumChepter162Ph += item.GetCurrentBalance();
							chepter162Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11630"))
						{
							sumChepter163Ph += item.GetCurrentBalance();
							chepter163Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11640"))
						{
							sumChepter164Ph += item.GetCurrentBalance();
							chepter164Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11650"))
						{
							sumChepter165Ph += item.GetCurrentBalance();
							chepter165Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11660"))
						{
							sumChepter166Ph += item.GetCurrentBalance();
							chepter166Ph += "<td>" + QString::number(item.GetCurrentBalance()) + "</td>";
						}
						if (0 == item.GetNumber().compare("11700"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter170Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter170Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11800"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter180Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter180Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("11810"))
						{
							sumChepter181Ph += item.GetCurrentBalance();
							chepter181Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11820"))
						{
							sumChepter182Ph += item.GetCurrentBalance();
							chepter182Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11830"))
						{
							sumChepter183Ph += item.GetCurrentBalance();
							chepter183Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11840"))
						{
							sumChepter184Ph += item.GetCurrentBalance();
							chepter184Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("11900"))
						{
							sChepter199Ph += item.GetCurrentBalance();
							chepter190Ph += "<td>" + QString::number(item.GetCurrentBalance(), 'f', 3) + "</td>";
							sumChepter190Ph += item.GetCurrentBalance();
						}


						//Краткосрочные обязательства
						if (0 == item.GetNumber().compare("22000"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter200Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter200Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22010"))
						{
							sumChepter201Ph += item.GetCurrentBalance()*(-1);
							chepter201Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22020"))
						{
							sumChepter202Ph += item.GetCurrentBalance()*(-1);
							chepter202Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22030") || 0 == item.GetNumber().compare("22040"))
						{
							sChepter203Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22100"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter210Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter210Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22110"))
						{
							sumChepter211Ph += item.GetCurrentBalance()*(-1);
							chepter211Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22120"))
						{
							sumChepter212Ph += item.GetCurrentBalance()*(-1);
							chepter212Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22130"))
						{
							sumChepter213Ph += item.GetCurrentBalance()*(-1);
							chepter213Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22140"))
						{
							sumChepter214Ph += item.GetCurrentBalance()*(-1);
							chepter214Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22200"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter220Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter220Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22210"))
						{
							sumChepter221Ph += item.GetCurrentBalance()*(-1);
							chepter221Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22220") || 0 == item.GetNumber().compare("22230"))
						{
							sChepter222Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22240"))
						{
							sumChepter223Ph += item.GetCurrentBalance()*(-1);
							chepter223Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22250") || 0 == item.GetNumber().compare("22260"))
						{
							sChepter224Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22270"))
						{
							sumChepter225Ph += item.GetCurrentBalance()*(-1);
							chepter225Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22300"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter230Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter230Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22310"))
						{
							sumChepter231Ph += item.GetCurrentBalance()*(-1);
							chepter231Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22320"))
						{
							sumChepter232Ph += item.GetCurrentBalance()*(-1);
							chepter232Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22330"))
						{
							sumChepter233Ph += item.GetCurrentBalance()*(-1);
							chepter233Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22340") || 0 == item.GetNumber().compare("22350")
							|| 0 == item.GetNumber().compare("22360") || 0 == item.GetNumber().compare("22370"))
						{
							sChepter234Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22400"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter240Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter240Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22500"))
						{
							sChepter259Ph += item.GetCurrentBalance();
							chepter250Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter250Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22510"))
						{
							sumChepter251Ph += item.GetCurrentBalance()*(-1);
							chepter251Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22520"))
						{
							sumChepter252Ph += item.GetCurrentBalance()*(-1);
							chepter252Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22530"))
						{
							sumChepter253Ph += item.GetCurrentBalance()*(-1);
							chepter253Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}


						//Долгосрочные обязательства
						if (0 == item.GetNumber().compare("22600"))
						{
							sChepter298Ph += item.GetCurrentBalance();
							chepter260Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter260Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22610") || 0 == item.GetNumber().compare("22640"))
						{
							sChepter261Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22620") || 0 == item.GetNumber().compare("22630"))
						{
							sChepter262Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22650"))
						{
							sumChepter263Ph += item.GetCurrentBalance()*(-1);
							chepter263Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("22660") || 0 == item.GetNumber().compare("22670"))
						{
							sChepter264Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("22700"))
						{
							sChepter298Ph += item.GetCurrentBalance();
							chepter270Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter270Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("22800"))
						{
							sChepter298Ph += item.GetCurrentBalance();
							chepter280Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter280Ph += item.GetCurrentBalance()*(-1);
						}


						//Собственный капитал
						if (0 == item.GetNumber().compare("33000"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter300Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter300Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33010"))
						{
							sumChepter301Ph += item.GetCurrentBalance()*(-1);
							chepter301Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33020"))
						{
							sumChepter302Ph += item.GetCurrentBalance()*(-1);
							chepter302Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33030"))
						{
							sumChepter303Ph += item.GetCurrentBalance()*(-1);
							chepter303Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33090"))
						{
							sumChepter304Ph += item.GetCurrentBalance()*(-1);
							chepter304Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33100"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter310Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter310Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33110"))
						{
							sumChepter311Ph += item.GetCurrentBalance()*(-1);
							chepter311Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33120") || 0 == item.GetNumber().compare("33130"))
						{
							sChepter313Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("33140"))
						{
							sumChepter314Ph += item.GetCurrentBalance()*(-1);
							chepter314Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
						}
						if (0 == item.GetNumber().compare("33150") || 0 == item.GetNumber().compare("33160"))
						{
							sChepter315Ph += item.GetCurrentBalance();
						}
						if (0 == item.GetNumber().compare("33200"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter320Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter320Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33300"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter330Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter330Ph += item.GetCurrentBalance()*(-1);
						}
						if (0 == item.GetNumber().compare("33400"))
						{
							sChepter339Ph += item.GetCurrentBalance();
							chepter340Ph += "<td>" + QString::number(item.GetCurrentBalance()*(-1), 'f', 3) + "</td>";
							sumChepter340Ph += item.GetCurrentBalance()*(-1);
						}

					}

					chepter33Ph += "<td>" + QString::number(sChepter33Ph, 'f', 3) + "</td>";
					sumChepter33Ph += sChepter33Ph;
					chepter53Ph += "<td>" + QString::number(sChepter53Ph, 'f', 3) + "</td>";
					sumChepter33Ph += sChepter53Ph;
					chepter54Ph += "<td>" + QString::number(sChepter54Ph, 'f', 3) + "</td>";
					sumChepter54Ph += sChepter54Ph;
					chepter71Ph += "<td>" + QString::number(sChepter71Ph, 'f', 3) + "</td>";
					sumChepter71Ph += sChepter71Ph;
					chepter121Ph += "<td>" + QString::number(sChepter121Ph, 'f', 3) + "</td>";
					sumChepter121Ph += sChepter121Ph;
					chepter131Ph += "<td>" + QString::number(sChepter131Ph, 'f', 3) + "</td>";
					sumChepter131Ph += sChepter131Ph;
					chepter203Ph += "<td>" + QString::number(sChepter203Ph*(-1), 'f', 3) + "</td>";
					sumChepter203Ph += sChepter203Ph*(-1);
					chepter222Ph += "<td>" + QString::number(sChepter222Ph*(-1), 'f', 3) + "</td>";
					sumChepter222Ph += sChepter222Ph*(-1);
					chepter224Ph += "<td>" + QString::number(sChepter224Ph*(-1), 'f', 3) + "</td>";
					sumChepter224Ph += sChepter224Ph*(-1);
					chepter234Ph += "<td>" + QString::number(sChepter234Ph*(-1), 'f', 3) + "</td>";
					sumChepter234Ph += sChepter234Ph*(-1);
					chepter261Ph += "<td>" + QString::number(sChepter261Ph*(-1), 'f', 3) + "</td>";
					sumChepter261Ph += sChepter261Ph*(-1);
					chepter262Ph += "<td>" + QString::number(sChepter262Ph*(-1), 'f', 3) + "</td>";
					sumChepter262Ph += sChepter262Ph*(-1);
					chepter264Ph += "<td>" + QString::number(sChepter264Ph*(-1), 'f', 3) + "</td>";
					sumChepter264Ph += sChepter264Ph*(-1);
					chepter313Ph += "<td>" + QString::number(sChepter313Ph*(-1), 'f', 3) + "</td>";
					sumChepter313Ph += sChepter313Ph*(-1);
					chepter315Ph += "<td>" + QString::number(sChepter315Ph*(-1), 'f', 3) + "</td>";
					sumChepter315Ph += sChepter315Ph*(-1);
					//итоги
					chepter99Ph += "<td>" + QString::number(sChepter99Ph, 'f', 3) + "</td>";
					sumChepter99Ph += sChepter99Ph;
					chepter119Ph += "<td>" + QString::number(sChepter100Ph + sChepter110Ph, 'f', 3) + "</td>";
					sumChepter119Ph += sChepter100Ph + sChepter110Ph;
					chepter199Ph += "<td>" + QString::number(sChepter199Ph + sChepter110Ph, 'f', 3) + "</td>";
					sumChepter199Ph += sChepter199Ph + sChepter110Ph;
					chepter1000Ph += "<td>" + QString::number(sChepter99Ph + sChepter199Ph + sChepter110Ph, 'f', 3) + "</td>";
					sumChepter1000Ph += sChepter99Ph + sChepter199Ph + sChepter110Ph;
					chepter259Ph += "<td>" + QString::number(sChepter259Ph*(-1), 'f', 3) + "</td>";
					sumChepter259Ph += sChepter259Ph*(-1);
					chepter298Ph += "<td>" + QString::number(sChepter298Ph*(-1), 'f', 3) + "</td>";
					sumChepter298Ph += sChepter298Ph*(-1);
					chepter299Ph += "<td>" + QString::number((sChepter259Ph + sChepter298Ph)*(-1), 'f', 3) + "</td>";
					sumChepter299Ph += (sChepter259Ph + sChepter298Ph)*(-1);
					chepter339Ph += "<td>" + QString::number(sChepter339Ph*(-1), 'f', 3) + "</td>";
					sumChepter339Ph += sChepter339Ph*(-1);
					chepter399Ph += "<td>" + QString::number((sChepter339Ph + sChepter259Ph + sChepter298Ph)*(-1), 'f', 3) + "</td>";
					sumChepter399Ph += (sChepter339Ph + sChepter259Ph + sChepter298Ph)*(-1);

				}


			}
		}

		/*monthHlder += "<th><b>" + QString::fromWCharArray(L"Итого") + "</b></th>";
		chepter10Ph += "<td>" + QString::number(sumChepter10Ph, 'f', 3) + "</td>";
		chepter20Ph += "<td>" + QString::number(sumChepter20Ph, 'f', 3) + "</td>";
		chepter30Ph += "<td>" + QString::number(sumChepter30Ph, 'f', 3) + "</td>";
		chepter31Ph += "<td>" + QString::number(sumChepter31Ph, 'f', 3) + "</td>";
		chepter32Ph += "<td>" + QString::number(sumChepter32Ph, 'f', 3) + "</td>";
		chepter33Ph += "<td>" + QString::number(sumChepter33Ph, 'f', 3) + "</td>";
		chepter34Ph += "<td>" + QString::number(sumChepter34Ph, 'f', 3) + "</td>";
		chepter35Ph += "<td>" + QString::number(sumChepter35Ph, 'f', 3) + "</td>";
		chepter40Ph += "<td>" + QString::number(sumChepter40Ph, 'f', 3) + "</td>";
		chepter41Ph += "<td>" + QString::number(sumChepter41Ph, 'f', 3) + "</td>";
		chepter42Ph += "<td>" + QString::number(sumChepter42Ph, 'f', 3) + "</td>";
		chepter43Ph += "<td>" + QString::number(sumChepter43Ph, 'f', 3) + "</td>";
		chepter50Ph += "<td>" + QString::number(sumChepter50Ph, 'f', 3) + "</td>";
		chepter51Ph += "<td>" + QString::number(sumChepter51Ph, 'f', 3) + "</td>";
		chepter52Ph += "<td>" + QString::number(sumChepter52Ph, 'f', 3) + "</td>";
		chepter53Ph += "<td>" + QString::number(sumChepter53Ph, 'f', 3) + "</td>";
		chepter54Ph += "<td>" + QString::number(sumChepter54Ph, 'f', 3) + "</td>";
		chepter55Ph += "<td>" + QString::number(sumChepter55Ph, 'f', 3) + "</td>";
		chepter56Ph += "<td>" + QString::number(sumChepter56Ph, 'f', 3) + "</td>";
		chepter59Ph += "<td>" + QString::number(sumChepter59Ph, 'f', 3) + "</td>";
		chepter60Ph += "<td>" + QString::number(sumChepter60Ph, 'f', 3) + "</td>";
		chepter70Ph += "<td>" + QString::number(sumChepter70Ph, 'f', 3) + "</td>";
		chepter71Ph += "<td>" + QString::number(sumChepter71Ph, 'f', 3) + "</td>";
		chepter72Ph += "<td>" + QString::number(sumChepter72Ph, 'f', 3) + "</td>";
		chepter73Ph += "<td>" + QString::number(sumChepter73Ph, 'f', 3) + "</td>";
		chepter74Ph += "<td>" + QString::number(sumChepter74Ph, 'f', 3) + "</td>";
		chepter742Ph += "<td>" + QString::number(sumChepter742Ph, 'f', 3) + "</td>";
		chepter75Ph += "<td>" + QString::number(sumChepter75Ph, 'f', 3) + "</td>";
		chepter76Ph += "<td>" + QString::number(sumChepter76Ph, 'f', 3) + "</td>";
		chepter77Ph += "<td>" + QString::number(sumChepter77Ph, 'f', 3) + "</td>";
		chepter78Ph += "<td>" + QString::number(sumChepter78Ph, 'f', 3) + "</td>";
		chepter79Ph += "<td>" + QString::number(sumChepter79Ph, 'f', 3) + "</td>";
		chepter80Ph += "<td>" + QString::number(sumChepter80Ph, 'f', 3) + "</td>";
		chepter81Ph += "<td>" + QString::number(sumChepter81Ph, 'f', 3) + "</td>";
		chepter82Ph += "<td>" + QString::number(sumChepter82Ph, 'f', 3) + "</td>";
		chepter83Ph += "<td>" + QString::number(sumChepter83Ph, 'f', 3) + "</td>";
		chepter90Ph += "<td>" + QString::number(sumChepter90Ph, 'f', 3) + "</td>";
		chepter91Ph += "<td>" + QString::number(sumChepter91Ph, 'f', 3) + "</td>";
		chepter92Ph += "<td>" + QString::number(sumChepter92Ph, 'f', 3) + "</td>";
		chepter93Ph += "<td>" + QString::number(sumChepter93Ph, 'f', 3) + "</td>";
		chepter99Ph += "<td>" + QString::number(sumChepter99Ph, 'f', 3) + "</td>";
		chepter100Ph += "<td>" + QString::number(sumChepter100Ph, 'f', 3) + "</td>";
		chepter101Ph += "<td>" + QString::number(sumChepter101Ph, 'f', 3) + "</td>";
		chepter102Ph += "<td>" + QString::number(sumChepter102Ph, 'f', 3) + "</td>";
		chepter103Ph += "<td>" + QString::number(sumChepter103Ph, 'f', 3) + "</td>";
		chepter104Ph += "<td>" + QString::number(sumChepter104Ph, 'f', 3) + "</td>";
		chepter105Ph += "<td>" + QString::number(sumChepter105Ph, 'f', 3) + "</td>";
		chepter106Ph += "<td>" + QString::number(sumChepter106Ph, 'f', 3) + "</td>";
		chepter107Ph += "<td>" + QString::number(sumChepter107Ph, 'f', 3) + "</td>";
		chepter108Ph += "<td>" + QString::number(sumChepter108Ph, 'f', 3) + "</td>";
		chepter109Ph += "<td>" + QString::number(sumChepter109Ph, 'f', 3) + "</td>";
		chepter110Ph += "<td>" + QString::number(sumChepter110Ph, 'f', 3) + "</td>";
		chepter119Ph += "<td>" + QString::number(sumChepter119Ph, 'f', 3) + "</td>";
		chepter120Ph += "<td>" + QString::number(sumChepter120Ph, 'f', 3) + "</td>";
		chepter121Ph += "<td>" + QString::number(sumChepter121Ph, 'f', 3) + "</td>";
		chepter122Ph += "<td>" + QString::number(sumChepter122Ph, 'f', 3) + "</td>";
		chepter130Ph += "<td>" + QString::number(sumChepter130Ph, 'f', 3) + "</td>";
		chepter131Ph += "<td>" + QString::number(sumChepter131Ph, 'f', 3) + "</td>";
		chepter132Ph += "<td>" + QString::number(sumChepter132Ph, 'f', 3) + "</td>";
		chepter133Ph += "<td>" + QString::number(sumChepter133Ph, 'f', 3) + "</td>";
		chepter140Ph += "<td>" + QString::number(sumChepter140Ph, 'f', 3) + "</td>";
		chepter141Ph += "<td>" + QString::number(sumChepter141Ph, 'f', 3) + "</td>";
		chepter142Ph += "<td>" + QString::number(sumChepter142Ph, 'f', 3) + "</td>";
		chepter143Ph += "<td>" + QString::number(sumChepter143Ph, 'f', 3) + "</td>";
		chepter144Ph += "<td>" + QString::number(sumChepter144Ph, 'f', 3) + "</td>";
		chepter145Ph += "<td>" + QString::number(sumChepter145Ph, 'f', 3) + "</td>";
		chepter146Ph += "<td>" + QString::number(sumChepter146Ph, 'f', 3) + "</td>";
		chepter150Ph += "<td>" + QString::number(sumChepter150Ph, 'f', 3) + "</td>";
		chepter151Ph += "<td>" + QString::number(sumChepter151Ph, 'f', 3) + "</td>";
		chepter152Ph += "<td>" + QString::number(sumChepter152Ph, 'f', 3) + "</td>";
		chepter160Ph += "<td>" + QString::number(sumChepter160Ph, 'f', 3) + "</td>";
		chepter161Ph += "<td>" + QString::number(sumChepter161Ph, 'f', 3) + "</td>";
		chepter162Ph += "<td>" + QString::number(sumChepter162Ph, 'f', 3) + "</td>";
		chepter163Ph += "<td>" + QString::number(sumChepter163Ph, 'f', 3) + "</td>";
		chepter164Ph += "<td>" + QString::number(sumChepter164Ph, 'f', 3) + "</td>";
		chepter165Ph += "<td>" + QString::number(sumChepter165Ph, 'f', 3) + "</td>";
		chepter166Ph += "<td>" + QString::number(sumChepter166Ph, 'f', 3) + "</td>";
		chepter170Ph += "<td>" + QString::number(sumChepter170Ph, 'f', 3) + "</td>";
		chepter180Ph += "<td>" + QString::number(sumChepter180Ph, 'f', 3) + "</td>";
		chepter181Ph += "<td>" + QString::number(sumChepter181Ph, 'f', 3) + "</td>";
		chepter182Ph += "<td>" + QString::number(sumChepter182Ph, 'f', 3) + "</td>";
		chepter183Ph += "<td>" + QString::number(sumChepter183Ph, 'f', 3) + "</td>";
		chepter184Ph += "<td>" + QString::number(sumChepter184Ph, 'f', 3) + "</td>";
		chepter190Ph += "<td>" + QString::number(sumChepter190Ph, 'f', 3) + "</td>";
		chepter199Ph += "<td>" + QString::number(sumChepter199Ph, 'f', 3) + "</td>";
		chepter1000Ph += "<td>" + QString::number(sumChepter1000Ph, 'f', 3) + "</td>";
		chepter200Ph += "<td>" + QString::number(sumChepter200Ph, 'f', 3) + "</td>";
		chepter201Ph += "<td>" + QString::number(sumChepter201Ph, 'f', 3) + "</td>";
		chepter202Ph += "<td>" + QString::number(sumChepter202Ph, 'f', 3) + "</td>";
		chepter203Ph += "<td>" + QString::number(sumChepter203Ph, 'f', 3) + "</td>";
		chepter210Ph += "<td>" + QString::number(sumChepter210Ph, 'f', 3) + "</td>";
		chepter211Ph += "<td>" + QString::number(sumChepter211Ph, 'f', 3) + "</td>";
		chepter212Ph += "<td>" + QString::number(sumChepter212Ph, 'f', 3) + "</td>";
		chepter213Ph += "<td>" + QString::number(sumChepter213Ph, 'f', 3) + "</td>";
		chepter214Ph += "<td>" + QString::number(sumChepter214Ph, 'f', 3) + "</td>";
		chepter220Ph += "<td>" + QString::number(sumChepter220Ph, 'f', 3) + "</td>";
		chepter221Ph += "<td>" + QString::number(sumChepter221Ph, 'f', 3) + "</td>";
		chepter222Ph += "<td>" + QString::number(sumChepter222Ph, 'f', 3) + "</td>";
		chepter223Ph += "<td>" + QString::number(sumChepter223Ph, 'f', 3) + "</td>";
		chepter224Ph += "<td>" + QString::number(sumChepter224Ph, 'f', 3) + "</td>";
		chepter225Ph += "<td>" + QString::number(sumChepter225Ph, 'f', 3) + "</td>";
		chepter230Ph += "<td>" + QString::number(sumChepter230Ph, 'f', 3) + "</td>";
		chepter231Ph += "<td>" + QString::number(sumChepter231Ph, 'f', 3) + "</td>";
		chepter232Ph += "<td>" + QString::number(sumChepter232Ph, 'f', 3) + "</td>";
		chepter233Ph += "<td>" + QString::number(sumChepter233Ph, 'f', 3) + "</td>";
		chepter234Ph += "<td>" + QString::number(sumChepter234Ph, 'f', 3) + "</td>";
		chepter240Ph += "<td>" + QString::number(sumChepter240Ph, 'f', 3) + "</td>";
		chepter250Ph += "<td>" + QString::number(sumChepter250Ph, 'f', 3) + "</td>";
		chepter251Ph += "<td>" + QString::number(sumChepter251Ph, 'f', 3) + "</td>";
		chepter252Ph += "<td>" + QString::number(sumChepter252Ph, 'f', 3) + "</td>";
		chepter253Ph += "<td>" + QString::number(sumChepter253Ph, 'f', 3) + "</td>";
		chepter259Ph += "<td>" + QString::number(sumChepter259Ph, 'f', 3) + "</td>";
		chepter260Ph += "<td>" + QString::number(sumChepter260Ph, 'f', 3) + "</td>";
		chepter261Ph += "<td>" + QString::number(sumChepter261Ph, 'f', 3) + "</td>";
		chepter262Ph += "<td>" + QString::number(sumChepter262Ph, 'f', 3) + "</td>";
		chepter263Ph += "<td>" + QString::number(sumChepter263Ph, 'f', 3) + "</td>";
		chepter264Ph += "<td>" + QString::number(sumChepter264Ph, 'f', 3) + "</td>";
		chepter270Ph += "<td>" + QString::number(sumChepter270Ph, 'f', 3) + "</td>";
		chepter280Ph += "<td>" + QString::number(sumChepter280Ph, 'f', 3) + "</td>";
		chepter290Ph += "<td>" + QString::number(sumChepter290Ph, 'f', 3) + "</td>";
		chepter298Ph += "<td>" + QString::number(sumChepter298Ph, 'f', 3) + "</td>";
		chepter299Ph += "<td>" + QString::number(sumChepter299Ph, 'f', 3) + "</td>";
		chepter300Ph += "<td>" + QString::number(sumChepter300Ph, 'f', 3) + "</td>";
		chepter301Ph += "<td>" + QString::number(sumChepter301Ph, 'f', 3) + "</td>";
		chepter302Ph += "<td>" + QString::number(sumChepter302Ph, 'f', 3) + "</td>";
		chepter303Ph += "<td>" + QString::number(sumChepter303Ph, 'f', 3) + "</td>";
		chepter304Ph += "<td>" + QString::number(sumChepter304Ph, 'f', 3) + "</td>";
		chepter310Ph += "<td>" + QString::number(sumChepter310Ph, 'f', 3) + "</td>";
		chepter311Ph += "<td>" + QString::number(sumChepter311Ph, 'f', 3) + "</td>";
		chepter313Ph += "<td>" + QString::number(sumChepter313Ph, 'f', 3) + "</td>";
		chepter314Ph += "<td>" + QString::number(sumChepter314Ph, 'f', 3) + "</td>";
		chepter315Ph += "<td>" + QString::number(sumChepter315Ph, 'f', 3) + "</td>";
		chepter320Ph += "<td>" + QString::number(sumChepter320Ph, 'f', 3) + "</td>";
		chepter330Ph += "<td>" + QString::number(sumChepter330Ph, 'f', 3) + "</td>";
		chepter340Ph += "<td>" + QString::number(sumChepter340Ph, 'f', 3) + "</td>";
		chepter339Ph += "<td>" + QString::number(sumChepter339Ph, 'f', 3) + "</td>";
		chepter399Ph += "<td>" + QString::number(sumChepter399Ph, 'f', 3) + "</td>";*/


		reportText.replace(QString("tillDatePh"), endDate, Qt::CaseInsensitive);
		reportText.replace(QString("MonthPH"), monthHlder, Qt::CaseInsensitive);
		reportText.replace(QString("chepter00Ph"), chepter00Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter10Ph"), chepter10Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter20Ph"), chepter20Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter30Ph"), chepter30Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter31Ph"), chepter31Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter32Ph"), chepter32Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter33Ph"), chepter33Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter34Ph"), chepter34Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter35Ph"), chepter35Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter40Ph"), chepter40Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter41Ph"), chepter41Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter42Ph"), chepter42Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter43Ph"), chepter43Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter50Ph"), chepter50Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter51Ph"), chepter51Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter52Ph"), chepter52Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter53Ph"), chepter53Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter54Ph"), chepter54Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter55Ph"), chepter55Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter56Ph"), chepter56Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter59Ph"), chepter59Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter60Ph"), chepter60Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter70Ph"), chepter70Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter71Ph"), chepter71Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter72Ph"), chepter72Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter73Ph"), chepter73Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter74Ph"), chepter74Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter742Ph"), chepter742Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter75Ph"), chepter75Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter76Ph"), chepter76Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter77Ph"), chepter77Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter78Ph"), chepter78Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter79Ph"), chepter79Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter80Ph"), chepter80Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter81Ph"), chepter81Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter82Ph"), chepter82Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter83Ph"), chepter83Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter90Ph"), chepter90Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter91Ph"), chepter91Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter92Ph"), chepter92Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter93Ph"), chepter93Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter99Ph"), chepter93Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter100Ph"), chepter100Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter101Ph"), chepter101Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter102Ph"), chepter102Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter103Ph"), chepter103Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter104Ph"), chepter104Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter105Ph"), chepter105Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter106Ph"), chepter106Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter107Ph"), chepter107Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter108Ph"), chepter108Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter109Ph"), chepter109Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter110Ph"), chepter110Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter119Ph"), chepter119Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter120Ph"), chepter120Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter121Ph"), chepter121Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter122Ph"), chepter122Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter130Ph"), chepter130Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter131Ph"), chepter131Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter132Ph"), chepter132Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter133Ph"), chepter133Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter140Ph"), chepter140Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter141Ph"), chepter141Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter142Ph"), chepter142Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter143Ph"), chepter143Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter144Ph"), chepter144Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter145Ph"), chepter145Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter146Ph"), chepter146Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter150Ph"), chepter150Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter151Ph"), chepter151Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter152Ph"), chepter152Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter160Ph"), chepter160Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter161Ph"), chepter161Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter162Ph"), chepter162Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter163Ph"), chepter163Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter164Ph"), chepter164Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter165Ph"), chepter165Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter166Ph"), chepter166Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter170Ph"), chepter170Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter180Ph"), chepter180Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter181Ph"), chepter181Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter182Ph"), chepter182Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter183Ph"), chepter183Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter184Ph"), chepter184Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter190Ph"), chepter190Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter199Ph"), chepter199Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter1000Ph"), chepter1000Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter200Ph"), chepter200Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter201Ph"), chepter201Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter202Ph"), chepter202Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter203Ph"), chepter203Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter210Ph"), chepter210Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter211Ph"), chepter211Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter212Ph"), chepter212Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter213Ph"), chepter213Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter214Ph"), chepter214Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter220Ph"), chepter220Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter221Ph"), chepter221Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter222Ph"), chepter222Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter223Ph"), chepter223Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter224Ph"), chepter224Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter225Ph"), chepter225Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter230Ph"), chepter230Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter231Ph"), chepter231Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter232Ph"), chepter232Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter233Ph"), chepter233Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter234Ph"), chepter234Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter240Ph"), chepter240Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter250Ph"), chepter250Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter251Ph"), chepter251Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter252Ph"), chepter252Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter253Ph"), chepter253Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter259Ph"), chepter259Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter260Ph"), chepter260Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter261Ph"), chepter261Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter262Ph"), chepter262Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter263Ph"), chepter263Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter264Ph"), chepter264Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter270Ph"), chepter270Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter280Ph"), chepter280Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter290Ph"), chepter290Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter298Ph"), chepter298Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter299Ph"), chepter299Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter300Ph"), chepter300Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter301Ph"), chepter301Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter302Ph"), chepter302Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter303Ph"), chepter303Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter304Ph"), chepter304Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter310Ph"), chepter310Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter311Ph"), chepter311Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter313Ph"), chepter313Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter314Ph"), chepter314Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter315Ph"), chepter315Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter320Ph"), chepter320Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter330Ph"), chepter330Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter340Ph"), chepter340Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter339Ph"), chepter339Ph, Qt::CaseInsensitive);
		reportText.replace(QString("chepter399Ph"), chepter399Ph, Qt::CaseInsensitive);

		docForm->webEngineView->setHtml(reportText);
		docForm->SetContent(reportText);
		docForm->webEngineView->show();
		docForm->show();
		Close();

	}
}

void GenerateCmpBlc::Close()
{
	this->parentWidget()->close();
}
void GenerateCmpBlc::ChangeRadio()
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


void GenerateCmpBlc::CalculatePrevMonth(std::string fromMonth, std::string tilMonth, std::string& prevFromMonth, std::string& tillFromMonth)
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
			prevFromMonth += std::to_string(month-1);
		}
		else
		{
			prevFromMonth += std::to_string(month-1);
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

int GenerateCmpBlc::CalculateMonthCount(std::string fromMonth, std::string tilMonth)
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
