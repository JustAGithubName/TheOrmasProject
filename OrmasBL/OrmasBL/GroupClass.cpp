#include "stdafx.h"
#include "GroupClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	Group::Group(DataLayer::groupsCollection gCollection)
	{
		id = std::get<0>(gCollection);
		name = std::get<1>(gCollection);
		defenition = std::get<2>(gCollection);
	}
	Group::Group()
	{
		name = "";
		defenition = "";
	}
	int Group::GetID()
	{
		return id;
	}

	std::string Group::GetName()
	{
		return name;
	}

	std::string Group::GetDefenition()
	{
		return defenition;
	}

	void Group::SetID(int cID)
	{
		id = cID;
	}
	void Group::SetName(std::string cName)
	{
		if (!cName.empty())
			boost::trim(cName);
		name = cName;
	}
	void Group::SetDefenition(std::string cDefenition)
	{
		if (!cDefenition.empty())
			boost::trim(cDefenition);
		defenition = cDefenition;
	}

	bool Group::CreateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string gName, std::string gDefenition, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, gName, gDefenition, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(gName, gDefenition);
		name = gName;
		defenition = gDefenition;
		if (0 != id && ormasDal.CreateGroups(id, name, defenition, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Group::CreateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateGroups(id, name, defenition, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Group::DeleteGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteGroup(id, errorMessage))
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

	bool Group::UpdateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cDefenition, std::string& errorMessage)
	{
		TrimStrings(cName, cDefenition);
		name = cName;
		defenition = cDefenition;
		if (0 != id && ormasDal.UpdateGroups(id, name, defenition, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Group::UpdateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateGroups(id, name, defenition, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Group::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !defenition.empty())
		{
			return ormasDal.GetFilterForGroups(id, name, defenition);
		}
		return "";
	}

	bool Group::GetGroupByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::groupsCollection> groupVector = ormasDal.GetGroups(errorMessage, filter);
		if (0 != groupVector.size())
		{
			id = std::get<0>(groupVector.at(0));
			name = std::get<1>(groupVector.at(0));
			defenition = std::get<2>(groupVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Group with this id";
		}
		return false;
	}

	int Group::GetGroupID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string filter = this->GenerateFilter(ormasDal);
		std::vector<DataLayer::groupsCollection> groupVector = ormasDal.GetGroups(errorMessage, filter);
		if (0 != groupVector.size())
		{
			return std::get<0>(groupVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find Group with this id";
		}
		return 0;
	}

	bool Group::IsEmpty()
	{
		if (0 == id && name == "" && defenition == "")
			return true;
		return false;
	}

	void Group::Clear()
	{
		id = 0;
		name.clear();
		defenition.clear();
	}

	void Group::TrimStrings(std::string& cName, std::string& cDefenition)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cDefenition.empty())
			boost::trim(cDefenition);
	}

	bool Group::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cDefenition, std::string& errorMessage)
	{
		Group group;
		group.Clear();
		errorMessage.clear();
		group.SetName(cName);
		group.SetDefenition(cDefenition);
		std::string filter = group.GenerateFilter(ormasDal);
		std::vector<DataLayer::groupsCollection> groupVector = ormasDal.GetGroups(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == groupVector.size())
		{
			return false;
		}
		errorMessage = "Group with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Group::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Group group;
		group.Clear();
		errorMessage.clear();
		group.SetName(name);
		group.SetDefenition(defenition);
		std::string filter = group.GenerateFilter(ormasDal);
		std::vector<DataLayer::groupsCollection> groupVector = ormasDal.GetGroups(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == groupVector.size())
		{
			return false;
		}
		errorMessage = "Group with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

