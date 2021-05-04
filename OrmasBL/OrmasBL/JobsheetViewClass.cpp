#include "stdafx.h"
#include "JobsheetViewClass.h"

namespace BusinessLayer{
	JobsheetView::JobsheetView(DataLayer::jobsheetViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		employeeName = std::get<2>(pCollection);
		employeeSurname = std::get<3>(pCollection);
		employeePhone = std::get<4>(pCollection);
		productName = std::get<5>(pCollection);
		count = std::get<6>(pCollection);
		measureName = std::get<7>(pCollection);
		productID = std::get<8>(pCollection);
		employeeID = std::get<9>(pCollection);
	}

	std::string JobsheetView::GetEmployeeName()
	{
		return employeeName;
	}

	std::string JobsheetView::GetEmployeeSurname()
	{
		return employeeSurname;
	}

	std::string JobsheetView::GetEmployeePhone()
	{
		return employeePhone;
	}

	std::string JobsheetView::GetProductName()
	{
		return productName;
	}

	std::string JobsheetView::GetMeasureName()
	{
		return measureName;
	}

	void JobsheetView::SetEmployeeName(std::string jEmployeeName)
	{
		employeeName = jEmployeeName;
	}

	void JobsheetView::SetEmployeeSurname(std::string jEmployeeSurname)
	{
		employeeSurname = jEmployeeSurname;
	}

	void JobsheetView::SetEmployeePhone(std::string jEmployeePhone)
	{
		employeePhone = jEmployeePhone;
	}

	void JobsheetView::SetProductName(std::string jProductName)
	{
		productName = jProductName;
	}

	void JobsheetView::SetMeasureName(std::string jMeasureName)
	{
		measureName = jMeasureName;
	}

	std::string JobsheetView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || employeeName.empty() || employeeSurname.empty() || employeePhone.empty() || productName.empty() || 0.0 != count 
			|| measureName.empty() || 0 != productID || 0 != employeeID)
		{
			return ormasDal.GetFilterForJobsheetView(id, date, employeeName, employeeSurname, employeePhone, productName, count, measureName, productID, employeeID);
		}
		return "";
	}
}