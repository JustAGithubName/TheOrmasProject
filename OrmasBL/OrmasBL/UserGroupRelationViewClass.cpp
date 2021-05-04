#include "stdafx.h"
#include "UserGroupRelationViewClass.h"

namespace BusinessLayer
{
	UserGroupRelationView::UserGroupRelationView(DataLayer::userGroupViewCollection uCollection)
	{
		id = std::get<0>(uCollection);
		groupName = std::get<1>(uCollection);
		userSurname = std::get<2>(uCollection);
		userName = std::get<3>(uCollection);
		roleID = std::get<4>(uCollection);
		groupID = std::get<5>(uCollection);
		userID = std::get<6>(uCollection);
	}

	std::string UserGroupRelationView::GetGroupName()
	{
		return groupName;
	}
	std::string UserGroupRelationView::GetUserSurname()
	{
		return userSurname;
	}
	std::string UserGroupRelationView::GetUsername()
	{
		return userName;
	}
	int UserGroupRelationView::GetRoleID()
	{
		return roleID;
	}

	void UserGroupRelationView::SetGroupName(std::string uGroupName)
	{
		groupName = uGroupName;
	}
	void UserGroupRelationView::SetUserSurname(std::string uUserSurname)
	{
		userSurname = uUserSurname;
	}
	void UserGroupRelationView::SetUsername(std::string uUserName)
	{
		userName = uUserName;
	}
	void UserGroupRelationView::SetRoleID(int uRoleID)
	{
		roleID = uRoleID;
	}

	std::string UserGroupRelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != groupID || 0 != userID)
		{
			return ormasDal.GetFilterForGroupView(id, groupName, userSurname, userName, roleID, groupID, userID);
		}
		return "";
	}
}