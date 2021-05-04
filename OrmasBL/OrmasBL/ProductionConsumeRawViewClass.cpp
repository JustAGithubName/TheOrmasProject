#include "stdafx.h"
#include "ProductionConsumeRawViewClass.h"

namespace BusinessLayer
{
	ProductionConsumeRawView::ProductionConsumeRawView(DataLayer::productionConsumeRawsViewCollection cCollection)
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

	std::string ProductionConsumeRawView::GetStatusCode()
	{
		return statusCode;
	}
	std::string ProductionConsumeRawView::GetStatusName()
	{
		return statusName;
	}
	std::string ProductionConsumeRawView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string ProductionConsumeRawView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string ProductionConsumeRawView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string ProductionConsumeRawView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string ProductionConsumeRawView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string ProductionConsumeRawView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string ProductionConsumeRawView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string ProductionConsumeRawView::GetStockEmployeePosition()
	{
		return stockEmployeePosition;
	}
	std::string ProductionConsumeRawView::GetCurrencyName()
	{
		return currencyName;
	}

	void ProductionConsumeRawView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void ProductionConsumeRawView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ProductionConsumeRawView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void ProductionConsumeRawView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void ProductionConsumeRawView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void ProductionConsumeRawView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void ProductionConsumeRawView::SetStockEmployeeName(std::string eStockEmployeeName)
	{
		stockEmployeeName = eStockEmployeeName;
	}
	void ProductionConsumeRawView::SetStockEmployeeSurname(std::string eStockEmployeeSurname)
	{
		stockEmployeeSurname = eStockEmployeeSurname;
	}
	void ProductionConsumeRawView::SetStockEmployeePhone(std::string eStockEmployeePhone)
	{
		stockEmployeePhone = eStockEmployeePhone;
	}
	void ProductionConsumeRawView::SetStockEmployeePosition(std::string eStockEmployeePosition)
	{
		stockEmployeePosition = eStockEmployeePosition;
	}
	void ProductionConsumeRawView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string ProductionConsumeRawView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty()
			|| !stockEmployeePhone.empty() || !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != stockEmployeeID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForConProdnView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				stockEmployeeName, stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName, stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}
}

