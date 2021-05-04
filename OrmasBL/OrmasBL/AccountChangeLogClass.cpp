#include "stdafx.h"
#include "AccountChangeLogClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AccountChangeLog::AccountChangeLog(DataLayer::accountChangeLogCollection aCollection)
	{
		id = std::get<0>(aCollection);
		accountID = std::get<1>(aCollection);
		number = std::get<2>(aCollection);
		startBalance = std::get<3>(aCollection);
		currentBalance = std::get<4>(aCollection);
		logDate = std::get<5>(aCollection);
		userID = std::get<6>(aCollection);
		operationID = std::get<7>(aCollection);
	}
	AccountChangeLog::AccountChangeLog()
	{
		id = 0;
		accountID = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
		logDate = "";
		userID = 0;
		operationID = 0;
	}

	int AccountChangeLog::GetID()
	{
		return id;
	}

	int AccountChangeLog::GetAccountID()
	{
		return accountID;
	}

	std::string AccountChangeLog::GetNumber()
	{
		return number;
	}

	double AccountChangeLog::GetStartBalance()
	{
		return startBalance;
	}

	double AccountChangeLog::GetCurrentBalance()
	{
		return currentBalance;
	}

	std::string AccountChangeLog::GetLogDate()
	{
		return logDate;
	}

	int AccountChangeLog::GetUserID()
	{
		return userID;
	}

	int AccountChangeLog::GetOperationID()
	{
		return operationID;
	}

	void AccountChangeLog::SetID(int ahID)
	{
		id = ahID;
	}

	void AccountChangeLog::SetAccountID(int aID)
	{
		accountID = aID;
	}

	void AccountChangeLog::SetNumber(std::string aNumber)
	{
		number = aNumber;
	}

	void AccountChangeLog::SetStartBalance(double aStartBalance)
	{
		startBalance = aStartBalance;
	}

	void AccountChangeLog::SetCurrentBalance(double aCurrentBalance)
	{
		currentBalance = aCurrentBalance;
	}

	void AccountChangeLog::SetLogDate(std::string aLogDate)
	{
		logDate = aLogDate;
	}

	void AccountChangeLog::SetUserID(int aUserID)
	{
		userID = aUserID;
	}

	void AccountChangeLog::SetOperationID(int aOperationID)
	{
		operationID = aOperationID;
	}



	bool AccountChangeLog::CreateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
		double aCurrentBalance, std::string aLogDate, int aUserID, int aOperationID, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, aID, aNumber, aStartBalance, aCurrentBalance, aLogDate, aUserID, aOperationID, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		accountID = aID;
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		logDate = aLogDate;
		userID = aUserID;
		operationID = aOperationID;
		if (0 != id && ormasDal.CreateAccountChangeLog(id, accountID, number, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountChangeLog::CreateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
		//return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateAccountChangeLog(id, accountID, number, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountChangeLog::DeleteAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountChangeLog(id, errorMessage))
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

	bool AccountChangeLog::UpdateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
		double aCurrentBalance, std::string aLogDate, int aUserID, int aOperationID, std::string& errorMessage)
	{
		accountID = aID;
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		logDate = aLogDate;
		userID = aUserID;
		operationID = aOperationID;
		if (0 != id && ormasDal.UpdateAccountChangeLog(id, accountID, number, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountChangeLog::UpdateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateAccountChangeLog(id, accountID, number, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string AccountChangeLog::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountID || !number.empty() || 0.0 != startBalance || 0.0 != currentBalance || !logDate.empty() || 0 != userID || 0 != operationID)
		{
			return ormasDal.GetFilterForAccountChangeLog(id, accountID, number, startBalance, currentBalance, logDate, userID, operationID);
		}
		return "";
	}

	bool AccountChangeLog::GetAccountChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountChangeLogCollection> accountChangeLogVector = ormasDal.GetAccountChangeLog(errorMessage, filter);
		if (0 != accountChangeLogVector.size())
		{
			id = std::get<0>(accountChangeLogVector.at(0));
			accountID = std::get<1>(accountChangeLogVector.at(0));
			number = std::get<2>(accountChangeLogVector.at(0));
			startBalance = std::get<3>(accountChangeLogVector.at(0));
			currentBalance = std::get<4>(accountChangeLogVector.at(0));
			logDate = std::get<5>(accountChangeLogVector.at(0));
			userID = std::get<6>(accountChangeLogVector.at(0));
			operationID = std::get<7>(accountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Account history with this id";
		}
		return false;
	}

	bool AccountChangeLog::GetAccountChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aUserID, std::string& errorMessage)
	{
		if (aUserID <= 0)
			return false;
		userID = aUserID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountChangeLogCollection> accountChangeLogVector = ormasDal.GetAccountChangeLog(errorMessage, filter);
		if (0 != accountChangeLogVector.size())
		{
			id = std::get<0>(accountChangeLogVector.at(0));
			accountID = std::get<1>(accountChangeLogVector.at(0));
			number = std::get<2>(accountChangeLogVector.at(0));
			startBalance = std::get<3>(accountChangeLogVector.at(0));
			currentBalance = std::get<4>(accountChangeLogVector.at(0));
			logDate = std::get<5>(accountChangeLogVector.at(0));
			userID = std::get<6>(accountChangeLogVector.at(0));
			operationID = std::get<7>(accountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Account history with this id";
		}
		return false;
	}

	bool AccountChangeLog::GetAccountChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aOperaionID, std::string& errorMessage)
	{
		if (aOperaionID <= 0)
			return false;
		operationID = aOperaionID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountChangeLogCollection> accountChangeLogVector = ormasDal.GetAccountChangeLog(errorMessage, filter);
		if (0 != accountChangeLogVector.size())
		{
			id = std::get<0>(accountChangeLogVector.at(0));
			accountID = std::get<1>(accountChangeLogVector.at(0));
			number = std::get<2>(accountChangeLogVector.at(0));
			startBalance = std::get<3>(accountChangeLogVector.at(0));
			currentBalance = std::get<4>(accountChangeLogVector.at(0));
			logDate = std::get<5>(accountChangeLogVector.at(0));
			userID = std::get<6>(accountChangeLogVector.at(0));
			operationID = std::get<7>(accountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Account history with this id";
		}
		return false;
	}

	bool AccountChangeLog::GetAccountChangeLogByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aAccountID, std::string& errorMessage)
	{
		if (aAccountID <= 0)
			return false;
		accountID = aAccountID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountChangeLogCollection> accountChangeLogVector = ormasDal.GetAccountChangeLog(errorMessage, filter);
		if (0 != accountChangeLogVector.size())
		{
			id = std::get<0>(accountChangeLogVector.at(0));
			accountID = std::get<1>(accountChangeLogVector.at(0));
			number = std::get<2>(accountChangeLogVector.at(0));
			startBalance = std::get<3>(accountChangeLogVector.at(0));
			currentBalance = std::get<4>(accountChangeLogVector.at(0));
			logDate = std::get<5>(accountChangeLogVector.at(0));
			userID = std::get<6>(accountChangeLogVector.at(0));
			operationID = std::get<7>(accountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find AccountChangeLog with this id";
		}
		return false;
	}

	bool AccountChangeLog::IsEmpty()
	{
		if (0 == id && 0 == accountID && number.empty() && 0.0 == startBalance && 0.0 == currentBalance && logDate.empty()
			&& 0 == userID && 0 == operationID)
			return true;
		return false;
	}

	void AccountChangeLog::Clear()
	{
		id = 0;
		accountID = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
		logDate = "";
		userID = 0;
		operationID = 0;
	}

	bool AccountChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
		double aCurrentBalance, std::string aLogDate, int aUserID, int aOperationID, std::string& errorMessage)
	{
		AccountChangeLog accountChangeLog;
		accountChangeLog.Clear();
		errorMessage.clear();
		accountChangeLog.SetAccountID(aID);
		accountChangeLog.SetNumber(aNumber);
		accountChangeLog.SetCurrentBalance(aCurrentBalance);
		accountChangeLog.SetStartBalance(aStartBalance);
		accountChangeLog.SetLogDate(aLogDate);
		accountChangeLog.SetUserID(aUserID);
		accountChangeLog.SetOperationID(aOperationID);
		std::string filter = accountChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountChangeLogCollection> accountChangeLogVector = ormasDal.GetAccountChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Account change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountChangeLog accountChangeLog;
		accountChangeLog.Clear();
		errorMessage.clear();
		accountChangeLog.SetAccountID(id);
		accountChangeLog.SetNumber(number);
		accountChangeLog.SetCurrentBalance(currentBalance);
		accountChangeLog.SetStartBalance(startBalance);
		accountChangeLog.SetLogDate(logDate);
		accountChangeLog.SetUserID(userID);
		accountChangeLog.SetOperationID(operationID);
		std::string filter = accountChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountChangeLogCollection> accountChangeLogVector = ormasDal.GetAccountChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Account change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}