#include "stdafx.h"
#include "ReceiptProductViewClass.h"

namespace BusinessLayer
{
	ReceiptProductView::ReceiptProductView(DataLayer::receiptProductsViewCollection rCollection)
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

	std::string ReceiptProductView::GetStatusCode()
	{
		return statusCode;
	}
	std::string ReceiptProductView::GetStatusName()
	{
		return statusName;
	}
	std::string ReceiptProductView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string ReceiptProductView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string ReceiptProductView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string ReceiptProductView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string ReceiptProductView::GetStockEmployeeName()
	{
		return stockEmployeeName;
	}
	std::string ReceiptProductView::GetStockEmployeeSurname()
	{
		return stockEmployeeSurname;
	}
	std::string ReceiptProductView::GetStockEmployeePhone()
	{
		return stockEmployeePhone;
	}
	std::string ReceiptProductView::GetStockEmployeePosition()
	{
		return stockEmployeePosition;
	}
	std::string ReceiptProductView::GetCurrencyName()
	{
		return currencyName;
	}

	void ReceiptProductView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void ReceiptProductView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ReceiptProductView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void ReceiptProductView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void ReceiptProductView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void ReceiptProductView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void ReceiptProductView::SetStockEmployeeName(std::string eStockEmployeeName)
	{
		stockEmployeeName = eStockEmployeeName;
	}
	void ReceiptProductView::SetStockEmployeeSurname(std::string eStockEmployeeSurname)
	{
		stockEmployeeSurname = eStockEmployeeSurname;
	}
	void ReceiptProductView::SetStockEmployeePhone(std::string eStockEmployeePhone)
	{
		stockEmployeePhone = eStockEmployeePhone;
	}
	void ReceiptProductView::SetStockEmployeePosition(std::string eStockEmployeePosition)
	{
		stockEmployeePosition = eStockEmployeePosition;
	}
	void ReceiptProductView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string ReceiptProductView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !stockEmployeeName.empty() || !stockEmployeeSurname.empty()
			|| !stockEmployeePhone.empty() || !stockEmployeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != stockEmployeeID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForRcpProdView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				stockEmployeeName, stockEmployeeSurname, stockEmployeePhone, stockEmployeePosition, count, sum, currencyName, stockEmployeeID, employeeID, statusID, currencyID);
		}
		return "";
	}
}
