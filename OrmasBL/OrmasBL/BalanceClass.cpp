#include "stdafx.h"
#include "BalanceClass.h"
#include "EmployeeClass.h"

namespace BusinessLayer{
	Balance::Balance(DataLayer::balancesCollection balCollection)
	{
		id = std::get<0>(balCollection);
		userID = std::get<1>(balCollection);
		subaccountID = std::get<2>(balCollection);
	}
	Balance::Balance()
	{
		userID = 0;
		subaccountID = 0;
	}
	int Balance::GetID()
	{
		return id;
	}

	int Balance::GetUserID()
	{
		return userID;
	}

	int Balance::GetSubaccountID()
	{
		return subaccountID;
	}

	void Balance::SetID(int cID)
	{
		id = cID;
	}
	void Balance::SetUserID(int uID)
	{
		userID = uID;
	}
	void Balance::SetSubaccountID(int cID)
	{
		subaccountID = cID;
	}

	bool Balance::CreateBalance(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID,  int saID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (IsDuplicate(globalVar, ormasDal, uID, saID, errorMessage))
			return false;
		userID = uID;
		subaccountID = saID;

		if (0 != id && ormasDal.CreateBalance(id, userID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Balance::CreateBalance(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateBalance(id, userID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Balance::DeleteBalance(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBalance(id, errorMessage))
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

	bool Balance::UpdateBalance(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int aID, std::string& errorMessage)
	{
		userID = uID;
		subaccountID = aID;
		if (0 != id && ormasDal.UpdateBalance(id, userID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Balance::UpdateBalance(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateBalance(id, userID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Balance::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != userID || 0 != subaccountID)
		{
			return ormasDal.GetFilterForBalance(id, userID, subaccountID);
		}
		return "";
	}

	bool Balance::GetBalanceByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 != balanceVector.size())
		{
			id = std::get<0>(balanceVector.at(0));
			userID = std::get<6>(balanceVector.at(0));
			subaccountID = std::get<7>(balanceVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find balance with this id";
		}
		return false;
	}

	bool Balance::GetBalanceByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		userID = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 != balanceVector.size())
		{
			id = std::get<0>(balanceVector.at(0));
			userID = std::get<6>(balanceVector.at(0));
			subaccountID = std::get<7>(balanceVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find balance with this user id";
		}
		return false;
	}

	std::vector<int> Balance::GetSubaccountIDlistByUserIDList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> cID, std::string& errorMessage)
	{
		std::vector<int> subaccID;
		if (cID.size()<=0)
			return subaccID;
		Employee employee;
		std::string filterClient = employee.GenerateINFilter(globalVar, ormasDal, cID);
		std::string filter = GenerateFilter(ormasDal);
		std::vector<std::string> filterList;
		filterList.push_back(filterClient);
		filterList.push_back(filter);
		filter = ormasDal.ConcatenateFilters(filterList);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 != balanceVector.size())
		{
			subaccID.push_back(std::get<7>(balanceVector.at(0)));
		}
		return subaccID;
	}

	bool Balance::GetBalanceBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		subaccountID = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (0 != balanceVector.size())
		{
			id = std::get<0>(balanceVector.at(0));
			userID = std::get<6>(balanceVector.at(0));
			subaccountID = std::get<7>(balanceVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find balance with this user id";
		}
		return false;
	}

	bool Balance::IsEmpty()
	{
		if (0 == id && 0 == userID && 0 == subaccountID)
			return true;
		return false;
	}

	void Balance::Clear()
	{
		id = 0;
		userID = 0;
		subaccountID = 0;
	}

	bool Balance::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int aID, std::string& errorMessage)
	{
		Balance balance;
		balance.Clear();
		errorMessage.clear();
		balance.SetUserID(uID);
		balance.SetSubaccountID(aID);
		std::string filter = balance.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balanceVector.size())
		{
			return false;
		}
		errorMessage = "User already have account with this currency! Please avoid the duplication!";
		return true;
	}

	bool Balance::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Balance balance;
		balance.Clear();
		errorMessage.clear();
		balance.SetUserID(userID);
		balance.SetSubaccountID(subaccountID);
		std::string filter = balance.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balanceVector.size())
		{
			return false;
		}
		errorMessage = "User already have account with this currency! Please avoid the duplication!";
		return true;
	}
}