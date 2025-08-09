#include "stdafx.h"
#include "CurrencyRateClass.h"
#include <boost/algorithm/string.hpp>
#include "MulticurrencyClass.h"
#include "MulticurrencyViewClass.h"
#include "SubaccountClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "CompanyAccountRelationClass.h"
#include "CompanyClass.h"
#include "AccountClass.h"
#include <codecvt>

namespace BusinessLayer
{
	CurrencyRate::CurrencyRate(DataLayer::currenciesRateCollection curCollection)
	{
		id = std::get<0>(curCollection);
		fromCurrencyID = std::get<1>(curCollection);
		fromValue = std::get<2>(curCollection);
		toCurrencyID = std::get<3>(curCollection);
		toValue = std::get<4>(curCollection);
		changeDate = std::get<5>(curCollection);
	}

	int CurrencyRate::GetID()
	{
		return id;
	}

	int CurrencyRate::GetFromCurrencyID()
	{
		return fromCurrencyID;
	}

	std::string CurrencyRate::GetChangeDate()
	{
		return changeDate;
	}

	double CurrencyRate::GetFromValue()
	{
		return fromValue;
	}

	int CurrencyRate::GetToCurrencyID()
	{
		return toCurrencyID;
	}

	double CurrencyRate::GetToValue()
	{
		return toValue;
	}

	void CurrencyRate::SetID(int cID)
	{
		id = cID;
	}
	void CurrencyRate::SetFromCurrencyID(int fID)
	{
		fromCurrencyID = fID;
	}
	void CurrencyRate::SetFromValue(double fValue)
	{
		fromValue = fValue;
	}
	void CurrencyRate::SetChangeDate(std::string cDate)
	{
		if (!cDate.empty())
			boost::trim(cDate);
		changeDate = cDate;
	}
	void CurrencyRate::SetToCurrencyID(int tID)
	{
		toCurrencyID = tID;
	}
	void CurrencyRate::SetToValue(double tValue)
	{
		toValue = tValue;
	}

	bool CurrencyRate::CreateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fCurrID, double fValue,
		int tCurrID, double tValue, std::string cDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, fCurrID, fValue, tCurrID, tValue, cDate, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(cDate);
		fromCurrencyID = fCurrID;
		changeDate = boost::to_upper_copy(cDate);
		fromValue = fValue;
		toCurrencyID = tCurrID;
		toValue = tValue;
		if (0 != id && ormasDal.CreateCurrencyRate(id, fromCurrencyID, fromValue, toCurrencyID, toValue, changeDate, errorMessage))
		{
			if (RecalculateSubaccounts(globalVar, ormasDal, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CurrencyRate::CreateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateCurrencyRate(id, fromCurrencyID, fromValue, toCurrencyID, toValue, changeDate, errorMessage))
		{
			if (RecalculateSubaccounts(globalVar, ormasDal, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CurrencyRate::DeleteCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCurrencyRate(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}
	bool CurrencyRate::UpdateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fCurrID, double fValue,
		int tCurrID, double tValue, std::string cDate, std::string& errorMessage)
	{
		
		TrimStrings(cDate);
		fromCurrencyID = fCurrID;
		changeDate = boost::to_upper_copy(cDate);
		fromValue = fValue;
		toCurrencyID = tCurrID;
		toValue = tValue;
		if (0 != id && ormasDal.UpdateCurrencyRate(id, fromCurrencyID, fromValue, toCurrencyID, toValue, changeDate, errorMessage))
		{
			if (RecalculateSubaccounts(globalVar, ormasDal, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CurrencyRate::UpdateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateCurrencyRate(id, fromCurrencyID, fromValue, toCurrencyID, toValue, changeDate, errorMessage))
		{
			if (RecalculateSubaccounts(globalVar, ormasDal, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string CurrencyRate::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != fromCurrencyID || 0 != fromValue || 0 != toCurrencyID || 0 != toValue || !changeDate.empty())
		{
			return ormasDal.GetFilterForCurrencyRate(id, fromCurrencyID, fromValue, toCurrencyID, toValue, changeDate);
		}
		return "";
	}

	bool CurrencyRate::GetCurrencyRateByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesRateViewCollection> currencyRateVector = ormasDal.GetCurrenciesRate(errorMessage, filter);
		if (0 != currencyRateVector.size())
		{
			id = std::get<0>(currencyRateVector.at(0));
			fromCurrencyID = std::get<5>(currencyRateVector.at(0));
			fromValue = std::get<2>(currencyRateVector.at(0));
			toCurrencyID = std::get<6>(currencyRateVector.at(0));
			toValue = std::get<4>(currencyRateVector.at(0));
			changeDate = std::get<7>(currencyRateVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find currency rate with this id";
		}
		return false;
	}

	bool CurrencyRate::GetCurrencyRateByFromCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fcID, std::string& errorMessage)
	{
		if (fcID <= 0)
			return false;
		fromCurrencyID = fcID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesRateViewCollection> currencyRateVector = ormasDal.GetCurrenciesRate(errorMessage, filter);
		if (0 != currencyRateVector.size())
		{
			id = std::get<0>(currencyRateVector.at(0));
			fromCurrencyID = std::get<5>(currencyRateVector.at(0));
			fromValue = std::get<2>(currencyRateVector.at(0));
			toCurrencyID = std::get<6>(currencyRateVector.at(0));
			toValue = std::get<4>(currencyRateVector.at(0));
			changeDate = std::get<7>(currencyRateVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find currency rate with this id";
		}
		return false;
	}

	bool CurrencyRate::GetCurrencyRateByToCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tcID, std::string& errorMessage)
	{
		if (tcID <= 0)
			return false;
		toCurrencyID = tcID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesRateViewCollection> currencyRateVector = ormasDal.GetCurrenciesRate(errorMessage, filter);
		if (0 != currencyRateVector.size())
		{
			id = std::get<0>(currencyRateVector.at(0));
			fromCurrencyID = std::get<5>(currencyRateVector.at(0));
			fromValue = std::get<2>(currencyRateVector.at(0));
			toCurrencyID = std::get<6>(currencyRateVector.at(0));
			toValue = std::get<4>(currencyRateVector.at(0));
			changeDate = std::get<7>(currencyRateVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find currency rate with this id";
		}
		return false;
	}

	bool CurrencyRate::IsEmpty()
	{
		if (0 == id && 0 == fromCurrencyID && 0 == fromValue && 0 == toCurrencyID && 0 == toValue && changeDate.empty())
			return true;
		return false;
	}

	void CurrencyRate::Clear()
	{
		id = 0;
		fromCurrencyID = 0;
		fromValue = 0;
		toCurrencyID = 0;
		toValue = 0;
		changeDate.clear();
		
	}

	void CurrencyRate::TrimStrings(std::string& cDate)
	{
		if (!cDate.empty())
			boost::trim(cDate);
	}

	bool CurrencyRate::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fCurrID, double fValue,
		int tCurrID, double tValue, std::string cDate, std::string& errorMessage)
	{
		CurrencyRate currencyRate;
		currencyRate.Clear();
		errorMessage.clear();
		currencyRate.SetChangeDate(cDate);
		currencyRate.SetFromCurrencyID(fCurrID);
		currencyRate.SetFromValue(fValue);
		currencyRate.SetToCurrencyID(tCurrID);
		currencyRate.SetToValue(tValue);
		std::string filter = currencyRate.GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesRateViewCollection> currencyRateVector = ormasDal.GetCurrenciesRate(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == currencyRateVector.size())
		{
			return false;
		}
		errorMessage = "Currency rate with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool CurrencyRate::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		CurrencyRate currencyRate;
		currencyRate.Clear();
		errorMessage.clear();
		currencyRate.SetChangeDate(changeDate);
		currencyRate.SetFromCurrencyID(fromCurrencyID);
		currencyRate.SetFromValue(fromValue);
		currencyRate.SetToCurrencyID(toCurrencyID);
		currencyRate.SetToValue(toValue);
		std::string filter = currencyRate.GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesRateViewCollection> currencyRateVector = ormasDal.GetCurrenciesRate(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == currencyRateVector.size())
		{
			return false;
		}
		errorMessage = "Currency rate with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool CurrencyRate::RecalculateSubaccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Multicurrency multicurrency;
		Subaccount subaccount;
		Subaccount exchangeSub;
		Subaccount mainSub;
		std::vector<int> exchSubID = multicurrency.GetAllExchSubaccountID(globalVar, ormasDal, errorMessage);
		multicurrency.Clear();
		std::vector<int> mainSubID;
		std::vector<int> entryExchSubID;
		double value = 0;
		if (exchSubID.size() > 0)
		{
			std::string filter = "";
			filter = subaccount.GenerateINFilter(globalVar, ormasDal, exchSubID);
			subaccount.Clear();
			std::vector<DataLayer::subaccountsViewCollection> subaccountVector = ormasDal.GetSubaccounts(errorMessage, filter);
			if (0 != subaccountVector.size())
			{
				int acc66040ID = 0;
				int acc66140ID = 0;
				Account account;
				if (!account.GetAccountByNumber(globalVar, ormasDal, "66040", errorMessage))
					return false;
				acc66040ID = account.GetID();
				account.Clear();
				if (!account.GetAccountByNumber(globalVar, ormasDal, "66140", errorMessage))
					return false;
				acc66140ID = account.GetID();

				for each (auto item in subaccountVector)
				{
					if (fromCurrencyID == std::get<8>(item))
					{
						value = 0;
						exchangeSub.Clear();
						mainSub.Clear();
						multicurrency.Clear();
						if (!exchangeSub.GetSubaccountByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
							return false;
						if (!multicurrency.GetMulticurrencyBySubCurrencyID(globalVar, ormasDal, exchangeSub.GetID(), errorMessage))
							return false;
						if (!mainSub.GetSubaccountByID(globalVar, ormasDal, multicurrency.GetSubaccountMainCurrencyID(), errorMessage))
							return false;
						if (mainSub.GetCurrentBalance()<0)
						{
							
							value = std::round((mainSub.GetCurrentBalance() - toValue / fromValue*exchangeSub.GetCurrentBalance()) * 100) / 100;
						}
						else
						{
							value = std::round((mainSub.GetCurrentBalance() - toValue / fromValue*exchangeSub.GetCurrentBalance()) * 100) / 100;
						}
						
						if (value > 0)
						{
							if (!CreateEntry(globalVar, ormasDal, value, acc66140ID, mainSub.GetID(), errorMessage))
								return false;
						}
						else if (value < 0)
						{
							if (!CreateEntry(globalVar, ormasDal, value, mainSub.GetID(), acc66040ID, errorMessage))
								return false;
						}
					}
						
				}
				return true;
			}
		}
		else
		{
			return true;
		}
		return false;
	}

	bool CurrencyRate::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double value, int debSubID, int credSubID, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(ormasDal.GetSystemDateTime());
		entry.SetDebitingAccountID(debSubID);
		if (value < 0)
		{
			entry.SetValue(value*(-1));
		}
		else
		{
			entry.SetValue(value);
		}
		entry.SetCreditingAccountID(credSubID);
		std::string	entryText;
		if (value < 0)
		{
			entryText += wstring_to_utf8(L"Доходы от курсовых разниц, ID операции = ");
		}
		else
		{
			entryText += wstring_to_utf8(L"Убытки от курсовых разниц, ID операции =");
		}
		entryText += std::to_string(id);
		entry.SetDescription(entryText);
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

	std::string CurrencyRate::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}