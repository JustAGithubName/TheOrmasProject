#include "stdafx.h"
#include "StockTransferViewClass.h"

namespace BusinessLayer
{
	StockTransferView::StockTransferView(DataLayer::stockTransferViewCollection rCollection)
	{
		id = std::get<0>(rCollection);
		date = std::get<1>(rCollection);
		executionDate = std::get<2>(rCollection);
		statusCode = std::get<3>(rCollection);
		statusName = std::get<4>(rCollection);
		employeeName = std::get<5>(rCollection);
		employeeSurname = std::get<6>(rCollection);
		employeePhone = std::get<7>(rCollection);
		employeePosition = std::get<8>(rCollection);
		stockEmployeeName = std::get<9>(rCollection);
		stockEmployeeSurname = std::get<10>(rCollection);
		stockEmployeePhone = std::get<11>(rCollection);
		stockEmployeePosition = std::get<12>(rCollection);
		count = std::get<13>(rCollection);
		sum = std::get<14>(rCollection);
		currencyName = std::get<15>(rCollection);
		stockEmployeeID = std::get<16>(rCollection);
		employeeID = std::get<17>(rCollection);
		statusID = std::get<18>(rCollection);
		currencyID = std::get<19>(rCollection);
	}

	std::string StockTransferView::GetStatusCode()
	{
		return statusCode;
	}
	std::string StockTransferView::GetStatusName()
	{
		return statusName;
	}
	std::string StockTransferView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string StockTransferView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string StockTransferView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string StockTransferView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string StockTransferView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string StockTransferView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string StockTransferView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string StockTransferView::GetStockEmployeePosition()
	{
		return stockEmployeePosition;
	}
	std::string StockTransferView::GetCurrencyName()
	{
		return currencyName;
	}


	void StockTransferView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void StockTransferView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void StockTransferView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void StockTransferView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void StockTransferView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void StockTransferView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void StockTransferView::SetStockEmployeeName(std::string eStockEmployeeName)
	{
		stockEmployeeName = eStockEmployeeName;
	}
	void StockTransferView::SetStockEmployeeSurname(std::string eStockEmployeeSurname)
	{
		stockEmployeeSurname = eStockEmployeeSurname;
	}
	void StockTransferView::SetStockEmployeePhone(std::string eStockEmployeePhone)
	{
		stockEmployeePhone = eStockEmployeePhone;
	}
	void StockTransferView::SetStockEmployeePosition(std::string eStockEmployeePosition)
	{
		stockEmployeePosition = eStockEmployeePosition;
	}
	void StockTransferView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string StockTransferView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty()
			|| !stockEmployeePhone.empty() || !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != stockEmployeeID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForStTranView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				stockEmployeeName, stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName, stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}
}

