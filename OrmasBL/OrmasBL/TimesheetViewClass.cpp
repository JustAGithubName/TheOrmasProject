#include "stdafx.h"
#include "TimesheetViewClass.h"

namespace BusinessLayer{
	TimesheetView::TimesheetView(DataLayer::timesheetViewCollection tCollection)
	{
		id = std::get<0>(tCollection);
		userName = std::get<1>(tCollection);
		userSurname = std::get<2>(tCollection);
		userPhone = std::get<3>(tCollection);
		date = std::get<4>(tCollection);
		workedTime = std::get<5>(tCollection);
		salaryID = std::get<6>(tCollection);
	}

	std::string TimesheetView::GetUsername()
	{
		return userName;
	}
	std::string TimesheetView::GetUserSurname()
	{
		return userSurname;
	}
	std::string TimesheetView::GetUserPhone()
	{
		return userPhone;
	}

	void TimesheetView::SetUsername(std::string sUserName)
	{
		userName = sUserName;
	}
	void TimesheetView::SetUserSurname(std::string sUserName)
	{
		userSurname = sUserName;
	}
	void TimesheetView::SetUserPhone(std::string sUserPhone)
	{
		userPhone = sUserPhone;
	}

	std::string TimesheetView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !userName.empty() || !userSurname.empty() || !userPhone.empty() || 0 != salaryID || 0 != workedTime || !date.empty())
		{
			return ormasDal.GetFilterForTimesheetView(id, userName, userSurname, userPhone, date, workedTime, salaryID);
		}
		return "";
	}
}