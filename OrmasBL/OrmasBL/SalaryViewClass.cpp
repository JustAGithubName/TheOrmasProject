#include "stdafx.h"
#include "SalaryViewClass.h"

namespace BusinessLayer{
	SalaryView::SalaryView(DataLayer::salariesViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		employeeID = std::get<1>(sCollection);
		employeeName = std::get<2>(sCollection);
		employeeSurname = std::get<3>(sCollection);
		employeePhone = std::get<4>(sCollection);
		date = std::get<5>(sCollection);
		value = std::get<6>(sCollection);
		currencyName = std::get<7>(sCollection);
		salaryTypeName = std::get<8>(sCollection);
		currencyID = std::get<9>(sCollection);
		salaryTypeID = std::get<10>(sCollection);
		isBonus = std::get<11>(sCollection);
	}

	std::string SalaryView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string SalaryView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string SalaryView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string SalaryView::GetCurrencyName()
	{
		return currencyName;
	}
	std::string SalaryView::GetSalaryTypeName()
	{
		return salaryTypeName;
	}

	void SalaryView::SetEmployeeName(std::string sEmployeeName)
	{
		employeeName = sEmployeeName;
	}
	void SalaryView::SetEmployeeSurname(std::string sEmployeeSurname)
	{
		employeeSurname = sEmployeeSurname;
	}
	void SalaryView::SetEmployeePhone(std::string sEmployeePhone)
	{
		employeePhone = sEmployeePhone;
	}
	void SalaryView::SetCurrencyName(std::string sCurrencyName)
	{
		currencyName = sCurrencyName;
	}
	void SalaryView::SetSalaryTypeName(std::string sSalaryTypeName)
	{
		sSalaryTypeName = sSalaryTypeName;
	}

	std::string SalaryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !employeeName.empty() || !employeeSurname.empty() || !employeePhone.empty() || !currencyName.empty() || !salaryTypeName.empty()
			|| 0 != employeeID || 0 != value || 0 != currencyID || 0 != salaryTypeID || !date.empty())
		{
			return ormasDal.GetFilterForSalariesView(id, employeeID, employeeName, employeeSurname, employeePhone, date, value, currencyName, salaryTypeName
				, currencyID, salaryTypeID);
		}
		return "";
	}
}