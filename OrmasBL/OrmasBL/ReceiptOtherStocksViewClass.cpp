#include "stdafx.h"
#include "ReceiptOtherStocksViewClass.h"

namespace BusinessLayer
{
	ReceiptOtherStocksView::ReceiptOtherStocksView(DataLayer::receiptOtherStocksViewCollection oCollection)
	{
		id = std::get<0>(oCollection);
		date = std::get<1>(oCollection);
		executionDate = std::get<2>(oCollection);
		statusCode = std::get<3>(oCollection);
		statusName = std::get<4>(oCollection);
		purveyorName = std::get<5>(oCollection);
		purveyorSurname = std::get<6>(oCollection);
		purveyorPhone = std::get<7>(oCollection);
		purveyorCompanyName = std::get<8>(oCollection);
		employeeName = std::get<9>(oCollection);
		employeeSurname = std::get<10>(oCollection);
		employeePhone = std::get<11>(oCollection);
		employeePosition = std::get<12>(oCollection);
		count = std::get<13>(oCollection);
		sum = std::get<14>(oCollection);
		currencyName = std::get<15>(oCollection);
		employeeID = std::get<16>(oCollection);
		purveyorID = std::get<17>(oCollection);
		statusID = std::get<18>(oCollection);
		currencyID = std::get<19>(oCollection);
	}

	std::string ReceiptOtherStocksView::GetStatusCode()
	{
		return statusCode;
	}
	std::string ReceiptOtherStocksView::GetStatusName()
	{
		return statusName;
	}
	std::string ReceiptOtherStocksView::GetPurveyorName()
	{
		return purveyorName;
	}
	std::string ReceiptOtherStocksView::GetPurveyorSurname()
	{
		return purveyorSurname;
	}
	std::string ReceiptOtherStocksView::GetPurveyorPhone()
	{
		return purveyorPhone;
	}
	std::string ReceiptOtherStocksView::GetPurveyorCompanyName()
	{
		return purveyorCompanyName;
	}
	std::string ReceiptOtherStocksView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string ReceiptOtherStocksView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string ReceiptOtherStocksView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string ReceiptOtherStocksView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string ReceiptOtherStocksView::GetCurrencyName()
	{
		return currencyName;
	}

	void ReceiptOtherStocksView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void ReceiptOtherStocksView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ReceiptOtherStocksView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void ReceiptOtherStocksView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void ReceiptOtherStocksView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void ReceiptOtherStocksView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void ReceiptOtherStocksView::SetPurveyorName(std::string ePurveyorName)
	{
		purveyorName = ePurveyorName;
	}
	void ReceiptOtherStocksView::SetPurveyorSurname(std::string ePurveyorSurname)
	{
		purveyorSurname = ePurveyorSurname;
	}
	void ReceiptOtherStocksView::SetPurveyorPhone(std::string ePurveyorPhone)
	{
		purveyorPhone = ePurveyorPhone;
	}
	void ReceiptOtherStocksView::SetPurveyorCompanyName(std::string ePurveyorCompanyName)
	{
		purveyorCompanyName = ePurveyorCompanyName;
	}
	void ReceiptOtherStocksView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string ReceiptOtherStocksView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !purveyorName.empty() || !purveyorSurname.empty()
			|| !purveyorPhone.empty() || !purveyorCompanyName.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != purveyorID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForRcpOthStView(id, date, executionDate, statusCode, statusName, purveyorName, purveyorSurname, purveyorPhone, purveyorCompanyName,
				employeeName, employeeSurname, employeePhone, employeePosition, count, sum, currencyName, purveyorID, employeeID, statusID, currencyID);
		}
		return "";
	}
}

