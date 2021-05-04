#include "stdafx.h"
#include "SubaccountLimitClass.h"


namespace BusinessLayer{
	SubaccountLimit::SubaccountLimit(DataLayer::subaccountLimitCollection saCollection)
	{
		id = std::get<0>(saCollection);
		subaccountID = std::get<1>(saCollection);
		minValue = std::get<2>(saCollection);
		maxValue = std::get<3>(saCollection);
	}
	SubaccountLimit::SubaccountLimit()
	{
		id = 0;
		subaccountID = 0;
		minValue = 0.0;
		maxValue = 0.0;
	}

	int SubaccountLimit::GetID()
	{
		return id;
	}

	int SubaccountLimit::GetSubaccountID()
	{
		return subaccountID;
	}

	double SubaccountLimit::GetMinValue()
	{
		return minValue;
	}

	double SubaccountLimit::GetMaxValue()
	{
		return maxValue;
	}

	
	void SubaccountLimit::SetID(int aID)
	{
		id = aID;
	}

	void SubaccountLimit::SetSubaccountID(int saID)
	{
		subaccountID = saID;
	}

	void SubaccountLimit::SetMinValue(double aMinValue)
	{
		minValue = aMinValue;
	}

	void SubaccountLimit::SetMaxValue(double aMaxValue)
	{
		maxValue = aMaxValue;
	}

	bool SubaccountLimit::CreateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID,  double sMin, double sMax, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, sID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		subaccountID = sID;
		minValue = sMin;
		maxValue = sMax;
		if (0 != id && ormasDal.CreateSubaccountLimit(id, subaccountID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountLimit::CreateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateSubaccountLimit(id, subaccountID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountLimit::DeleteSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSubaccountLimit(id, errorMessage))
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

	bool SubaccountLimit::UpdateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, double sMin, double sMax, std::string& errorMessage)
	{
		subaccountID = sID;
		minValue = sMin;
		maxValue = sMax;
		if (0 != id && ormasDal.UpdateSubaccountLimit(id, subaccountID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool SubaccountLimit::UpdateSubaccountLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateSubaccountLimit(id, subaccountID, minValue, maxValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string SubaccountLimit::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountID || 0.0 != minValue || 0.0 != maxValue)
		{
			return ormasDal.GetFilterForSubaccountLimit(id, subaccountID, minValue, maxValue);
		}
		return "";
	}

	bool SubaccountLimit::GetSubaccountLimitByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int slID, std::string& errorMessage)
	{
		if (slID <= 0)
			return false;
		id = slID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountLimitViewCollection> subaccountLimitVector = ormasDal.GetSubaccountLimit(errorMessage, filter);
		if (0 != subaccountLimitVector.size())
		{
			id = std::get<0>(subaccountLimitVector.at(0));
			subaccountID = std::get<2>(subaccountLimitVector.at(0));
			minValue = std::get<3>(subaccountLimitVector.at(0));
			maxValue = std::get<4>(subaccountLimitVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount limit with this id";
		}
		return false;
	}

	bool SubaccountLimit::GetSubaccountLimitBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		subaccountID = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountLimitViewCollection> subaccountLimitVector = ormasDal.GetSubaccountLimit(errorMessage, filter);
		if (0 != subaccountLimitVector.size())
		{
			id = std::get<0>(subaccountLimitVector.at(0));
			subaccountID = std::get<2>(subaccountLimitVector.at(0));
			minValue = std::get<3>(subaccountLimitVector.at(0));
			maxValue = std::get<4>(subaccountLimitVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount limit with this id";
		}
		return false;
	}

	bool SubaccountLimit::IsEmpty()
	{
		if (0 == id && 0 == subaccountID  && 0.0 == minValue && 0.0 == maxValue)
			return true;
		return false;
	}

	void SubaccountLimit::Clear()
	{
		id = 0;
		subaccountID = 0;
		minValue = 0.0;
		maxValue = 0.0;
	}

	bool SubaccountLimit::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		SubaccountLimit subaccountLimit;
		subaccountLimit.Clear();
		errorMessage.clear();
		subaccountLimit.SetSubaccountID(sID);
		std::string filter = subaccountLimit.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountLimitViewCollection> subaccountLimitVector = ormasDal.GetSubaccountLimit(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountLimitVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount limit with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool SubaccountLimit::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		SubaccountLimit subaccountLimit;
		subaccountLimit.Clear();
		errorMessage.clear();
		subaccountLimit.SetSubaccountID(subaccountID);
		std::string filter = subaccountLimit.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountLimitViewCollection> subaccountLimitVector = ormasDal.GetSubaccountLimit(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountLimitVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount limit with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}