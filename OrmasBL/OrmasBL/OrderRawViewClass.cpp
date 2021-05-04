#include "stdafx.h"
#include "OrderRawViewClass.h"

namespace BusinessLayer
{
	OrderRawView::OrderRawView(DataLayer::orderRawsViewCollection oCollection)
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

	std::string OrderRawView::GetStatusCode()
	{
		return statusCode;
	}
	std::string OrderRawView::GetStatusName()
	{
		return statusName;
	}
	std::string OrderRawView::GetPurveyorName()
	{
		return purveyorName;
	}
	std::string OrderRawView::GetPurveyorSurname()
	{
		return purveyorSurname;
	}
	std::string OrderRawView::GetPurveyorPhone()
	{
		return purveyorPhone;
	}
	std::string OrderRawView::GetPurveyorCompanyName()
	{
		return purveyorCompanyName;
	}
	std::string OrderRawView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string OrderRawView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string OrderRawView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string OrderRawView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string OrderRawView::GetCurrencyName()
	{
		return currencyName;
	}

	void OrderRawView::SetStatusCode(std::string oStatusCode)
	{
		statusCode = oStatusCode;
	}
	void OrderRawView::SetStatusName(std::string oStatusName)
	{
		statusName = oStatusName;
	}
	void OrderRawView::SetPurveyorName(std::string oPurveyorName)
	{
		purveyorName = oPurveyorName;
	}
	void OrderRawView::SetPurveyorSurname(std::string oPurveyorSurname)
	{
		purveyorSurname = oPurveyorSurname;
	}
	void OrderRawView::SetPurveyorPhone(std::string oPurveyorPhone)
	{
		purveyorPhone = oPurveyorPhone;
	}
	void OrderRawView::SetPurveyorCompanyName(std::string oPurveyorCompanyName)
	{
		purveyorCompanyName = oPurveyorCompanyName;
	}
	void OrderRawView::SetEmployeeName(std::string oEmployeeName)
	{
		employeeName = oEmployeeName;
	}
	void OrderRawView::SetEmployeeSurname(std::string oEmployeeSurname)
	{
		employeeSurname = oEmployeeSurname;
	}
	void OrderRawView::SetEmployeePhone(std::string oEmployeePhone)
	{
		employeePhone = oEmployeePhone;
	}
	void OrderRawView::SetEmployeePosition(std::string oEmployeePosition)
	{
		employeePosition = oEmployeePosition;
	}
	void OrderRawView::SetCurrencyName(std::string oCurrencyName)
	{
		currencyName = oCurrencyName;
	}

	std::string OrderRawView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !purveyorName.empty() || !purveyorSurname.empty()
			|| !purveyorPhone.empty() || !purveyorCompanyName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || 0 != count || 0 != sum || !currencyName.empty() || 0 != employeeID || 0 != purveyorID
			|| 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForOrdRawView(id, date, executionDate, statusCode, statusName, purveyorName,
				purveyorSurname, purveyorPhone, purveyorCompanyName, employeeName, employeeSurname, employeePhone, employeePosition, count, sum, currencyName, employeeID,
				purveyorID, statusID, currencyID);
		}
		return "";
	}
}

