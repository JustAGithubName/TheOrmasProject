#ifndef USERGROUPRELATIONVIEWCLASS_H
#define USERGROUPRELATIONVIEWCLASS_H
#include "UserGroupRelationClass.h"

namespace BusinessLayer
{
	class UserGroupRelationView : public UserGroupRelation
	{
		std::string groupName = "";
		std::string userName = "";
		std::string userSurname = "";
		int roleID = 0;
	public:
		UserGroupRelationView(DataLayer::userGroupViewCollection);
		UserGroupRelationView(){};
		~UserGroupRelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//UserGroupView class Accessors
		std::string GetGroupName();
		std::string GetUsername();
		std::string GetUserSurname();
		int GetRoleID();

		void SetGroupName(std::string);
		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetRoleID(int);
	};
}

#endif //UserGroupVIEWCLASS_H