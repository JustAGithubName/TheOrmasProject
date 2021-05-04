#include "stdafx.h"
#include "CashBookListDlg.h"
#include "DocForm.h"


CashBookListDlg::CashBookListDlg(BusinessLayer::OrmasBL *ormasBL, QWidget *parent) :QDialog(parent)
{
	setupUi(this);
	setModal(true);
	dialogBL = ormasBL;
	parentForm = parent;
	mainForm = (MainForm *)this->parent();

	QDate currentDate = QDate::currentDate();
	currDate = GetCurrentDate();
	forDateEdit->setDate(QDate::fromString(currDate.c_str(), "dd.MM.yyyy"));
	QObject::connect(okBtn, &QPushButton::released, this, &CashBookListDlg::Generate);
	QObject::connect(cancelBtn, &QPushButton::released, this, &CashBookListDlg::Close);
}

CashBookListDlg::~CashBookListDlg()
{

}


void CashBookListDlg::Generate()
{
	BusinessLayer::Status status;
	if (!status.GetStatusByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "EXECUTED", errorMessage))
		return;
	std::string errorMessage = "";
	BusinessLayer::Payment payment;
	BusinessLayer::Withdrawal withdrowal;
	payment.SetDate(forDateEdit->text().toUtf8().constData());
	payment.SetStatusID(status.GetID());
	std::string pmtFilter = payment.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::PaymentView> vecPmtRep = dialogBL->GetAllDataForClass<BusinessLayer::PaymentView>(errorMessage, pmtFilter);
	
	withdrowal.SetDate(forDateEdit->text().toUtf8().constData());
	withdrowal.SetStatusID(status.GetID());
	std::string wthFilter = withdrowal.GenerateFilter(dialogBL->GetOrmasDal());
	std::vector<BusinessLayer::WithdrawalView> vecWthRep = dialogBL->GetAllDataForClass<BusinessLayer::WithdrawalView>(errorMessage, wthFilter);

	DocForm *docForm = new DocForm(dialogBL, this);
	docForm->setAttribute(Qt::WA_DeleteOnClose);
	docForm->setWindowTitle(tr("Print cash book list"));
	QMdiSubWindow *printRepWindow = new QMdiSubWindow;
	printRepWindow->setWidget(docForm);
	printRepWindow->setAttribute(Qt::WA_DeleteOnClose);
	printRepWindow->resize(docForm->size().width() + 18, docForm->size().height() + 30);
	((MainForm*)parentForm)->mdiArea->addSubWindow(printRepWindow);

	QFile file;
	file.setFileName(":/docs/cash_list.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(NULL, QString(tr("Info")),
			QString(tr("Cannot find report tamplate!")),
			QString(tr("Ok")));
		return;
	}
	QString reportText = file.readAll();
	QString tableBody;
	if (vecPmtRep.size() == 0 && vecWthRep.size() == 0)
	{
		reportText.replace(QString("DatePh"), forDateEdit->text(), Qt::CaseInsensitive);
		reportText.replace(QString("CashSumPh"), QString::number(0), Qt::CaseInsensitive);
		reportText.replace(QString("TableBodyPh"), QString(""), Qt::CaseInsensitive);
		reportText.replace(QString("TodayInSumPh"), QString::number(0), Qt::CaseInsensitive);
		reportText.replace(QString("TodayOutSumPh"), QString::number(0), Qt::CaseInsensitive);
		reportText.replace(QString("TodayPastSumPh"), QString::number(0), Qt::CaseInsensitive);
		reportText.replace(QString("CachierNamePh"), QString(""), Qt::CaseInsensitive);
		reportText.replace(QString("AccounantNamePh"), QString(""), Qt::CaseInsensitive);
	}
	else
	{
		BusinessLayer::Role role;
		BusinessLayer::Employee accountant;
		BusinessLayer::Employee cashier;
		BusinessLayer::User user;
		BusinessLayer::Subaccount subAcc;
		BusinessLayer::Balance balance;

		if (0 == role.GetRoleIDByName(dialogBL->globalVar, dialogBL->GetOrmasDal(), "CHIEF ACCOUNTANT", errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' role!")),
				QString(tr("Ok")));
			return;
		}
		
		accountant.SetRoleID(role.GetID());
		std::string empFilter = accountant.GenerateFilter(dialogBL->GetOrmasDal());
		std::vector<BusinessLayer::EmployeeView> vecEmpRep = dialogBL->GetAllDataForClass<BusinessLayer::EmployeeView>(errorMessage, empFilter);
		if (vecEmpRep.size() == 0)
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CHIEF ACCOUNTANT' employee!")),
				QString(tr("Ok")));
			return;
		}
		else
		{
			accountant.SetName(vecEmpRep.at(0).GetName());
			accountant.SetSurname(vecEmpRep.at(0).GetSurname());
		}

		if (!cashier.GetEmployeeByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dialogBL->loggedUser->GetID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHIER' employee!")),
				QString(tr("Ok")));
			return;
		}

		BusinessLayer::CashboxEmployeeRelation ceRel;
		int cashboxID = ceRel.GetCashboxIDByEmployeeID(dialogBL->globalVar, dialogBL->GetOrmasDal(), dialogBL->loggedUser->GetID(), errorMessage);
		BusinessLayer::Cashbox cashbox;
		if (!cashbox.GetCashboxByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashboxID, errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find 'CASHBOX' for this employee!")),
				QString(tr("Ok")));
			return;
		}

		BusinessLayer::Subaccount cahsboxSubacc;
		if (!cahsboxSubacc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), cashbox.GetSubaccountID(), errorMessage))
		{
			QMessageBox::information(NULL, QString(tr("Warning")),
				QString(tr("Connot find subaccount for this employee!")),
				QString(tr("Ok")));
			return;
		}

		BusinessLayer::SubaccountHistory saccHistory;
		BusinessLayer::Entry entry;
		std::vector<BusinessLayer::SubaccountView> vecSubacc;
		std::vector<BusinessLayer::SubaccountHistory> vecSubAccHistory;
		std::vector<BusinessLayer::ExtendedEntryView> vecEntryDeb;
		std::vector<BusinessLayer::ExtendedEntryView> vecEntryCred;
		std::string filterDebit;
		std::string filterCredit;
		std::string filterSub;
		std::string filterSubHistory;
		std::string filterAccHistory;
		
		double debSum = 0.0;
		double credSum = 0.0;
		
		BusinessLayer::SubaccountHistory saccHistoryEnd;
		std::vector<BusinessLayer::SubaccountHistory> vecSubAccHistoryEnd;

		std::string fromDate = "";
		std::string tillDate = "";
		std::string prevMonthEnd = "";
		std::string prevDate = "";
		std::string currentDate = forDateEdit->text().toUtf8().constData();

		GetPrevMonthEnd(currentDate, fromDate, tillDate, prevMonthEnd, prevDate);

		saccHistoryEnd.Clear();
		saccHistoryEnd.SetSubaccountID(cahsboxSubacc.GetID());
		if (!prevMonthEnd.empty())
		{
			saccHistoryEnd.SetTillDate(prevMonthEnd);
		}
		filterAccHistory.clear();
		filterAccHistory = saccHistoryEnd.GenerateFilter(dialogBL->GetOrmasDal());
		vecSubAccHistoryEnd = dialogBL->GetAllDataForClass<BusinessLayer::SubaccountHistory>(errorMessage, filterAccHistory);

		/*filterDebit.clear();
		entry.Clear();
		vecEntryDeb.clear();
		entry.SetDebitingAccountID(cahsboxSubacc.GetParentAccountID());
		filterDebit = entry.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDate, currentDate);
		vecEntryDeb = dialogBL->GetAllDataForClass<BusinessLayer::ExtendedEntryView>(errorMessage, filterDebit);

		filterCredit.clear();
		entry.Clear();
		vecEntryCred.clear();
		entry.SetCreditingAccountID(cahsboxSubacc.GetParentAccountID());
		filterCredit = entry.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDate, currentDate);
		vecEntryCred = dialogBL->GetAllDataForClass<BusinessLayer::ExtendedEntryView>(errorMessage, filterCredit);*/

		QDate selectDate = QDate::fromString(currentDate.c_str(), "dd.MM.yyyy");
		int selectMonth = selectDate.month();
		
		QDate prevDateFromSelectedDate = QDate::fromString(prevDate.c_str(), "dd.MM.yyyy");
		int prevSelectMonth = prevDateFromSelectedDate.month();
		

		BusinessLayer::Payment paymentMonth;
		BusinessLayer::Withdrawal withdrowalMonth;
		double startValue = 0;
		double endValue = 0;

		if (selectMonth == prevSelectMonth)
		{
			pmtFilter.clear();
			paymentMonth.SetCashboxAccountID(cashbox.GetSubaccountID());
			paymentMonth.SetStatusID(status.GetID());
			std::string pmtFilter = paymentMonth.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDate, prevDate);
			std::vector<BusinessLayer::PaymentView> vecPmtRepMonth = dialogBL->GetAllDataForClass<BusinessLayer::PaymentView>(errorMessage, pmtFilter);

			wthFilter.clear();
			withdrowalMonth.SetStatusID(status.GetID());
			withdrowalMonth.SetCashboxAccountID(cashbox.GetSubaccountID());
			std::string wthFilter = withdrowalMonth.GenerateFilterForPeriod(dialogBL->globalVar, dialogBL->GetOrmasDal(), fromDate, prevDate);
			std::vector<BusinessLayer::WithdrawalView> vecWthRepMonth = dialogBL->GetAllDataForClass<BusinessLayer::WithdrawalView>(errorMessage, wthFilter);
			
			if (vecSubAccHistoryEnd.size() > 0)
			{
				startValue = vecSubAccHistoryEnd.at(0).GetStartBalance();
			}
			else
			{
				startValue = cahsboxSubacc.GetStartBalance();
			}

			for each (auto payItem in vecPmtRepMonth)
			{
				startValue += payItem.GetValue();
			}
			for each (auto withItem in vecWthRepMonth)
			{
				startValue -= withItem.GetValue();
			}
		}
		else
		{
			if (vecSubAccHistoryEnd.size() > 0)
			{
				startValue = vecSubAccHistoryEnd.at(0).GetStartBalance();
			}
			else
			{
				startValue = cahsboxSubacc.GetStartBalance();
			}
		}
		
		if (vecPmtRep.size() > 0)
		{
			std::string accNumber = "";
			BusinessLayer::Account acc;
			for each (auto item in vecPmtRep)
			{
				if (item.GetCashboxAccountID() == cashbox.GetSubaccountID())
				{
					acc.Clear();
					accNumber.clear();
					payment.Clear();
					subAcc.Clear();
					balance.Clear();
					user.Clear();
					if (!payment.GetPaymentByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetID(), errorMessage))
					{
						QMessageBox::information(NULL, QString(tr("Info")),
							QString(tr("Payment is wrong!")),
							QString(tr("Ok")));
						return;
					}
					if (item.GetUserID() > 0)
					{
						if (!user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetUserID(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Info")),
								QString(tr("Can't find this user!")),
								QString(tr("Ok")));
							return;
						}
						if (!balance.GetBalanceByUserID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetUserID(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Info")),
								QString(tr("Can't find balance for this user!")),
								QString(tr("Ok")));
							return;
						}
						if (item.GetSubaccountID() > 0)
						{
							if (!subAcc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetSubaccountID(), errorMessage))
							{
								QMessageBox::information(NULL, QString(tr("Info")),
									QString(tr("Can't find subaccount for this user!")),
									QString(tr("Ok")));
								return;
							}
						}
						else
						{
							if (!subAcc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance.GetSubaccountID(), errorMessage))
							{
								QMessageBox::information(NULL, QString(tr("Info")),
									QString(tr("Can't find subaccount for this user!")),
									QString(tr("Ok")));
								return;
							}
						}

					}
					tableBody += "<tr>";
					tableBody += "<td>" + QString::number(item.GetID()) + "</td>";
					if (item.GetUserID() > 0)
					{
						tableBody += "<td>" + QString::fromWCharArray(L"Принято от: ") + QString(user.GetSurname().c_str()) + " " + QString(user.GetName().c_str()) + "</td>";
						tableBody += "<td>" + QString(subAcc.GetNumber().c_str()) + "</td>";
					}
					else
					{
						acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetAccountID(), errorMessage);
						tableBody += "<td>" + QString::fromWCharArray(L"Принято от: ") + QString(item.GetWho().c_str()) + "</td>";
						tableBody += "<td>" + QString(acc.GetNumber().c_str()) + "</td>";
					}
					tableBody += "<td>" + QString::number(item.GetValue(), 'f', 3) + "</td>";
					tableBody += "<td>" + QString("-") + "</td>";
					tableBody += "</tr>";
					InSum += item.GetValue();
				}
			}
		}
		if (vecWthRep.size() > 0)
		{
			std::string accNumber = "";
			BusinessLayer::Account acc;
			for each (auto item in vecWthRep)
			{
				if (item.GetCashboxAccountID() == cashbox.GetSubaccountID())
				{
					acc.Clear();
					accNumber.clear();
					withdrowal.Clear();
					subAcc.Clear();
					balance.Clear();
					user.Clear();
					if (!withdrowal.GetWithdrawalByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetID(), errorMessage))
					{
						QMessageBox::information(NULL, QString(tr("Info")),
							QString(tr("Withdrawal is wrong!")),
							QString(tr("Ok")));
						return;
					}
					if (item.GetUserID() > 0)
					{
						if (!user.GetUserByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetUserID(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Info")),
								QString(tr("Can't find this user!")),
								QString(tr("Ok")));
							return;
						}
						if (!balance.GetBalanceByUserID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetUserID(), errorMessage))
						{
							QMessageBox::information(NULL, QString(tr("Info")),
								QString(tr("Can't find balance for this user!")),
								QString(tr("Ok")));
							return;
						}
						if (item.GetSubaccountID() > 0)
						{
							if (!subAcc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetSubaccountID(), errorMessage))
							{
								QMessageBox::information(NULL, QString(tr("Info")),
									QString(tr("Can't find subaccount for this user!")),
									QString(tr("Ok")));
								return;
							}
						}
						else
						{
							if (!subAcc.GetSubaccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), balance.GetSubaccountID(), errorMessage))
							{
								QMessageBox::information(NULL, QString(tr("Info")),
									QString(tr("Can't find subaccount for this user!")),
									QString(tr("Ok")));
								return;
							}
						}
					}
					tableBody += "<tr>";
					tableBody += "<td>" + QString::number(item.GetID()) + "</td>";
					if (item.GetUserID() > 0)
					{
						tableBody += "<td>" + QString::fromWCharArray(L"Выдано: ") + QString(user.GetSurname().c_str()) + " " + QString(user.GetName().c_str()) + "</td>";
						tableBody += "<td>" + QString(subAcc.GetNumber().c_str()) + "</td>";
					}
					else
					{
						acc.GetAccountByID(dialogBL->globalVar, dialogBL->GetOrmasDal(), item.GetAccountID(), errorMessage);
						tableBody += "<td>" + QString::fromWCharArray(L"Выдано: ") + QString(item.GetWho().c_str()) + "</td>";
						tableBody += "<td>" + QString(acc.GetNumber().c_str()) + "</td>";
					}
					tableBody += "<td>" + QString("-") + "</td>";
					tableBody += "<td>" + QString::number(item.GetValue(), 'f', 3) + "</td>";
					tableBody += "</tr>";
					OutSum += item.GetValue();
				}
			}
		}

		endValue = startValue + InSum - OutSum;
		reportText.replace(QString("DatePh"), forDateEdit->text(), Qt::CaseInsensitive);
		reportText.replace(QString("CashSumPh"), QString::number(startValue,'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("TableBodyPh"), tableBody, Qt::CaseInsensitive);
		reportText.replace(QString("TodayInSumPh"), QString::number(InSum,'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("TodayOutSumPh"), QString::number(OutSum,'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("TodayPastSumPh"), QString::number(endValue,'f',3), Qt::CaseInsensitive);
		reportText.replace(QString("CachierNamePh"), QString(cashier.GetSurname().c_str()) + " " + QString(cashier.GetName().c_str()), Qt::CaseInsensitive);
		reportText.replace(QString("AccounantNamePh"), QString(accountant.GetSurname().c_str()) + " " + QString(accountant.GetName().c_str()), Qt::CaseInsensitive);
	}

	docForm->webEngineView->setHtml(reportText);
	docForm->SetContent(reportText);
	docForm->webEngineView->show();
	docForm->show();
	Close();
}

void CashBookListDlg::Close()
{
	this->parentWidget()->close();
}

void CashBookListDlg::GetPrevMonthEnd(std::string forDate, std::string& fromDate, std::string& tillDate, std::string& prevMonthEnd, std::string& prevDate)
{
	QDate currentDate = QDate::fromString(forDate.c_str(), "dd.MM.yyyy");
	int day = currentDate.day();
	int month = currentDate.month();
	int year = currentDate.year();

	std::string startDate;
	std::string endDate;
	
	QDate curMonthDate;
	QDate pastMonthDate;
	int coundOfDaysCurr;
	int coundOfDaysPast; //  = pastMonthDate.daysInMonth();

	startDate = "01.";
	if (month < 10)
	{
		startDate += "0";
		startDate += std::to_string(month);
	}
	else
	{
		startDate += std::to_string(month);
	}
	startDate += ".";
	startDate += std::to_string(year);

	curMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
	coundOfDaysCurr = curMonthDate.daysInMonth();
	endDate = std::to_string(coundOfDaysCurr);
	endDate += ".";
	if (month < 10)
	{
		endDate += "0";
		endDate += std::to_string(month);
	}
	else
	{
		endDate += std::to_string(month);
	}
	endDate += ".";
	endDate += std::to_string(year);

	fromDate = startDate;
	tillDate = endDate;

	startDate = "";
	endDate = "";

	if (month == 1)
	{
		startDate = "01.";
		startDate += std::to_string(12);
		startDate += ".";
		startDate += std::to_string(year - 1);
		pastMonthDate = (QDate::fromString(startDate.c_str(), "dd.MM.yyyy"));
		coundOfDaysPast = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDaysPast);
		endDate += ".";
		endDate += std::to_string(12);
		endDate += ".";
		endDate += std::to_string(year - 1);

		prevMonthEnd = endDate;
	}
	if (month > 1)
	{
		startDate = "01.";
		if (month<11)
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
		coundOfDaysPast = pastMonthDate.daysInMonth();
		endDate = std::to_string(coundOfDaysPast);
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
		prevMonthEnd = endDate;
	}

	startDate = "";
	endDate = "";

	if (day == 1)
	{
		prevDate = prevMonthEnd;
	}
	else
	{
		if (day - 1 < 10)
		{
			startDate = "0";
			startDate += std::to_string(day - 1);
			startDate += ".";
		}
		else
		{ 
			startDate = std::to_string(day - 1);
			startDate += ".";
		}
		if (month < 11)
		{
			startDate += "0";
			startDate += std::to_string(month);
		}
		else
		{
			startDate += std::to_string(month);
		}
		startDate += ".";
		startDate += std::to_string(year); 
		prevDate = startDate;
	}
}

std::string CashBookListDlg::GetCurrentDate()
{
	QDate currentDate = QDate::currentDate();
	int day = currentDate.day();
	int month = currentDate.month();
	int year = currentDate.year();

	std::string startDate = "";
	startDate = std::to_string(day);
	startDate += ".";
	if (month < 11)
	{
		startDate += "0";
		startDate += std::to_string(month);
	}
	else
	{
		startDate += std::to_string(month);
	}
	startDate += ".";
	startDate += std::to_string(year);

	return startDate;
}