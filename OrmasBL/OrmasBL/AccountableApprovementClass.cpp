#include "stdafx.h"
#include "AccountableApprovementClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	AccountableApprovement::AccountableApprovement(DataLayer::accountableApprovementCollection cCollection)
	{
		id = std::get<0>(cCollection);;
		approveDate = std::get<1>(cCollection);;
		directorID = std::get<2>(cCollection);
		accountantID = std::get<3>(cCollection);
		accountableDocumentID = std::get<4>(cCollection);
	}

	int AccountableApprovement::GetID()
	{
		return id;
	}

	int AccountableApprovement::GetDirectorID()
	{
		return directorID;
	}
	int AccountableApprovement::GetAccountantID()
	{
		return accountantID;
	}
	std::string AccountableApprovement::GetApproveDate()
	{
		return approveDate;
	}

	int AccountableApprovement::GetAccountableDocumentID()
	{
		return accountableDocumentID;
	}

	void AccountableApprovement::SetID(int aID)
	{
		id = aID;
	}
	void AccountableApprovement::SetDirectorID(int dirID)
	{
		directorID = dirID;
	}
	void AccountableApprovement::SetAccounantID(int accoID)
	{
		accountantID = accoID;
	}
	void AccountableApprovement::SetApproveDate(std::string aDate)
	{
		approveDate = aDate;
	}

	void AccountableApprovement::SetAccountableDocumentID(int accoDocID)
	{
		accountableDocumentID = accoDocID;
	}

	bool AccountableApprovement::CreateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int dirID, int accoID, 
		int aDocumentID, std::string& errorMessage)
	{

		//if (IsDuplicate(globalVar, ormasDal, eID, aInformation, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		approveDate = aDate;
		directorID = dirID;
		accountantID = accoID;
		accountableDocumentID = aDocumentID;
		if (ormasDal.CreateAccountableApprovement(id, approveDate, directorID, accountantID, accountableDocumentID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableApprovement::CreateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccountableApprovement(id, approveDate, directorID, accountantID, accountableDocumentID, errorMessage))
		{
			return true;

		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableApprovement::DeleteAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteAccountableApprovement(id, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableApprovement::DeleteAccountableApprovementByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteAccountableApprovementByDocumentID(accountableDocumentID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableApprovement::UpdateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int dirID, int accoID,
		int aDocumentID, std::string& errorMessage)
	{
		approveDate = aDate;
		directorID = dirID;
		accountantID = accoID;
		accountableDocumentID = aDocumentID;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.UpdateAccountableApprovement(id, approveDate, directorID, accountantID, accountableDocumentID,  errorMessage))
		{
			return true;
		}
		return false;
	}
	bool AccountableApprovement::UpdateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateAccountableApprovement(id, approveDate, directorID, accountantID, accountableDocumentID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string AccountableApprovement::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != directorID || 0 != accountantID || 0 != accountableDocumentID || !approveDate.empty())
		{
			return ormasDal.GetFilterForAccountableApprovement(id, approveDate, directorID, accountantID, accountableDocumentID);
		}
		return "";
	}

	bool AccountableApprovement::GetAccountableApprovementByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (0 != accountableApprovementVector.size())
		{
			id = std::get<0>(accountableApprovementVector.at(0));
			approveDate = std::get<1>(accountableApprovementVector.at(0));
			directorID = std::get<2>(accountableApprovementVector.at(0));
			accountantID = std::get<3>(accountableApprovementVector.at(0));
		    accountableDocumentID = std::get<4>(accountableApprovementVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable Approvement with this id";
		}
		return false;
	}

	bool AccountableApprovement::GetAccountableApprovementByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		accountableDocumentID = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (0 != accountableApprovementVector.size())
		{
			id = std::get<0>(accountableApprovementVector.at(0));
			approveDate = std::get<1>(accountableApprovementVector.at(0));
			directorID = std::get<2>(accountableApprovementVector.at(0));
			accountantID = std::get<3>(accountableApprovementVector.at(0));
			accountableDocumentID = std::get<4>(accountableApprovementVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable Approvement with this id";
		}
		return false;
	}

	std::vector<int> AccountableApprovement::GetAllApprovementByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> accountableDocumentIDVector;
		AccountableApprovement bpRelation;
		bpRelation.SetAccountableDocumentID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountablePaymentVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (0 != accountablePaymentVector.size())
		{
			for each (auto item in accountablePaymentVector)
			{
				accountableDocumentIDVector.push_back(std::get<0>(item));
			}
		}
		return accountableDocumentIDVector;
	}

	bool AccountableApprovement::IsEmpty()
	{
		if (0 == id && 0 == directorID && 0 == accountantID && 0 == accountableDocumentID && approveDate.empty())
			return true;
		return false;
	}

	void AccountableApprovement::Clear()
	{
		id = 0;
		directorID = 0;
		accountantID = 0;
		accountableDocumentID = 0;
		approveDate.clear();
	}

	bool AccountableApprovement::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int aDocumentID, std::string& errorMessage)
	{
		AccountableApprovement accountableApprovement;
		accountableApprovement.Clear();
		errorMessage.clear();
		accountableApprovement.SetApproveDate(aDate);
		accountableApprovement.SetAccountableDocumentID(aDocumentID);
		
		std::string filter = accountableApprovement.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableApprovementVector.size())
		{
			return false;
		}
		errorMessage = "Accountable approvement with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableApprovement::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableApprovement accountableApprovement;
		accountableApprovement.Clear();
		errorMessage.clear();
		accountableApprovement.SetApproveDate(approveDate);
		accountableApprovement.SetAccountableDocumentID(accountableDocumentID);

		std::string filter = accountableApprovement.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableApprovementVector.size())
		{
			return false;
		}
		errorMessage = "Accountable approvement with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}