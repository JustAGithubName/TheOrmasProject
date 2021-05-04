#include "stdafx.h"
#include "ConsumeProductViewClass.h"

namespace BusinessLayer
{
	ConsumeProductView::ConsumeProductView(DataLayer::consumeProductsViewCollection cCollection)
	{
		id = std::get<0>(cCollection);
		date = std::get<1>(cCollection);
		executionDate = std::get<2>(cCollection);
		statusCode = std::get<3>(cCollection);
		statusName = std::get<4>(cCollection);
		employeeName = std::get<5>(cCollection);
		employeeSurname = std::get<6>(cCollection);
		employeePhone = std::get<7>(cCollection);
		employeePosition = std::get<8>(cCollection);
		stockEmployeeName = std::get<9>(cCollection);
		stockEmployeeSurname = std::get<10>(cCollection);
		stockEmployeePhone = std::get<11>(cCollection);
		stockEmployeePosition = std::get<12>(cCollection);
		count = std::get<13>(cCollection);
		sum = std::get<14>(cCollection);
		currencyName = std::get<15>(cCollection);
		stockEmployeeID = std::get<16>(cCollection);
		employeeID = std::get<17>(cCollection);
		statusID = std::get<18>(cCollection);
		currencyID = std::get<19>(cCollection);
	}

	std::string ConsumeProductView::GetStatusCode()
	{
		return statusCode;
	}
	std::string ConsumeProductView::GetStatusName()
	{
		return statusName;
	}
	std::string ConsumeProductView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string ConsumeProductView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string ConsumeProductView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string ConsumeProductView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string ConsumeProductView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string ConsumeProductView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string ConsumeProductView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string ConsumeProductView::GetStockEmployeePosition()
	{
		return stockEmployeePosition;
	}
	std::string ConsumeProductView::GetCurrencyName()
	{
		return currencyName;
	}

	void ConsumeProductView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void ConsumeProductView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ConsumeProductView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void ConsumeProductView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void ConsumeProductView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void ConsumeProductView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void ConsumeProductView::SetStockEmployeeName(std::string eStockEmployeeName)
	{
		stockEmployeeName = eStockEmployeeName;
	}
	void ConsumeProductView::SetStockEmployeeSurname(std::string eStockEmployeeSurname)
	{
		stockEmployeeSurname = eStockEmployeeSurname;
	}
	void ConsumeProductView::SetStockEmployeePhone(std::string eStockEmployeePhone)
	{
		stockEmployeePhone = eStockEmployeePhone;
	}
	void ConsumeProductView::SetStockEmployeePosition(std::string eStockEmployeePosition)
	{
		stockEmployeePosition = eStockEmployeePosition;
	}
	void ConsumeProductView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string ConsumeProductView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty()
			|| !stockEmployeePhone.empty() || !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != stockEmployeeID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForConProdView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				stockEmployeeName, stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName,stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}
}

