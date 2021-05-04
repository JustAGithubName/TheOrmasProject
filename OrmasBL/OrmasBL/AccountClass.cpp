#include "stdafx.h"
#include "AccountClass.h"
#include "SubaccountClass.h"
#include "ChartOfAccountsClass.h"
#include "AccountTypeClass.h"
#include "AccountChangeLogClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Account::Account(DataLayer::accountsCollection aCollection)
	{
		id = std::get<0>(aCollection);
		number = std::get<1>(aCollection);
		startBalance = std::get<2>(aCollection);
		currentBalance = std::get<3>(aCollection);
	}
	Account::Account()
	{
		id = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
	}

	int Account::GetID()
	{
		return id;
	}

	std::string Account::GetNumber()
	{
		return number;
	}

	double Account::GetStartBalance()
	{
		return startBalance;
	}

	double Account::GetCurrentBalance()
	{
		return currentBalance;
	}

	void Account::SetID(int aID)
	{
		id = aID;
	}

	void Account::SetNumber(std::string aNumber)
	{
		number = aNumber;
	}

	void Account::SetStartBalance(double aStartBalance)
	{
		startBalance = aStartBalance;
	}

	void Account::SetCurrentBalance(double aCurrentBalance)
	{
		currentBalance = aCurrentBalance;
	}

	bool Account::CreateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aNumber, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		if (0 != id && ormasDal.CreateAccount(id, number, startBalance, currentBalance, errorMessage))
		{
			if (CreateAccountChangeLog(globalVar, ormasDal, id, number, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Account::CreateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccount(id, number, startBalance, currentBalance, errorMessage))
		{
			if (CreateAccountChangeLog(globalVar, ormasDal, id, number, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Account::DeleteAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccount(id, errorMessage))
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

	bool Account::UpdateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string& errorMessage)
	{
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		if (0 != id && ormasDal.UpdateAccount(id, number, startBalance, currentBalance, errorMessage))
		{
			if (CreateAccountChangeLog(globalVar, ormasDal, id, number, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Account::UpdateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateAccount(id, number, startBalance, currentBalance, errorMessage))
		{
			if (CreateAccountChangeLog(globalVar, ormasDal, id, number, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Account::GenerateLikeFilterForNumber(DataLayer::OrmasDal& ormasDal)
	{
		if (!number.empty())
		{
			return ormasDal.GetLikeFilterForAccountNumber(number);
		}
		return "";
	}

	std::string Account::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !number.empty() || 0.0 != startBalance || 0.0 != currentBalance)
		{
			return ormasDal.GetFilterForAccount(id, number, startBalance, currentBalance);
		}
		return "";
	}

	bool Account::GetAccountByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage, filter);
		if (0 != accountVector.size())
		{
			id = std::get<0>(accountVector.at(0));
			number = std::get<1>(accountVector.at(0));
			startBalance = std::get<2>(accountVector.at(0));
			currentBalance = std::get<3>(accountVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find account with this id";
		}
		return false;
	}

	bool Account::GetAccountByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage)
	{
		if (aNumber.empty())
			return false;
		number = aNumber;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage, filter);
		if (0 != accountVector.size())
		{
			id = std::get<0>(accountVector.at(0));
			number = std::get<1>(accountVector.at(0));
			startBalance = std::get<2>(accountVector.at(0));
			currentBalance = std::get<3>(accountVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find account with this id";
		}
		return false;
	}

	std::vector<int> Account::GetChildAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::vector<int> childID;
		if (0 == id)
			return childID;
		std::string filter = GenerateLikeFilterForNumber(ormasDal);
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage, filter);
		if (0 != accountVector.size())
		{
			for each (auto item in accountVector)
			{
				childID.push_back(std::get<0>(item));
			}
			
		}
		return childID;
	}

	bool Account::IsEmpty()
	{
		if (0 == id && number.empty() && 0.0 == startBalance && 0.0 == currentBalance)
			return true;
		return false;
	}

	bool Account::HaveSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int accountID)
	{
		id = accountID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage, filter);
		if (0 != accountVector.size())
		{
			id = std::get<0>(accountVector.at(0));
			number = std::get<1>(accountVector.at(0));
			startBalance = std::get<2>(accountVector.at(0));
			currentBalance = std::get<3>(accountVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find account with this id";
			return true;
		}
		if (number.substr(3,2).compare("00") == 0)
		{
			std::string accountRootNumber = number.substr(0, 3);
			if (!ormasDal.HaveChildAccount(accountRootNumber))
			{
				return false;
			}
		}
		Subaccount subaccount;
		subaccount.SetParentAccountID(accountID);
		std::string subFilter = subaccount.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountsViewCollection> subaccountVector = ormasDal.GetSubaccounts(errorMessage, subFilter);
		if (0 == subaccountVector.size())
		{
			return false;
		}
		return true;
	}

	void Account::Clear()
	{
		id = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
	}

	bool Account::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage)
	{
		Account account;
		account.Clear();
		errorMessage.clear();
		account.SetNumber(aNumber);
		std::string filter = account.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountVector.size())
		{
			return false;
		}
		errorMessage = "Account with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Account::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Account account;
		account.Clear();
		errorMessage.clear();
		account.SetNumber(number);
		std::string filter = account.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountVector.size())
		{
			return false;
		}
		errorMessage = "Account with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string Account::GetName(DataLayer::OrmasDal& ormasDal)
	{
		ChartOfAccounts chartOfAccounts;
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountssVector;
		if (!this->GetNumber().empty() && this->GetNumber().length() > 0)
		{
			std::string numberOfAccount = this->GetNumber().substr(0, 5);
			chartOfAccounts.SetNumber(numberOfAccount);
			std::string filter = chartOfAccounts.GenerateFilter(ormasDal);
			chartOfAccountssVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
			if (0 < chartOfAccountssVector.size())
			{
				return std::get<2>(chartOfAccountssVector.at(0));
			}
		}
		return "";
	}

	bool Account::AccountOperationValidation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double aValue)
	{
		/*AccountType atype;
		if (atype.GetAccountTypeByNumber(globalVar, ormasDal, GetAccountTypeNumber(ormasDal), errorMessage))
		{
			if (0 == atype.GetName().compare("ACTIVE"))
			{
				if (aValue > 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			if (0 == atype.GetName().compare("PASSIVE"))
			{
				if (aValue < 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			if (0 == atype.GetName().compare("ACTIVE/PASSIVE"))
			{
				return true;
			}
		}*/
		return true;
	}

	void Account::BalanceShortInfo(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double &active, double &passive, std::string& errorMessage)
	{
		std::vector<DataLayer::accountsCollection> accountVector = ormasDal.GetAccounts(errorMessage);
		if (0 != accountVector.size())
		{
			double curBalance = 0;
			std::string number = "";
			for each (auto item in accountVector)
			{
				curBalance = 0;
				number = "";
				curBalance = std::get<3>(item);
				number = std::get<1>(item);
				if (0 == number.substr(3, 2).compare("00"))
				{
					if (curBalance > 0)
					{
						active += curBalance;
					}
					else
					{
						passive += curBalance;
					}
				}
			}
		}
		else
		{
			errorMessage = "Cannot calculate balance!";
		}
	}

	bool Account::CreateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int accountID, std::string aNumber,
		double aStartBalance, double aCurrentBalance, std::string& errorMessage)
	{
		AccountChangeLog acLog;
		acLog.SetAccountID(accountID);
		acLog.SetNumber(aNumber);
		acLog.SetStartBalance(aStartBalance);
		acLog.SetCurrentBalance(aCurrentBalance);
		acLog.SetLogDate(ormasDal.GetSystemDateTime());
		acLog.SetUserID(globalVar->userID);
		acLog.SetOperationID(globalVar->currentOperationID);
		if (acLog.CreateAccountChangeLog(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}
}