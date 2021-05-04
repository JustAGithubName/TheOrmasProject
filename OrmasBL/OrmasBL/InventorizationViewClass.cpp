#include "stdafx.h"
#include "InventorizationViewClass.h"

namespace BusinessLayer
{
	InventorizationView::InventorizationView(DataLayer::inventorizationsViewCollection iCollection)
	{
		id = std::get<0>(iCollection);
		date = std::get<1>(iCollection);
		executionDate = std::get<2>(iCollection);
		statusCode = std::get<3>(iCollection);
		statusName = std::get<4>(iCollection);
		employeeName = std::get<5>(iCollection);
		employeeSurname = std::get<6>(iCollection);
		employeePhone = std::get<7>(iCollection);
		employeePosition = std::get<8>(iCollection);
		stockEmployeeName = std::get<9>(iCollection);
		stockEmployeeSurname = std::get<10>(iCollection);
		stockEmployeePhone = std::get<11>(iCollection);
		stockEmployeePosition = std::get<12>(iCollection);
		count = std::get<13>(iCollection);
		sum = std::get<14>(iCollection);
		currencyName = std::get<15>(iCollection);
		stockEmployeeID = std::get<16>(iCollection);
		employeeID = std::get<17>(iCollection);
		statusID = std::get<18>(iCollection);
		currencyID = std::get<19>(iCollection);
	}

	std::string InventorizationView::GetStatusCode()
	{
		return statusCode;
	}
	std::string InventorizationView::GetStatusName()
	{
		return statusName;
	}
	std::string InventorizationView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string InventorizationView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string InventorizationView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string InventorizationView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string InventorizationView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string InventorizationView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string InventorizationView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string InventorizationView::GetStockEmployeePosition()
	{
		return stockEmployeePhone;
	}
	std::string InventorizationView::GetCurrencyName()
	{
		return currencyName;
	}

	void InventorizationView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void InventorizationView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void InventorizationView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void InventorizationView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void InventorizationView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void InventorizationView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void InventorizationView::SetStockEmployeeName(std::string eStockEmployeeName)
	{
		stockEmployeeName = eStockEmployeeName;
	}
	void InventorizationView::SetStockEmployeeSurname(std::string eStockEmployeeSurname)
	{
		stockEmployeeSurname = eStockEmployeeSurname;
	}
	void InventorizationView::SetStockEmployeePhone(std::string eStockEmployeePhone)
	{
		stockEmployeePhone = eStockEmployeePhone;
	}
	void InventorizationView::SetStockEmployeePosition(std::string eStockEmployeePosition)
	{
		stockEmployeePosition = eStockEmployeePosition;
	}
	void InventorizationView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string InventorizationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty()
			|| !stockEmployeePhone.empty() || !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != stockEmployeeID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForInvView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				stockEmployeeName, stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName, stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}
}

