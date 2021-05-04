#include "stdafx.h"
#include "UserGroupRelationClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	UserGroupRelation::UserGroupRelation(DataLayer::userGroupCollection dCollection)
	{
		id = std::get<0>(dCollection);
		groupID = std::get<1>(dCollection);
		userID = std::get<2>(dCollection);
	}
	UserGroupRelation::UserGroupRelation()
	{
		groupID = 0;
		userID = 0;
	}

	int UserGroupRelation::GetID()
	{
		return id;
	}

	int UserGroupRelation::GetGroupID()
	{
		return groupID;
	}

	int UserGroupRelation::GetUserID()
	{
		return userID;
	}

	void UserGroupRelation::SetID(int dID)
	{
		id = dID;
	}
	void UserGroupRelation::SetGroupID(int ugGroupID)
	{
		groupID = ugGroupID;
	}
	void UserGroupRelation::SetUserID(int ugUserID)
	{
		userID = ugUserID;
	}
	
	bool UserGroupRelation::CreateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int guGroupID, int guUserID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, guGroupID, guUserID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		groupID = guGroupID;
		userID = guUserID;
		if (0 != id && ormasDal.CreateUserGroup(id, groupID, userID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool UserGroupRelation::CreateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateUserGroup(id, groupID, userID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool UserGroupRelation::DeleteUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteUserGroup(id, errorMessage))
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

	bool UserGroupRelation::UpdateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int guGroupID, int guUserID, std::string& errorMessage)
	{
		groupID = guGroupID;
		userID = guUserID;
		if (0 != id && ormasDal.UpdateUserGroup(id, groupID, userID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool UserGroupRelation::UpdateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateUserGroup(id, groupID, userID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string UserGroupRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != groupID || 0 != userID)
		{
			return ormasDal.GetFilterForUserGroup(id, groupID, userID);
		}
		return "";
	}

	bool UserGroupRelation::GetUserGroupRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string& errorMessage)
	{
		if (dID <= 0)
			return false;
		id = dID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::userGroupViewCollection> userGroupRelationVector = ormasDal.GetUserGroup(errorMessage, filter);
		if (0 != userGroupRelationVector.size())
		{
			id = std::get<0>(userGroupRelationVector.at(0));
			groupID = std::get<5>(userGroupRelationVector.at(0));
			userID = std::get<6>(userGroupRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find division account relation with this id";
		}
		return false;
	}

	std::vector<int> UserGroupRelation::GetAllGroupIDByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		std::vector<int> groupIDList;
		if (uID <= 0)
			return groupIDList;
		userID = uID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::userGroupViewCollection> userGroupVector = ormasDal.GetUserGroup(errorMessage, filter);
		if (0 < userGroupVector.size())
		{
			for each (auto gItem in userGroupVector)
			{
				groupIDList.push_back(std::get<5>(gItem));
			}
		}
		else
		{
			errorMessage = "Cannot find group fro this user!";
		}
		return groupIDList;
	}

	std::vector<int> UserGroupRelation::GetAllUserIDByGroupID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gID, std::string& errorMessage)
	{
		std::vector<int> userIDList;
		if (gID <= 0)
			return userIDList;
		groupID = gID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::userGroupViewCollection> userGroupVector = ormasDal.GetUserGroup(errorMessage, filter);
		if (0 < userGroupVector.size())
		{
			for each (auto gItem in userGroupVector)
			{
				userIDList.push_back(std::get<6>(gItem));
			}
		}
		else
		{
			errorMessage = "Cannot find group fro this user!";
		}
		return userIDList;
	}

	bool UserGroupRelation::IsEmpty()
	{
		if (0 == id && 0 == groupID && 0 == userID)
			return true;
		return false;
	}

	void UserGroupRelation::Clear()
	{
		id = 0;
		groupID = 0;
		userID = 0;
	}

	void UserGroupRelation::TrimStrings(std::string& dCode)
	{
		if (!dCode.empty())
			boost::trim(dCode);
	}

	bool UserGroupRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int guGroupID, int guUserID, std::string& errorMessage)
	{
		UserGroupRelation userGroupRelation;
		userGroupRelation.Clear();
		errorMessage.clear();
		userGroupRelation.SetGroupID(guGroupID);
		userGroupRelation.SetUserID(guUserID);
		std::string filter = userGroupRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::userGroupViewCollection> userGroupRelationVector = ormasDal.GetUserGroup(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == userGroupRelationVector.size())
		{
			return false;
		}
		errorMessage = "User group relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool UserGroupRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		UserGroupRelation userGroupRelation;
		userGroupRelation.Clear();
		errorMessage.clear();
		userGroupRelation.SetGroupID(groupID);
		userGroupRelation.SetUserID(userID);
		std::string filter = userGroupRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::userGroupViewCollection> userGroupRelationVector = ormasDal.GetUserGroup(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == userGroupRelationVector.size())
		{
			return false;
		}
		errorMessage = "User group relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

