#include "stdafx.h"
#include "OtherStocksTypeClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	OtherStocksType::OtherStocksType(DataLayer::otherStocksTypeCollection pTypeCollection)
	{
		id = std::get<0>(pTypeCollection);
		name = std::get<1>(pTypeCollection);
		shortName = std::get<2>(pTypeCollection);
		code = std::get<3>(pTypeCollection);
	}

	int OtherStocksType::GetID()
	{
		return id;
	}

	std::string OtherStocksType::GetName()
	{
		return name;
	}

	std::string OtherStocksType::GetShortName()
	{
		return shortName;
	}

	std::string OtherStocksType::GetCode()
	{
		return code;
	}

	void OtherStocksType::SetID(int pID)
	{
		id = pID;
	}
	void OtherStocksType::SetName(std::string pName)
	{
		if (!pName.empty())
			boost::trim(pName);
		name = pName;
	}
	void OtherStocksType::SetShortName(std::string pShortName)
	{
		if (!pShortName.empty())
			boost::trim(pShortName);
		shortName = pShortName;
	}
	void OtherStocksType::SetCode(std::string pCode)
	{
		if (!pCode.empty())
			boost::trim(pCode);
		code = boost::to_upper_copy(pCode);
	}

	bool OtherStocksType::CreateOtherStocksType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pTypeName, std::string pTypeShortName, std::string pTypeCode,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pTypeName, pTypeShortName, pTypeCode, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(pTypeName, pTypeShortName, pTypeCode);
		name = pTypeName;
		shortName = pTypeShortName;
		code = boost::to_upper_copy(pTypeCode);
		if (0 != id && ormasDal.CreateOtherStocksType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OtherStocksType::CreateOtherStocksType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id &&ormasDal.CreateOtherStocksType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OtherStocksType::DeleteOtherStocksType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteOtherStocksType(id, errorMessage))
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
	bool OtherStocksType::UpdateOtherStocksType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pTypeName, std::string pTypeShortName, std::string pTypeCode,
		std::string& errorMessage)
	{
		TrimStrings(pTypeName, pTypeShortName, pTypeCode);
		name = pTypeName;
		shortName = pTypeShortName;
		code = boost::to_upper_copy(pTypeCode);
		if (0 != id &&ormasDal.UpdateOtherStocksType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool OtherStocksType::UpdateOtherStocksType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateOtherStocksType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string OtherStocksType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !shortName.empty() || !code.empty())
		{
			return ormasDal.GetFilterForOtherStocksType(id, name, shortName, code);
		}
		return "";
	}

	bool OtherStocksType::GetOtherStocksTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksTypeCollection> otherStocksTypeVector = ormasDal.GetOtherStocksType(errorMessage, filter);
		if (0 != otherStocksTypeVector.size())
		{
			id = std::get<0>(otherStocksTypeVector.at(0));
			name = std::get<1>(otherStocksTypeVector.at(0));
			shortName = std::get<2>(otherStocksTypeVector.at(0));
			code = std::get<3>(otherStocksTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find OtherStocks type with this id";
		}
		return false;
	}

	bool OtherStocksType::GetOtherStocksTypeByCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pCode, std::string& errorMessage)
	{
		if (pCode.empty())
			return false;
		code = pCode;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksTypeCollection> otherStocksTypeVector = ormasDal.GetOtherStocksType(errorMessage, filter);
		if (0 != otherStocksTypeVector.size())
		{
			id = std::get<0>(otherStocksTypeVector.at(0));
			name = std::get<1>(otherStocksTypeVector.at(0));
			shortName = std::get<2>(otherStocksTypeVector.at(0));
			code = std::get<3>(otherStocksTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find OtherStocks type with this id";
		}
		return false;
	}

	bool OtherStocksType::IsEmpty()
	{
		if (0 == id && name == "" && shortName == "" && code == "")
			return true;
		return false;
	}

	void OtherStocksType::Clear()
	{
		id = 0;
		name.clear();
		shortName.clear();
		code.clear();
	}

	void OtherStocksType::TrimStrings(std::string& pTypeName, std::string& pTypeShortName, std::string& pTypeCode)
	{
		if (!pTypeName.empty())
			boost::trim(pTypeName);
		if (!pTypeShortName.empty())
			boost::trim(pTypeShortName);
		if (!pTypeCode.empty())
			boost::trim(pTypeCode);
	}

	bool OtherStocksType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pTypeName, std::string pTypeShortName, std::string pTypeCode, std::string& errorMessage)
	{
		OtherStocksType otherStocksType;
		otherStocksType.Clear();
		errorMessage.clear();
		otherStocksType.SetName(pTypeName);
		otherStocksType.SetShortName(pTypeShortName);
		otherStocksType.SetCode(pTypeCode);
		std::string filter = otherStocksType.GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksTypeCollection> otherStocksTypeVector = ormasDal.GetOtherStocksType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == otherStocksTypeVector.size())
		{
			return false;
		}
		errorMessage = "OtherStocks type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool OtherStocksType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		OtherStocksType otherStocksType;
		otherStocksType.Clear();
		errorMessage.clear();
		otherStocksType.SetName(name);
		otherStocksType.SetShortName(shortName);
		otherStocksType.SetCode(code);
		std::string filter = otherStocksType.GenerateFilter(ormasDal);
		std::vector<DataLayer::otherStocksTypeCollection> otherStocksTypeVector = ormasDal.GetOtherStocksType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == otherStocksTypeVector.size())
		{
			return false;
		}
		errorMessage = "OtherStocks type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}