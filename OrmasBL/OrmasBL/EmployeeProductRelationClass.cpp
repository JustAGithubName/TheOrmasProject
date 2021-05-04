#include "stdafx.h"
#include "EmployeeProductRelationClass.h"


namespace BusinessLayer{
	EmployeeProductRelation::EmployeeProductRelation(DataLayer::employeeProductCollection aeCollection)
	{
		id = std::get<0>(aeCollection);
		employeeID = std::get<1>(aeCollection);
		productID = std::get<2>(aeCollection);
	}
	EmployeeProductRelation::EmployeeProductRelation()
	{
		id = 0;
		employeeID = 0;
		productID = 0;
	}

	int EmployeeProductRelation::GetID()
	{
		return id;
	}

	int EmployeeProductRelation::GetProductID()
	{
		return productID;
	}

	int EmployeeProductRelation::GetEmployeeID()
	{
		return employeeID;
	}

	void EmployeeProductRelation::SetID(int epID)
	{
		id = epID;
	}
	void EmployeeProductRelation::SetProductID(int pID)
	{
		productID = pID;
	}
	void EmployeeProductRelation::SetEmployeeID(int eID)
	{
		employeeID = eID;
	}

	bool EmployeeProductRelation::CreateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, eID, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		employeeID = eID;
		productID = pID;

		if (ormasDal.CreateEmployeeProduct(id, employeeID, productID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EmployeeProductRelation::CreateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateEmployeeProduct(id, employeeID, productID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EmployeeProductRelation::DeleteEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteEmployeeProduct(employeeID, productID, errorMessage))
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

	bool EmployeeProductRelation::UpdateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, eID, pID, errorMessage))
			return false;
		employeeID = eID;
		productID = pID;
		if (ormasDal.UpdateEmployeeProduct(id, employeeID, productID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool EmployeeProductRelation::UpdateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (ormasDal.UpdateEmployeeProduct(id, employeeID, productID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string EmployeeProductRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || 0 != productID)
		{
			return ormasDal.GetFilterForEmployeeProduct(id, employeeID, productID);
		}
		return "";
	}

	bool EmployeeProductRelation::GetEmployeeProductByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		id = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::employeeProductViewCollection> employeeProductVector = ormasDal.GetEmployeeProduct(errorMessage, filter);
		if (0 != employeeProductVector.size())
		{
			id = std::get<0>(employeeProductVector.at(0));
			employeeID = std::get<6>(employeeProductVector.at(0));
			productID = std::get<7>(employeeProductVector.at(0));
			return true;
		}
		return false;
	}

	std::vector<int> EmployeeProductRelation::GetAllEmployeeByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> employeeIDVector;
		EmployeeProductRelation aeRelation;
		aeRelation.SetProductID(pID);
		aeRelation.SetEmployeeID(0);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::employeeProductViewCollection> employeeProductVector = ormasDal.GetEmployeeProduct(errorMessage, filter);
		if (0 != employeeProductVector.size())
		{
			for each (auto item in employeeProductVector)
			{
				employeeIDVector.push_back(std::get<6>(item));
			}
		}
		return employeeIDVector;
	}

	std::vector<int> EmployeeProductRelation::GetAllProductByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		std::vector<int> productIDVector;
		EmployeeProductRelation aeRelation;
		aeRelation.SetEmployeeID(eID);
		aeRelation.SetProductID(0);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::employeeProductViewCollection> employeeProductVector = ormasDal.GetEmployeeProduct(errorMessage, filter);
		if (0 != employeeProductVector.size())
		{
			for each (auto item in employeeProductVector)
			{
				productIDVector.push_back(std::get<7>(item));
			}
		}
		return productIDVector;
	}


	bool EmployeeProductRelation::IsEmpty()
	{
		if (0 == id && 0 == employeeID && 0 == productID)
			return true;
		return false;
	}

	void EmployeeProductRelation::Clear()
	{
		id = 0;
		employeeID = 0;
		productID = 0;
	}

	bool EmployeeProductRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int pID, std::string& errorMessage)
	{
		EmployeeProductRelation apRelation;
		apRelation.Clear();
		errorMessage.clear();
		apRelation.SetEmployeeID(eID);
		apRelation.SetProductID(pID);
		std::string filter = apRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::employeeProductViewCollection> employeeProductVector = ormasDal.GetEmployeeProduct(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == employeeProductVector.size())
		{
			return false;
		}
		errorMessage = "Employee-Product Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool EmployeeProductRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		EmployeeProductRelation apRelation;
		apRelation.Clear();
		errorMessage.clear();
		apRelation.SetEmployeeID(employeeID);
		apRelation.SetProductID(productID);
		std::string filter = apRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::employeeProductViewCollection> employeeProductVector = ormasDal.GetEmployeeProduct(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == employeeProductVector.size())
		{
			return false;
		}
		errorMessage = "Employee-Product Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}