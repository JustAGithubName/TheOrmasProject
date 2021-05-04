#include "stdafx.h"
#include "WriteOffViewClass.h"

namespace BusinessLayer
{
	WriteOffView::WriteOffView(DataLayer::writeOffsViewCollection oCollection)
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

	std::string WriteOffView::GetStatusCode()
	{
		return statusCode;
	}
	std::string WriteOffView::GetStatusName()
	{
		return statusName;
	}
	std::string WriteOffView::GetClientName()
	{
		return clientName;
	}
	std::string WriteOffView::GetClientSurname()
	{
		return clientSurname;
	}
	std::string WriteOffView::GetClientPhone()
	{
		return clientPhone;
	}
	std::string WriteOffView::GetClientAddress()
	{
		return clientAddres;
	}
	std::string WriteOffView::GetClientFirm()
	{
		return clientFirm;
	}
	std::string WriteOffView::GetEmployeeName()
	{
		return employeeName;
	}
	std::string WriteOffView::GetEmployeeSurname()
	{
		return employeeSurname;
	}
	std::string WriteOffView::GetEmployeePhone()
	{
		return employeePhone;
	}
	std::string WriteOffView::GetCurrencyName()
	{
		return currencyName;
	}

	void WriteOffView::SetStatusCode(std::string cStatusCode)
	{
		statusCode = cStatusCode;
	}
	void WriteOffView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void WriteOffView::SetEmployeeName(std::string cEmployeeName)
	{
		employeeName = cEmployeeName;
	}
	void WriteOffView::SetEmployeeSurname(std::string cEmployeeSurname)
	{
		employeeSurname = cEmployeeSurname;
	}
	void WriteOffView::SetEmployeePhone(std::string cEmployeePhone)
	{
		employeePhone = cEmployeePhone;
	}

	void WriteOffView::SetClientName(std::string oClientName)
	{
		clientName = oClientName;
	}
	void WriteOffView::SetClientSurname(std::string oClientSurname)
	{
		clientSurname = oClientSurname;
	}
	void WriteOffView::SetClientPhone(std::string oClientPhone)
	{
		clientPhone = oClientPhone;
	}
	void WriteOffView::SetClientAddress(std::string oClientAddres)
	{
		clientAddres = oClientAddres;
	}
	void WriteOffView::SetClientFirm(std::string oClientFirm)
	{
		clientFirm = oClientFirm;
	}

	void WriteOffView::SetCurrencyName(std::string eCurrencyName)
	{
		currencyName = eCurrencyName;
	}

	std::string WriteOffView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !executionDate.empty() || !statusCode.empty() || !statusName.empty() || !employeeName.empty() || !employeeSurname.empty()
			|| !employeePhone.empty() || !clientName.empty() || !clientSurname.empty() || !clientPhone.empty()
			|| !clientAddres.empty() || !clientFirm.empty() || 0 != count || 0 != sum || !currencyName.empty() ||
			0 != clientID || 0 != employeeID || 0 != statusID || currencyID)
		{
			return ormasDal.GetFilterForWOffView(id, date, executionDate, statusCode, statusName, clientName,
				clientSurname, clientPhone, clientAddres, clientFirm, employeeName, employeeSurname, employeePhone, count, sum, currencyName, employeeID,
				clientID, statusID, currencyID);
		}
		return "";
	}
}




