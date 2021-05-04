#include "stdafx.h"
#include "StatusClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	Status::Status(DataLayer::statusCollection sCollection)
	{
		id = std::get<0>(sCollection);
		code = std::get<1>(sCollection);
		name = std::get<2>(sCollection);
		comment = std::get<3>(sCollection);
	}

	int Status::GetID()
	{
		return id;
	}

	std::string Status::GetCode()
	{
		return  code;
	}

	std::string Status::GetName()
	{
		return name;
	}

	std::string Status::GetComment()
	{
		return comment;
	}

	void Status::SetID(int sID)
	{
		id = sID;
	}
	void Status::SetCode(std::string sCode)
	{
		if (!sCode.empty())
			boost::trim(sCode);
		code = sCode;
	}
	void Status::SetName(std::string sName)
	{
		if (!sName.empty())
			boost::trim(sName);
		name = boost::to_upper_copy(sName);
	}
	void Status::SetComment(std::string sComment)
	{
		comment = sComment;
	}


	bool Status::CreateStatus(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sCode, std::string sName, std::string sComment, 
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, sCode, sName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(sCode, sName);
		code = sCode;
		name = boost::to_upper_copy(sName);
		comment = sComment;
		if (0 != id && ormasDal.CreateStatus(id, code, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Status::CreateStatus(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateStatus(id, code, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Status::DeleteStatus(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteStatus(id, errorMessage))
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
	bool Status::UpdateStatus(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sCode, std::string sName, std::string sComment, 
		std::string& errorMessage)
	{
		TrimStrings(sCode, sName);
		code = sCode;
		name = boost::to_upper_copy(sName);
		comment = sComment;
		if (0 != id && ormasDal.UpdateStatus(id, code, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Status::UpdateStatus(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateStatus(id, code, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Status::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !code.empty() || !name.empty() || !comment.empty())
		{
			return ormasDal.GetFilterForStatus(id, code, name, comment);
		}
		return "";
	}

	bool Status::GetStatusByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::statusCollection> statusVector = ormasDal.GetStatus(errorMessage, filter);
		if (0 != statusVector.size())
		{
			id = std::get<0>(statusVector.at(0));
			code = std::get<1>(statusVector.at(0));
			name = std::get<2>(statusVector.at(0));
			comment = std::get<3>(statusVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find status with this id";
		}
		return false;
	}
	
	bool Status::GetStatusByName(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sName, std::string& errorMessage)
	{
		if (!sName.empty())
			boost::trim(sName);
		if (sName.empty())
			return false;
		name = boost::to_upper_copy(sName);
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::statusCollection> statusVector = ormasDal.GetStatus(errorMessage, filter);
		if (0 != statusVector.size())
		{
			id = std::get<0>(statusVector.at(0));
			code = std::get<1>(statusVector.at(0));
			name = std::get<2>(statusVector.at(0));
			comment = std::get<3>(statusVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find status with this name";
		}
		return false;
	}

	bool Status::IsEmpty()
	{
		if(0 == id && code == "" && name == "" && comment == "")
			return true;
		return false;
	}

	void Status::Clear()
	{
		id = 0;
		code.clear();
		name.clear();
		comment.clear();
	}

	void Status::TrimStrings(std::string& sCode, std::string& sName)
	{
		if (!sCode.empty())
			boost::trim(sCode);
		if (!sName.empty())
			boost::trim(sName);
	}

	bool Status::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sCode, std::string sName, std::string& errorMessage)
	{
		Status status;
		status.Clear();
		errorMessage.clear();
		status.SetCode(sCode);
		status.SetName(sName);
		std::string filter = status.GenerateFilter(ormasDal);
		std::vector<DataLayer::statusCollection> statusVector = ormasDal.GetStatus(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == statusVector.size())
		{
			return false;
		}
		errorMessage = "Status with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Status::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Status status;
		status.Clear();
		errorMessage.clear();
		status.SetCode(code);
		status.SetName(name);
		std::string filter = status.GenerateFilter(ormasDal);
		std::vector<DataLayer::statusCollection> statusVector = ormasDal.GetStatus(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == statusVector.size())
		{
			return false;
		}
		errorMessage = "Status with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::map<std::string, int> Status::GetStatusesAsMap(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap;
		std::vector<DataLayer::statusCollection> statusVector = ormasDal.GetStatus(errorMessage);
		if (statusVector.size() > 0)
		{
			for each (auto item in statusVector)
			{
				statusMap.insert(std::make_pair(std::get<2>(item), std::get<0>(item)));
			}
		}
		return statusMap;
	}
}