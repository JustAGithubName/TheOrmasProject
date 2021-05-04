#include "stdafx.h"
#include "ShareholderClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	Shareholder::Shareholder(DataLayer::shareholdersCollection cCollection)
	{
		userID = std::get<0>(cCollection);
		countOfStock = std::get<1>(cCollection);
		information = std::get<2>(cCollection);
	}

	int Shareholder::GetUserID()
	{
		return userID;
	}

	double Shareholder::GetCountOfStock()
	{
		return countOfStock;
	}

	std::string Shareholder::GetInformation()
	{
		return information;
	}

	void Shareholder::SetUserID(int uID)
	{
		userID = uID;
	}
	void Shareholder::SetCountOfStock(double sCountOfStock)
	{
		countOfStock = sCountOfStock;
	}
	void Shareholder::SetInformation(std::string aInformation)
	{
		if (!aInformation.empty())
			boost::trim(aInformation);
		information = aInformation;
	}

	bool Shareholder::CreateShareholder(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sCoubtOfStock, std::string aInformation, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, errorMessage))
			return false;
		TrimStrings(aInformation);
		userID = uID;
		countOfStock = sCoubtOfStock;
		information = aInformation;
		if (ormasDal.CreateShareholder(userID, countOfStock, information, errorMessage))
		{
			if (CreateBalanceForShareholder(globalVar, ormasDal, userID, errorMessage))
				return true;
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Shareholder::CreateShareholder(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (ormasDal.CreateShareholder(userID, countOfStock, information, errorMessage))
		{
			if (CreateBalanceForShareholder(globalVar, ormasDal, userID, errorMessage))
				return true;
			return false;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Shareholder::DeleteShareholder(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteShareholder(id, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Shareholder::UpdateShareholder(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sCountOfStock, std::string aInformation, std::string& errorMessage)
	{
		TrimStrings(aInformation);
		userID = uID;
		countOfStock = sCountOfStock;
		information = aInformation;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.UpdateShareholder(userID, countOfStock, information, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool Shareholder::UpdateShareholder(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateShareholder(userID, countOfStock, information, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string Shareholder::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !information.empty() || 0 != userID || 0 != countOfStock)
		{
			return ormasDal.GetFilterForShareholder(id, userID, countOfStock, information);
		}
		return "";
	}

	bool Shareholder::GetShareholderByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::shareholdersViewCollection> shareholderVector = ormasDal.GetShareholders(errorMessage, filter);
		if (0 != shareholderVector.size())
		{
			userID = std::get<0>(shareholderVector.at(0));
			countOfStock = std::get<5>(shareholderVector.at(0));
			information = std::get<6>(shareholderVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Shareholder with this id";
		}
		return false;
	}

	bool Shareholder::IsEmpty()
	{
		if (0 == userID && 0 == countOfStock && information.empty())
			return true;
		return false;
	}

	void Shareholder::Clear()
	{
		userID = 0;
		countOfStock = 0;
		information.clear();
	}

	void Shareholder::TrimStrings(std::string& aInformation)
	{
		if (!aInformation.empty())
			boost::trim(aInformation);

	}

	bool Shareholder::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		Shareholder shareholder;
		shareholder.Clear();
		errorMessage.clear();
		shareholder.SetUserID(uID);
		shareholder.SetCountOfStock(0);
		shareholder.SetInformation("");
		std::string filter = shareholder.GenerateFilter(ormasDal);
		std::vector<DataLayer::shareholdersViewCollection> shareholderVector = ormasDal.GetShareholders(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == shareholderVector.size())
		{
			return false;
		}
		errorMessage = "Shareholder with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Shareholder::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Shareholder shareholder;
		shareholder.Clear();
		errorMessage.clear();
		shareholder.SetUserID(userID);
		shareholder.SetCountOfStock(0);
		shareholder.SetInformation("");
		std::string filter = shareholder.GenerateFilter(ormasDal);
		std::vector<DataLayer::shareholdersViewCollection> shareholderVector = ormasDal.GetShareholders(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == shareholderVector.size())
		{
			return false;
		}
		errorMessage = "Shareholder with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}