#include "stdafx.h"
#include "DivisionEmployeeRelationClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	DivisionEmployeeRelation::DivisionEmployeeRelation(DataLayer::divisionEmployeeCollection dCollection)
	{
		id = std::get<0>(dCollection);
		divisionID = std::get<1>(dCollection);
		employeeID = std::get<2>(dCollection);
		isContract = std::get<3>(dCollection);
	}
	DivisionEmployeeRelation::DivisionEmployeeRelation()
	{
		divisionID = 0;
		employeeID = 0;
		isContract = false;
	}

	int DivisionEmployeeRelation::GetID()
	{
		return id;
	}

	int DivisionEmployeeRelation::GetDivisionID()
	{
		return divisionID;
	}

	int DivisionEmployeeRelation::GetEmployeeID()
	{
		return employeeID;
	}

	bool DivisionEmployeeRelation::GetIsContract()
	{
		return isContract;
	}

	void DivisionEmployeeRelation::SetID(int dID)
	{
		id = dID;
	}
	void DivisionEmployeeRelation::SetDivisionID(int dDivisionID)
	{
		divisionID = dDivisionID;
	}
	void DivisionEmployeeRelation::SetEmployeeID(int dEmployeeID)
	{
		employeeID = dEmployeeID;
	}
	
	void DivisionEmployeeRelation::SetIsContract(bool dIsContract)
	{
		isContract = dIsContract;
	}

	bool DivisionEmployeeRelation::CreateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dEmployeeID, bool dIsContract, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, dDivisionID, dEmployeeID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		divisionID = dDivisionID;
		employeeID = dEmployeeID;
		isContract = dIsContract;
		if (0 != id && ormasDal.CreateDivisionEmployee(id, divisionID, employeeID, isContract, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool DivisionEmployeeRelation::CreateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateDivisionEmployee(id, divisionID, employeeID, isContract, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool DivisionEmployeeRelation::DeleteDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteDivisionEmployee(divisionID, employeeID, errorMessage))
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

	bool DivisionEmployeeRelation::UpdateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dEmployeeID, bool dIsContract, std::string& errorMessage)
	{
		divisionID = dDivisionID;
		employeeID = dEmployeeID;
		isContract = dIsContract;
		if (0 != id && ormasDal.UpdateDivisionEmployee(id, divisionID, employeeID, isContract, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool DivisionEmployeeRelation::UpdateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateDivisionEmployee(id, divisionID, employeeID, isContract, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string DivisionEmployeeRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != divisionID || 0 != employeeID)
		{
			return ormasDal.GetFilterForDivisionEmployee(id, divisionID, employeeID, isContract);
		}
		return "";
	}

	bool DivisionEmployeeRelation::GetDivisionEmployeeRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string& errorMessage)
	{
		if (dID <= 0)
			return false;
		id = dID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionEmployeeCollection> DivisionEmployeeRelationVector = ormasDal.GetDivisionEmployee(errorMessage, filter);
		if (0 != DivisionEmployeeRelationVector.size())
		{
			id = std::get<0>(DivisionEmployeeRelationVector.at(0));
			divisionID = std::get<1>(DivisionEmployeeRelationVector.at(0));
			employeeID = std::get<2>(DivisionEmployeeRelationVector.at(0));
			isContract = std::get<3>(DivisionEmployeeRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find division employee relation with this id";
		}
		return false;
	}

	bool DivisionEmployeeRelation::GetDivisionEmployeeRelationByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		employeeID = eID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionEmployeeCollection> DivisionEmployeeRelationVector = ormasDal.GetDivisionEmployee(errorMessage, filter);
		if (0 != DivisionEmployeeRelationVector.size())
		{
			id = std::get<0>(DivisionEmployeeRelationVector.at(0));
			divisionID = std::get<1>(DivisionEmployeeRelationVector.at(0));
			employeeID = std::get<2>(DivisionEmployeeRelationVector.at(0));
			isContract = std::get<3>(DivisionEmployeeRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find division employee relation with this id";
		}
		return false;
	}


	bool DivisionEmployeeRelation::IsEmpty()
	{
		if (0 == id && 0 == divisionID && 0 == employeeID && isContract == false)
			return true;
		return false;
	}

	void DivisionEmployeeRelation::Clear()
	{
		id = 0;
		divisionID = 0;
		employeeID = 0;
		isContract = false;
	}

	bool DivisionEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dEmployeeID, std::string& errorMessage)
	{
		DivisionEmployeeRelation divisionEmployeeRelation;
		divisionEmployeeRelation.Clear();
		errorMessage.clear();
		divisionEmployeeRelation.SetDivisionID(dDivisionID);
		divisionEmployeeRelation.SetEmployeeID(dEmployeeID);
		std::string filter = divisionEmployeeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionEmployeeCollection> divisionEmployeeRelationVector = ormasDal.GetDivisionEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == divisionEmployeeRelationVector.size())
		{
			return false;
		}
		errorMessage = "Division employee relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool DivisionEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		DivisionEmployeeRelation divisionEmployeeRelation;
		divisionEmployeeRelation.Clear();
		errorMessage.clear();
		divisionEmployeeRelation.SetDivisionID(divisionID);
		divisionEmployeeRelation.SetEmployeeID(employeeID);
		std::string filter = divisionEmployeeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::divisionEmployeeCollection> divisionEmployeeRelationVector = ormasDal.GetDivisionEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == divisionEmployeeRelationVector.size())
		{
			return false;
		}
		errorMessage = "Division employee relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

