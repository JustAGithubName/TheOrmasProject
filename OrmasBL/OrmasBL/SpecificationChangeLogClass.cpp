#include "stdafx.h"
#include "SpecificationChangeLogClass.h"

namespace BusinessLayer
{
	SpecificationChangeLog::SpecificationChangeLog(DataLayer::specificationChangeLogCollection sLogCollection)
	{
		id = std::get<0>(sLogCollection);
		specificationID = std::get<1>(sLogCollection);
		productID = std::get<2>(sLogCollection);
		count = std::get<3>(sLogCollection);
		logDate = std::get<4>(sLogCollection);
		userID = std::get<5>(sLogCollection);
	}

	int SpecificationChangeLog::GetID()
	{
		return id;
	}

	int SpecificationChangeLog::GetSpecificationID()
	{
		return specificationID;
	}

	int SpecificationChangeLog::GetProductID()
	{
		return productID;
	}

	double SpecificationChangeLog::GetCount()
	{
		return count;
	}

	std::string SpecificationChangeLog::GetLogDate()
	{
		return logDate;
	}

	int SpecificationChangeLog::GetUserID()
	{
		return userID;
	}

	void SpecificationChangeLog::SetID(int sID)
	{
		id = sID;
	}
	void SpecificationChangeLog::SetSpecificationID(int pSpecificationID)
	{
		specificationID = pSpecificationID;
	}
	void SpecificationChangeLog::SetProductID(int pProductID)
	{
		productID = pProductID;
	}
	void SpecificationChangeLog::SetCount(double pCount)
	{
		count = pCount;
	}

	void SpecificationChangeLog::SetLogDate(std::string sLogDate)
	{
		logDate = sLogDate;
	}
	void SpecificationChangeLog::SetUserID(int pUserID)
	{
		userID = pUserID;
	}

	bool SpecificationChangeLog::CreateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, 
		std::string sLogDate, int sUserID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		specificationID = sID;
		productID = pID;
		count = slCount;
		logDate = sLogDate;
		userID = sUserID;
		if (0 != id && ormasDal.CreateSpecificationChangeLog(id, specificationID, productID, count, logDate, userID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool SpecificationChangeLog::CreateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateSpecificationChangeLog(id, specificationID, productID, count, logDate, userID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool SpecificationChangeLog::DeleteSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSpecificationChangeLog(id, errorMessage))
		{
			Clear();
			return true;
		}
		return false;
	}

	bool SpecificationChangeLog::UpdateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, 
		double slCount, std::string sLogDate, int sUserID, std::string& errorMessage)
	{
		specificationID = sID;
		productID = pID;
		count = slCount;
		logDate = sLogDate;
		userID = sUserID;
		if (0 != id && ormasDal.UpdateSpecificationChangeLog(id, specificationID, productID, count,  logDate, userID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool SpecificationChangeLog::UpdateSpecificationChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateSpecificationChangeLog(id, specificationID, productID, count, logDate, userID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string SpecificationChangeLog::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != specificationID || 0 != productID || 0 != count || !logDate.empty() || 0!=userID)
		{
			return ormasDal.GetFilterForSpecificationChangeLog(id, specificationID, productID, count, logDate, userID);
		}
		return "";
	}

	bool SpecificationChangeLog::GetSpecificationChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationChangeLogCollection> specificationChangeLogVector = ormasDal.GetSpecificationChangeLog(errorMessage, filter);
		if (0 != specificationChangeLogVector.size())
		{
			id = std::get<0>(specificationChangeLogVector.at(0));
			specificationID = std::get<1>(specificationChangeLogVector.at(0));
			productID = std::get<2>(specificationChangeLogVector.at(0));
			count = std::get<3>(specificationChangeLogVector.at(0));
			logDate = std::get<4>(specificationChangeLogVector.at(0));
			userID = std::get<5>(specificationChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find specification list with this id";
		}
		return false;
	}

	bool SpecificationChangeLog::GetSpecificationChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		if (uID <= 0)
			return false;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationChangeLogCollection> specificationChangeLogVector = ormasDal.GetSpecificationChangeLog(errorMessage, filter);
		if (0 != specificationChangeLogVector.size())
		{
			id = std::get<0>(specificationChangeLogVector.at(0));
			specificationID = std::get<1>(specificationChangeLogVector.at(0));
			productID = std::get<2>(specificationChangeLogVector.at(0));
			count = std::get<3>(specificationChangeLogVector.at(0));
			logDate = std::get<4>(specificationChangeLogVector.at(0));
			userID = std::get<5>(specificationChangeLogVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find specification list with this id";
		}
		return false;
	}


	bool SpecificationChangeLog::IsEmpty()
	{
		if (0 == id && 0 == specificationID && 0 == count && 0 == productID && logDate.empty() && 0== userID)
			return true;
		return false;
	}

	void SpecificationChangeLog::Clear()
	{
		id = 0;
		specificationID = 0;
		productID = 0;
		count = 0;
		logDate.empty();
		userID = 0;
	}

	bool SpecificationChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int pID, double slCount, 
		std::string sLogDate, int sUserID, std::string& errorMessage)
	{
		SpecificationChangeLog specificationChangeLog;
		specificationChangeLog.Clear();
		errorMessage.clear();
		specificationChangeLog.SetSpecificationID(sID);
		specificationChangeLog.SetProductID(pID);
		specificationChangeLog.SetCount(slCount);
		specificationChangeLog.SetLogDate(sLogDate);
		specificationChangeLog.SetUserID(sUserID);
		std::string filter = specificationChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationChangeLogCollection> specificationChangeLogVector = ormasDal.GetSpecificationChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == specificationChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Specification change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool SpecificationChangeLog::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		SpecificationChangeLog specificationChangeLog;
		specificationChangeLog.Clear();
		errorMessage.clear();
		specificationChangeLog.SetSpecificationID(specificationID);
		specificationChangeLog.SetProductID(productID);
		specificationChangeLog.SetCount(count);
		specificationChangeLog.SetLogDate(logDate);
		specificationChangeLog.SetUserID(userID);
		std::string filter = specificationChangeLog.GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationChangeLogCollection> specificationChangeLogVector = ormasDal.GetSpecificationChangeLog(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == specificationChangeLogVector.size())
		{
			return false;
		}
		errorMessage = "Specification change log with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}