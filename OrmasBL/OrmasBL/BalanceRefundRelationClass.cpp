#include "stdafx.h"
#include "BalanceRefundRelationClass.h"


namespace BusinessLayer{
	BalanceRefundRelation::BalanceRefundRelation(DataLayer::balanceRefundCollection brCollection)
	{
		id = std::get<0>(brCollection);
		balanceID = std::get<1>(brCollection);
		refundID = std::get<2>(brCollection);
	}
	BalanceRefundRelation::BalanceRefundRelation()
	{
		id = 0;
		balanceID = 0;
		refundID = 0;
	}

	int BalanceRefundRelation::GetID()
	{
		return id;
	}

	int BalanceRefundRelation::GetBalanceID()
	{
		return balanceID;
	}

	int BalanceRefundRelation::GetRefundID()
	{
		return refundID;
	}

	void BalanceRefundRelation::SetID(int brID)
	{
		id = brID;
	}
	void BalanceRefundRelation::SetBalanceID(int bID)
	{
		balanceID = bID;
	}
	void BalanceRefundRelation::SetRefundID(int rID)
	{
		refundID = rID;
	}

	bool BalanceRefundRelation::CreateBalanceRefundRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int rID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bID, rID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		balanceID = bID;
		refundID = rID;

		if (ormasDal.CreateBalanceRefund(id, balanceID, refundID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalanceRefundRelation::CreateBalanceRefundRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateBalanceRefund(id, balanceID, refundID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalanceRefundRelation::DeleteBalanceRefundRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBalanceRefund(balanceID, refundID, errorMessage))
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



	std::string BalanceRefundRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != balanceID || 0 != refundID)
		{
			return ormasDal.GetFilterForBalanceRefund(id, balanceID, refundID);
		}
		return "";
	}

	std::vector<int> BalanceRefundRelation::GetAllRefundByBalanceID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> refundIDVector;
		if (bID <= 0)
			return refundIDVector;
		
		BalanceRefundRelation bpRelation;
		bpRelation.SetBalanceID(bID);
		bpRelation.SetRefundID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceRefundCollection> balanceRefundVector = ormasDal.GetBalanceRefund(errorMessage, filter);
		if (0 != balanceRefundVector.size())
		{
			for each (auto item in balanceRefundVector)
			{
				refundIDVector.push_back(std::get<1>(item));
			}
		}
		return refundIDVector;
	}

	std::vector<int> BalanceRefundRelation::GetAllBalanceByRefundID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		std::vector<int> balanceIDVector;
		if (rID <= 0)
			return balanceIDVector;
		
		BalanceRefundRelation bpRelation;
		bpRelation.SetBalanceID(0);
		bpRelation.SetRefundID(rID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceRefundCollection> balanceRefundVector = ormasDal.GetBalanceRefund(errorMessage, filter);
		if (0 != balanceRefundVector.size())
		{
			for each (auto item in balanceRefundVector)
			{
				balanceIDVector.push_back(std::get<0>(item));
			}
		}
		return balanceIDVector;
	}


	bool BalanceRefundRelation::IsEmpty()
	{
		if (0 == id && 0 == balanceID && 0 == refundID)
			return true;
		return false;
	}

	void BalanceRefundRelation::Clear()
	{
		id = 0;
		balanceID = 0;
		refundID = 0;
	}

	bool BalanceRefundRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int rID, std::string& errorMessage)
	{
		BalanceRefundRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(bID);
		bpRelation.SetRefundID(rID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceRefundCollection> balanceRefundVector = ormasDal.GetBalanceRefund(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balanceRefundVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Refund Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool BalanceRefundRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		BalanceRefundRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(balanceID);
		bpRelation.SetRefundID(refundID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balanceRefundCollection> balanceRefundVector = ormasDal.GetBalanceRefund(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balanceRefundVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Refund Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}