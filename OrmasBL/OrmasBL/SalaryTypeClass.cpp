#include "stdafx.h"
#include "SalaryTypeClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer
{
	SalaryType::SalaryType(DataLayer::salaryTypeCollection stCollection)
	{
		id = std::get<0>(stCollection);
		code = std::get<1>(stCollection);
		name = std::get<2>(stCollection);
	}

	int SalaryType::GetID()
	{
		return id;
	}

	std::string SalaryType::GetCode()
	{
		return code;
	}

	std::string SalaryType::GetName()
	{
		return name;
	}

	void SalaryType::SetID(int rID)
	{
		id = rID;
	}
	void SalaryType::SetCode(std::string stCode)
	{
		if (!stCode.empty())
			boost::trim(stCode);
		code = stCode;
	}
	void SalaryType::SetName(std::string stName)
	{
		if (!stName.empty())
			boost::trim(stName);
		name = stName;
	}
	
	bool SalaryType::CreateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string stCode, std::string stName, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, stCode, stName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(stCode, stName);
		code = stCode;
		name = stName;
		if (0 != id && ormasDal.CreateSalaryType(id, code, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SalaryType::CreateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateSalaryType(id, code, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SalaryType::DeleteSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSalaryType(id, errorMessage))
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
	bool SalaryType::UpdateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string stCode, std::string stName, std::string& errorMessage)
	{
		TrimStrings(stCode, stName);
		code = stCode;
		name = stName;
		if (0 != id && ormasDal.UpdateSalaryType(id, code, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SalaryType::UpdateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateSalaryType(id, code, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string SalaryType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !code.empty() || !name.empty() )
		{
			return ormasDal.GetFilterForSalaryType(id, code, name);
		}
		return "";
	}

	bool SalaryType::GetSalaryTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage)
	{
		if (rID <= 0)
			return false;
		id = rID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::salaryTypeCollection> salaryTypeVector = ormasDal.GetSalaryType(errorMessage, filter);
		if (0 != salaryTypeVector.size())
		{
			id = std::get<0>(salaryTypeVector.at(0));
			code = std::get<1>(salaryTypeVector.at(0));
			name = std::get<2>(salaryTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find SalaryType with this id";
		}
		return false;
	}
	
	bool SalaryType::IsEmpty()
	{
		if (0 == id && code == "" && name == "")
			return true;
		return false;
	}

	void SalaryType::Clear()
	{
		id = 0;
		code.clear();
		name.clear();
	}

	void SalaryType::TrimStrings(std::string& stCode, std::string& stName)
	{
		if (!stCode.empty())
			boost::trim(stCode);
		if (!stName.empty())
			boost::trim(stName);
	}

	bool SalaryType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string stCode, std::string stName, std::string& errorMessage)
	{
		SalaryType salaryType;
		salaryType.Clear();
		errorMessage.clear();
		salaryType.SetCode(stCode);
		salaryType.SetName(stName);
		std::string filter = salaryType.GenerateFilter(ormasDal);
		std::vector<DataLayer::salaryTypeCollection> salaryTypeVector = ormasDal.GetSalaryType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == salaryTypeVector.size())
		{
			return false;
		}
		errorMessage = "Salary type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool SalaryType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		SalaryType salaryType;
		salaryType.Clear();
		errorMessage.clear();
		salaryType.SetCode(code);
		salaryType.SetName(name);
		std::string filter = salaryType.GenerateFilter(ormasDal);
		std::vector<DataLayer::salaryTypeCollection> salaryTypeVector = ormasDal.GetSalaryType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == salaryTypeVector.size())
		{
			return false;
		}
		errorMessage = "Salary type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::map<std::string, int> SalaryType::GetSalaryTypesAsMap(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> salaryTypeMap;
		std::vector<DataLayer::salaryTypeCollection> salaryTypeVector = ormasDal.GetSalaryType(errorMessage);
		if (salaryTypeVector.size() > 0)
		{
			for each (auto item in salaryTypeVector)
			{
				salaryTypeMap.insert(std::make_pair(std::get<1>(item), std::get<0>(item)));
			}
		}
		return salaryTypeMap;
	}
}