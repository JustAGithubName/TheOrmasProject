#include "stdafx.h"
#include "PercentRateClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	PercentRate::PercentRate(DataLayer::percentRateCollection pCollection)
	{
		id = std::get<0>(pCollection);
		value = std::get<1>(pCollection);
		condition = std::get<2>(pCollection);
		positionID = std::get<3>(pCollection);
	}
	
	PercentRate::PercentRate()
	{
		value = 0;
		condition = "";
		positionID = 0;
	}
	
	int PercentRate::GetID()
	{
		return id;
	}

	double PercentRate::GetValue()
	{
		return value;
	}
	std::string PercentRate::GetCondition()
	{
		return condition;
	}
	int PercentRate::GetPositionID()
	{
		return positionID;
	}
	

	void PercentRate::SetID(int pID)
	{
		id = pID;
	}
	void PercentRate::SetValue(double pValue)
	{
		value = pValue;
	}
	void PercentRate::SetCondition(std::string pCondition)
	{
		if (!pCondition.empty())
			boost::trim(pCondition);
		condition = pCondition;
	}
	void PercentRate::SetPositionID(int pID)
	{
		positionID = pID;
	}

	

	bool PercentRate::CreatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double pValue, std::string pCondition, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pValue, pCondition, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(pCondition);
		value = pValue;
		condition = pCondition;
		positionID = pID;

		if (0 != id && ormasDal.CreatePercentRate(id, value, condition, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PercentRate::CreatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreatePercentRate(id, value, condition, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PercentRate::DeletePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeletePercentRate(id, errorMessage))
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

	bool PercentRate::UpdatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double pValue, std::string pCondition, int pID, std::string& errorMessage)
	{
		TrimStrings(pCondition);
		value = pValue;
		condition = pCondition;
		positionID = pID;
		if (0 != id && ormasDal.UpdatePercentRate(id, value, condition, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PercentRate::UpdatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdatePercentRate(id, value, condition, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string PercentRate::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != value || !condition.empty() || 0 != positionID)
		{
			return ormasDal.GetFilterForPercentRate(id, value, condition, positionID);
		}
		return "";
	}

	bool PercentRate::GetPercentRateByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::percentRateCollection> percentRateVector = ormasDal.GetPercentRate(errorMessage, filter);
		if (0 != percentRateVector.size())
		{
			id = std::get<0>(percentRateVector.at(0));
			value = std::get<1>(percentRateVector.at(0));
			condition = std::get<2>(percentRateVector.at(0));
			positionID = std::get<3>(percentRateVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find percent rate with this id";
		}
		return false;
	}

	bool PercentRate::IsEmpty()
	{
		if (0 == id && 0.0 == value  && condition.empty() && 0 == positionID)
			return true;
		return false;
	}

	void PercentRate::Clear()
	{
		id = 0;
		value = 0;
		condition.clear();
		positionID = 0;
	}

	void PercentRate::TrimStrings(std::string& pCondition)
	{
		if (!pCondition.empty())
			boost::trim(pCondition);
	}

	bool PercentRate::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double pValue, std::string pCondition, int pID, std::string& errorMessage)
	{
		PercentRate percentRate;
		percentRate.Clear();
		errorMessage.clear();
		percentRate.SetValue(pValue);
		percentRate.SetCondition(pCondition);
		percentRate.SetPositionID(pID);
		std::string filter = percentRate.GenerateFilter(ormasDal);
		std::vector<DataLayer::percentRateCollection> percentRateVector = ormasDal.GetPercentRate(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == percentRateVector.size())
		{
			return false;
		}
		errorMessage = "Percent rate with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool PercentRate::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		PercentRate percentRate;
		percentRate.Clear();
		errorMessage.clear();
		percentRate.SetValue(value);
		percentRate.SetCondition(condition);
		percentRate.SetPositionID(positionID);
		std::string filter = percentRate.GenerateFilter(ormasDal);
		std::vector<DataLayer::percentRateCollection> percentRateVector = ormasDal.GetPercentRate(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == percentRateVector.size())
		{
			return false;
		}
		errorMessage = "Percent rate with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}