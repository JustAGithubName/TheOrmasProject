#include "stdafx.h"
#include "PayslipClass.h"
#include "PaymentClass.h"
#include "UserClass.h"
#include "RoleClass.h"
#include "SubaccountClass.h"
#include "SalaryClass.h"
#include "BalanceClass.h"
#include "BalancePayslipRelationClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyEmployeeRelationClass.h"
#include "CompanyClass.h"
#include "DivisionEmployeeRelationClass.h"
#include "DivisionClass.h"
#include "AccountClass.h"
#include <codecvt>

namespace BusinessLayer{
	Payslip::Payslip(DataLayer::payslipsCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		value = std::get<2>(pCollection);
		salaryID = std::get<3>(pCollection);
		currencyID = std::get<4>(pCollection);
	}
	Payslip::Payslip()
	{
		date = "";
		value = 0.0;
		salaryID = 0;
		currencyID = 0;
	}
	int Payslip::GetID()
	{
		return id;
	}

	std::string Payslip::GetDate()
	{
		return date;
	}

	double Payslip::GetValue()
	{
		return value;
	}

	int Payslip::GetSalaryID()
	{
		return salaryID;
	}

	int Payslip::GetCurrencyID()
	{
		return currencyID;
	}

	void Payslip::SetID(int pID)
	{
		id = pID;
	}

	void Payslip::SetDate(std::string pDate)
	{
		date = pDate;
	}

	void Payslip::SetValue(double pValue)
	{
		value = pValue;
	}

	void Payslip::SetSalaryID(int sID)
	{
		salaryID = sID;
	}
	void Payslip::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	bool Payslip::CreatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int sID, int cID,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pDate, pValue, sID, cID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		date = pDate;
		value = pValue;
		salaryID = sID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreatePayslip(id, date, value, salaryID, currencyID, errorMessage))
		{
			if (Payout(globalVar, ormasDal, salaryID, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Payslip::CreatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreatePayslip(id, date, value, salaryID, currencyID, errorMessage))
		{
			if (Payout(globalVar, ormasDal, salaryID, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Payslip::DeletePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (!this->GetPayslipByID(globalVar, ormasDal, id, errorMessage))
			return false;
		if (ormasDal.DeletePayslip(id, errorMessage))
		{
			if (CancelPayslip(globalVar, ormasDal, salaryID, currencyID, errorMessage))
			{
				Clear();
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool Payslip::UpdatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int sID, int cID,
		std::string& errorMessage)
	{
		date = pDate;
		value = pValue;
		salaryID = sID;
		currencyID = cID;
		currentValue = GetCurrentValue(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdatePayslip(id, date, value, salaryID, currencyID, errorMessage))
		{
			if (Payout(globalVar, ormasDal, salaryID, currencyID, currentValue, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				currentValue = 0.0;
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Payslip::UpdatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		currentValue = GetCurrentValue(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdatePayslip(id, date, value, salaryID, currencyID, errorMessage))
		{
			if (Payout(globalVar, ormasDal, salaryID, currencyID, currentValue, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				currentValue = 0.0;
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string Payslip::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != salaryID || 0 != currencyID || 0 != value)
		{
			return ormasDal.GetFilterForPayslip(id, date, value, salaryID, currencyID);
		}
		return "";
	}

	bool Payslip::GetPayslipByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipsViewCollection> payslipVector = ormasDal.GetPayslips(errorMessage, filter);
		if (0 != payslipVector.size())
		{
			id = std::get<0>(payslipVector.at(0));
			date = std::get<1>(payslipVector.at(0));
			value = std::get<2>(payslipVector.at(0));
			salaryID = std::get<4>(payslipVector.at(0));
			currencyID = std::get<5>(payslipVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Payslip with this id";
		}
		return false;
	}

	bool Payslip::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && 0 == salaryID && 0 == currencyID)
			return true;
		return false;
	}

	void Payslip::Clear()
	{
		id = 0;
		date.clear();
		value = 0;
		salaryID = 0;
		currencyID = 0;
	}

	bool Payslip::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
		std::string& errorMessage)
	{
		Payslip payslip;
		payslip.Clear();
		errorMessage.clear();
		payslip.SetDate(pDate);
		payslip.SetValue(pValue);
		payslip.SetSalaryID(uID);
		payslip.SetCurrencyID(cID);
		std::string filter = payslip.GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipsViewCollection> payslipVector = ormasDal.GetPayslips(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == payslipVector.size())
		{
			return false;
		}
		errorMessage = "Payslip with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Payslip::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Payslip payslip;
		payslip.Clear();
		errorMessage.clear();
		payslip.SetDate(date);
		payslip.SetValue(value);
		payslip.SetSalaryID(salaryID);
		payslip.SetCurrencyID(currencyID);
		std::string filter = payslip.GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipsViewCollection> payslipVector = ormasDal.GetPayslips(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == payslipVector.size())
		{
			return false;
		}
		errorMessage = "Payslip with these parameters are already exist! Please avoid the duplication!";
		return true;
	}


	bool Payslip::Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cID, std::string& errorMessage)
	{
		CompanyAccountRelation cAccRel;
		CompanyEmployeeRelation cEmpRel;
		DivisionEmployeeRelation deRel;
		Division division;
		Balance balance;
		Balance tempBalance;
		Company company;
		Salary salary;
		User user;
		Role role;
		Subaccount sub;
		Account acc;
		if (!acc.GetAccountByNumber(globalVar, ormasDal, "22210", errorMessage))
		{
			return false;
		}
		if (!salary.GetSalaryByID(globalVar, ormasDal, sID, errorMessage))
		{
			if (errorMessage.empty())
				errorMessage = "Cannot find salary with this ID!";
			return false;
		}
		Payment payment;
		payment.SetUserID(salary.GetEmployeeID());
		std::string filter = payment.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 < balanceVector.size())
		{
			for each (auto item in balanceVector)
			{
				sub.Clear();
				tempBalance.Clear();
				if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
					return false;
				if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
				{
					if (sub.GetParentAccountID() == acc.GetID())
					{
						balance.SetSubaccountID(sub.GetID());
					}
				}
			}
		}
		else
		{
			return false;
		}
		if (balance.GetSubaccountID() <= 0)
			return false;
		if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
		{
			int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
			if (!user.GetUserByID(globalVar, ormasDal, salary.GetEmployeeID(), errorMessage))
				return false;
			if (!role.GetRoleByID(globalVar, ormasDal, user.GetRoleID(), errorMessage))
				return false;
			if (!deRel.GetDivisionEmployeeRelationByEmployeeID(globalVar, ormasDal, user.GetID(), errorMessage))
				return false;
			if (!division.GetDivisionByID(globalVar, ormasDal, deRel.GetDivisionID(), errorMessage))
				return false;
			int debAccID = 0;
			if (0 == division.GetCode().compare("RELEASE"))
			{
				debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55220", errorMessage);
			}
			else if (0 == division.GetCode().compare("ADMINISTRATION"))
			{
				debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55310", errorMessage);
			}
			else if (0 == division.GetCode().compare("PRODUCTION"))
			{
				debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
			}
			int credAccID = balance.GetSubaccountID(); 
			if (0 == debAccID || 0 == credAccID || 0 == companyID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
				BalancePayslipRelation bpRelation;
				bpRelation.SetBalanceID(balance.GetID());
				bpRelation.SetPayslipID(this->id);
				if (bpRelation.CreateBalancePayslipRelation(globalVar, ormasDal, errorMessage))
					return true;
			}
		}
		return false;
	}

	bool Payslip::Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cID, double previousValue, std::string& errorMessage)
	{
		CompanyAccountRelation cAccRel;
		CompanyEmployeeRelation cEmpRel;
		DivisionEmployeeRelation deRel;
		Division division;
		Balance balance;
		Balance tempBalance;
		Company company;
		Salary salary;
		User user;
		Role role;
		Subaccount sub;
		Account acc;
		if (!acc.GetAccountByNumber(globalVar, ormasDal, "22210", errorMessage))
		{
			return false;
		}
		if (!salary.GetSalaryByID(globalVar, ormasDal, sID, errorMessage))
		{
			if (errorMessage.empty())
				errorMessage = "Cannot find salary with this ID!";
			return false;
		}
		Payment payment;
		payment.SetUserID(salary.GetEmployeeID());
		std::string filter = payment.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 < balanceVector.size())
		{
			for each (auto item in balanceVector)
			{
				sub.Clear();
				tempBalance.Clear();
				if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
					return false;
				if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
				{
					if (sub.GetParentAccountID() == acc.GetID())
					{
						balance.SetSubaccountID(sub.GetID());
					}
				}
			}
		}
		else
		{
			return false;
		}
		if (balance.GetSubaccountID() <= 0)
			return false;
		if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
		{
			int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
			if (!user.GetUserByID(globalVar, ormasDal, salary.GetEmployeeID(), errorMessage))
				return false;
			if (!role.GetRoleByID(globalVar, ormasDal, user.GetRoleID(), errorMessage))
				return false;
			if (!deRel.GetDivisionEmployeeRelationByEmployeeID(globalVar, ormasDal, user.GetID(), errorMessage))
				return false;
			if (!division.GetDivisionByID(globalVar, ormasDal, deRel.GetDivisionID(), errorMessage))
				return false;
			int debAccID = 0;
			if (0 == division.GetCode().compare("RELEASE"))
			{
				debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55220", errorMessage);
			}
			else if (0 == division.GetCode().compare("ADMINISTRATION"))
			{
				debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "55310", errorMessage);
			}
			else if (0 == division.GetCode().compare("PRODUCTION"))
			{
				debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
			}
			int credAccID = balance.GetSubaccountID();
			if (0 == debAccID || 0 == credAccID || 0 == companyID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, previousValue, ormasDal.GetSystemDateTime(), errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	double Payslip::GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Payslip payslip;
		if (payslip.GetPayslipByID(globalVar, ormasDal, pID, errorMessage))
			return payslip.GetValue();
		return 0;
	}

	bool Payslip::CancelPayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cID, std::string& errorMessage)
	{
		CompanyAccountRelation cAccRel;
		CompanyEmployeeRelation cEmpRel;
		DivisionEmployeeRelation deRel;
		Division division;
		Balance balance;
		Balance tempBalance;
		Company company;
		Salary salary;
		User user;
		Role role;
		Subaccount sub;
		Account acc;
		if (!acc.GetAccountByNumber(globalVar, ormasDal, "22210", errorMessage))
		{
			return false;
		}
		if (!salary.GetSalaryByID(globalVar, ormasDal, sID, errorMessage))
		{
			if (errorMessage.empty())
				errorMessage = "Cannot find salary with this ID!";
			return false;
		}
		Payment payment;
		payment.SetUserID(salary.GetEmployeeID());
		std::string filter = payment.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 < balanceVector.size())
		{
			for each (auto item in balanceVector)
			{
				sub.Clear();
				tempBalance.Clear();
				if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
					return false;
				if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
				{
					if (sub.GetParentAccountID() == acc.GetID())
					{
						balance.SetSubaccountID(sub.GetID());
					}
				}
			}
		}
		else
		{
			return false;
		}
		if (balance.GetSubaccountID() <= 0)
			return false;
		if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
		{
			int companyID = company.GetCompanyID(globalVar, ormasDal, errorMessage);
			int debAccID = cAccRel.GetAccountIDByCompanyID(globalVar, ormasDal, companyID, "10730", errorMessage);
			int credAccID = balance.GetSubaccountID();
			if (0 == debAccID || 0 == credAccID || 0 == companyID)
			{
				return false;
			}
			if (this->CorrectingEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
				BalancePayslipRelation bpRelation;
				bpRelation.SetBalanceID(balance.GetID());
				bpRelation.SetPayslipID(this->id);
				if (bpRelation.DeleteBalancePayslipRelation(globalVar, ormasDal, errorMessage))
					return true;
			}
		}
		return false;
	}

	bool Payslip::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Операция начисление заработной платы"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool Payslip::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена начисление заработной платы, для коррекции"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage, true))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		entry.Clear();
		eoRelation.Clear();
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Операция начисление заработной платы"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool Payslip::CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена начисление заработной платы"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	std::string Payslip::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}