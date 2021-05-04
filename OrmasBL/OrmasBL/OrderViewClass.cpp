#include "stdafx.h"
#include "OrderViewClass.h"

namespace BusinessLayer
{
	OrderView::OrderView(DataLayer::ordersViewCollection oCollection)
	{
		id = std::get<0>(oCollection);
		date = std::get<1>(oCollection);
		executionDate = std::get<2>(oCollection);
		statusCode = std::get<3>(oCollection);
		statusName = std::get<4>(oCollection);
		clientName = std::get<5>(oCollection);
		clientSurname = std::get<6>(oCollection);
		clientPhone = std::get<7>(oCollection);
		clientAddres = std::get<8>(oCollection);
		clientFirm = std::get<9>(oCollection);
		employeeName = std::get<10>(oCollection);
		employeeSurname = std::get<11>(oCollection);
		employeePhone = std::get<12>(oCollection);
		count = std::get<13>(oCollection);
		sum = std::get<14>(oCollection);
		currencyName = std::get<15>(oCollection);
		employeeID = std::get<16>(oCollection);
		clientID = std::get<17>(oCollection);
		statusID = std::get<18>(oCollection);
		currencyID = std::get<19>(oCollection);
	}

	std::string OrderView::GetStatusCode()
	{
		return statusCode;
	}
	std::string OrderView::GetStatusName()
	{
		return statusName;
	}
	std::string OrderView::GetClientName()
	{
		return clientName;
	}
	std::string OrderView::GetClientSurname()
	{
		return clientSurname;
	}
	std::string OrderView::GetClientPhone()
	{
		return clientPhone;
	}
	std::string OrderView::GetClientAddress()
	{
		return clientAddres;
	}
	std::string OrderView::GetClientFirm()
	{
		return clientFirm;
	}
	std::string OrderView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string OrderView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string OrderView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string OrderView::GetCurrencyName()
	{
		return currencyName;
	}

	void OrderView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void OrderView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void OrderView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void OrderView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void OrderView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}
	
	void OrderView::SetClientName(std::string oClientName)
	{
		clientName = oClientName;
	}
	void OrderView::SetClientSurname(std::string oClientSurname)
	{
		clientSurname = oClientSurname;
	}
	void OrderView::SetClientPhone(std::string oClientPhone)
	{
		clientPhone = oClientPhone;
	}
	void OrderView::SetClientAddress(std::string oClientAddres)
	{
		clientAddres = oClientAddres;
	}
	void OrderView::SetClientFirm(std::string oClientFirm)
	{
		clientFirm = oClientFirm;
	}

	void OrderView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string OrderView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !clientName.empty() || !clientSurname.empty() || !clientPhone.empty()
			|| !clientAddres.empty() || !clientFirm.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != clientID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForOrderView(id, date, executionDate, statusCode, statusName, clientName,
				clientSurname, clientPhone, clientAddres, clientFirm, employeeName, employeeSurname, employeePhone, count, sum, currencyName, employeeID,
				clientID, statusID, currencyID);
		}
		return "";
	}
}

