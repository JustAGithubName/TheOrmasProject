#include "stdafx.h"
#include "SubaccountHistoryClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	SubaccountHistory::SubaccountHistory(DataLayer::subaccountHistoryCollection aCollection)
	{
		id = std::get<0>(aCollection);
		subaccountID = std::get<1>(aCollection);
		startBalance = std::get<2>(aCollection);
		currentBalance = std::get<3>(aCollection);
		fromDate = std::get<4>(aCollection);
		tillDate = std::get<5>(aCollection);
	}
	SubaccountHistory::SubaccountHistory()
	{
		id = 0;
		subaccountID = 0;
		startBalance = 0.0;
		currentBalance = 0.0;
		fromDate = "";
		tillDate = "";
	}

	int SubaccountHistory::GetID()
	{
		return id;
	}

	int SubaccountHistory::GetSubaccountID()
	{
		return subaccountID;
	}

	double SubaccountHistory::GetStartBalance()
	{
		return startBalance;
	}

	double SubaccountHistory::GetCurrentBalance()
	{
		return currentBalance;
	}

	std::string SubaccountHistory::GetFromDate()
	{
		return fromDate;
	}

	std::string SubaccountHistory::GetTillDate()
	{
		return tillDate;
	}

	void SubaccountHistory::SetID(int ahID)
	{
		id = ahID;
	}

	void SubaccountHistory::SetSubaccountID(int sID)
	{
		subaccountID = sID;
	}

	void SubaccountHistory::SetStartBalance(double aStartBalance)
	{
		startBalance = aStartBalance;
	}

	void SubaccountHistory::SetCurrentBalance(double aCurrentBalance)
	{
		currentBalance = aCurrentBalance;
	}

	void SubaccountHistory::SetFromDate(std::string aFromDate)
	{
		fromDate = aFromDate;
	}

	void SubaccountHistory::SetTillDate(std::string aTillDate)
	{
		tillDate = aTillDate;
	}

	bool SubaccountHistory::CreateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, double aStartBalance,
		double aCurrentBalance, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aID, aFromDate, aTillDate, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		subaccountID = aID;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		fromDate = aFromDate;
		tillDate = aTillDate;
		if (0 != id && ormasDal.CreateSubaccountHistory(id, subaccountID, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountHistory::CreateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateSubaccountHistory(id, subaccountID, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountHistory::DeleteSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSubaccountHistory(id, errorMessage))
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

	bool SubaccountHistory::UpdateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, double aStartBalance,
		double aCurrentBalance, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		subaccountID = aID;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		fromDate = aFromDate;
		tillDate = aTillDate;
		if (0 != id && ormasDal.UpdateSubaccountHistory(id, subaccountID, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountHistory::UpdateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateSubaccountHistory(id, subaccountID, startBalance, currentBalance, fromDate, tillDate, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string SubaccountHistory::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountID || 0.0 != startBalance || 0.0 != currentBalance || !fromDate.empty() || !tillDate.empty())
		{
			return ormasDal.GetFilterForSubaccountHistory(id, subaccountID, startBalance, currentBalance, fromDate, tillDate);
		}
		return "";
	}

	bool SubaccountHistory::GetSubaccountHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountHistoryCollection> subaccountHistoryVector = ormasDal.GetSubaccountHistory(errorMessage, filter);
		if (0 != subaccountHistoryVector.size())
		{
			id = std::get<0>(subaccountHistoryVector.at(0));
			subaccountID = std::get<1>(subaccountHistoryVector.at(0));
			startBalance = std::get<2>(subaccountHistoryVector.at(0));
			currentBalance = std::get<3>(subaccountHistoryVector.at(0));
			fromDate = std::get<4>(subaccountHistoryVector.at(0));
			tillDate = std::get<5>(subaccountHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount history with this id";
		}
		return false;
	}

	bool SubaccountHistory::GetSubaccountHistoryBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aSubaccountID, std::string& errorMessage)
	{
		if (aSubaccountID <= 0)
			return false;
		subaccountID = aSubaccountID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountHistoryCollection> subaccountHistoryVector = ormasDal.GetSubaccountHistory(errorMessage, filter);
		if (0 != subaccountHistoryVector.size())
		{
			id = std::get<0>(subaccountHistoryVector.at(0));
			subaccountID = std::get<1>(subaccountHistoryVector.at(0));
			startBalance = std::get<2>(subaccountHistoryVector.at(0));
			currentBalance = std::get<3>(subaccountHistoryVector.at(0));
			fromDate = std::get<4>(subaccountHistoryVector.at(0));
			tillDate = std::get<5>(subaccountHistoryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount history with this id";
		}
		return false;
	}

	bool SubaccountHistory::IsEmpty()
	{
		if (0 == id && 0 == subaccountID && 0.0 == startBalance && 0.0 == currentBalance && fromDate.empty()
			&& tillDate.empty())
			return true;
		return false;
	}

	void SubaccountHistory::Clear()
	{
		id = 0;
		subaccountID = 0;
		startBalance = 0.0;
		currentBalance = 0.0;
		fromDate = "";
		tillDate = "";
	}

	bool SubaccountHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aFromDate, std::string aTillDate, std::string& errorMessage)
	{
		SubaccountHistory subaccountHistory;
		subaccountHistory.Clear();
		errorMessage.clear();
		subaccountHistory.SetSubaccountID(aID);
		subaccountHistory.SetFromDate(aFromDate);
		subaccountHistory.SetTillDate(aTillDate);
		std::string filter = subaccountHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountHistoryCollection> subaccountHistoryVector = ormasDal.GetSubaccountHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool SubaccountHistory::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		SubaccountHistory subaccountHistory;
		subaccountHistory.Clear();
		errorMessage.clear();
		subaccountHistory.SetSubaccountID(id);
		subaccountHistory.SetFromDate(fromDate);
		subaccountHistory.SetTillDate(tillDate);
		std::string filter = subaccountHistory.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountHistoryCollection> subaccountHistoryVector = ormasDal.GetSubaccountHistory(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountHistoryVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount history with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}