#include "stdafx.h"
#include "SalaryClass.h"

namespace BusinessLayer{
	Salary::Salary(DataLayer::salariesCollection sCollection)
	{
		id = std::get<0>(sCollection);
		employeeID = std::get<1>(sCollection);
		value = std::get<2>(sCollection);
		currencyID = std::get<3>(sCollection);
		salaryTypeID = std::get<4>(sCollection);
		date = std::get<5>(sCollection);
		isBonus = std::get<6>(sCollection);
	}
	Salary::Salary()
	{
		id = 0;
		employeeID = 0;
		value = 0.0;
		currencyID = 0;
		salaryTypeID = 0;
		date = "";
		isBonus = false;
	}

	int Salary::GetID()
	{
		return id;
	}

	int Salary::GetEmployeeID()
	{
		return employeeID;
	}

	double Salary::GetValue()
	{
		return value;
	}

	int Salary::GetCurrencyID()
	{
		return currencyID;
	}

	int Salary::GetSalaryTypeID()
	{
		return salaryTypeID;
	}

	std::string Salary::GetDate()
	{
		return date;
	}

	bool Salary::GetIsBonus()
	{
		return isBonus;
	}

	void Salary::SetID(int sID)
	{
		id = sID;
	}

	void Salary::SetEmployeeID(int eID)
	{
		employeeID = eID;
	}
	void Salary::SetValue(double bValue)
	{
		value = bValue;
	}
	void Salary::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	void Salary::SetSalaryTypeID(int stID)
	{
		salaryTypeID = stID;
	}

	void Salary::SetDate(std::string bDate)
	{
		date = bDate;
	}

	void Salary::SetIsBonus(bool sIsBonus)
	{
		isBonus = sIsBonus;
	}

	bool Salary::CreateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sValue, int cID, int stID, std::string sDate,
		bool sIsBonus, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, sValue, cID, sDate, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		employeeID = uID;
		value = sValue;
		currencyID = cID;
		salaryTypeID = stID;
		date = sDate;
		isBonus = sIsBonus;
		if (0 != employeeID && ormasDal.CreateSalary(id, employeeID, value, currencyID, salaryTypeID, date, isBonus, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Salary::CreateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateSalary(id, employeeID, value, currencyID, salaryTypeID, date, isBonus, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Salary::DeleteSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSalary(id, errorMessage))
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

	bool Salary::UpdateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sValue, int cID, int stID, std::string sDate,
		bool sIsBonus, std::string& errorMessage)
	{
		employeeID = uID;
		value = sValue;
		currencyID = cID;
		salaryTypeID = stID;
		date = sDate;
		isBonus = sIsBonus;
		if (0 != employeeID && ormasDal.UpdateSalary(id, employeeID, value, currencyID, salaryTypeID, date, isBonus, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Salary::UpdateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateSalary(id, employeeID, value, currencyID, salaryTypeID, date, isBonus, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Salary::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || 0 != value || 0 != currencyID || 0 != salaryTypeID || !date.empty())
		{
			return ormasDal.GetFilterForSalary(id, employeeID, value, currencyID, salaryTypeID, date, isBonus);
		}
		return "";
	}

	bool Salary::GetSalaryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::salariesViewCollection> salaryVector = ormasDal.GetSalaries(errorMessage, filter);
		if (0 != salaryVector.size())
		{
			id = std::get<0>(salaryVector.at(0));
			employeeID = std::get<1>(salaryVector.at(0));
			date = std::get<5>(salaryVector.at(0));
			value = std::get<6>(salaryVector.at(0));
			currencyID = std::get<9>(salaryVector.at(0));
			salaryTypeID = std::get<10>(salaryVector.at(0));
			isBonus = std::get<11>(salaryVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Salary with this id";
		}
		return false;
	}

	bool Salary::IsEmpty()
	{
		if (0 == id  && 0 == employeeID && 0.0 == value && 0 == currencyID && 0 == salaryTypeID && date.empty() && isBonus == false)
			return true;
		return false;
	}

	void Salary::Clear()
	{
		id = 0;
		employeeID = 0;
		value = 0;
		currencyID = 0;
		salaryTypeID = 0;
		date.clear();
		isBonus = false;
	}
	
	bool Salary::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sValue, int cID, std::string sDate, std::string& errorMessage)
	{
		Salary salary;
		salary.Clear();
		errorMessage.clear();
		salary.SetEmployeeID(uID);
		salary.SetValue(sValue);
		salary.SetCurrencyID(cID);
		salary.SetDate(sDate);
		std::string filter = salary.GenerateFilter(ormasDal);
		std::vector<DataLayer::salariesViewCollection> salaryVector = ormasDal.GetSalaries(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == salaryVector.size())
		{
			return false;
		}
		errorMessage = "Salary with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Salary::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Salary salary;
		salary.Clear();
		errorMessage.clear();
		salary.SetEmployeeID(employeeID);
		salary.SetValue(value);
		salary.SetCurrencyID(currencyID);
		salary.SetDate(date);
		std::string filter = salary.GenerateFilter(ormasDal);
		std::vector<DataLayer::salariesViewCollection> salaryVector = ormasDal.GetSalaries(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == salaryVector.size())
		{
			return false;
		}
		errorMessage = "Salary with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}