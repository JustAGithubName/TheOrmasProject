#include "stdafx.h"
#include "AccountTypeClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AccountType::AccountType(DataLayer::accountTypeCollection aCollection)
	{
		id = std::get<0>(aCollection);
		name = std::get<1>(aCollection);
		number = std::get<2>(aCollection);
		comment = std::get<3>(aCollection);
	}

	int AccountType::GetID()
	{
		return id;
	}

	std::string AccountType::GetName()
	{
		return name;
	}

	int AccountType::GetNumber()
	{
		return number;
	}

	std::string AccountType::GetComment()
	{
		return comment;
	}

	void AccountType::SetID(int aID)
	{
		id = aID;
	}
	void AccountType::SetName(std::string aName)
	{
		if (!aName.empty())
			boost::trim(aName);
		name = aName;
	}
	void AccountType::SetComment(std::string aComment)
	{
		if (!aComment.empty())
			boost::trim(aComment);
		comment = aComment;
	}

	void AccountType::SetNumber(int aNumber)
	{
		number = aNumber;
	}

	bool AccountType::CreateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aName, int aNumber, std::string aComment, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aName, aNumber, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(aName, aComment);
		name = aName;
		number = aNumber;
		comment = aComment;		
		if (0 != id && ormasDal.CreateAccountType(id, name, number, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountType::CreateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateAccountType(id, name, number, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountType::DeleteAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountType(id, errorMessage))
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
	bool AccountType::UpdateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aName, int aNumber, std::string aComment, std::string& errorMessage)
	{
		TrimStrings(aName, aComment);
		name = aName;
		number = aNumber;
		comment = aComment;
		if (0 != id && ormasDal.UpdateAccountType(id, name, number, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountType::UpdateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateAccountType(id, name, number, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string AccountType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != number || !name.empty() || !comment.empty())
		{
			return ormasDal.GetFilterForAccountType(id, name, number, comment);
		}
		return "";
	}

	bool AccountType::GetAccountTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountTypeCollection> accountTypesVector = ormasDal.GetAccountType(errorMessage, filter);
		if (0 != accountTypesVector.size())
		{
			id = std::get<0>(accountTypesVector.at(0));
			name = std::get<1>(accountTypesVector.at(0));
			number = std::get<2>(accountTypesVector.at(0));
			comment = std::get<3>(accountTypesVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find account type with this id";
		}
		return false;
	}

	bool AccountType::GetAccountTypeByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aNumber, std::string& errorMessage)
	{
		if (aNumber <= 0)
			return false;
		number = aNumber;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountTypeCollection> accountTypesVector = ormasDal.GetAccountType(errorMessage, filter);
		if (0 != accountTypesVector.size())
		{
			id = std::get<0>(accountTypesVector.at(0));
			name = std::get<1>(accountTypesVector.at(0));
			number = std::get<2>(accountTypesVector.at(0));
			comment = std::get<3>(accountTypesVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find account type with this number";
		}
		return false;
	}

	bool AccountType::IsEmpty()
	{
		if (0 == id && name == "" && comment == "" && 0 == number)
			return true;
		return false;
	}

	void AccountType::Clear()
	{
		id = 0;
		name.clear();
		comment.clear();
		number = 0;
	}

	void AccountType::TrimStrings(std::string& aName, std::string& aComment)
	{
		if (!aName.empty())
			boost::trim(aName);
		if (!aComment.empty())
			boost::trim(aComment);
	}

	bool AccountType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aName, int aNumber, std::string& errorMessage)
	{
		AccountType accountType;
		accountType.Clear();
		errorMessage.clear();
		accountType.SetName(aName);
		accountType.SetNumber(aNumber);
		std::string filter = accountType.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountTypeCollection> accountTypesVector = ormasDal.GetAccountType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountTypesVector.size())
		{
			return false;
		}
		errorMessage = "Account type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountType accountType;
		accountType.Clear();
		errorMessage.clear();
		accountType.SetName(name);
		accountType.SetNumber(number);
		std::string filter = accountType.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountTypeCollection> AccountTypesVector = ormasDal.GetAccountType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == AccountTypesVector.size())
		{
			return false;
		}
		errorMessage = "Account type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}