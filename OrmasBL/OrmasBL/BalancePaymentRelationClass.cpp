#include "stdafx.h"
#include "BalancePaymentRelationClass.h"


namespace BusinessLayer{
	BalancePaymentRelation::BalancePaymentRelation(DataLayer::balancePaymentCollection bpCollection)
	{
		id = std::get<0>(bpCollection);
		balanceID = std::get<1>(bpCollection);
		paymentID = std::get<2>(bpCollection);
	}
	BalancePaymentRelation::BalancePaymentRelation()
	{
		id = 0;
		balanceID = 0;
		paymentID = 0;
	}
	
	int BalancePaymentRelation::GetID()
	{
		return id;
	}

	int BalancePaymentRelation::GetBalanceID()
	{
		return balanceID;
	}

	int BalancePaymentRelation::GetPaymentID()
	{
		return paymentID;
	}

	void BalancePaymentRelation::SetID(int bpID)
	{
		id = bpID;
	}
	void BalancePaymentRelation::SetBalanceID(int bID)
	{
		balanceID = bID;
	}
	void BalancePaymentRelation::SetPaymentID(int pID)
	{
		paymentID = pID;
	}
	
	bool BalancePaymentRelation::CreateBalancePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bID, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		balanceID = bID;
		paymentID = pID;

		if (ormasDal.CreateBalancePayment(id, balanceID, paymentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalancePaymentRelation::CreateBalancePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateBalancePayment(id, balanceID, paymentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalancePaymentRelation::DeleteBalancePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBalancePayment(balanceID, paymentID, errorMessage))
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

	

	std::string BalancePaymentRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != balanceID || 0 != paymentID)
		{
			return ormasDal.GetFilterForBalancePayment(id, balanceID, paymentID);
		}
		return "";
	}

	std::vector<int> BalancePaymentRelation::GetAllPaymentByBalanceID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> paymentIDVector;
		if (bID <= 0)
			return paymentIDVector;

	
		BalancePaymentRelation bpRelation;
		bpRelation.SetBalanceID(bID);
		bpRelation.SetPaymentID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePaymentCollection> balancePaymentVector = ormasDal.GetBalancePayment(errorMessage, filter);
		if (0 != balancePaymentVector.size())
		{
			for each (auto item in balancePaymentVector)
			{
				paymentIDVector.push_back(std::get<1>(item));
			}
		}
		return paymentIDVector;
	}

	std::vector<int> BalancePaymentRelation::GetAllBalanceByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> balanceIDVector;
		if (pID <= 0)
			return balanceIDVector;
		
		BalancePaymentRelation bpRelation;
		bpRelation.SetBalanceID(0);
		bpRelation.SetPaymentID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePaymentCollection> balancePaymentVector = ormasDal.GetBalancePayment(errorMessage, filter);
		if (0 != balancePaymentVector.size())
		{
			for each (auto item in balancePaymentVector)
			{
				balanceIDVector.push_back(std::get<0>(item));
			}
		}
		return balanceIDVector;
	}


	bool BalancePaymentRelation::IsEmpty()
	{
		if (0 == id && 0 == balanceID && 0 == paymentID)
			return true;
		return false;
	}

	void BalancePaymentRelation::Clear()
	{
		id = 0;
		balanceID = 0;
		paymentID = 0;
	}
	
	bool BalancePaymentRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		BalancePaymentRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(bID);
		bpRelation.SetPaymentID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePaymentCollection> balancePaymentVector = ormasDal.GetBalancePayment(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balancePaymentVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Payment Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool BalancePaymentRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		BalancePaymentRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(balanceID);
		bpRelation.SetPaymentID(paymentID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePaymentCollection> balancePaymentVector = ormasDal.GetBalancePayment(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balancePaymentVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Payment Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}