#include "stdafx.h"
#include "GenerateAccRepDlg.h"
#include "MainForm.h"
#include "ReportForm.h"
#include "DataForm.h"
#include "QRadioButton.h"


GenerateAccCardRep::GenerateAccCardRep(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();
	
	vInt = new QIntValidator(0, 1000000000, this);
	accIDEdit->setValidator(vInt);

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

	QObject::connect(accBtn, &QPushButton::released, this, &GenerateAccCardRep::OpenAccDlg);
	QObject::connect(sAccBtn, &QPushButton::released, this, &GenerateAccCardRep::OpenSAccDlg);
	QObject::connect(accNumberEdit, &QLineEdit::textChanged, this, &GenerateAccCardRep::AccTextChanged);
	QObject::connect(okBtn, &QPushButton::released, this, &GenerateAccCardRep::Generate);
	QObject::connect(this, SIGNAL(CloseCreatedForms()), ((MainForm*)((DataForm*)parent)->GetParent()), SLOT(CloseChildsByName()));
	QObject::connect(cancelBtn, &QPushButton::released, this, &GenerateAccCardRep::Close);
	QObject::connect(oneAccRb, &QRadioButton::released, this, &GenerateAccCardRep::CheckBoxChanged);
	QObject::connect(allAccRb, &QRadioButton::released, this, &GenerateAccCardRep::CheckBoxChanged);

	std::map<std::string, int> rolesMap = BusinessLayer::Role::GetRolesAsMap(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), errorMessage);
	if (0 == rolesMap.size())
		return;

	

	if (mainForm->GetLoggedUser()->GetRoleID() != rolesMap.find("SUPERUSER")->second ||
		mainForm->GetLoggedUser()->GetRoleID() != rolesMap.find("CHIEF ACCOUNTANT")->second)
	{
		allAccRb->hide();
		oneAccRb->setChecked(true);
		CheckBoxChanged();
	}
}

GenerateAccCardRep::~GenerateAccCardRep()
{
	delete vInt;
	emit CloseCreatedForms();
}

void GenerateAccCardRep::SetID(int ID, QString childName)
{
	if (0 != ID)
	{
		if (0 != childName.length())
		{
			this->hide();
			this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
			this->show();
			this->raise();
			this->activateWindow();
			QApplication::setActiveWindow(this);

			if (childName == QString("accountForm"))
			{
				accIDEdit->setText(QString::number(ID));
				BusinessLayer::Account account;
				if (account.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accNumberEdit->setReadOnly(true);
					accNumberEdit->setText(account.GetNumber().c_str());
				}
			}
			if (childName == QString("subaccountForm"))
			{
				accIDEdit->setText(QString::number(ID));
				BusinessLayer::Subaccount subaccount;
				if (subaccount.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), ID, errorMessage))
				{
					accNumberEdit->setReadOnly(true);
					accNumberEdit->setText(subaccount.GetNumber().c_str());
				}
			}
		}
	}
}

void GenerateAccCardRep::Generate()
{
	QString message = tr("Loading...");
	//QWidget* checkedWidget = IsWindowExist(((MainForm*)parentForm)->mdiArea->subWindowList(), QString("generateAccRepForm"));
	//if (checkedWidget == nullptr)
	//{
	ReportForm *rForm = new ReportForm(dialogBL, mainForm);
		rForm->setWindowTitle(tr("Account turnover balance sheet"));
		std::string prevMonthLastDate = GetPrevMonthEnd(fromDateEdit->text().toUtf8().constData());
		if (oneAccRb->isChecked())
		{
			if (accIDEdit->text().toInt() >0)
			{
				rForm->FillAccCrdTable(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), accIDEdit->text().toInt(), prevMonthLastDate);
			}
			else
			{
				delete rForm;
				QMessageBox::information(NULL, QString(tr("Warning")),
					QString(tr("Please select account ot subaccount")),
					QString(tr("Ok")));
				errorMessage = "";
			}
		}
		else
		{
			rForm->FillAccCrdTable(fromDateEdit->text().toUtf8().constData(), tillDateEdit->text().toUtf8().constData(), prevMonthLastDate);
		}
		if (errorMessage.empty())
		{
			//rForm->setObjectName("generateAccRepForm");
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
	//}
	//else
	//{
	//	checkedWidget->topLevelWidget();
	//	checkedWidget->activateWindow();
	//}
	Close();
}

void GenerateAccCardRep::Close()
{
	this->parentWidget()->close();
}

void GenerateAccCardRep::OpenAccDlg()
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
		BusinessLayer::Account account;
		if (account.GetAccountByNumber(mainForm->oBL->globalVar, mainForm->oBL->GetOrmasDal(), "10250", errorMessage))
		{
			BusinessLayer::Account accountForFilter;
			accountForFilter.SetID(account.GetID());
			filter = accountForFilter.GenerateFilter(mainForm->oBL->GetOrmasDal());
		}
	}
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Accounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::Account>(errorMessage, filter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("accountForm");
		dForm->QtConnect<BusinessLayer::Account>();
		QMdiSubWindow *dAccountWindow = new QMdiSubWindow;
		dAccountWindow->setWidget(dForm);
		dAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(dAccountWindow);
		dAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All accounts are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void GenerateAccCardRep::OpenSAccDlg()
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
	QString message = tr("Loading...");
	mainForm->statusBar()->showMessage(message);
	DataForm *dForm = new DataForm(dialogBL, mainForm);
	dForm->setWindowTitle(tr("Subccounts"));
	dForm->hide();
	dForm->setWindowModality(Qt::WindowModal);
	dForm->FillTable<BusinessLayer::SubaccountView>(errorMessage, filter);
	if (errorMessage.empty())
	{
		dForm->parentDialog = this;
		dForm->setObjectName("subaccountForm");
		dForm->QtConnect<BusinessLayer::SubaccountView>();
		QMdiSubWindow *dSAccountWindow = new QMdiSubWindow;
		dSAccountWindow->setWidget(dForm);
		dSAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
		mainForm->mdiArea->addSubWindow(dSAccountWindow);
		dSAccountWindow->resize(dForm->size().width() + 18, dForm->size().height() + 30);
		dForm->topLevelWidget();
		dForm->activateWindow();
		QApplication::setActiveWindow(dForm);
		dForm->SetDecoration();
		dForm->show();
		dForm->raise();
		dForm->setWindowFlags(dForm->windowFlags() | Qt::WindowStaysOnTopHint);
		QString message = tr("All subaccounts are shown");
		mainForm->statusBar()->showMessage(message);
	}
	else
	{
		delete dForm;
		QString message = tr("End with error!");
		mainForm->statusBar()->showMessage(message);
		QMessageBox::information(NULL, QString(tr("Warning")),
			QString(tr(errorMessage.c_str())),
			QString(tr("Ok")));
		errorMessage = "";
	}
}

void GenerateAccCardRep::CheckBoxChanged()
{
	if (oneAccRb->isChecked())
	{
		oneAccWidget->setEnabled(true);
		
	}
	else if (allAccRb->isChecked())
	{
		oneAccWidget->setDisabled(true);
		accIDEdit->setText("");
		accNumberEdit->setText("");
		accNamePh->setText("");
	}
}


void GenerateAccCardRep::AccTextChanged()
{
	if (accNumberEdit->text().length() == 5 || accNumberEdit->text().length() == 6)
	{
		BusinessLayer::Account account;
		if (account.GetAccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), accNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			accIDEdit->setText(QString::number(account.GetID()));
			if (account.GetName(dialogBL->GetOrmasDal()).c_str() != nullptr)
				accNamePh->setText(account.GetName(dialogBL->GetOrmasDal()).c_str());
		}
		else
		{
			accNamePh->setText(tr("Incorrect account number!"));
			accIDEdit->setText("");
		}
	}
	else if (accNumberEdit->text().length() == 15)
	{
		BusinessLayer::Subaccount subaccount;
		if (subaccount.GetSubaccountByNumber(dialogBL->globalVar, dialogBL->GetOrmasDal(), accNumberEdit->text().toUtf8().constData(), errorMessage))
		{
			accIDEdit->setText(QString::number(subaccount.GetID()));
			if (subaccount.GetName(dialogBL->GetOrmasDal()).c_str() != nullptr)
				accNamePh->setText(subaccount.GetName(dialogBL->GetOrmasDal()).c_str());
		}
		else
		{
			accNamePh->setText(tr("Incorrect account number!"));
			accIDEdit->setText("");
		}
	}
	else
	{
		accNamePh->setText("");
		accIDEdit->setText("");
	}
}

std::string GenerateAccCardRep::GetPrevMonthEnd(std::string date)
{
	QDate currentDate = QDate::fromString(date.c_str(), "dd.MM.yyyy");
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