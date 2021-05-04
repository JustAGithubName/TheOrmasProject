#include "stdafx.h"

#include "CloseOfMonthDlg.h"
#include "DataForm.h"

#include <map>


CloseOfMonthDlg::CloseOfMonthDlg(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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
	}
	if (day < 15 && month > 1)
	{
		startDate = "01.";
		startDate += std::to_string(month-1);
		startDate += ".";
		startDate += std::to_string(year);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDays);
		endDate += ".";
		endDate += std::to_string(month-1);
		endDate += ".";
		endDate += std::to_string(year);
	}
	fromDateEdit->setDate(QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	tillDateEdit->setDate(QDate::fromString(endDate.c_str(), "dd.MM.yyyy"));
	QObject::connect(okBtn, &QPushButton::released, this, &CloseOfMonthDlg::Calculate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &CloseOfMonthDlg::Close);
}

CloseOfMonthDlg::~CloseOfMonthDlg()
{

}


void CloseOfMonthDlg::Calculate()
{
	std::string fromDate = fromDateEdit->text().toUtf8().constData();
	std::string tillDate = tillDateEdit->text().toUtf8().constData();
	dialogBL->StartIsolatedTransaction(errorMessage);
	if (dialogBL->CloseOfMonth(fromDate, tillDate))
	{
		if (!dialogBL->CommitTransaction(errorMessage))
		{
			dialogBL->CancelTransaction(errorMessage);
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
		}
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Close of month is successfully ended!")),
			QString(tr("Ok")));
	}
	else
	{
		dialogBL->CancelTransaction(errorMessage);
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Close of month is failed!")),
			QString(tr("Ok")));
	}
	Close();
}

void CloseOfMonthDlg::Close()
{
	this->parentWidget()->close();
}
