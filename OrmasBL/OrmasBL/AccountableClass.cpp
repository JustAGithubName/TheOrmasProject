#include "stdafx.h"
#include "AccountableClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	Accountable::Accountable(DataLayer::accountableCollection cCollection)
	{
		id = std::get<0>(cCollection);;
		employeeID = std::get<1>(cCollection);
		information = std::get<2>(cCollection);
	}

	int Accountable::GetID()
	{
		return id;
	}

	int Accountable::GetEmployeeID()
	{
		return employeeID;
	}
	std::string Accountable::GetInformation()
	{
		return information;
	}
	
	void Accountable::SetID(int aID)
	{
		id = aID;
	}
	void Accountable::SetEmployeeID(int eID)
	{
		employeeID = eID;
	}
	void Accountable::SetInformation(std::string aInformation)
	{
		if (!aInformation.empty())
			boost::trim(aInformation);
		information = aInformation;
	}
	
	bool Accountable::CreateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string aInformation, std::string& errorMessage)
	{
		
		//if (IsDuplicate(globalVar, ormasDal, eID, aInformation, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		TrimStrings(aInformation);
		employeeID = eID;
		information = aInformation;
		if (ormasDal.CreateAccountable(id, employeeID, information, errorMessage))
		{
			if (CreateBalanceForAccountable(globalVar, ormasDal,  employeeID, errorMessage))
				return true;
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Accountable::CreateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAccountable(id, employeeID, information, errorMessage))
		{
			if (CreateBalanceForAccountable(globalVar, ormasDal, employeeID, errorMessage))
				return true;
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Accountable::DeleteAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteAccountable(id, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Accountable::UpdateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,  int eID, std::string aInformation, std::string& errorMessage)
	{
		TrimStrings(aInformation);
		
		employeeID = eID;
		information = aInformation;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.UpdateAccountable(id, employeeID, information, errorMessage))
		{
				return true;
		}
		return false;
	}
	bool Accountable::UpdateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateAccountable(id, employeeID, information, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string Accountable::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || !information.empty())
		{
			return ormasDal.GetFilterForAccountable(id, employeeID, information);
		}
		return "";
	}

	bool Accountable::GetAccountableByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableViewCollection> accountableVector = ormasDal.GetAccountable(errorMessage, filter);
		if (0 != accountableVector.size())
		{
			id = std::get<0>(accountableVector.at(0));
			employeeID = std::get<1>(accountableVector.at(0));
			information = std::get<4>(accountableVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable with this id";
		}
		return false;
	}

	bool Accountable::GetAccountableByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		employeeID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableViewCollection> accountableVector = ormasDal.GetAccountable(errorMessage, filter);
		if (0 != accountableVector.size())
		{
			id = std::get<0>(accountableVector.at(0));
			employeeID = std::get<1>(accountableVector.at(0));
			information = std::get<4>(accountableVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable with this id";
		}
		return false;
	}

	bool Accountable::IsEmpty()
	{
		if (0 == id && 0 == employeeID && information.empty())
			return true;
		return false;
	}

	void Accountable::Clear()
	{
		id = 0;
		employeeID = 0;
		information.clear();
	}

	void Accountable::TrimStrings(std::string& aInformation)
	{
		if (!aInformation.empty())
			boost::trim(aInformation);
		
	}

	bool Accountable::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, int eID, std::string aInformation, std::string& errorMessage)
	{
		Accountable accountable;
		accountable.Clear();
		errorMessage.clear();
		accountable.SetID(aID);
		accountable.SetEmployeeID(eID);
		accountable.SetInformation(aInformation);
		std::string filter = accountable.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableViewCollection> accountableVector = ormasDal.GetAccountable(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableVector.size())
		{
			return false;
		}
		errorMessage = "Accountable with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Accountable::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Accountable accountable;
		accountable.Clear();
		errorMessage.clear();
		accountable.SetID(id);
		accountable.SetEmployeeID(employeeID);
		accountable.SetInformation(information);
		std::string filter = accountable.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableViewCollection> accountableVector = ormasDal.GetAccountable(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableVector.size())
		{
			return false;
		}
		errorMessage = "Accountable with this parameters are already exist! Please avoid the duplication!";
		return true;
	}	
}