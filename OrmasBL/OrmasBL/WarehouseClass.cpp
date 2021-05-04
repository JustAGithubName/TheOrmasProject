#include "stdafx.h"
#include "WarehouseClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	Warehouse::Warehouse(DataLayer::warehouseCollection wCollection)
	{
		id = std::get<0>(wCollection);
		name = std::get<1>(wCollection);
		address = std::get<2>(wCollection);
		phone = std::get<3>(wCollection);
		warehouseTypeID = std::get<4>(wCollection); 
		subaccountID = std::get<5>(wCollection);
	}
	Warehouse::Warehouse()
	{
		name = "";
		address = "";
		phone = "";
		subaccountID = 0;
		subaccountID = 0;
	}
	int Warehouse::GetID()
	{
		return id;
	}
	
	std::string Warehouse::GetName()
	{
		return name;
	}

	std::string Warehouse::GetAddress()
	{
		return address;
	}

	std::string Warehouse::GetPhone()
	{
		return phone;
	}

	int Warehouse::GetWarehouseTypeID()
	{
		return warehouseTypeID;
	}

	int Warehouse::GetSubaccountID()
	{
		return subaccountID;
	}


	void Warehouse::SetID(int cID)
	{
		id = cID;
	}

	void Warehouse::SetName(std::string wName)
	{
		if (!wName.empty())
			boost::trim(wName);
		name = wName;
	}
	void Warehouse::SetAddress(std::string wAddress)
	{
		if (!wAddress.empty())
			boost::trim(wAddress);
		address = wAddress;
	}

	void Warehouse::SetPhone(std::string wPhone)
	{
		if (!wPhone.empty())
			boost::trim(wPhone);
		phone = wPhone;
	}

	void Warehouse::SetWarehouseTypeID(int wTypeID)
	{
		warehouseTypeID = wTypeID;
	}

	void Warehouse::SetSubaccountID(int subaccID)
	{
		subaccountID = subaccID;
	}

	bool Warehouse::CreateWarehouse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wName, std::string wAddress, std::string wPhone,
		int wTypeID, int subaccID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, subaccID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(wName, wAddress, wPhone);
		name = wName;
		address = wAddress;
		phone = wPhone;
		warehouseTypeID = wTypeID;
		subaccountID = subaccID;
		if (0 != id && ormasDal.CreateWarehouse(id, name, address, phone, warehouseTypeID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Warehouse::CreateWarehouse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateWarehouse(id, name, address, phone, warehouseTypeID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Warehouse::DeleteWarehouse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteWarehouse(id, errorMessage))
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

	bool Warehouse::UpdateWarehouse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wName, std::string wAddress, std::string wPhone,
		int wTypeID, int subaccID, std::string& errorMessage)
	{
		TrimStrings(wName, wAddress, wPhone);
		name = wName;
		address = wAddress;
		phone = wPhone;
		warehouseTypeID = wTypeID;
		subaccountID = subaccID;
		if (0 != id && ormasDal.UpdateWarehouse(id, name, address, phone, warehouseTypeID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Warehouse::UpdateWarehouse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateWarehouse(id, name, address, phone, warehouseTypeID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Warehouse::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != warehouseTypeID || 0 != subaccountID || !name.empty() || !address.empty() || !phone.empty())
		{
			return ormasDal.GetFilterForWarehouse(id, name, address, phone, warehouseTypeID, subaccountID);
		}
		return "";
	}

	std::string Warehouse::GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> wIDList)
	{
		if (0 != id || 0 != warehouseTypeID || 0 != subaccountID || !name.empty() || !address.empty() || !phone.empty())
		{
			return ormasDal.GetINFilterForWarehouseID(wIDList);
		}
		return "";
	}

	bool Warehouse::GetWarehouseByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseViewCollection> warehouseVector = ormasDal.GetWarehouse(errorMessage, filter);
		if (0 != warehouseVector.size())
		{
			id = std::get<0>(warehouseVector.at(0));
			name = std::get<1>(warehouseVector.at(0));
			address = std::get<4>(warehouseVector.at(0));
			phone = std::get<5>(warehouseVector.at(0));
			warehouseTypeID = std::get<6>(warehouseVector.at(0));
			subaccountID = std::get<7>(warehouseVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Warehouse with this id";
		}
		return false;
	}

	std::vector<int>  Warehouse::GetAllWarehouseIDByTypeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage)
	{
		std::vector<int> wID;
		if (tID <= 0)
			return wID;
		warehouseTypeID = tID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseViewCollection> warehouseVector = ormasDal.GetWarehouse(errorMessage, filter);
		if (0 != warehouseVector.size())
		{
			for each (auto item in warehouseVector)
			{
				wID.push_back(std::get<0>(item));
			}
		}
		return wID;
	}

	int Warehouse::GetWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string filter = this->GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseViewCollection> warehouseVector = ormasDal.GetWarehouse(errorMessage, filter);
		if (0 != warehouseVector.size())
		{
			return std::get<0>(warehouseVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find Warehouse with this id";
		}
		return 0;
	}

	bool Warehouse::IsEmpty()
	{
		if (0 == id && 0 == warehouseTypeID && 0 == subaccountID && name == "" && address == "" && phone == "")
			return true;
		return false;
	}

	void Warehouse::Clear()
	{
		id = 0;
		name.clear();
		address.clear();
		phone.clear();
		warehouseTypeID = 0;
		subaccountID = 0;
	}

	void Warehouse::TrimStrings(std::string& wName, std::string& wAddress, std::string& wPhone)
	{
		if (!wName.empty())
			boost::trim(wName);
		if (!wAddress.empty())
			boost::trim(wAddress);
		if (!wPhone.empty())
			boost::trim(wPhone);
	}

	bool Warehouse::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int subaccID, std::string& errorMessage)
	{
		Warehouse warehouse;
		warehouse.Clear();
		errorMessage.clear();
		warehouse.SetSubaccountID(subaccID);
		std::string filter = warehouse.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseViewCollection> warehouseVector = ormasDal.GetWarehouse(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == warehouseVector.size())
		{
			return false;
		}
		errorMessage = "Warehouse with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Warehouse::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Warehouse warehouse;
		warehouse.Clear();
		errorMessage.clear();
		warehouse.SetSubaccountID(subaccountID);
		std::string filter = warehouse.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseViewCollection> warehouseVector = ormasDal.GetWarehouse(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == warehouseVector.size())
		{
			return false;
		}
		errorMessage = "Warehouse with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}
