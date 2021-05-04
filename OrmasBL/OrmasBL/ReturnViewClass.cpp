#include "stdafx.h"
#include "ReturnViewClass.h"

namespace BusinessLayer
{
	ReturnView::ReturnView(DataLayer::returnsViewCollection rCollection)
	{
		id = std::get<0>(rCollection);
		date = std::get<1>(rCollection);
		executionDate = std::get<2>(rCollection);
		statusCode = std::get<3>(rCollection);
		statusName = std::get<4>(rCollection);
		clientName = std::get<5>(rCollection);
		clientSurname = std::get<6>(rCollection);
		clientPhone = std::get<7>(rCollection);
		clientAddres = std::get<8>(rCollection);
		clientFirm = std::get<9>(rCollection);
		employeeName = std::get<10>(rCollection);
		employeeSurname = std::get<11>(rCollection);
		employeePhone = std::get<12>(rCollection);
		count = std::get<13>(rCollection);
		sum = std::get<14>(rCollection);
		currencyName = std::get<15>(rCollection);
		employeeID = std::get<16>(rCollection);
		clientID = std::get<17>(rCollection);
		statusID = std::get<18>(rCollection);
		currencyID = std::get<19>(rCollection);
	}
	
	std::string ReturnView::GetStatusCode()
	{
		return statusCode;
	}
	std::string ReturnView::GetStatusName()
	{
		return statusName;
	}
	std::string ReturnView::GetClientName()
	{
		return clientName;
	}
	std::string ReturnView::GetClientSurname()
	{
		return clientSurname;
	}
	std::string ReturnView::GetClientPhone()
	{
		return clientPhone;
	}
	std::string ReturnView::GetClientAddress()
	{
		return clientAddres;
	}
	std::string ReturnView::GetClientFirm()
	{
		return clientFirm;
	}
	std::string ReturnView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string ReturnView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string ReturnView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string ReturnView::GetCurrencyName()
	{
		return currencyName;
	}

	void ReturnView::SetStatusCode(std::string rStatusCode)
	{
		statusCode = rStatusCode;
	}
	void ReturnView::SetStatusName(std::string rRtatusName)
	{
		statusName = rRtatusName;
	}
	void ReturnView::SetClientName(std::string rClientName)
	{
		clientName = rClientName;
	}
	void ReturnView::SetClientSurname(std::string rClientSurname)
	{
		clientSurname = rClientSurname;
	}
	void ReturnView::SetClientPhone(std::string rClientPhone)
	{
		clientPhone = rClientPhone;
	}
	void ReturnView::SetClientAddress(std::string rClientAddres)
	{
		clientAddres = rClientAddres;
	}
	void ReturnView::SetClientFirm(std::string rClientFirm)
	{
		clientFirm = rClientFirm;
	}
	void ReturnView::SetEmployeeName(std::string rEmployeeName)
	{
		employeeName = rEmployeeName;
	}
	void ReturnView::SetEmployeeSurname(std::string rEmployeeSurname)
	{
		employeeSurname = rEmployeeSurname;
	}
	void ReturnView::SetEmployeePhone(std::string rEmployeePhone)
	{
		employeePhone = rEmployeePhone;
	}
	void ReturnView::SetCurrencyName(std::string rCurrencyName)
	{
		currencyName = rCurrencyName;
	}

	std::string ReturnView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !clientName.empty() || !clientSurname.empty()
			|| !clientPhone.empty() || !clientAddres.empty() || !clientFirm.empty() || !employeeName.empty() || !employeeSurname.empty() || !employeePhone.empty()
			|| 0 != count || 0 != sum || !currencyName.empty() || 0 != employeeID || 0 != clientID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForReturnView(id, date, executionDate, statusCode, statusName, clientName, clientSurname, clientPhone, clientAddres,
				clientFirm, employeeName, employeeSurname, employeePhone, count, sum, currencyName, employeeID, clientID, statusID, currencyID);
		}
		return "";
	}
}

