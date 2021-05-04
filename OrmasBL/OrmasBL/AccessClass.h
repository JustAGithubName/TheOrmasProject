#ifndef ACCESSCLASS_H
#define ACCESSCLASS_H

#include "OrmasDAL.h"
#include "UserClass.h"


namespace BusinessLayer{
	class Access{
	protected:
		int id = 0;
		int roleID = 0;
		int accessItemID = 0;
	public:
		Access();
		Access(int aID, int rID, int aiID) :id(aID), roleID(rID), accessItemID(aiID){};
		Access(DataLayer::accessesCollection);
		~Access(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetRoleID();
		int GetAccessItemID();

		//Access class Mutators
		void SetID(int);
		void SetRoleID(int);
		void SetAccessItemID(int);

		// Create, delete and update Access
		bool CreateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int aiID, std::string& errorMessage);
		bool UpdateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int aiID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccessByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		bool CheckAccess(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, int accessItemID, std::string checkedDivision, std::string checkingItem);
		bool CheckAccess(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, int accessItemID, std::string checkedDivision);
		std::string GetCRUDAccess(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, User*, std::string accessItemName);
		std::vector<int> GetRightsList(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, User*);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int aiID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //ACCESSCLASS_H