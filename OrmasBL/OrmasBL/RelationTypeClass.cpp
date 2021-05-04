#include "stdafx.h"
#include "RelationTypeClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	RelationType::RelationType(DataLayer::relationTypeCollection rtCollection)
	{
		id = std::get<0>(rtCollection);
		name = std::get<1>(rtCollection);
		comment = std::get<2>(rtCollection);
	}
	RelationType::RelationType()
	{
		name = "";
		comment = "";
	}
	int RelationType::GetID()
	{
		return id;
	}

	std::string RelationType::GetName()
	{
		return name;
	}
	std::string RelationType::GetComment()
	{
		return comment;
	}
	

	void RelationType::SetID(int cID)
	{
		id = cID;
	}
	void RelationType::SetName(std::string rtName)
	{
		if (!rtName.empty())
			boost::trim(rtName);
		name = rtName;
	}
	void RelationType::SetComment(std::string rtComment)
	{
		comment = rtComment;
	}
	
	bool RelationType::CreateRelationType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string rtName, std::string rtComment, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		TrimStrings(rtName);
		name = rtName;
		comment = rtComment;
		if (0 != id && ormasDal.CreateRelationType(id, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool RelationType::CreateRelationType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateRelationType(id, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool RelationType::DeleteRelationType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteRelationType(id, errorMessage))
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

	bool RelationType::UpdateRelationType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string rtName, std::string rtComment, std::string& errorMessage)
	{
		TrimStrings(rtName);
		name = rtName;
		comment = rtComment;
		if (0 != id && ormasDal.UpdateRelationType(id, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool RelationType::UpdateRelationType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateRelationType(id, name, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string RelationType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !comment.empty())
		{
			return ormasDal.GetFilterForRelationType(id, name, comment);
		}
		return "";
	}

	bool RelationType::GetRelationTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::relationTypeCollection> relationTypeVector = ormasDal.GetRelationType(errorMessage, filter);
		if (0 != relationTypeVector.size())
		{
			id = std::get<0>(relationTypeVector.at(0));
			name = std::get<1>(relationTypeVector.at(0));
			comment = std::get<2>(relationTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find access item with this id";
		}
		return false;
	}

	bool RelationType::IsEmpty()
	{
		if (0 == id && name.empty() && comment.empty())
			return true;
		return false;
	}

	void RelationType::Clear()
	{
		id = 0;
		name.clear();
		comment.clear();
	}

	void RelationType::TrimStrings(std::string& rtName)
	{
		if (!rtName.empty())
			boost::trim(rtName);
	}
}