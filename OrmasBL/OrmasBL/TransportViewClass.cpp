#include "stdafx.h"
#include "TransportViewClass.h"

namespace BusinessLayer
{
	TransportView::TransportView(DataLayer::transportsViewCollection tCollection)
	{
		id = std::get<0>(tCollection);
		date = std::get<1>(tCollection);
		executionDate = std::get<2>(tCollection);
		statusCode = std::get<3>(tCollection);
		statusName = std::get<4>(tCollection);
		userName = std::get<5>(tCollection);
		userSurname = std::get<6>(tCollection);
		userPhone = std::get<7>(tCollection);
		userPosition = std::get<8>(tCollection);
		employeeName = std::get<9>(tCollection);
		employeeSurname = std::get<10>(tCollection);
		employeePhone = std::get<11>(tCollection);
		employeePosition = std::get<12>(tCollection);
		count = std::get<13>(tCollection);
		sum = std::get<14>(tCollection);
		currencyName = std::get<15>(tCollection);
		employeeID = std::get<16>(tCollection);
		userID = std::get<17>(tCollection);
		statusID = std::get<18>(tCollection);
		currencyID = std::get<19>(tCollection);
	}

	std::string TransportView::GetStatusCode()
	{
		return statusCode;
	}
	std::string TransportView::GetStatusName()
	{
		return statusName;
	}
	std::string TransportView::GetUsername()
	{
		return userName;
	}
	std::string TransportView::GetUserSurname()
	{
		return userSurname;
	}
	std::string TransportView::GetUserPhone()
	{
		return userPhone;
	}
	std::string TransportView::GetUserPosition()
	{
		return userPosition;
	}
	std::string TransportView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string TransportView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string TransportView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string TransportView::GetEmployeePosition()
	{
		return employeePosition;
	}
	std::string TransportView::GetCurrencyName()
	{
		return currencyName;
	}

	void TransportView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void TransportView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void TransportView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void TransportView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void TransportView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	void TransportView::SetEmployeePosition(std::string cEmployeePosition)
	{
		employeePosition = cEmployeePosition;
	}
	void TransportView::SetUserName(std::string eUserName)
	{
		userName = eUserName;
	}
	void TransportView::SetUserSurname(std::string eUserSurname)
	{
		userSurname = eUserSurname;
	}
	void TransportView::SetUserPhone(std::string eUserPhone)
	{
		userPhone = eUserPhone;
	}
	void TransportView::SetUserPosition(std::string eUserPosition)
	{
		userPosition = eUserPosition;
	}
	void TransportView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string TransportView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !employeePosition.empty() || !userName.empty() || !userSurname.empty()
			|| !userPhone.empty() || !userPosition.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != userID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForStTranView(id, date, executionDate, statusCode, statusName, employeeName, employeeSurname, employeePhone, employeePosition,
				userName, userSurname, userPhone, userPosition, count, sum, currencyName, userID, employeeID, statusID, currencyID);
		}
		return "";
	}
}

