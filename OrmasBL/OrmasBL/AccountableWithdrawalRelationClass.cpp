#include "stdafx.h"
#include "AccountableWithdrawalRelationClass.h"


namespace BusinessLayer{
	AccountableWithdrawalRelation::AccountableWithdrawalRelation(DataLayer::accountableWithdrawalCollection bpCollection)
	{
		id = std::get<0>(bpCollection);
		accountableDocumentID = std::get<1>(bpCollection);
		withdrawalID = std::get<2>(bpCollection);
	}
	AccountableWithdrawalRelation::AccountableWithdrawalRelation()
	{
		id = 0;
		accountableDocumentID = 0;
		withdrawalID = 0;
	}

	int AccountableWithdrawalRelation::GetID()
	{
		return id;
	}

	int AccountableWithdrawalRelation::GetAccountableDocumentID()
	{
		return accountableDocumentID;
	}

	int AccountableWithdrawalRelation::GetWithdrawalID()
	{
		return withdrawalID;
	}

	void AccountableWithdrawalRelation::SetID(int bpID)
	{
		id = bpID;
	}
	void AccountableWithdrawalRelation::SetAccountableDocumentID(int bID)
	{
		accountableDocumentID = bID;
	}
	void AccountableWithdrawalRelation::SetWithdrawalID(int pID)
	{
		withdrawalID = pID;
	}

	bool AccountableWithdrawalRelation::CreateAccountableWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bID, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		accountableDocumentID = bID;
		withdrawalID = pID;

		if (ormasDal.CreateAccountableWithdrawal(id, accountableDocumentID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableWithdrawalRelation::CreateAccountableWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccountableWithdrawal(id, accountableDocumentID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableWithdrawalRelation::DeleteAccountableWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountableWithdrawal(id, errorMessage))
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
	bool AccountableWithdrawalRelation::DeleteAccountableWithdrawalRelationByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountableWithdrawalByDocumentID(accountableDocumentID, errorMessage))
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


	std::string AccountableWithdrawalRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountableDocumentID || 0 != withdrawalID)
		{
			return ormasDal.GetFilterForAccountableWithdrawal(id, accountableDocumentID, withdrawalID);
		}
		return "";
	}

	bool AccountableWithdrawalRelation::GetAccountableWithdrawalByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
		if (0 != accountableWithdrawalVector.size())
		{
			id = std::get<0>(accountableWithdrawalVector.at(0));
			accountableDocumentID = std::get<1>(accountableWithdrawalVector.at(0));
			withdrawalID = std::get<2>(accountableWithdrawalVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable Withdrawal with this id";
		}
		return false;
	}

	std::vector<int> AccountableWithdrawalRelation::GetAllWithdrawalByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> WithdrawalIDVector;
		AccountableWithdrawalRelation bpRelation;
		bpRelation.SetAccountableDocumentID(bID);
		bpRelation.SetWithdrawalID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
		if (0 != accountableWithdrawalVector.size())
		{
			for each (auto item in accountableWithdrawalVector)
			{
				WithdrawalIDVector.push_back(std::get<0>(item));
			}
		}
		return WithdrawalIDVector;
	}

	std::vector<int> AccountableWithdrawalRelation::GetAllAccountableByWithdrawalID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> accountableDocumentIDVector;
		AccountableWithdrawalRelation bpRelation;
		bpRelation.SetAccountableDocumentID(0);
		bpRelation.SetWithdrawalID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
		if (0 != accountableWithdrawalVector.size())
		{
			for each (auto item in accountableWithdrawalVector)
			{
				accountableDocumentIDVector.push_back(std::get<0>(item));
			}
		}
		return accountableDocumentIDVector;
	}


	bool AccountableWithdrawalRelation::IsEmpty()
	{
		if (0 == id && 0 == accountableDocumentID && 0 == withdrawalID)
			return true;
		return false;
	}

	void AccountableWithdrawalRelation::Clear()
	{
		id = 0;
		accountableDocumentID = 0;
		withdrawalID = 0;
	}

	bool AccountableWithdrawalRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		AccountableWithdrawalRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetAccountableDocumentID(bID);
		bpRelation.SetWithdrawalID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableWithdrawalVector.size())
		{
			return false;
		}
		errorMessage = "Accountable-Withdrawal Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableWithdrawalRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableWithdrawalRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetAccountableDocumentID(accountableDocumentID);
		bpRelation.SetWithdrawalID(withdrawalID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableWithdrawalVector.size())
		{
			return false;
		}
		errorMessage = "Accountable-Withdrawal Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}