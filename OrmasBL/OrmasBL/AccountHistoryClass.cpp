#include "stdafx.h"
#include "AccountHistoryClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AccountHistory::AccountHistory(DataLayer::accountHistoryCollection aCollection)
	{
		id = std::get<0>(aCollection);
		accountID = std::get<1>(aCollection);
		number = std::get<2>(aCollection);
		startBalance = std::get<3>(aCollection);
		currentBalance = std::get<4>(aCollection);
		fromDate = std::get<5>(aCollection);
		tillDate = std::get<6>(aCollection);
	}
	AccountHistory::AccountHistory()
	{
		id = 0;
		accountID = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
		fromDate = "";
		tillDate = ""; 
	}

	int AccountHistory::GetID()
	{
		return id;
	}

	int AccountHistory::GetAccountID()
	{
		return accountID;
	}

	std::string AccountHistory::GetNumber()
	{
		return number;
	}

	double AccountHistory::GetStartBalance()
	{
		return startBalance;
	}

	double AccountHistory::GetCurrentBalance()
	{
		return currentBalance;
	}

	std::string AccountHistory::GetFromDate()
	{
		return fromDate;
	}

	std::string AccountHistory::GetTillDate()
	{
		return tillDate;
	}

	void AccountHistory::SetID(int ahID)
	{
		id = ahID;
	}

	void AccountHistory::SetAccountID(int aID)
	{
		accountID = aID;
	}

	void AccountHistory::SetNumber(std::string aNumber)
	{
		number = aNumber;
	}

	void AccountHistory::SetStartBalance(double aStartBalance)
	{
		startBalance = aStartBalance;
	}

	void AccountHistory::SetCurrentBalance(double aCurrentBalance)
	{
		currentBalance = aCurrentBalance;
	}

	void AccountHistory::SetFromDate(std::string aFromDate)
	{
		fromDate = aFromDate;
	}

	void AccountHistory::SetTillDate(std::string aTillDate)
	{
		tillDate = aTillDate;
	}

	bool AccountHistory::CreateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
		double aCurrentBalance, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aID, aFromDate, aTillDate, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		accountID = aID;
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		fromDate = aFromDate;
		tillDate = aTillDate;
		if (0 != id && ormasDal.CreateAccountHistory(id, accountID, number, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountHistory::CreateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateAccountHistory(id, accountID, number, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountHistory::DeleteAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountHistory(id, errorMessage))
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

	bool AccountHistory::UpdateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
		double aCurrentBalance, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		accountID = aID;
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		fromDate = aFromDate;
		tillDate = aTillDate;
		if (0 != id && ormasDal.UpdateAccountHistory(id, accountID, number, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountHistory::UpdateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateAccountHistory(id, accountID, number, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string AccountHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountID || !number.empty() || 0.0 != startBalance || 0.0 != currentBalance || !fromDate.empty() || !tillDate.empty())
		{
			return ormasDal.GetFilterForAccountHistory(id, accountID, number, startBalance, currentBalance, fromDate, tillDate);
		}
		return "";
	}

	bool AccountHistory::GetAccountHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountHistoryCollection> accountHistoryVector = ormasDal.GetAccountHistory(errorMessage, filter);
		if (0 != accountHistoryVector.size())
		{
			id = std::get<0>(accountHistoryVector.at(0));
			accountID = std::get<1>(accountHistoryVector.at(0));
			number = std::get<2>(accountHistoryVector.at(0));
			startBalance = std::get<3>(accountHistoryVector.at(0));
			currentBalance = std::get<4>(accountHistoryVector.at(0));
			fromDate = std::get<5>(accountHistoryVector.at(0));
			tillDate = std::get<6>(accountHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Account history with this id";
		}
		return false;
	}

	bool AccountHistory::GetAccountHistoryByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aAccountID, std::string& errorMessage)
	{
		if (aAccountID <= 0)
			return false;
		accountID = aAccountID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountHistoryCollection> accountHistoryVector = ormasDal.GetAccountHistory(errorMessage, filter);
		if (0 != accountHistoryVector.size())
		{
			id = std::get<0>(accountHistoryVector.at(0));
			accountID = std::get<1>(accountHistoryVector.at(0));
			number = std::get<2>(accountHistoryVector.at(0));
			startBalance = std::get<3>(accountHistoryVector.at(0));
			currentBalance = std::get<4>(accountHistoryVector.at(0));
			fromDate = std::get<5>(accountHistoryVector.at(0));
			tillDate = std::get<6>(accountHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find AccountHistory with this id";
		}
		return false;
	}

	bool AccountHistory::IsEmpty()
	{
		if (0 == id && 0 == accountID && number.empty() && 0.0 == startBalance && 0.0 == currentBalance && fromDate.empty()
			&& tillDate.empty())
			return true;
		return false;
	}

	void AccountHistory::Clear()
	{
		id = 0;
		accountID = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
		fromDate = "";
		tillDate = "";
	}

	bool AccountHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		AccountHistory accountHistory;
		accountHistory.Clear();
		errorMessage.clear();
		accountHistory.SetAccountID(aID);
		accountHistory.SetFromDate(aFromDate);
		accountHistory.SetTillDate(aTillDate);
		std::string filter = accountHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountHistoryCollection> accountHistoryVector = ormasDal.GetAccountHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Account history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountHistory accountHistory;
		accountHistory.Clear();
		errorMessage.clear();
		accountHistory.SetAccountID(id);
		accountHistory.SetFromDate(fromDate);
		accountHistory.SetTillDate(tillDate);
		std::string filter = accountHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountHistoryCollection> accountHistoryVector = ormasDal.GetAccountHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Account history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}