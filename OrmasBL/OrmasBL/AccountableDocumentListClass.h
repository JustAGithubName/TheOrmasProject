#ifndef AccountableDocumentListRELATIONCLASS_H
#define AccountableDocumentListRELATIONCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class AccountableDocumentListRelation
	{
	protected:
		int id = 0;
		int accountableDocumentID = 0;
		int expenseDocumentID = 0;
	public:
		AccountableDocumentListRelation();
		AccountableDocumentListRelation(int adlID, int adID, int edID) :id(adlID), accountableDocumentID(adID), expenseDocumentID(edID){};
		AccountableDocumentListRelation(DataLayer::accountableDocumentListCollection);
		~AccountableDocumentListRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetAccountableDocumentID();
		int GetExpenseDocumentID();

		//Access class Mutators
		void SetID(int);
		void SetAccountableDocumentID(int);
		void SetExpenseDocumentID(int);

		// Create, delete and update Access
		bool CreateAccountableDocumentListRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableDocumentListRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableDocumentListRelationByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableDocumentListRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, int edID, std::string& errorMessage);


		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetDocumentListByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, std::string& errorMessage);
		bool GetDocumentListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		std::vector<int> GetAllListByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, std::string& errorMessage);
		std::vector<int> GetAllListByExpenseDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int edID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int adID, int edID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif