#ifndef AccountablePAYMENTRELATIONCLASS_H
#define AccountablePAYMENTRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class AccountablePaymentRelation
	{
	protected:
		int id = 0;
		int accountableDocumentID = 0;
		int paymentID = 0;
	public:
		AccountablePaymentRelation();
		AccountablePaymentRelation(int bpID, int bID, int pID) :id(bpID), accountableDocumentID(bID), paymentID(pID){};
		AccountablePaymentRelation(DataLayer::accountablePaymentCollection);
		~AccountablePaymentRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetAccountableDocumentID();
		int GetPaymentID();

		//Access class Mutators
		void SetID(int);
		void SetAccountableDocumentID(int);
		void SetPaymentID(int);

		// Create, delete and update Access
		bool CreateAccountablePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountablePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountablePaymentRelationByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountablePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int aID, std::string& errorMessage);


		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountablePaymentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		std::vector<int> GetAllPaymentByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		std::vector<int> GetAllAccountableByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif