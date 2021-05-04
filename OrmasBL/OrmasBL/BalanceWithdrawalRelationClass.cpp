#include "stdafx.h"
#include "BalanceWithdrawalRelationClass.h"


namespace BusinessLayer{
	BalanceWithdrawalRelation::BalanceWithdrawalRelation(DataLayer::balanceWithdrawalCollection bwCollection)
	{
		id = std::get<0>(bwCollection);
		balanceID = std::get<1>(bwCollection);
		withdrawalID = std::get<2>(bwCollection);
	}
	BalanceWithdrawalRelation::BalanceWithdrawalRelation()
	{
		id = 0;
		balanceID = 0;
		withdrawalID = 0;
	}

	int BalanceWithdrawalRelation::GetID()
	{
		return id;
	}

	int BalanceWithdrawalRelation::GetBalanceID()
	{
		return balanceID;
	}

	int BalanceWithdrawalRelation::GetWithdrawalID()
	{
		return withdrawalID;
	}

	void BalanceWithdrawalRelation::SetID(int bwID)
	{
		id = bwID;
	}
	void BalanceWithdrawalRelation::SetBalanceID(int bID)
	{
		balanceID = bID;
	}
	void BalanceWithdrawalRelation::SetWithdrawalID(int wID)
	{
		withdrawalID = wID;
	}

	bool BalanceWithdrawalRelation::CreateBalanceWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int wID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bID, wID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		balanceID = bID;
		withdrawalID = wID;

		if (ormasDal.CreateBalanceWithdrawal(id, balanceID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalanceWithdrawalRelation::CreateBalanceWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateBalanceWithdrawal(id, balanceID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalanceWithdrawalRelation::DeleteBalanceWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBalanceWithdrawal(balanceID, withdrawalID, errorMessage))
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



	std::string BalanceWithdrawalRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if ( 0 != id || 0 != balanceID || 0 != withdrawalID)
		{
			return ormasDal.GetFilterForBalanceWithdrawal(id, balanceID, withdrawalID);
		}
		return "";
	}

	std::vector<int> BalanceWithdrawalRelation::GetAllWithdrawalByBalanceID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> refundIDVector;
		if (bID <= 0)
			return refundIDVector;
		std::vector<int> withdrawalIDVector;
		BalanceWithdrawalRelation bpRelation;
		bpRelation.SetBalanceID(bID);
		bpRelation.SetWithdrawalID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceWithdrawalCollection> balanceWithdrawalVector = ormasDal.GetBalanceWithdrawal(errorMessage, filter);
		if (0 != balanceWithdrawalVector.size())
		{
			for each (auto item in balanceWithdrawalVector)
			{
				withdrawalIDVector.push_back(std::get<1>(item));
			}
		}
		return withdrawalIDVector;
	}

	std::vector<int> BalanceWithdrawalRelation::GetAllBalanceByWithdrawalID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{

		std::vector<int> balanceIDVector;
		if (wID <= 0)
			return balanceIDVector;
	
		BalanceWithdrawalRelation bpRelation;
		bpRelation.SetBalanceID(0);
		bpRelation.SetWithdrawalID(wID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceWithdrawalCollection> balanceWithdrawalVector = ormasDal.GetBalanceWithdrawal(errorMessage, filter);
		if (0 != balanceWithdrawalVector.size())
		{
			for each (auto item in balanceWithdrawalVector)
			{
				balanceIDVector.push_back(std::get<0>(item));
			}
		}
		return balanceIDVector;
	}


	bool BalanceWithdrawalRelation::IsEmpty()
	{
		if (0 == id && 0 == balanceID && 0 == withdrawalID)
			return true;
		return false;
	}

	void BalanceWithdrawalRelation::Clear()
	{
		id = 0;
		balanceID = 0;
		withdrawalID = 0;
	}


	bool BalanceWithdrawalRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		BalanceWithdrawalRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(bID);
		bpRelation.SetWithdrawalID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceWithdrawalCollection> balanceWithdrawalVector = ormasDal.GetBalanceWithdrawal(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balanceWithdrawalVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Withdrawal Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool BalanceWithdrawalRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		BalanceWithdrawalRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(balanceID);
		bpRelation.SetWithdrawalID(withdrawalID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceWithdrawalCollection> balanceWithdrawalVector = ormasDal.GetBalanceWithdrawal(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balanceWithdrawalVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Withdrawal Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}