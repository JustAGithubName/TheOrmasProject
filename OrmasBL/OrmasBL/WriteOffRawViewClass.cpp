#include "stdafx.h"
#include "WriteOffRawViewClass.h"

namespace BusinessLayer
{
	WriteOffRawView::WriteOffRawView(DataLayer::writeOffRawsViewCollection wCollection)
	{
		id = std::get<0>(wCollection);
		date = std::get<1>(wCollection);
		executionDate = std::get<2>(wCollection);
		statusCode = std::get<3>(wCollection);
		statusName = std::get<4>(wCollection);
		employeeName = std::get<5>(wCollection);
		employeeSurname = std::get<6>(wCollection);
		employeePhone = std::get<7>(wCollection);
		employeePosition = std::get<8>(wCollection);
		stockEmployeeName = std::get<9>(wCollection);
		stockEmployeeSurname = std::get<10>(wCollection);
		stockEmployeePhone = std::get<11>(wCollection);
		stockEmployeePosition = std::get<12>(wCollection);
		count = std::get<13>(wCollection);
		sum = std::get<14>(wCollection);
		currencyName = std::get<15>(wCollection);
		stockEmployeeID = std::get<16>(wCollection);
		employeeID = std::get<17>(wCollection);
		statusID = std::get<18>(wCollection);
		currencyID = std::get<19>(wCollection);
	}

	std::string WriteOffRawView::GetStatusCode()
	{
		return statusCode;
	}
	std::string WriteOffRawView::GetStatusName()
	{
		return statusName;
	}
	std::string WriteOffRawView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string WriteOffRawView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string WriteOffRawView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string WriteOffRawView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string WriteOffRawView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string WriteOffRawView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string WriteOffRawView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string WriteOffRawView::GetStockEmployeePosition()
	{
		return stockEmployeePosition;
	}
	std::string WriteOffRawView::GetCurrencyName()
	{
		return currencyName;
	}
	
	void WriteOffRawView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void WriteOffRawView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void WriteOffRawView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void WriteOffRawView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void WriteOffRawView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void WriteOffRawView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void WriteOffRawView::SetStockEmployeeName(std::string eStockEmployeeName)
	{
		stockEmployeeName = eStockEmployeeName;
	}
	void WriteOffRawView::SetStockEmployeeSurname(std::string eStockEmployeeSurname)
	{
		stockEmployeeSurname = eStockEmployeeSurname;
	}
	void WriteOffRawView::SetStockEmployeePhone(std::string eStockEmployeePhone)
	{
		stockEmployeePhone = eStockEmployeePhone;
	}
	void WriteOffRawView::SetStockEmployeePosition(std::string eStockEmployeePosition)
	{
		stockEmployeePosition = eStockEmployeePosition;
	}
	void WriteOffRawView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string WriteOffRawView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty()
			|| !stockEmployeePhone.empty() || !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != stockEmployeeID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForWOffRawView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				stockEmployeeName, stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName, stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}
}


