#include "stdafx.h"
#include "DivisionAccountRelationClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	DivisionAccountRelation::DivisionAccountRelation(DataLayer::divisionAccountCollection dCollection)
	{
		id = std::get<0>(dCollection);
		divisionID = std::get<1>(dCollection);
		accountID = std::get<2>(dCollection);
		code = std::get<3>(dCollection);
	}
	DivisionAccountRelation::DivisionAccountRelation()
	{
		divisionID = 0;
		accountID = 0;
		code = "";
	}
	
	int DivisionAccountRelation::GetID()
	{
		return id;
	}

	int DivisionAccountRelation::GetDivisionID()
	{
		return divisionID;
	}
	
	int DivisionAccountRelation::GetAccountID()
	{
		return accountID;
	}

	std::string DivisionAccountRelation::GetCode()
	{
		return code;
	}

	void DivisionAccountRelation::SetID(int dID)
	{
		id = dID;
	}
	void DivisionAccountRelation::SetDivisionID(int dDivisionID)
	{
		divisionID = dDivisionID;
	}
	void DivisionAccountRelation::SetAccountID(int dDivisionID)
	{
		accountID = dDivisionID;
	}
	void DivisionAccountRelation::SetCode(std::string dCode)
	{
		if (!dCode.empty())
			boost::trim(dCode);
		code = boost::to_upper_copy(dCode);
	}

	bool DivisionAccountRelation::CreateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dAccountID, 
		std::string dCode, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, dDivisionID, dCode, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		divisionID = dDivisionID;
		accountID = dAccountID;
		TrimStrings(dCode);
		code = boost::to_upper_copy(dCode);
		if (0 != id && ormasDal.CreateDivisionAccount(id, divisionID, accountID, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool DivisionAccountRelation::CreateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateDivisionAccount(id, divisionID, accountID, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool DivisionAccountRelation::DeleteDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteDivisionAccount(id, errorMessage))
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

	bool DivisionAccountRelation::UpdateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dAccountID,
		std::string dCode, std::string& errorMessage)
	{
		TrimStrings(dCode);
		divisionID = dDivisionID;
		accountID = dAccountID;
		code = boost::to_upper_copy(dCode);
		if (0 != id && ormasDal.UpdateDivisionAccount(id, divisionID, accountID, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool DivisionAccountRelation::UpdateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateDivisionAccount(id, divisionID, accountID, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string DivisionAccountRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != divisionID || 0 != accountID || !code.empty())
		{
			return ormasDal.GetFilterForDivisionAccount(id, divisionID, accountID, code);
		}
		return "";
	}

	bool DivisionAccountRelation::GetDivisionAccountRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string& errorMessage)
	{
		if (dID <= 0)
			return false;
		id = dID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionAccountViewCollection> divisionAccountRelationVector = ormasDal.GetDivisionAccount(errorMessage, filter);
		if (0 != divisionAccountRelationVector.size())
		{
			id = std::get<0>(divisionAccountRelationVector.at(0));
			divisionID = std::get<5>(divisionAccountRelationVector.at(0));
			accountID = std::get<6>(divisionAccountRelationVector.at(0));
			code = std::get<4>(divisionAccountRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find division account relation with this id";
		}
		return false;
	}

	bool DivisionAccountRelation::GetDARelationByDivisionIDAndCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string daCode, std::string& errorMessage)
	{
		if (dID <= 0 || daCode.empty())
			return false;
		divisionID = dID;
		code = daCode;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionAccountViewCollection> divisionAccountRelationVector = ormasDal.GetDivisionAccount(errorMessage, filter);
		if (0 != divisionAccountRelationVector.size())
		{
			id = std::get<0>(divisionAccountRelationVector.at(0));
			divisionID = std::get<5>(divisionAccountRelationVector.at(0));
			accountID = std::get<6>(divisionAccountRelationVector.at(0));
			code = std::get<4>(divisionAccountRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find division account relation with this division id";
		}
		return false;
	}

	bool DivisionAccountRelation::IsEmpty()
	{
		if (0 == id && 0 == divisionID && 0 == accountID && code == "")
			return true;
		return false;
	}

	void DivisionAccountRelation::Clear()
	{
		id = 0;
		divisionID = 0;
		accountID = 0;
		code.clear();
	}

	void DivisionAccountRelation::TrimStrings(std::string& dCode)
	{
		if (!dCode.empty())
			boost::trim(dCode);
	}

	bool DivisionAccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, std::string cCode, std::string& errorMessage)
	{
		DivisionAccountRelation divisionAccountRelation;
		divisionAccountRelation.Clear();
		errorMessage.clear();
		divisionAccountRelation.SetDivisionID(dDivisionID);
		divisionAccountRelation.SetCode(cCode);
		std::string filter = divisionAccountRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionAccountViewCollection> divisionAccountRelationVector = ormasDal.GetDivisionAccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == divisionAccountRelationVector.size())
		{
			return false;
		}
		errorMessage = "Division account relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool DivisionAccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		DivisionAccountRelation divisionAccountRelation;
		divisionAccountRelation.Clear();
		errorMessage.clear();
		divisionAccountRelation.SetDivisionID(divisionID);
		divisionAccountRelation.SetCode(code);
		std::string filter = divisionAccountRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionAccountViewCollection> divisionAccountRelationVector = ormasDal.GetDivisionAccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == divisionAccountRelationVector.size())
		{
			return false;
		}
		errorMessage = "Division account relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

