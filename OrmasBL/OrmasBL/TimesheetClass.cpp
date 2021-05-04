#include "stdafx.h"
#include "TimesheetClass.h"

namespace BusinessLayer{
	Timesheet::Timesheet(DataLayer::timesheetCollection tCollection)
	{
		id = std::get<0>(tCollection);
		salaryID = std::get<1>(tCollection);
		workedTime = std::get<2>(tCollection);
		date = std::get<3>(tCollection);
	}
	Timesheet::Timesheet()
	{
		salaryID = 0;
		workedTime = 0.0;
		date = "";
	}
	
	int Timesheet::GetID()
	{
		return id;
	}

	int Timesheet::GetSalaryID()
	{
		return salaryID;
	}
	
	double Timesheet::GetWorkedTime()
	{
		return workedTime;
	}

	std::string Timesheet::GetDate()
	{
		return date;
	}
	
	void Timesheet::SetID(int tID)
	{
		id = tID;
	}

	void Timesheet::SetSalaryID(int tID)
	{
		salaryID = tID;
	}

	void Timesheet::SetWorkedTime(double tWorkedTime)
	{
		workedTime = tWorkedTime;
	}

	void Timesheet::SetDate(std::string tDate)
	{
		date = tDate;
	}
	
	bool Timesheet::CreateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double tWorkedTime, std::string tDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, sID, tWorkedTime, tDate , errorMessage))
			return false;
		id = ormasDal.GenerateID();
		salaryID = sID;
		workedTime = tWorkedTime;
		date = tDate;
		if (0 != id && ormasDal.CreateTimesheet(id, salaryID, workedTime, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Timesheet::CreateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateTimesheet(id, salaryID, workedTime, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Timesheet::DeleteTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (!this->GetTimesheetByID(globalVar, ormasDal, id, errorMessage))
			return false;
		if (ormasDal.DeleteTimesheet(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool Timesheet::UpdateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double tWorkedTime, std::string tDate, std::string& errorMessage)
	{
		salaryID = sID;
		workedTime = tWorkedTime;
		date = tDate;
		if (0 != id && ormasDal.UpdateTimesheet(id, salaryID, workedTime, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Timesheet::UpdateTimesheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateTimesheet(id, salaryID, workedTime, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Timesheet::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != salaryID ||  0 != workedTime || !date.empty())
		{
			return ormasDal.GetFilterForTimesheet(id, salaryID, workedTime, date);
		}
		return "";
	}

	std::string Timesheet::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string tilDate)
	{
		if (!fromDate.empty() && !tilDate.empty())
		{
			return ormasDal.GetFilterForTimesheetForPeriod(id, salaryID, workedTime, date, fromDate, tilDate);
		}
		return "";
	}

	bool Timesheet::GetTimesheetByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::timesheetViewCollection> timesheetVector = ormasDal.GetTimesheet(errorMessage, filter);
		if (0 != timesheetVector.size())
		{
			id = std::get<0>(timesheetVector.at(0));
			salaryID = std::get<6>(timesheetVector.at(0));
			workedTime = std::get<5>(timesheetVector.at(0));
			date = std::get<4>(timesheetVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find timesheet with this id";
		}
		return false;
	}

	bool Timesheet::IsEmpty()
	{
		if (0 == id && 0 == salaryID && 0.0 == workedTime && date.empty())
			return true;
		return false;
	}

	void Timesheet::Clear()
	{
		id = 0;
		salaryID = 0;
		workedTime = 0;
		date.clear();
	}

	bool Timesheet::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double tWorkedTime, std::string tDate, std::string& errorMessage)
	{
		Timesheet timesheet;
		timesheet.Clear();
		errorMessage.clear();
		timesheet.SetSalaryID(sID);
		timesheet.SetWorkedTime(tWorkedTime);
		timesheet.SetDate(tDate);
		std::string filter = timesheet.GenerateFilter(ormasDal);
		std::vector<DataLayer::timesheetViewCollection> timesheetVector = ormasDal.GetTimesheet(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == timesheetVector.size())
		{
			return false;
		}
		errorMessage = "Timesheet with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Timesheet::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Timesheet timesheet;
		timesheet.Clear();
		errorMessage.clear();
		timesheet.SetSalaryID(salaryID);
		timesheet.SetWorkedTime(workedTime);
		timesheet.SetDate(date);
		std::string filter = timesheet.GenerateFilter(ormasDal);
		std::vector<DataLayer::timesheetViewCollection> timesheetVector = ormasDal.GetTimesheet(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == timesheetVector.size())
		{
			return false;
		}
		errorMessage = "Timesheet with these parameters are already exist! Please avoid the duplication!";
		return true;
	}
}