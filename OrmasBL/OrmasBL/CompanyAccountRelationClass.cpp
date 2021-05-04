#include "stdafx.h"
#include "CompanyAccountRelationClass.h"
#include "AccountClass.h"


namespace BusinessLayer{
	CompanyAccountRelation::CompanyAccountRelation(DataLayer::companyAccountCollection caCollection)
	{
		id = std::get<0>(caCollection);
		companyID = std::get<0>(caCollection);
		accountID = std::get<1>(caCollection);
	}
	CompanyAccountRelation::CompanyAccountRelation()
	{
		id = 0;
		companyID = 0;
		accountID = 0;
	}

	int CompanyAccountRelation::GetID()
	{
		return id;
	}

	int CompanyAccountRelation::GetCompanyID()
	{
		return companyID;
	}

	int CompanyAccountRelation::GetAccountID()
	{
		return accountID;
	}

	void CompanyAccountRelation::SetID(int caID)
	{
		id = caID;
	}
	void CompanyAccountRelation::SetCompanyID(int cID)
	{
		companyID = cID;
	}
	void CompanyAccountRelation::SetAccountID(int aID)
	{
		accountID = aID;
	}

	bool CompanyAccountRelation::CreateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, cID, aID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		companyID = cID;
		accountID = aID;

		if (ormasDal.CreateCompanyAccount(id, companyID, accountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CompanyAccountRelation::CreateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateCompanyAccount(id, companyID, accountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CompanyAccountRelation::DeleteCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCompanyAccount(companyID, accountID, errorMessage))
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

	bool CompanyAccountRelation::UpdateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage)
	{
		companyID = cID;
		accountID = aID;
		if (0 != id && ormasDal.UpdateCompanyAccount(id, companyID, accountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CompanyAccountRelation::UpdateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateCompanyAccount(id, companyID, accountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string CompanyAccountRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != companyID || 0 != accountID)
		{
			return ormasDal.GetFilterForCompanyAccount(id, companyID, accountID);
		}
		return "";
	}

	bool CompanyAccountRelation::GetCompanyAccountByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, std::string& errorMessage)
	{
		if (id <= 0)
			return false;
		CompanyAccountRelation ceRelation;
		ceRelation.SetID(id);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::companyAccountViewCollection> companyAccountVector = ormasDal.GetCompanyAccount(errorMessage, filter);
		if (0 != companyAccountVector.size())
		{
			id = std::get<0>(companyAccountVector.at(0));
			companyID = std::get<3>(companyAccountVector.at(0));
			accountID = std::get<4>(companyAccountVector.at(0));
			return true;
		}
		return false;
	}

	std::vector<int> CompanyAccountRelation::GetAllCompanyByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		std::vector<int> companyIDVector;
		CompanyAccountRelation caRelation;
		caRelation.SetAccountID(aID);
		caRelation.SetCompanyID(0);
		std::string filter = caRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::companyAccountViewCollection> companyAccountVector = ormasDal.GetCompanyAccount(errorMessage, filter);
		if (0 != companyAccountVector.size())
		{
			for each (auto item in companyAccountVector)
			{
				companyIDVector.push_back(std::get<3>(item));
			}
		}
		return companyIDVector;
	}

	std::vector<int> CompanyAccountRelation::GetAllAccountByCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		std::vector<int> accountIDVector;
		CompanyAccountRelation caRelation;
		caRelation.SetAccountID(0);
		caRelation.SetCompanyID(cID);
		std::string filter = caRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::companyAccountViewCollection> companyAccountVector = ormasDal.GetCompanyAccount(errorMessage, filter);
		if (0 != companyAccountVector.size())
		{
			for each (auto item in companyAccountVector)
			{
				accountIDVector.push_back(std::get<4>(item));
			}
		}
		return accountIDVector;
	}


	bool CompanyAccountRelation::IsEmpty()
	{
		if (0 == companyID && 0 == accountID)
			return true;
		return false;
	}

	void CompanyAccountRelation::Clear()
	{
		companyID = 0;
		accountID = 0;
	}

	bool CompanyAccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage)
	{
		CompanyAccountRelation caRelation;
		caRelation.Clear();
		errorMessage.clear();
		caRelation.SetCompanyID(cID);
		caRelation.SetAccountID(aID);
		std::string filter = caRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::companyAccountViewCollection> companyAccountVector = ormasDal.GetCompanyAccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == companyAccountVector.size())
		{
			return false;
		}
		errorMessage = "Company-Account Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool CompanyAccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		CompanyAccountRelation caRelation;
		caRelation.Clear();
		errorMessage.clear();
		caRelation.SetCompanyID(companyID);
		caRelation.SetAccountID(accountID);
		std::string filter = caRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::companyAccountViewCollection> companyAccountVector = ormasDal.GetCompanyAccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == companyAccountVector.size())
		{
			return false;
		}
		errorMessage = "Company-Account Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	int CompanyAccountRelation::GetAccountIDByCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string parentNumber, std::string& errorMessage)
	{
		Account account;
		std::vector<int> accVec;
		accVec = GetAllAccountByCompanyID(globalVar, ormasDal, cID, errorMessage);
		if (accVec.size() > 0)
		{
			for each (int accID in accVec)
			{
				account.Clear();
				if (account.GetAccountByID(globalVar, ormasDal, accID, errorMessage))
				{
					if (0 == account.GetNumber().compare(parentNumber))
					{
						return account.GetID();
					}
				}
			}
		}
		return 0;
	}
}