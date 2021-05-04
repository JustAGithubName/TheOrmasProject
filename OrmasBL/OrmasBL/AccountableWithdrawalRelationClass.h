#ifndef AccountableWithdrawalRELATIONCLASS_H
#define AccountableWithdrawalRELATIONCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class AccountableWithdrawalRelation
	{
	protected:
		int id = 0;
		int accountableDocumentID = 0;
		int withdrawalID = 0;
	public:
		AccountableWithdrawalRelation();
		AccountableWithdrawalRelation(int bpID, int bID, int pID) :id(bpID), accountableDocumentID(bID), withdrawalID(pID){};
		AccountableWithdrawalRelation(DataLayer::accountableWithdrawalCollection);
		~AccountableWithdrawalRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetAccountableDocumentID();
		int GetWithdrawalID();

		//Access class Mutators
		void SetID(int);
		void SetAccountableDocumentID(int);
		void SetWithdrawalID(int);

		// Create, delete and update Access
		bool CreateAccountableWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableWithdrawalRelationByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableWithdrawalRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int aID, std::string& errorMessage);


		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableWithdrawalByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		std::vector<int> GetAllWithdrawalByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		std::vector<int> GetAllAccountableByWithdrawalID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif