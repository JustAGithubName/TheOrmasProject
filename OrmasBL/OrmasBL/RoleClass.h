#ifndef ROLECLASS_H
#define ROLECLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Role
	{
		int id = 0;
		std::string code = "";
		std::string name = "";
		std::string comment = "";
	public:
		Role(int rID, std::string rCode, std::string rName, std::string comment) :id(rID), code(rCode), name(rName), comment(comment){};
		Role(DataLayer::rolesCollection);
		Role(){};
		~Role(){};
		
		//Role class Accessors
		int GetID();
		std::string GetCode();
		std::string GetName();
		std::string GetComment();

		//Please implement Mutators
		void SetID(int);
		void SetCode(std::string);
		void SetName(std::string);
		void SetComment(std::string);
		
		//Create, delete, update methods
		bool CreateRole(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateRole(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteRole(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateRole(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string rCode, std::string rName, std::string rComment, std::string& errorMessage);
		bool UpdateRole(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string rCode, std::string rName, std::string rComment, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetRoleByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		int GetRoleIDByName(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string rName, std::string& errorMessage);
		static std::map<std::string, int> GetRolesAsMap(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string rCode, std::string rName, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //ROLECLASS_H