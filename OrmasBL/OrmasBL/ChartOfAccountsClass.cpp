#include "stdafx.h"
#include "ChartOfAccountsClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	ChartOfAccounts::ChartOfAccounts(DataLayer::chartOfAccountsCollection cCollection)
	{
		id = std::get<0>(cCollection);
		number = std::get<1>(cCollection);
		name = std::get<2>(cCollection);
		accountTypeID = std::get<3>(cCollection);
	}

	int ChartOfAccounts::GetID()
	{
		return id;
	}

	std::string ChartOfAccounts::GetNumber()
	{
		return number;
	}

	std::string ChartOfAccounts::GetName()
	{
		return name;
	}

	int ChartOfAccounts::GetAccountTypeID()
	{
		return accountTypeID;
	}

	void ChartOfAccounts::SetID(int cID)
	{
		id = cID;
	}

	void ChartOfAccounts::SetNumber(std::string cNumber)
	{
		if (!cNumber.empty())
			boost::trim(cNumber);
		number = cNumber;
	}

	void ChartOfAccounts::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}
	
	void ChartOfAccounts::SetAccountTypeID(int cAccountTypeID)
	{
		accountTypeID = cAccountTypeID;
	}

	bool ChartOfAccounts::CreateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string cName, int cAccountTypeID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, cNumber, cName, cAccountTypeID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(cNumber, cName);
		number = cNumber;
		name = cName;
		accountTypeID = cAccountTypeID;
		if (0 != id && ormasDal.CreateChartOfAccount(id, number, name, accountTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ChartOfAccounts::CreateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateChartOfAccount(id, number, name, accountTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ChartOfAccounts::DeleteChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteChartOfAccount(id, errorMessage))
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
	bool ChartOfAccounts::UpdateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string cName, int cAccountTypeID, std::string& errorMessage)
	{
		TrimStrings(cNumber, cName);
		number = cNumber;
		name = cName;
		accountTypeID = cAccountTypeID;
		if (0 != id && ormasDal.UpdateChartOfAccount(id, number, name, accountTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ChartOfAccounts::UpdateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateChartOfAccount(id, number, name, accountTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string ChartOfAccounts::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !number.empty() || 0 != accountTypeID)
		{
			return ormasDal.GetFilterForChartOfAccount(id, number, name, accountTypeID);
		}
		return "";
	}

	bool ChartOfAccounts::GetChartOfAccountsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountssVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
		if (0 != chartOfAccountssVector.size())
		{
			id = std::get<0>(chartOfAccountssVector.at(0));
			number = std::get<1>(chartOfAccountssVector.at(0));
			name = std::get<2>(chartOfAccountssVector.at(0));
			accountTypeID = std::get<4>(chartOfAccountssVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find chart of accounts with this id";
		}
		return false;
	}

	bool ChartOfAccounts::GetChartOfAccountsByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string& errorMessage)
	{
		if (cNumber.empty())
			return false;
		number = cNumber;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountssVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
		if (0 != chartOfAccountssVector.size())
		{
			id = std::get<0>(chartOfAccountssVector.at(0));
			number = std::get<1>(chartOfAccountssVector.at(0));
			name = std::get<2>(chartOfAccountssVector.at(0));
			accountTypeID = std::get<4>(chartOfAccountssVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find chart of accounts with this id";
		}
		return false;
	}

	bool ChartOfAccounts::IsEmpty()
	{
		if (0 == id && name == "" && number == "" && 0 == accountTypeID)
			return true;
		return false;
	}

	void ChartOfAccounts::Clear()
	{
		id = 0;
		number.clear();
		name.clear();
		accountTypeID = 0;
	}

	void ChartOfAccounts::TrimStrings(std::string& cNumber, std::string& cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cNumber.empty())
			boost::trim(cNumber);
	}

	bool ChartOfAccounts::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string cName, int cAccountTypeID, std::string& errorMessage)
	{
		ChartOfAccounts chartOfAccounts;
		chartOfAccounts.Clear();
		errorMessage.clear();
		chartOfAccounts.SetNumber(cNumber);
		chartOfAccounts.SetName(cName);
		chartOfAccounts.SetAccountTypeID(cAccountTypeID);
		std::string filter = chartOfAccounts.GenerateFilter(ormasDal);
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountssVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == chartOfAccountssVector.size())
		{
			return false;
		}
		errorMessage = "Chart of accounts with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ChartOfAccounts::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ChartOfAccounts chartOfAccounts;
		chartOfAccounts.Clear();
		errorMessage.clear();
		chartOfAccounts.SetNumber(number);
		chartOfAccounts.SetName(name);
		chartOfAccounts.SetAccountTypeID(accountTypeID);
		std::string filter = chartOfAccounts.GenerateFilter(ormasDal);
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountssVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == chartOfAccountssVector.size())
		{
			return false;
		}
		errorMessage = "Chart of accounts with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}