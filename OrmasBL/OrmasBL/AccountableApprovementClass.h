#ifndef ACCOUNTABLEAPPROVEMENTCLASS_H
#define ACCOUNTABLEAPPROVEMENTCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class AccountableApprovement
	{
	protected:
		int id = 0;
		std::string approveDate = "";
		int directorID = 0;
		int accountantID = 0;
		int accountableDocumentID = 0;
	public:
		AccountableApprovement(){};
		AccountableApprovement(int aaID, std::string approvementDate, int dirID, int accoID, int aDocumentID) :id(aaID), approveDate(approvementDate), 
			directorID(dirID), accountantID(accoID), accountableDocumentID(aDocumentID){};
		AccountableApprovement(DataLayer::accountableApprovementCollection);
		~AccountableApprovement(){};

		std::string errorMessage = "";
		//AccountableApprovement class Accessors
		int GetID();
		std::string GetApproveDate();
		int GetDirectorID();
		int GetAccountantID();
		int GetAccountableDocumentID();


		//AccountableApprovement class Mutators
		void SetID(int);
		void SetApproveDate(std::string);
		void SetDirectorID(int);
		void SetAccounantID(int);
		void SetAccountableDocumentID(int);


		//Create, delete, update methods
		bool CreateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableApprovementByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int dirID, int accoID, int aDocumentID, std::string& errorMessage);
		bool UpdateAccountableApprovement(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int dirID, int accoID, int aDocumentID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableApprovementByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetAccountableApprovementByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		std::vector<int> GetAllApprovementByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int aDocumentID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //ACCOUNTABLEAPPROVEMENTCLASS_H