#include "stdafx.h"
#include "WarehouseTypeClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	WarehouseType::WarehouseType(DataLayer::warehouseTypeCollection wCollection)
	{
		id = std::get<0>(wCollection);
		code = std::get<1>(wCollection);
		purpose = std::get<2>(wCollection);
		name = std::get<3>(wCollection);
	}
	WarehouseType::WarehouseType()
	{
		code = "";
		purpose = "";
		name = "";
	}
	int WarehouseType::GetID()
	{
		return id;
	}

	std::string WarehouseType::GetCode()
	{
		return code;
	}

	std::string WarehouseType::GetPurpose()
	{
		return purpose;
	}

	std::string WarehouseType::GetName()
	{
		return name;
	}

	void WarehouseType::SetID(int cID)
	{
		id = cID;
	}
	
	void WarehouseType::SetCode(std::string wCode)
	{
		if (!wCode.empty())
			boost::trim(wCode);
		code = wCode;
	}
	void WarehouseType::SetPurpose(std::string wPurpose)
	{
		if (!wPurpose.empty())
			boost::trim(wPurpose);
		purpose = wPurpose;
	}
	void WarehouseType::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}

	bool WarehouseType::CreateWarehouseType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wtCode, std::string wtPurpose, std::string wtName, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, wtName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(wtName, wtCode, wtPurpose);
		code = wtCode;
		purpose = wtPurpose;
		name = wtName;
		if (0 != id && ormasDal.CreateWarehouseType(id, code, purpose, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool WarehouseType::CreateWarehouseType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateWarehouseType(id, code, purpose, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool WarehouseType::DeleteWarehouseType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteWarehouseType(id, errorMessage))
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

	bool WarehouseType::UpdateWarehouseType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wtCode, std::string wtPurpose, std::string wtName, std::string& errorMessage)
	{
		TrimStrings(wtName, wtCode, wtPurpose);
		code = wtCode;
		purpose = wtPurpose;
		name = wtName;
		if (0 != id && ormasDal.UpdateWarehouseType(id, code, purpose, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool WarehouseType::UpdateWarehouseType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateWarehouseType(id, code, purpose, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string WarehouseType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !code.empty() || !purpose.empty())
		{
			return ormasDal.GetFilterForWarehouseType(id, code, purpose, name);
		}
		return "";
	}

	bool WarehouseType::GetWarehouseTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		if (wID <= 0)
			return false;
		id = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseTypeCollection> warehouseTypeVector = ormasDal.GetWarehouseType(errorMessage, filter);
		if (0 != warehouseTypeVector.size())
		{
			id = std::get<0>(warehouseTypeVector.at(0));
			code = std::get<1>(warehouseTypeVector.at(0));
			purpose = std::get<2>(warehouseTypeVector.at(0));
			name = std::get<3>(warehouseTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find WarehouseType with this id";
		}
		return false;
	}

	bool WarehouseType::GetWarehouseTypeByCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wtCode, std::string& errorMessage)
	{
		if (wtCode.empty())
			return false;
		code = wtCode;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseTypeCollection> warehouseTypeVector = ormasDal.GetWarehouseType(errorMessage, filter);
		if (0 != warehouseTypeVector.size())
		{
			id = std::get<0>(warehouseTypeVector.at(0));
			code = std::get<1>(warehouseTypeVector.at(0));
			purpose = std::get<2>(warehouseTypeVector.at(0));
			name = std::get<3>(warehouseTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find WarehouseType with this id";
		}
		return false;
	}

	int WarehouseType::GetWarehouseTypeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string filter = this->GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseTypeCollection> warehouseTypeVector = ormasDal.GetWarehouseType(errorMessage, filter);
		if (0 != warehouseTypeVector.size())
		{
			return std::get<0>(warehouseTypeVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find Warehouse Type with this id";
		}
		return 0;
	}

	bool WarehouseType::IsEmpty()
	{
		if (0 == id && name == "" && code == "" && purpose == "")
			return true;
		return false;
	}

	void WarehouseType::Clear()
	{
		id = 0;
		name.clear();
		code.clear();
		purpose.clear();
	}

	void WarehouseType::TrimStrings(std::string& cName, std::string& cAddress, std::string& cPhone)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cAddress.empty())
			boost::trim(cAddress);
		if (!cPhone.empty())
			boost::trim(cPhone);
	}

	bool WarehouseType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wName, std::string& errorMessage)
	{
		WarehouseType warehouseType;
		warehouseType.Clear();
		errorMessage.clear();
		warehouseType.SetName(wName);
		std::string filter = warehouseType.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseTypeCollection> warehouseTypeVector = ormasDal.GetWarehouseType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == warehouseTypeVector.size())
		{
			return false;
		}
		errorMessage = "Warehouse Type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WarehouseType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		WarehouseType warehouseType;
		warehouseType.Clear();
		errorMessage.clear();
		warehouseType.SetName(name);
		std::string filter = warehouseType.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseTypeCollection> warehouseTypeVector = ormasDal.GetWarehouseType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == warehouseTypeVector.size())
		{
			return false;
		}
		errorMessage = "Warehouse Type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::map<std::string, int> WarehouseType::GetWarehouseTypesAsMap(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> warehouseTypeMap;
		std::vector<DataLayer::warehouseTypeCollection> warehouseTypeVector = ormasDal.GetWarehouseType(errorMessage);
		if (warehouseTypeVector.size() > 0)
		{
			for each (auto item in warehouseTypeVector)
			{
				warehouseTypeMap.insert(std::make_pair(std::get<1>(item), std::get<0>(item)));
			}
		}
		return warehouseTypeMap;
	}
}

