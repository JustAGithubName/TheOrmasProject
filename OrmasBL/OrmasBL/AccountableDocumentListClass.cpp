#include "stdafx.h"
#include "AccountableDocumentListClass.h"


namespace BusinessLayer{
	AccountableDocumentListRelation::AccountableDocumentListRelation(DataLayer::accountableDocumentListCollection bpCollection)
	{
		id = std::get<0>(bpCollection);
		accountableDocumentID = std::get<1>(bpCollection);
		expenseDocumentID = std::get<2>(bpCollection);
	}
	AccountableDocumentListRelation::AccountableDocumentListRelation()
	{
		id = 0;
		accountableDocumentID = 0;
		expenseDocumentID = 0;
	}

	int AccountableDocumentListRelation::GetID()
	{
		return id;
	}

	int AccountableDocumentListRelation::GetAccountableDocumentID()
	{
		return accountableDocumentID;
	}

	int AccountableDocumentListRelation::GetExpenseDocumentID()
	{
		return expenseDocumentID;
	}

	void AccountableDocumentListRelation::SetID(int bpID)
	{
		id = bpID;
	}
	void AccountableDocumentListRelation::SetAccountableDocumentID(int bID)
	{
		accountableDocumentID = bID;
	}
	void AccountableDocumentListRelation::SetExpenseDocumentID(int pID)
	{
		expenseDocumentID = pID;
	}

	bool AccountableDocumentListRelation::CreateAccountableDocumentListRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, int edID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, adID, edID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		accountableDocumentID = adID;
		expenseDocumentID = edID;

		if (ormasDal.CreateAccountableDocumentList(id, accountableDocumentID, expenseDocumentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableDocumentListRelation::CreateAccountableDocumentListRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccountableDocumentList(id, accountableDocumentID, expenseDocumentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableDocumentListRelation::DeleteAccountableDocumentListRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountableDocumentList(id, errorMessage))
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
	bool AccountableDocumentListRelation::DeleteAccountableDocumentListRelationByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountableDocumentListByDocumentID(accountableDocumentID, errorMessage))
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


	std::string AccountableDocumentListRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountableDocumentID || 0 != expenseDocumentID)
		{
			return ormasDal.GetFilterForAccountableDocumentList(id, accountableDocumentID, expenseDocumentID);
		}
		return "";
	}

	bool AccountableDocumentListRelation::GetDocumentListByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, std::string& errorMessage)
	{
		if (adID <= 0)
			return false;
		accountableDocumentID = adID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableListVector = ormasDal.GetAccountableDocumentList(errorMessage, filter);
		if (0 != accountableListVector.size())
		{
			id = std::get<0>(accountableListVector.at(0));
			accountableDocumentID = std::get<1>(accountableListVector.at(0));
			expenseDocumentID = std::get<2>(accountableListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable List with this id";
		}
		return false;
	}

	bool AccountableDocumentListRelation::GetDocumentListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableListVector = ormasDal.GetAccountableDocumentList(errorMessage, filter);
		if (0 != accountableListVector.size())
		{
			id = std::get<0>(accountableListVector.at(0));
			accountableDocumentID = std::get<1>(accountableListVector.at(0));
			expenseDocumentID = std::get<2>(accountableListVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable List with this id";
		}
		return false;
	}

	std::vector<int> AccountableDocumentListRelation::GetAllListByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, std::string& errorMessage)
	{
		std::vector<int> listIDVector;
		AccountableDocumentListRelation adlRelation;
		adlRelation.SetAccountableDocumentID(adID);
		adlRelation.SetExpenseDocumentID(0);
		std::string filter = adlRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableDocumentListVector = ormasDal.GetAccountableDocumentList(errorMessage, filter);
		if (0 != accountableDocumentListVector.size())
		{
			for each (auto item in accountableDocumentListVector)
			{
				listIDVector.push_back(std::get<0>(item));
			}
		}
		return listIDVector;
	}

	std::vector<int> AccountableDocumentListRelation::GetAllListByExpenseDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int edID, std::string& errorMessage)
	{
		std::vector<int> listIDVector;
		AccountableDocumentListRelation adlRelation;
		adlRelation.SetAccountableDocumentID(0);
		adlRelation.SetExpenseDocumentID(edID);
		std::string filter = adlRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableDocumentListVector = ormasDal.GetAccountableDocumentList(errorMessage, filter);
		if (0 != accountableDocumentListVector.size())
		{
			for each (auto item in accountableDocumentListVector)
			{
				listIDVector.push_back(std::get<0>(item));
			}
		}
		return listIDVector;
	}


	bool AccountableDocumentListRelation::IsEmpty()
	{
		if (0 == id && 0 == accountableDocumentID && 0 == expenseDocumentID)
			return true;
		return false;
	}

	void AccountableDocumentListRelation::Clear()
	{
		id = 0;
		accountableDocumentID = 0;
		expenseDocumentID = 0;
	}

	bool AccountableDocumentListRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, int edID, std::string& errorMessage)
	{
		AccountableDocumentListRelation adlRelation;
		adlRelation.Clear();
		errorMessage.clear();
		adlRelation.SetAccountableDocumentID(adID);
		adlRelation.SetExpenseDocumentID(edID);
		std::string filter = adlRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableDocumentListVector = ormasDal.GetAccountableDocumentList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableDocumentListVector.size())
		{
			return false;
		}
		errorMessage = "Accountable document list Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableDocumentListRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableDocumentListRelation adlRelation;
		adlRelation.Clear();
		errorMessage.clear();
		adlRelation.SetAccountableDocumentID(accountableDocumentID);
		adlRelation.SetExpenseDocumentID(expenseDocumentID);
		std::string filter = adlRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableDocumentListVector = ormasDal.GetAccountableDocumentList(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableDocumentListVector.size())
		{
			return false;
		}
		errorMessage = "Accountable document list Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}