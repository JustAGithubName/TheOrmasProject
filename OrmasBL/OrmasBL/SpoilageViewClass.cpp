#include "stdafx.h"
#include "SpoilageViewClass.h"

namespace BusinessLayer
{
	SpoilageView::SpoilageView(DataLayer::spoilageViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		date = std::get<1>(sCollection);
		count = std::get<2>(sCollection);
		sum = std::get<3>(sCollection);
		currencyName = std::get<4>(sCollection);
		statusName = std::get<5>(sCollection);
		employeeName = std::get<6>(sCollection);
		employeeSurname = std::get<7>(sCollection);
		employeePhone = std::get<8>(sCollection);
		employeePosition = std::get<9>(sCollection);
		employeeID = std::get<10>(sCollection);
		statusID = std::get<11>(sCollection);
		currencyID = std::get<12>(sCollection);
	}

	std::string SpoilageView::GetStatusName()
	{
		return statusName;
	}
	std::string SpoilageView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string SpoilageView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string SpoilageView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string SpoilageView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string SpoilageView::GetCurrencyName()
	{
		return currencyName;
	}

	
	void SpoilageView::SetStatusName(std::string rRtatusName)
	{
		statusName = rRtatusName;
	}
	void SpoilageView::SetEmployeeName(std::string rEmployeeName)
	{
		employeeName = rEmployeeName;
	}
	void SpoilageView::SetEmployeeSurname(std::string rEmployeeSurname)
	{
		employeeSurname = rEmployeeSurname;
	}
	void SpoilageView::SetEmployeePhone(std::string rEmployeePhone)
	{
		employeePhone = rEmployeePhone;
	}
	void SpoilageView::SetEmployeePosition(std::string rEmployeePosition)
	{
		employeePosition = rEmployeePosition;
	}
	void SpoilageView::SetCurrencyName(std::string rCurrencyName)
	{
		currencyName = rCurrencyName;
	}

	std::string SpoilageView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		
		if (0 != id || !date.empty() || 0 != count || 0 != sum || !currencyName.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty() || !employeePhone.empty() || !employeePosition.empty()
			 || 0 != employeeID  || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForSpoilageView(id, date, count, sum, currencyName, statusName, employeeName, employeeSurname, employeePhone,
				employeePosition, employeeID, statusID, currencyID);
		}
		return "";
	}
}

