#include "stdafx.h"
#include "GenerateWTBSDlg.h"
#include "ReportForm.h"


GenerateWTBS::GenerateWTBS(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
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

	QObject::connect(okBtn, &QPushButton::released, this, &GenerateWTBS::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateWTBS::Close);
	InitComboBox();
}

GenerateWTBS::~GenerateWTBS()
{
}

void GenerateWTBS::Generate()
{
	QString message = tr("Loading...");
	QWidget* checkedWidget= IsWindowExist(((MainForm*)parentForm)->mdiArea->subWindowList(), QString("generateWTBSForm"));
	if (checkedWidget == nullptr)
	{
		ReportForm *rForm = new ReportForm(dialogBL, mainForm);
		rForm->setWindowTitle(tr("Warehouse turnover balance sheet"));
		std::string prevMonthLastDate = GetPrevMonthEnd(fromDateEdit->text().toUtf8().constData());
		rForm->FillStockTable(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), warehouseCmb->currentData().toInt(), prevMonthLastDate);
		if (errorMessage.empty())
		{
			QMdiSubWindow *accountWindow = new QMdiSubWindow;
			accountWindow->setWidget(rForm);
			accountWindow->setAttribute(Qt::WA_DeleteOnClose);
			((MainForm*)parentForm)->mdiArea->addSubWindow(accountWindow);
			accountWindow->resize(rForm->size().width() + 18, rForm->size().height() + 30);
			rForm->show();
			rForm->topLevelWidget();
			rForm->activateWindow();
			rForm->raise();
			rForm->setWindowFlags(rForm->windowFlags() | Qt::WindowStaysOnTopHint);
		}
		else
		{
			delete rForm;
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr(errorMessage.c_str())),
				QString(tr("Ok")));
			errorMessage = "";
		}
	}
	else
	{
		checkedWidget->topLevelWidget();
		checkedWidget->activateWindow();
	}
	Close();
}

void GenerateWTBS::Close()
{
	this->parentWidget()->close();
}

void GenerateWTBS::InitComboBox()
{
	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	std::string filter = "";

	if (mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("SUPERUSER")->second ||
		mainForm->GetLoggedUser()->GetRoleID() == rolesMap.find("CHIEF ACCOUNTANT")->second)
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
	std::vector<BusinessLayer::WarehouseView> curWarehouse = dialogBL->GetAllDataForClass<BusinessLayer::WarehouseView>(errorMessage,filter);
	if (!curWarehouse.empty())
	{
		for (unsigned int i = 0; i < curWarehouse.size(); i++)
		{
			warehouseCmb->addItem(curWarehouse[i].GetName().c_str(), QVariant(curWarehouse[i].GetID()));
		}
	}
}

std::string GenerateWTBS::GetPrevMonthEnd(std::string date)
{
	QDate currentDate = QDate::fromString(date.c_str(),"dd.MM.yyyy");
	int day = currentDate.day();
	int month = currentDate.month();
	int year = currentDate.year();

	std::string startDate;
	std::string endDate;
	QDate pastMonthDate;
	int coundOfDays; //  = pastMonthDate.daysInMonth();

	if (month == 1)
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
		return endDate;
	}
	if (month > 1)
	{
		startDate = "01.";
		if (month < 11)
		{
			startDate += "0";
			startDate += std::to_string(month - 1);
		}
		else
		{
			startDate += std::to_string(month - 1);
		}
		startDate += ".";
		startDate += std::to_string(year);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDays = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDays);
		endDate += ".";
		if (month < 11)
		{
			endDate += "0";
			endDate += std::to_string(month - 1);
		}
		else
		{
			endDate += std::to_string(month - 1);
		}
		endDate += ".";
		endDate += std::to_string(year);
		return endDate;
	}

	return "";
}