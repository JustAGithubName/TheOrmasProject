#include "stdafx.h"
#include "CashboxEmployeeRelationClass.h"
#include "EmployeeClass.h"


namespace BusinessLayer{
	CashboxEmployeeRelation::CashboxEmployeeRelation(DataLayer::cashboxEmployeeCollection ceCollection)
	{
		id = std::get<0>(ceCollection);
		cashboxID = std::get<1>(ceCollection);
		employeeID = std::get<2>(ceCollection);
	}
	CashboxEmployeeRelation::CashboxEmployeeRelation()
	{
		id = 0;
		cashboxID = 0;
		employeeID = 0;
	}

	int CashboxEmployeeRelation::GetID()
	{
		return id;
	}

	int CashboxEmployeeRelation::GetCashboxID()
	{
		return cashboxID;
	}

	int CashboxEmployeeRelation::GetEmployeeID()
	{
		return employeeID;
	}

	void CashboxEmployeeRelation::SetID(int ceID)
	{
		id = ceID;
	}
	void CashboxEmployeeRelation::SetCashboxID(int cID)
	{
		cashboxID = cID;
	}
	void CashboxEmployeeRelation::SetEmployeeID(int aID)
	{
		employeeID = aID;
	}

	bool CashboxEmployeeRelation::CreateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, cID, eID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		cashboxID = cID;
		employeeID = eID;

		if (ormasDal.CreateCashboxEmployee(id, cashboxID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CashboxEmployeeRelation::CreateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateCashboxEmployee(id, cashboxID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CashboxEmployeeRelation::DeleteCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCashboxEmployee(cashboxID, employeeID, errorMessage))
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

	bool CashboxEmployeeRelation::UpdateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, std::string& errorMessage)
	{
		cashboxID = cID;
		employeeID = eID;
		if (0 != id && ormasDal.UpdateCashboxEmployee(id, cashboxID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CashboxEmployeeRelation::UpdateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateCashboxEmployee(id, cashboxID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string CashboxEmployeeRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != cashboxID || 0 != employeeID)
		{
			return ormasDal.GetFilterForCashboxEmployee(id, cashboxID, employeeID);
		}
		return "";
	}

	bool CashboxEmployeeRelation::GetCashboxEmployeeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, std::string& errorMessage)
	{
		if (id <= 0)
			return false;
		CashboxEmployeeRelation ceRelation;
		ceRelation.SetID(id);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxEmployeeViewCollection> CashboxEmployeeVector = ormasDal.GetCashboxEmployee(errorMessage, filter);
		if (0 != CashboxEmployeeVector.size())
		{
			id = std::get<0>(CashboxEmployeeVector.at(0));
			cashboxID = std::get<7>(CashboxEmployeeVector.at(0));
			employeeID = std::get<8>(CashboxEmployeeVector.at(0));
			return true;
		}
		return false;
	}

	int CashboxEmployeeRelation::GetCashboxIDByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		CashboxEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(eID);
		ceRelation.SetCashboxID(0);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxEmployeeViewCollection> cashboxEmployeeVector = ormasDal.GetCashboxEmployee(errorMessage, filter);
		if (0 != cashboxEmployeeVector.size())
		{
			return std::get<7>(cashboxEmployeeVector.at(0));
		}
		return 0;
	}

	bool CashboxEmployeeRelation::GetCashboxEmployeeByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		CashboxEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(eID);
		ceRelation.SetCashboxID(0);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxEmployeeViewCollection> CashboxEmployeeVector = ormasDal.GetCashboxEmployee(errorMessage, filter);
		if (0 != CashboxEmployeeVector.size())
		{
			id = std::get<0>(CashboxEmployeeVector.at(0));
			cashboxID = std::get<7>(CashboxEmployeeVector.at(0));
			employeeID = std::get<8>(CashboxEmployeeVector.at(0));
			return true;
		}
		return false;
	}

	int CashboxEmployeeRelation::GetEmployeeIDByCashboxID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		CashboxEmployeeRelation ceRelation;
		ceRelation.SetEmployeeID(0);
		ceRelation.SetCashboxID(cID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxEmployeeViewCollection> cashboxEmployeeVector = ormasDal.GetCashboxEmployee(errorMessage, filter);
		if (0 != cashboxEmployeeVector.size())
		{
			return std::get<8>(cashboxEmployeeVector.at(0));
		}
		return 0;
	}


	bool CashboxEmployeeRelation::IsEmpty()
	{
		if (0 == id && 0 ==cashboxID && 0 == employeeID)
			return true;
		return false;
	}

	void CashboxEmployeeRelation::Clear()
	{
		id = 0;
		cashboxID = 0;
		employeeID = 0;
	}

	bool CashboxEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, std::string& errorMessage)
	{
		CashboxEmployeeRelation ceRelation;
		ceRelation.Clear();
		errorMessage.clear();
		ceRelation.SetCashboxID(cID);
		ceRelation.SetEmployeeID(eID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxEmployeeViewCollection> cashboxEmployeeVector = ormasDal.GetCashboxEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == cashboxEmployeeVector.size())
		{
			return false;
		}
		errorMessage = "Cashbox-employee Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool CashboxEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		CashboxEmployeeRelation ceRelation;
		ceRelation.Clear();
		errorMessage.clear();
		ceRelation.SetCashboxID(cashboxID);
		ceRelation.SetEmployeeID(employeeID);
		std::string filter = ceRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxEmployeeViewCollection> cashboxEmployeeVector = ormasDal.GetCashboxEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == cashboxEmployeeVector.size())
		{
			return false;
		}
		errorMessage = "Cashbox-employee Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}