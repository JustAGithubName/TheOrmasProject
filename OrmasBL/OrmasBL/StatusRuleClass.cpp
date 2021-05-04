#include "stdafx.h"
#include "StatusRuleClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	StatusRule::StatusRule(DataLayer::statusRuleCollection sCollection)
	{
		id = std::get<0>(sCollection);
		operation = std::get<1>(sCollection);
		statusID = std::get<2>(sCollection);
	}

	int StatusRule::GetID()
	{
		return id;
	}

	std::string StatusRule::GetOperation()
	{
		return  operation;
	}

	int StatusRule::GetStatusID()
	{
		return statusID;
	}

	void StatusRule::SetID(int sID)
	{
		id = sID;
	}
	void StatusRule::SetOperation(std::string sOperation)
	{
		if (!sOperation.empty())
			boost::trim(sOperation);
		operation = boost::to_upper_copy(sOperation);
	}
	void StatusRule::SetStatusID(int sID)
	{
		statusID = sID;
	}


	bool StatusRule::CreateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, int sID,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, sOperation, sID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(sOperation);
		operation = boost::to_upper_copy(sOperation);
		statusID = sID;
		if (0 != id && ormasDal.CreateStatusRule(id, operation, statusID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool StatusRule::CreateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStatusRule(id, operation, statusID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool StatusRule::DeleteStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteStatusRule(id, errorMessage))
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
	bool StatusRule::UpdateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, int sID,
		std::string& errorMessage)
	{
		TrimStrings(sOperation);
		operation = boost::to_upper_copy(sOperation);
		statusID = sID;
		if (0 != id && ormasDal.UpdateStatusRule(id, operation, statusID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool StatusRule::UpdateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateStatusRule(id, operation, statusID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string StatusRule::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !operation.empty() || 0 != statusID)
		{
			return ormasDal.GetFilterForStatusRule(id, operation, statusID);
		}
		return "";
	}

	bool StatusRule::GetStatusRuleByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::statusRuleViewCollection> statusRuleVector = ormasDal.GetStatusRule(errorMessage, filter);
		if (0 != statusRuleVector.size())
		{
			id = std::get<0>(statusRuleVector.at(0));
			operation = std::get<1>(statusRuleVector.at(0));
			statusID = std::get<3>(statusRuleVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Status Rule with this id";
		}
		return false;
	}

	bool StatusRule::GetStatusRuleByOperation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, std::string& errorMessage)
	{
		if (!sOperation.empty())
			boost::trim(sOperation);
		if (sOperation.empty())
			return false;
		operation = boost::to_upper_copy(sOperation);
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::statusRuleViewCollection> statusRuleVector = ormasDal.GetStatusRule(errorMessage, filter);
		if (0 != statusRuleVector.size())
		{
			id = std::get<0>(statusRuleVector.at(0));
			operation = std::get<1>(statusRuleVector.at(0));
			statusID = std::get<3>(statusRuleVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Status Rule with this name";
		}
		return false;
	}

	bool StatusRule::IsEmpty()
	{
		if (0 == id && operation == "" && 0 == statusID)
			return true;
		return false;
	}

	void StatusRule::Clear()
	{
		id = 0;
		operation.clear();
		statusID = 0;
	}

	void StatusRule::TrimStrings(std::string& sOperation)
	{
		if (!sOperation.empty())
			boost::trim(sOperation);
	}

	bool StatusRule::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, int sID, std::string& errorMessage)
	{
		StatusRule statusRule;
		statusRule.Clear();
		errorMessage.clear();
		statusRule.SetOperation(sOperation);
		statusRule.SetStatusID(sID);
		std::string filter = statusRule.GenerateFilter(ormasDal);
		std::vector<DataLayer::statusRuleViewCollection> statusRuleVector = ormasDal.GetStatusRule(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == statusRuleVector.size())
		{
			return false;
		}
		errorMessage = "Status Rule with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool StatusRule::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		StatusRule statusRule;
		statusRule.Clear();
		errorMessage.clear();
		statusRule.SetOperation(operation);
		statusRule.SetStatusID(statusID);
		std::string filter = statusRule.GenerateFilter(ormasDal);
		std::vector<DataLayer::statusRuleViewCollection> statusRuleVector = ormasDal.GetStatusRule(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == statusRuleVector.size())
		{
			return false;
		}
		errorMessage = "Status Rule with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}