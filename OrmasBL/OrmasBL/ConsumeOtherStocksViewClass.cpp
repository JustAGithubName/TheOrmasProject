#include "stdafx.h"
#include "ConsumeOtherStocksViewClass.h"

namespace BusinessLayer
{
	ConsumeOtherStocksView::ConsumeOtherStocksView(DataLayer::consumeOtherStocksViewCollection cCollection)
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

	std::string ConsumeOtherStocksView::GetStatusCode()
	{
		return statusCode;
	}
	std::string ConsumeOtherStocksView::GetStatusName()
	{
		return statusName;
	}
	std::string ConsumeOtherStocksView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string ConsumeOtherStocksView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string ConsumeOtherStocksView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string ConsumeOtherStocksView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string ConsumeOtherStocksView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string ConsumeOtherStocksView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string ConsumeOtherStocksView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string ConsumeOtherStocksView::GetStockEmployeePosition()
	{
		return stockEmployeePosition;
	}
	std::string ConsumeOtherStocksView::GetCurrencyName()
	{
		return currencyName;
	}

	void ConsumeOtherStocksView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void ConsumeOtherStocksView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ConsumeOtherStocksView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void ConsumeOtherStocksView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void ConsumeOtherStocksView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void ConsumeOtherStocksView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void ConsumeOtherStocksView::SetStockEmployeeName(std::string sStockEmployeeName)
	{
		stockEmployeeName = sStockEmployeeName;
	}
	void ConsumeOtherStocksView::SetStockEmployeeSurname(std::string cStockEmployeeSurname)
	{
		stockEmployeeSurname = cStockEmployeeSurname;
	}
	void ConsumeOtherStocksView::SetStockEmployeePhone(std::string cStockEmployeePhone)
	{
		stockEmployeePhone = cStockEmployeePhone;
	}
	void ConsumeOtherStocksView::SetStockEmployeePosition(std::string cStockEmployeePosition)
	{
		stockEmployeePosition = cStockEmployeePosition;
	}
	void ConsumeOtherStocksView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}

	std::string ConsumeOtherStocksView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty() || !stockEmployeePhone.empty()
			|| !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() || 0 != stockEmployeeID || 0 != employeeID || 0 != statusID 
			|| 0 != currencyID)
		{
			return ormasDal.GetFilterForConOthStView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition, stockEmployeeName,
				stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName, stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}

}

