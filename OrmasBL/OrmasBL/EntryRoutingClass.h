#ifndef ENTRYROUTINGCLASS_H
#define ENTRYROUTINGCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class EntryRouting{
	protected:
		int id = 0;
		std::string operation = "";
		int debitAccountID = 0;
		int creditAccountID = 0;
	public:
		EntryRouting();
		EntryRouting(int eID, std::string eOperation, int eDebit,int eCredit) :id(eID), operation(eOperation),
			debitAccountID(eDebit), creditAccountID(eCredit){};
		EntryRouting(DataLayer::entryRoutingCollection);
		~EntryRouting(){};

		std::string errorMessage = "";
		//EntryRouting class EntryRoutingors
		int GetID();
		std::string GetOperation();
		int GetDebitAccountID();
		int GetCreditAccountID();

		//EntryRouting class Mutators
		void SetID(int);
		void SetOperation(std::string);
		void SetDebitAccountID(int);
		void SetCreditAccountID(int);

		// Create, delete and update EntryRouting
		bool CreateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eOperation, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage);
		bool UpdateEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eOperation, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetEntryRoutingByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		bool CheckEntryRouting(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eOperation, int eDebitAccountID, int eCreditAccountID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //ENTRYROUTINGCLASS_H