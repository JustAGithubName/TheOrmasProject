#include "stdafx.h"
#include "FixedAssetsOperationsClass.h"

namespace BusinessLayer
{
	FixedAssetsOperations::FixedAssetsOperations(DataLayer::fixedAssetsOperationsCollection fCollection)
	{
		id = std::get<0>(fCollection);
		date = std::get<1>(fCollection);
		name = std::get<2>(fCollection);
		value = std::get<3>(fCollection);
		increment = std::get<4>(fCollection);
		decrement = std::get<5>(fCollection);
		fixedAssetsID = std::get<6>(fCollection);
	}

	int FixedAssetsOperations::GetID()
	{
		return id;
	}

	std::string FixedAssetsOperations::GetDate()
	{
		return date;
	}

	std::string FixedAssetsOperations::GetName()
	{
		return name;
	}

	double FixedAssetsOperations::GetValue()
	{
		return value;
	}

	bool FixedAssetsOperations::GetIncrement()
	{
		return increment;
	}

	bool FixedAssetsOperations::GetDecrement()
	{
		return decrement;
	}

	int FixedAssetsOperations::GetFixedAssetsID()
	{
		return fixedAssetsID;
	}

	void FixedAssetsOperations::SetID(int fID)
	{
		id = fID;
	}

	void FixedAssetsOperations::SetDate(std::string oDate)
	{
		date = oDate;
	}

	void FixedAssetsOperations::SetName(std::string oName)
	{
		name = oName;
	}

	void FixedAssetsOperations::SetValue(double oValue)
	{
		value = oValue;
	}

	void FixedAssetsOperations::SetIncrement(bool oIncrement)
	{
		increment = oIncrement;
	}

	void FixedAssetsOperations::SetDecrement(bool oDecrement)
	{
		decrement = oDecrement;
	}

	void FixedAssetsOperations::SetFixedAssetsID(int faID)
	{
		fixedAssetsID = faID;
	}

	bool FixedAssetsOperations::CreateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, std::string oName,
		double oValue, bool oIncrement, bool oDecrement, int faID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, oDate, oName, oValue, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		date = oDate;
		name = oName;
		value = oValue;
		increment = oIncrement;
		decrement = oDecrement;
		fixedAssetsID = faID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateFixedAssetsOperations(id, date, name, value, increment,
			decrement, fixedAssetsID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool FixedAssetsOperations::CreateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateFixedAssetsOperations(id, date, name, value, increment,
			decrement, fixedAssetsID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool FixedAssetsOperations::DeleteFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteFixedAssetsOperation(id, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool FixedAssetsOperations::UpdateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, std::string oName,
		double oValue, bool oIncrement, bool oDecrement, int faID, std::string& errorMessage)
	{
		date = oDate;
		name = oName;
		value = oValue;
		increment = oIncrement;
		decrement = oDecrement;
		fixedAssetsID = faID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateFixedAssetsOperations(id, date, name, value, increment,
			decrement, fixedAssetsID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool FixedAssetsOperations::UpdateFixedAssetsOperations(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateFixedAssetsOperations(id, date, name, value, increment,
			decrement, fixedAssetsID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string FixedAssetsOperations::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !name.empty() || 0 != value || 0 != fixedAssetsID)
		{
			return ormasDal.GetFilterForFixedAssetsOperations(id, date, name, value, increment,
				decrement, fixedAssetsID);
		}
		return "";
	}

	bool FixedAssetsOperations::GetFixedAssetsOperationsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fID, std::string& errorMessage)
	{
		if (fID <= 0)
			return false;
		id = fID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsOperationsCollection> fixedAssetsOperationsVector = ormasDal.GetFixedAssetsOperation(errorMessage, filter);
		if (0 != fixedAssetsOperationsVector.size())
		{
			id = std::get<0>(fixedAssetsOperationsVector.at(0));
			date = std::get<1>(fixedAssetsOperationsVector.at(0));
			name = std::get<2>(fixedAssetsOperationsVector.at(0));
			value = std::get<3>(fixedAssetsOperationsVector.at(0));
			increment = std::get<4>(fixedAssetsOperationsVector.at(0));
			decrement = std::get<5>(fixedAssetsOperationsVector.at(0));
			fixedAssetsID = std::get<6>(fixedAssetsOperationsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find fixed assets operations with this id";
		}
		return false;
	}

	bool FixedAssetsOperations::IsEmpty()
	{
		if (0 == id && date == "" && name == "" && 0.0 == value 
			&& false == increment && false == decrement && 0 == fixedAssetsID)
			return true;
		return false;
	}

	void FixedAssetsOperations::Clear()
	{
		id = 0;
		date = "";
		name = "";
		value = 0.0;
		increment = false;
		decrement = false;
		fixedAssetsID = 0;
	}

	bool FixedAssetsOperations::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, std::string oName, double oValue, std::string& errorMessage)
	{
		FixedAssetsOperations fixedAssetsOperations;
		fixedAssetsOperations.Clear();
		errorMessage.clear();
		fixedAssetsOperations.SetDate(oDate);
		fixedAssetsOperations.SetName(oName);
		fixedAssetsOperations.SetValue(oValue);
		std::string filter = fixedAssetsOperations.GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsOperationsCollection> FixedAssetsOperationsVector = ormasDal.GetFixedAssetsOperation(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == FixedAssetsOperationsVector.size())
		{
			return false;
		}
		errorMessage = "Fixed assets operation with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool FixedAssetsOperations::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		FixedAssetsOperations fixedAssetsOperations;
		fixedAssetsOperations.Clear();
		errorMessage.clear();
		fixedAssetsOperations.SetDate(date);
		fixedAssetsOperations.SetName(name);
		fixedAssetsOperations.SetValue(value);
		std::string filter = fixedAssetsOperations.GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsOperationsCollection> FixedAssetsOperationsVector = ormasDal.GetFixedAssetsOperation(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == FixedAssetsOperationsVector.size())
		{
			return false;
		}
		errorMessage = "Fixed assets operation with these parameters are already exist! Please avoid the duplication!";
		return true;
	}
}
