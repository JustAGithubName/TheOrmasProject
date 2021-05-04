#include "stdafx.h"
#include "SubaccountChangeLogClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	SubaccountChangeLog::SubaccountChangeLog(DataLayer::subaccountChangeLogCollection aCollection)
	{
		id = std::get<0>(aCollection);
		subaccountID = std::get<1>(aCollection);
		startBalance = std::get<2>(aCollection);
		currentBalance = std::get<3>(aCollection);
		logDate = std::get<4>(aCollection);
		userID = std::get<5>(aCollection);
		operationID = std::get<6>(aCollection);
	}
	SubaccountChangeLog::SubaccountChangeLog()
	{
		id = 0;
		subaccountID = 0;
		startBalance = 0.0;
		currentBalance = 0.0;
		logDate = "";
		userID = 0;
		operationID = 0;
	}

	int SubaccountChangeLog::GetID()
	{
		return id;
	}

	int SubaccountChangeLog::GetSubaccountID()
	{
		return subaccountID;
	}

	double SubaccountChangeLog::GetStartBalance()
	{
		return startBalance;
	}

	double SubaccountChangeLog::GetCurrentBalance()
	{
		return currentBalance;
	}

	std::string SubaccountChangeLog::GetLogDate()
	{
		return logDate;
	}

	int SubaccountChangeLog::GetUserID()
	{
		return userID;
	}

	int SubaccountChangeLog::GetOperationID()
	{
		return operationID;
	}
	void SubaccountChangeLog::SetID(int ahID)
	{
		id = ahID;
	}

	void SubaccountChangeLog::SetSubaccountID(int sID)
	{
		subaccountID = sID;
	}

	void SubaccountChangeLog::SetStartBalance(double aStartBalance)
	{
		startBalance = aStartBalance;
	}

	void SubaccountChangeLog::SetCurrentBalance(double aCurrentBalance)
	{
		currentBalance = aCurrentBalance;
	}

	void SubaccountChangeLog::SetLogDate(std::string aLogDate)
	{
		logDate = aLogDate;
	}

	void SubaccountChangeLog::SetUserID(int sUserID)
	{
		userID = sUserID;
	}
	
	void SubaccountChangeLog::SetOperationID(int sOperationID)
	{
		operationID = sOperationID;
	}

	bool SubaccountChangeLog::CreateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
		double saCurrentBalance, std::string saLogDate, int sUserID, int sOperationID, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, saID, saStartBalance, saCurrentBalance, saLogDate, sUserID, sOperationID, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		subaccountID = saID;
		startBalance = saStartBalance;
		currentBalance = saCurrentBalance;
		logDate = saLogDate;
		userID = sUserID;
		operationID = sOperationID;
		if (0 != id && ormasDal.CreateSubaccountChangeLog(id, subaccountID, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountChangeLog::CreateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
//return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateSubaccountChangeLog(id, subaccountID, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountChangeLog::DeleteSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSubaccountChangeLog(id, errorMessage))
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

	bool SubaccountChangeLog::UpdateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
		double saCurrentBalance, std::string saLogDate, int sUserID, int sOperationID, std::string& errorMessage)
	{
		subaccountID = saID;
		startBalance = saStartBalance;
		currentBalance = saCurrentBalance;
		logDate = saLogDate;
		userID = sUserID;
		operationID = sOperationID;
		if (0 != id && ormasDal.UpdateSubaccountChangeLog(id, subaccountID, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountChangeLog::UpdateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateSubaccountChangeLog(id, subaccountID, startBalance, currentBalance, logDate, userID, operationID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string SubaccountChangeLog::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountID || 0.0 != startBalance || 0.0 != currentBalance || !logDate.empty() || 0!= userID || 0!=operationID)
		{
			return ormasDal.GetFilterForSubaccountChangeLog(id, subaccountID, startBalance, currentBalance, logDate, userID, operationID);
		}
		return "";
	}

	std::string SubaccountChangeLog::GenerateFilterForPeriod(DataLayer::OrmasDal& ormasDal, std::string fromDate, std::string tillDate)
	{
		if (0 != id || 0 != subaccountID || 0.0 != startBalance || 0.0 != currentBalance || !logDate.empty() || 0 != userID || 0 != operationID || !fromDate.empty()
			|| !tillDate.empty())
		{
			return ormasDal.GetFilterForSubaccountChangeLogForPeriod(id, subaccountID, startBalance, currentBalance, logDate, userID, operationID, fromDate, tillDate);
		}
		return "";
	}

	bool SubaccountChangeLog::GetSubaccountChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountChangeLogCollection> subaccountChangeLogVector = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		if (0 != subaccountChangeLogVector.size())
		{
			id = std::get<0>(subaccountChangeLogVector.at(0));
			subaccountID = std::get<1>(subaccountChangeLogVector.at(0));
			startBalance = std::get<2>(subaccountChangeLogVector.at(0));
			currentBalance = std::get<3>(subaccountChangeLogVector.at(0));
			logDate = std::get<4>(subaccountChangeLogVector.at(0));
			userID = std::get<5>(subaccountChangeLogVector.at(0));
			operationID = std::get<6>(subaccountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount change log with this id";
		}
		return false;
	}

	bool SubaccountChangeLog::GetSubaccountChangeLogBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aSubaccountID, std::string& errorMessage)
	{
		if (aSubaccountID <= 0)
			return false;
		subaccountID = aSubaccountID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountChangeLogCollection> subaccountChangeLogVector = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		if (0 != subaccountChangeLogVector.size())
		{
			id = std::get<0>(subaccountChangeLogVector.at(0));
			subaccountID = std::get<1>(subaccountChangeLogVector.at(0));
			startBalance = std::get<2>(subaccountChangeLogVector.at(0));
			currentBalance = std::get<3>(subaccountChangeLogVector.at(0));
			logDate = std::get<4>(subaccountChangeLogVector.at(0));
			userID = std::get<5>(subaccountChangeLogVector.at(0));
			operationID = std::get<6>(subaccountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount ChangeLog with this id";
		}
		return false;
	}

	bool SubaccountChangeLog::GetSubaccountChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aUserID, std::string& errorMessage)
	{
		if (aUserID <= 0)
			return false;
		userID = aUserID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountChangeLogCollection> subaccountChangeLogVector = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		if (0 != subaccountChangeLogVector.size())
		{
			id = std::get<0>(subaccountChangeLogVector.at(0));
			subaccountID = std::get<1>(subaccountChangeLogVector.at(0));
			startBalance = std::get<2>(subaccountChangeLogVector.at(0));
			currentBalance = std::get<3>(subaccountChangeLogVector.at(0));
			logDate = std::get<4>(subaccountChangeLogVector.at(0));
			userID = std::get<5>(subaccountChangeLogVector.at(0));
			operationID = std::get<6>(subaccountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount ChangeLog with this id";
		}
		return false;
	}

	bool SubaccountChangeLog::GetSubaccountChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aOperationID, std::string& errorMessage)
	{
		if (aOperationID <= 0)
			return false;
		operationID = aOperationID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountChangeLogCollection> subaccountChangeLogVector = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		if (0 != subaccountChangeLogVector.size())
		{
			id = std::get<0>(subaccountChangeLogVector.at(0));
			subaccountID = std::get<1>(subaccountChangeLogVector.at(0));
			startBalance = std::get<2>(subaccountChangeLogVector.at(0));
			currentBalance = std::get<3>(subaccountChangeLogVector.at(0));
			logDate = std::get<4>(subaccountChangeLogVector.at(0));
			userID = std::get<5>(subaccountChangeLogVector.at(0));
			operationID = std::get<6>(subaccountChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount ChangeLog with this id";
		}
		return false;
	}

	bool SubaccountChangeLog::IsEmpty()
	{
		if (0 == id && 0 == subaccountID && 0.0 == startBalance && 0.0 == currentBalance && logDate.empty()
			&& 0 == userID && 0== operationID)
			return true;
		return false;
	}

	void SubaccountChangeLog::Clear()
	{
		id = 0;
		subaccountID = 0;
		startBalance = 0.0;
		currentBalance = 0.0;
		logDate = "";
		userID = 0;
		operationID = 0;
	}

	bool SubaccountChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
		double saCurrentBalance, std::string saLogDate, int sUserID, int sOperationID, std::string& errorMessage)
	{
		SubaccountChangeLog subaccountChangeLog;
		subaccountChangeLog.Clear();
		errorMessage.clear();
		subaccountChangeLog.SetSubaccountID(saID);
		subaccountChangeLog.SetStartBalance(saStartBalance);
		subaccountChangeLog.SetCurrentBalance(saCurrentBalance);
		subaccountChangeLog.SetLogDate(saLogDate);
		subaccountChangeLog.SetUserID(sUserID);
		subaccountChangeLog.SetOperationID(sOperationID);
		std::string filter = subaccountChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountChangeLogCollection> subaccountChangeLogVector = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool SubaccountChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		SubaccountChangeLog subaccountChangeLog;
		subaccountChangeLog.Clear();
		errorMessage.clear();
		subaccountChangeLog.SetSubaccountID(subaccountID);
		subaccountChangeLog.SetStartBalance(startBalance);
		subaccountChangeLog.SetCurrentBalance(currentBalance);
		subaccountChangeLog.SetLogDate(logDate);
		subaccountChangeLog.SetUserID(userID);
		subaccountChangeLog.SetOperationID(operationID);
		std::string filter = subaccountChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountChangeLogCollection> subaccountChangeLogVector = ormasDal.GetSubaccountChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}