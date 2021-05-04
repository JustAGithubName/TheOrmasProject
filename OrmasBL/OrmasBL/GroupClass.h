#ifndef GROUPCLASS_H
#define GROUPCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Group
	{
		int id = 0;
		std::string name = "";
		std::string defenition = "";
	public:
		Group();
		Group(int dID, std::string dName, std::string dDefenition) :id(dID),
			name(dName), defenition(dDefenition){};
		Group(DataLayer::groupsCollection);
		~Group(){};

		std::string errorMessage = "";
		//Group class Accessors
		int GetID();
		std::string GetName();
		std::string GetDefenition();
		
		//Group class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetDefenition(std::string);
		
		// Create, delete and update Group
		bool CreateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string gName, std::string gDefenition, std::string& errorMessage);
		bool UpdateGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string gName, std::string gDefenition, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetGroupByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		int GetGroupID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string gName, std::string gDefenition, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //GroupCLASS_H