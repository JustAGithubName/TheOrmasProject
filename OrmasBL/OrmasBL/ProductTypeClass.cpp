#include "stdafx.h"
#include "ProductTypeClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	ProductType::ProductType(DataLayer::productTypeCollection pTypeCollection)
	{
		id = std::get<0>(pTypeCollection);
		name = std::get<1>(pTypeCollection);
		shortName = std::get<2>(pTypeCollection);
		code = std::get<3>(pTypeCollection);
	}

	int ProductType::GetID()
	{
		return id;
	}

	std::string ProductType::GetName()
	{
		return name;
	}

	std::string ProductType::GetShortName()
	{
		return shortName;
	}

	std::string ProductType::GetCode()
	{
		return code;
	}

	void ProductType::SetID(int pID)
	{
		id = pID;
	}
	void ProductType::SetName(std::string pName)
	{
		if (!pName.empty())
			boost::trim(pName);
		name = pName;
	}
	void ProductType::SetShortName(std::string pShortName)
	{
		if (!pShortName.empty())
			boost::trim(pShortName);
		shortName = pShortName;
	}
	void ProductType::SetCode(std::string pCode)
	{
		if (!pCode.empty())
			boost::trim(pCode);
		code = boost::to_upper_copy(pCode);
	}

	bool ProductType::CreateProductType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pTypeName, std::string pTypeShortName, std::string pTypeCode,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pTypeName, pTypeShortName, pTypeCode, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(pTypeName, pTypeShortName, pTypeCode);
		name = pTypeName;
		shortName = pTypeShortName;
		code = boost::to_upper_copy(pTypeCode);
		if (0 != id && ormasDal.CreateProductType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ProductType::CreateProductType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id &&ormasDal.CreateProductType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ProductType::DeleteProductType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteProductType(id, errorMessage))
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
	bool ProductType::UpdateProductType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pTypeName, std::string pTypeShortName, std::string pTypeCode,
		std::string& errorMessage)
	{
		TrimStrings(pTypeName, pTypeShortName, pTypeCode);
		name = pTypeName;
		shortName = pTypeShortName;
		code = boost::to_upper_copy(pTypeCode);
		if (0 != id &&ormasDal.UpdateProductType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ProductType::UpdateProductType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateProductType(id, name, shortName, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string ProductType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !shortName.empty() || !code.empty())
		{
			return ormasDal.GetFilterForProductType(id, name, shortName, code);
		}
		return "";
	}

	bool ProductType::GetProductTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productTypeCollection> productTypeVector = ormasDal.GetProductTypes(errorMessage, filter);
		if (0 != productTypeVector.size())
		{
			id = std::get<0>(productTypeVector.at(0));
			name = std::get<1>(productTypeVector.at(0));
			shortName = std::get<2>(productTypeVector.at(0));
			code = std::get<3>(productTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find product type with this id";
		}
		return false;
	}

	bool ProductType::GetProductTypeByCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pCode, std::string& errorMessage)
	{
		if (pCode.empty())
			return false;
		code = pCode;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productTypeCollection> productTypeVector = ormasDal.GetProductTypes(errorMessage, filter);
		if (0 != productTypeVector.size())
		{
			id = std::get<0>(productTypeVector.at(0));
			name = std::get<1>(productTypeVector.at(0));
			shortName = std::get<2>(productTypeVector.at(0));
			code = std::get<3>(productTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find product type with this id";
		}
		return false;
	}
	
	bool ProductType::IsEmpty()
	{
		if (0 == id && name == "" && shortName == "" && code == "")
			return true;
		return false;
	}

	void ProductType::Clear()
	{
		id = 0;
		name.clear();
		shortName.clear();
		code.clear();
	}

	void ProductType::TrimStrings(std::string& pTypeName, std::string& pTypeShortName, std::string& pTypeCode)
	{
		if (!pTypeName.empty())
			boost::trim(pTypeName);
		if (!pTypeShortName.empty())
			boost::trim(pTypeShortName);
		if (!pTypeCode.empty())
			boost::trim(pTypeCode);
	}

	bool ProductType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pTypeName, std::string pTypeShortName, std::string pTypeCode, std::string& errorMessage)
	{
		ProductType productType;
		productType.Clear();
		errorMessage.clear();
		productType.SetName(pTypeName);
		productType.SetShortName(pTypeShortName);
		productType.SetCode(pTypeCode);
		std::string filter = productType.GenerateFilter(ormasDal);
		std::vector<DataLayer::productTypeCollection> productTypeVector = ormasDal.GetProductTypes(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productTypeVector.size())
		{
			return false;
		}
		errorMessage = "Product type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductType productType;
		productType.Clear();
		errorMessage.clear();
		productType.SetName(name);
		productType.SetShortName(shortName);
		productType.SetCode(code);
		std::string filter = productType.GenerateFilter(ormasDal);
		std::vector<DataLayer::productTypeCollection> productTypeVector = ormasDal.GetProductTypes(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productTypeVector.size())
		{
			return false;
		}
		errorMessage = "Product type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}