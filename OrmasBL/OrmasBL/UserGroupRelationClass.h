#ifndef USERGROUPRELATIONCLASS_H
#define USERGROUPRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class UserGroupRelation
	{
	protected:
		int id = 0;
		int groupID = 0;
		int userID = 0;
	public:
		UserGroupRelation();
		UserGroupRelation(int ugID, int ugGroupID, int ugUserID) :id(ugID), groupID(ugGroupID),
			userID(ugUserID){};
		UserGroupRelation(DataLayer::userGroupCollection);
		~UserGroupRelation(){};

		std::string errorMessage = "";
		//UserGroupRelation class Accessors
		int GetID();
		int GetGroupID();
		int GetUserID();
		

		//UserGroupRelation class Mutators
		void SetID(int);
		void SetGroupID(int);
		void SetUserID(int);
		

		// Create, delete and update UserGroupRelation
		bool CreateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ugGroupID, int ugUserID, std::string& errorMessage);
		bool UpdateUserGroupRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ugGroupID, int ugUserID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetUserGroupRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ugID, std::string& errorMessage);
		bool GetDARelationByDivisionIDAndCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string code, std::string& errorMessage);
		std::vector<int> GetAllGroupIDByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		std::vector<int> GetAllUserIDByGroupID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ugGroupID, int ugUserID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //UserGroupRELATIONCLASS_H