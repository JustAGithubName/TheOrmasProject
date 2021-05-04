#include "stdafx.h"
#include "CurrencyClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	Currency::Currency(DataLayer::currenciesCollection curCollection)
	{
		id = std::get<0>(curCollection);
		code = std::get<1>(curCollection);
		shortName = std::get<2>(curCollection);
		name = std::get<3>(curCollection);
		unit = std::get<4>(curCollection);
		mainTrade = std::get<5>(curCollection);
	}
	
	int Currency::GetID()
	{
		return id;
	}

	int Currency::GetCode()
	{
		return code;
	}

	std::string Currency::GetShortName()
	{
		return shortName;
	}

	std::string Currency::GetName()
	{
		return name;
	}

	int Currency::GetUnit()
	{
		return unit;
	}

	bool Currency::GetMainTrade()
	{
		return mainTrade;
	}

	void Currency::SetID(int cID)
	{
		id = cID;
	}
	void Currency::SetCode(int cCode)
	{
		code = cCode;
	}
	void Currency::SetShortName(std::string cShortName)
	{
		if (!cShortName.empty())
			boost::trim(cShortName);
		shortName = boost::to_upper_copy(cShortName);
	}
	void Currency::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}
	void Currency::SetUnit(int cUnit)
	{
		unit = cUnit;
	}
	void Currency::SetMainTrade(bool cMainTrade)
	{
		mainTrade = cMainTrade;
	}

	bool Currency::CreateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cCode, std::string cShortName, std::string cName, int cUnit,
		bool cMainTrade, std::string& errorMessage)
	{
		if (0 < GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage) && cMainTrade == true)
		{
			errorMessage = "System already have the main trade currency! Please delete or update it first, \
						   						   before adding a new currency which will be a main trade currency!";
			return false;
		}
		if (IsDuplicate(globalVar, ormasDal, cShortName, cName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(cShortName, cName);
		code = cCode;
		shortName = boost::to_upper_copy(cShortName);
		name = cName;
		unit = cUnit;
		mainTrade = cMainTrade;
		if (0 != id && ormasDal.CreateCurrency(id, code, shortName, name, unit, mainTrade, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Currency::CreateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 < GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage) && mainTrade == true)
		{
			errorMessage = "System already have the main trade currency! Please delete or update it first, \
						   						   before adding a new currency which will be a main trade currency!";
			return false;
		}
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateCurrency(id, code, shortName, name, unit, mainTrade, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Currency::DeleteCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCurrency(id, errorMessage))
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
	bool Currency::UpdateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cCode, std::string cShortName, std::string cName, int cUnit,
		bool cMainTrade, std::string& errorMessage)
	{
		int mainTradeID = 0;
		mainTradeID = GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (mainTradeID != id)
		{
			if (0 < mainTradeID && cMainTrade == true)
			{
				errorMessage = "System already have the main trade currency! Please delete or update it first, \
							   						   	before adding a new currency which will be a main trade currency!";
				return false;
			}
		}
		TrimStrings(cShortName, cName);
		code = cCode;
		shortName = boost::to_upper_copy(cShortName);
		name = cName;
		unit = cUnit;
		mainTrade = cMainTrade;
		if (0 != id && ormasDal.UpdateCurrency(id, code, shortName, name, unit, mainTrade, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Currency::UpdateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		int mainTradeID = 0;
		mainTradeID = GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (mainTradeID != id)
		{
			if (0 < mainTradeID && mainTrade == true)
			{
				errorMessage = "System already have the main trade currency! Please delete or update it first, \
							   							 before adding a new currency which will be a main trade currency!";
				return false;
			}
		}
		if (0 != id && ormasDal.UpdateCurrency(id, code, shortName, name, unit, mainTrade, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	
	std::string Currency::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != code || !name.empty() || !shortName.empty())
		{
			return ormasDal.GetFilterForCurrency(id, code, shortName, name, unit, mainTrade);
		}
		return "";
	}

	bool Currency::GetCurrencyByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesCollection> currencyVector = ormasDal.GetCurrencies(errorMessage, filter);
		if (0 != currencyVector.size())
		{
			id = std::get<0>(currencyVector.at(0));
			code = std::get<1>(currencyVector.at(0));
			shortName = std::get<2>(currencyVector.at(0));
			name = std::get<3>(currencyVector.at(0));
			unit = std::get<4>(currencyVector.at(0));
			mainTrade = std::get<5>(currencyVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find currency with this id";
		}
		return false;
	}
	
	bool Currency::IsEmpty()
	{
		if (0 == id && 0 == code && shortName == "" &&	name == "" && 0 == unit && mainTrade == false)
			return true;
		return false;
	}

	void Currency::Clear()
	{
		id = 0;
		code = 0;
		shortName.clear();
		name.clear();
		unit = 0;
		mainTrade = false;
	}

	void Currency::TrimStrings(std::string& cShortName, std::string& cName)
	{
		if (!cShortName.empty())
			boost::trim(cShortName);
		if (!cName.empty())
			boost::trim(cName);
	}

	bool Currency::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cShortName, std::string cName, std::string& errorMessage)
	{
		Currency currency;
		currency.Clear();
		errorMessage.clear();
		currency.SetShortName(cShortName);
		currency.SetName(cName);
		std::string filter = currency.GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesCollection> currencyVector = ormasDal.GetCurrencies(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == currencyVector.size())
		{
			return false;
		}
		errorMessage = "Currency with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Currency::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Currency currency;
		currency.Clear();
		errorMessage.clear();
		currency.SetShortName(shortName);
		currency.SetName(name);
		std::string filter = currency.GenerateFilter(ormasDal);
		std::vector<DataLayer::currenciesCollection> currencyVector = ormasDal.GetCurrencies(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == currencyVector.size())
		{
			return false;
		}
		errorMessage = "Currency with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	int Currency::GetMainTradeCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::vector<DataLayer::currenciesCollection> currencyVector = ormasDal.GetCurrencies(errorMessage);
		if (0 != currencyVector.size())
		{
			for each (auto item in currencyVector)
			{
				if (std::get<5>(item))
					return std::get<0>(item);
			}
		}
		return 0;
	}
}