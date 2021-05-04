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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateCmpBlc::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateCmpBlc::Close);
}

GenerateCmpBlc::~GenerateCmpBlc()
{
	delete aHistory;
}

void GenerateCmpBlc::Generate()
{
	CalculatePrevMonth(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), prevFromMonth, prevTillMonth);
	//aHistory->SetFromDate(fromDateEdit->text().toUtf8().constData());
	aHistory->SetTillDate(tillDateEdit->text().toUtf8().constData());
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
				reportText.replace(QString("tillDatePh"), tillDateEdit->text(), Qt::CaseInsensitive);
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

void GenerateCmpBlc::Close()
{
	this->parentWidget()->close();
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
