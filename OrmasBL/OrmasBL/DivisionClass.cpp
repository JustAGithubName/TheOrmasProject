#include "stdafx.h"
#include "DivisionClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	Division::Division(DataLayer::divisionsCollection dCollection)
	{
		id = std::get<0>(dCollection);
		name = std::get<1>(dCollection);
		code = std::get<2>(dCollection);
	}
	Division::Division()
	{
		name = "";
		code = "";
	}
	int Division::GetID()
	{
		return id;
	}

	std::string Division::GetName()
	{
		return name;
	}

	std::string Division::GetCode()
	{
		return code;
	}

	void Division::SetID(int dID)
	{
		id = dID;
	}
	void Division::SetName(std::string dName)
	{
		if (!dName.empty())
			boost::trim(dName);
		name = dName;
	}
	void Division::SetCode(std::string dCode)
	{
		if (!dCode.empty())
			boost::trim(dCode);
		code = boost::to_upper_copy(dCode);
	}

	bool Division::CreateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string dName, std::string dCode, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, dName, dCode, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(dName, dCode);
		name = dName;
		code = boost::to_upper_copy(dCode);
		if (0 != id && ormasDal.CreateDivision(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Division::CreateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateDivision(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Division::DeleteDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteDivision(id, errorMessage))
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

	bool Division::UpdateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string dName, std::string dCode, std::string& errorMessage)
	{
		TrimStrings(dName, dCode);
		name = dName;
		code = boost::to_upper_copy(dCode);
		if (0 != id && ormasDal.UpdateDivision(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Division::UpdateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateDivision(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Division::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !code.empty())
		{
			return ormasDal.GetFilterForDivision(id, name, code);
		}
		return "";
	}

	bool Division::GetDivisionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string& errorMessage)
	{
		if (dID <= 0)
			return false;
		id = dID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionsCollection> divisionVector = ormasDal.GetDivisions(errorMessage, filter);
		if (0 != divisionVector.size())
		{
			id = std::get<0>(divisionVector.at(0));
			name = std::get<1>(divisionVector.at(0));
			code = std::get<2>(divisionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Division with this id";
		}
		return false;
	}

	bool Division::IsEmpty()
	{
		if (0 == id && name == "" && code == "")
			return true;
		return false;
	}

	void Division::Clear()
	{
		id = 0;
		name.clear();
		code.clear();
	}

	void Division::TrimStrings(std::string& dName, std::string& dCode)
	{
		if (!dName.empty())
			boost::trim(dName);
		if (!dCode.empty())
			boost::trim(dCode);
	}

	bool Division::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cCode, std::string& errorMessage)
	{
		Division division;
		division.Clear();
		errorMessage.clear();
		division.SetName(cName);
		division.SetCode(cCode);
		std::string filter = division.GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionsCollection> divisionVector = ormasDal.GetDivisions(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == divisionVector.size())
		{
			return false;
		}
		errorMessage = "Division with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Division::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Division division;
		division.Clear();
		errorMessage.clear();
		division.SetName(name);
		division.SetCode(code);
		std::string filter = division.GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionsCollection> divisionVector = ormasDal.GetDivisions(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == divisionVector.size())
		{
			return false;
		}
		errorMessage = "Division with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

