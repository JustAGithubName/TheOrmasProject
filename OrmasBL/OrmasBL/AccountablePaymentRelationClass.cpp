#include "stdafx.h"
#include "AccountablePaymentRelationClass.h"


namespace BusinessLayer{
	AccountablePaymentRelation::AccountablePaymentRelation(DataLayer::accountablePaymentCollection bpCollection)
	{
		id = std::get<0>(bpCollection);
		accountableDocumentID = std::get<1>(bpCollection);
		paymentID = std::get<2>(bpCollection);
	}
	AccountablePaymentRelation::AccountablePaymentRelation()
	{
		id = 0;
		accountableDocumentID = 0;
		paymentID = 0;
	}

	int AccountablePaymentRelation::GetID()
	{
		return id;
	}

	int AccountablePaymentRelation::GetAccountableDocumentID()
	{
		return accountableDocumentID;
	}

	int AccountablePaymentRelation::GetPaymentID()
	{
		return paymentID;
	}

	void AccountablePaymentRelation::SetID(int bpID)
	{
		id = bpID;
	}
	void AccountablePaymentRelation::SetAccountableDocumentID(int bID)
	{
		accountableDocumentID = bID;
	}
	void AccountablePaymentRelation::SetPaymentID(int pID)
	{
		paymentID = pID;
	}

	bool AccountablePaymentRelation::CreateAccountablePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bID, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		accountableDocumentID = bID;
		paymentID = pID;

		if (ormasDal.CreateAccountablePayment(id, accountableDocumentID, paymentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountablePaymentRelation::CreateAccountablePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccountablePayment(id, accountableDocumentID, paymentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountablePaymentRelation::DeleteAccountablePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountablePayment(id, errorMessage))
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
	bool AccountablePaymentRelation::DeleteAccountablePaymentRelationByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountablePaymentByDocumentID(accountableDocumentID, errorMessage))
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


	std::string AccountablePaymentRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountableDocumentID || 0 != paymentID)
		{
			return ormasDal.GetFilterForAccountablePayment(id, accountableDocumentID, paymentID);
		}
		return "";
	}

	bool AccountablePaymentRelation::GetAccountablePaymentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountablePaymentCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
		if (0 != accountablePaymentVector.size())
		{
			id = std::get<0>(accountablePaymentVector.at(0));
			accountableDocumentID = std::get<1>(accountablePaymentVector.at(0));
			paymentID = std::get<2>(accountablePaymentVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable payment with this id";
		}
		return false;
	}

	std::vector<int> AccountablePaymentRelation::GetAllPaymentByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> paymentIDVector;
		AccountablePaymentRelation bpRelation;
		bpRelation.SetAccountableDocumentID(bID);
		bpRelation.SetPaymentID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountablePaymentCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
		if (0 != accountablePaymentVector.size())
		{
			for each (auto item in accountablePaymentVector)
			{
				paymentIDVector.push_back(std::get<0>(item));
			}
		}
		return paymentIDVector;
	}

	std::vector<int> AccountablePaymentRelation::GetAllAccountableByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> accountableDocumentIDVector;
		AccountablePaymentRelation bpRelation;
		bpRelation.SetAccountableDocumentID(0);
		bpRelation.SetPaymentID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountablePaymentCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
		if (0 != accountablePaymentVector.size())
		{
			for each (auto item in accountablePaymentVector)
			{
				accountableDocumentIDVector.push_back(std::get<0>(item));
			}
		}
		return accountableDocumentIDVector;
	}


	bool AccountablePaymentRelation::IsEmpty()
	{
		if (0 == id && 0 == accountableDocumentID && 0 == paymentID)
			return true;
		return false;
	}

	void AccountablePaymentRelation::Clear()
	{
		id = 0;
		accountableDocumentID = 0;
		paymentID = 0;
	}

	bool AccountablePaymentRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		AccountablePaymentRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetAccountableDocumentID(bID);
		bpRelation.SetPaymentID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountablePaymentCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountablePaymentVector.size())
		{
			return false;
		}
		errorMessage = "Accountable-Payment Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountablePaymentRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountablePaymentRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetAccountableDocumentID(accountableDocumentID);
		bpRelation.SetPaymentID(paymentID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountablePaymentCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountablePaymentVector.size())
		{
			return false;
		}
		errorMessage = "Accountable-Payment Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}