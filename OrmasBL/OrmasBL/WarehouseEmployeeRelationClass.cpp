#include "stdafx.h"
#include "WarehouseEmployeeRelationClass.h"
#include "EmployeeClass.h"


namespace BusinessLayer{
	WarehouseEmployeeRelation::WarehouseEmployeeRelation(DataLayer::warehouseEmployeeCollection weCollection)
	{
		id = std::get<0>(weCollection);
		warehouseID = std::get<1>(weCollection);
		employeeID = std::get<2>(weCollection);
	}
	WarehouseEmployeeRelation::WarehouseEmployeeRelation()
	{
		id = 0;
		warehouseID = 0;
		employeeID = 0;
	}

	int WarehouseEmployeeRelation::GetID()
	{
		return id;
	}

	int WarehouseEmployeeRelation::GetWarehouseID()
	{
		return warehouseID;
	}

	int WarehouseEmployeeRelation::GetEmployeeID()
	{
		return employeeID;
	}

	void WarehouseEmployeeRelation::SetID(int ceID)
	{
		id = ceID;
	}
	void WarehouseEmployeeRelation::SetWarehouseID(int wID)
	{
		warehouseID = wID;
	}
	void WarehouseEmployeeRelation::SetEmployeeID(int eID)
	{
		employeeID = eID;
	}

	bool WarehouseEmployeeRelation::CreateWarehouseEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int eID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, wID, eID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		warehouseID = wID;
		employeeID = eID;

		if (ormasDal.CreateWarehouseEmployee(id, warehouseID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool WarehouseEmployeeRelation::CreateWarehouseEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateWarehouseEmployee(id, warehouseID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool WarehouseEmployeeRelation::DeleteWarehouseEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteWarehouseEmployee(warehouseID, employeeID, errorMessage))
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

	bool WarehouseEmployeeRelation::UpdateWarehouseEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int eID, std::string& errorMessage)
	{
		warehouseID = wID;
		employeeID = eID;
		if (0 != id && ormasDal.UpdateWarehouseEmployee(id, warehouseID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool WarehouseEmployeeRelation::UpdateWarehouseEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateWarehouseEmployee(id, warehouseID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string WarehouseEmployeeRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != warehouseID || 0 != employeeID)
		{
			return ormasDal.GetFilterForWarehouseEmployee(id, warehouseID, employeeID);
		}
		return "";
	}

	bool WarehouseEmployeeRelation::GetWarehouseEmployeeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, std::string& errorMessage)
	{
		if (id <= 0)
			return false;
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetID(id);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 != warehouseEmployeeVector.size())
		{
			id = std::get<0>(warehouseEmployeeVector.at(0));
			warehouseID = std::get<7>(warehouseEmployeeVector.at(0));
			employeeID = std::get<8>(warehouseEmployeeVector.at(0));
			return true;
		}
		return false;
	}

	bool WarehouseEmployeeRelation::GetWarehouseEmployeeByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		if (wID <= 0)
			return false;
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetWarehouseID(wID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 != warehouseEmployeeVector.size())
		{
			id = std::get<0>(warehouseEmployeeVector.at(0));
			warehouseID = std::get<7>(warehouseEmployeeVector.at(0));
			employeeID = std::get<8>(warehouseEmployeeVector.at(0));
			return true;
		}
		return false;
	}

	bool WarehouseEmployeeRelation::GetWarehouseEmployeeByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(eID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 != warehouseEmployeeVector.size())
		{
			id = std::get<0>(warehouseEmployeeVector.at(0));
			warehouseID = std::get<7>(warehouseEmployeeVector.at(0));
			employeeID = std::get<8>(warehouseEmployeeVector.at(0));
			return true;
		}
		return false;
	}

	int WarehouseEmployeeRelation::GetWarehouseIDByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(eID);
		ceRelation.SetWarehouseID(0);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 != warehouseEmployeeVector.size())
		{
			return std::get<7>(warehouseEmployeeVector.at(0));
		}
		return 0;
	}

	int WarehouseEmployeeRelation::GetEmployeeIDByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(0);
		ceRelation.SetWarehouseID(wID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 != warehouseEmployeeVector.size())
		{
			return std::get<8>(warehouseEmployeeVector.at(0));
		}
		return 0;
	}


	bool WarehouseEmployeeRelation::IsEmpty()
	{
		if (0 == id && 0 == warehouseID && 0 == employeeID)
			return true;
		return false;
	}

	void WarehouseEmployeeRelation::Clear()
	{
		id = 0;
		warehouseID = 0;
		employeeID = 0;
	}

	bool WarehouseEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRelation;
		weRelation.Clear();
		errorMessage.clear();
		weRelation.SetWarehouseID(cID);
		weRelation.SetEmployeeID(eID);
		std::string filter = weRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == warehouseEmployeeVector.size())
		{
			return false;
		}
		errorMessage = "Warehouse-employee Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool WarehouseEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		WarehouseEmployeeRelation weRelation;
		weRelation.Clear();
		errorMessage.clear();
		weRelation.SetWarehouseID(warehouseID);
		weRelation.SetEmployeeID(employeeID);
		std::string filter = weRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == warehouseEmployeeVector.size())
		{
			return false;
		}
		errorMessage = "Warehouse-employee Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::vector<int> WarehouseEmployeeRelation::GetWarehouseIDListByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID)
	{
		std::vector<int> warehouseIDVector;
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(eID);
		ceRelation.SetWarehouseID(0);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 < warehouseEmployeeVector.size())
		{
			for each (auto weItem in warehouseEmployeeVector)
			{
				warehouseIDVector.push_back(std::get<7>(weItem));
			}
		}
		return warehouseIDVector;
	}

	std::vector<int> WarehouseEmployeeRelation::GetEmployeeIDListByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID)
	{
		std::vector<int> employeeIDVector;
		WarehouseEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(0);
		ceRelation.SetWarehouseID(wID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::warehouseEmployeeViewCollection> warehouseEmployeeVector = ormasDal.GetWarehouseEmployee(errorMessage, filter);
		if (0 < warehouseEmployeeVector.size())
		{
			for each (auto weItem in warehouseEmployeeVector)
			{
				employeeIDVector.push_back(std::get<8>(weItem));
			}
		}
		return employeeIDVector;
	}
}