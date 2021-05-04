#include "stdafx.h"
#include "JobsheetClass.h"

namespace BusinessLayer{
	Jobsheet::Jobsheet(DataLayer::jobsheetCollection jCollection)
	{
		id = std::get<0>(jCollection);
		date = std::get<1>(jCollection);
		count = std::get<2>(jCollection);
		productID = std::get<3>(jCollection);
		employeeID = std::get<4>(jCollection);
	}
	Jobsheet::Jobsheet()
	{
		date = "";
		count = 0.0;
		productID = 0;
		employeeID = 0;
	}
	int Jobsheet::GetID()
	{
		return id;
	}

	std::string Jobsheet::GetDate()
	{
		return date;
	}

	double Jobsheet::GetCount()
	{
		return count;
	}

	int Jobsheet::GetProductID()
	{
		return productID;
	}

	int Jobsheet::GetEmployeeID()
	{
		return employeeID;
	}

	void Jobsheet::SetID(int jID)
	{
		id = jID;
	}

	void Jobsheet::SetDate(std::string jDate)
	{
		date = jDate;
	}

	void Jobsheet::SetCount(double jCount)
	{
		count = jCount;
	}

	void Jobsheet::SetProductID(int pID)
	{
		productID = pID;
	}

	void Jobsheet::SetEmployeeID(int eID)
	{
		employeeID = eID;
	}


	bool Jobsheet::CreateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string jDate, double jCount, int pID, int eID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, jDate, jCount, pID, eID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		date = jDate;
		count = jCount;
		productID = pID;
		employeeID = eID;
		if (0 != id && ormasDal.CreateJobsheet(id, date, count, productID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Jobsheet::CreateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateJobsheet(id, date, count, productID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Jobsheet::DeleteJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteJobsheet(id, errorMessage))
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

	bool Jobsheet::UpdateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string jDate, double jCount, int pID, int eID, std::string& errorMessage)
	{
		date = jDate;
		count = jCount;
		productID = pID;
		employeeID = eID;
		if (0 != id && ormasDal.UpdateJobsheet(id, date, count, productID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Jobsheet::UpdateJobsheet(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateJobsheet(id, date, count, productID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Jobsheet::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0.0 != count || 0 != productID || 0 != employeeID )
		{
			return ormasDal.GetFilterForJobsheet(id, date, count, productID, employeeID);
		}
		return "";
	}

	std::string Jobsheet::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string tilDate)
	{
		if (!fromDate.empty() && !tilDate.empty())
		{
			return ormasDal.GetFilterForJobsheetForPeriod(id, date, count, productID, employeeID, fromDate, tilDate);
		}
		return "";
	}

	bool Jobsheet::GetJobsheetByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::jobsheetViewCollection> jobsheetVector = ormasDal.GetJobsheet(errorMessage, filter);
		if (0 != jobsheetVector.size())
		{
			id = std::get<0>(jobsheetVector.at(0));
			date = std::get<1>(jobsheetVector.at(0));
			count = std::get<6>(jobsheetVector.at(0));
			productID = std::get<8>(jobsheetVector.at(0));
			employeeID = std::get<9>(jobsheetVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Jobsheet with this id";
		}
		return false;
	}

	bool Jobsheet::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == count && 0 == productID && 0 == employeeID)
			return true;
		return false;
	}

	void Jobsheet::Clear()
	{
		id = 0;
		date.clear();
		count = 0;
		productID = 0;
		employeeID = 0;
	}

	bool Jobsheet::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string jDate, double jCount, int pID, int eID, std::string& errorMessage)
	{
		Jobsheet jobsheet;
		jobsheet.Clear();
		errorMessage.clear();
		jobsheet.SetDate(jDate);
		jobsheet.SetCount(jCount);
		jobsheet.SetProductID(pID);
		jobsheet.SetEmployeeID(eID);
		std::string filter = jobsheet.GenerateFilter(ormasDal);
		std::vector<DataLayer::jobsheetViewCollection> jobsheetVector = ormasDal.GetJobsheet(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == jobsheetVector.size())
		{
			return false;
		}
		errorMessage = "Jobsheet with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Jobsheet::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Jobsheet jobsheet;
		jobsheet.Clear();
		errorMessage.clear();
		jobsheet.SetDate(date);
		jobsheet.SetCount(count);
		jobsheet.SetProductID(productID);
		jobsheet.SetEmployeeID(employeeID);
		std::string filter = jobsheet.GenerateFilter(ormasDal);
		std::vector<DataLayer::jobsheetViewCollection> jobsheetVector = ormasDal.GetJobsheet(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == jobsheetVector.size())
		{
			return false;
		}
		errorMessage = "Jobsheet with these parameters are already exist! Please avoid the duplication!";
		return true;
	}
}