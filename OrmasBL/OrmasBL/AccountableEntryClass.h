#ifndef ACCOUNTABLEENTRYCLASS_H
#define ACCOUNTABLEENTRYCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class AccountableEntry
	{
	protected:
		int id = 0;
		int debitAccountID = 0;
		int debitSubaccountID = 0;
		double value = 0;
		int creditAccountID = 0;
		int creditSubaccountID = 0;
		int accountableDocumentID = 0;
	public:
		AccountableEntry(){};
		AccountableEntry(int aeID, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID) :id(aeID), debitAccountID(daID),
			debitSubaccountID(dsID), value(eValue), creditAccountID(caID), creditSubaccountID(csID), accountableDocumentID(aDocumentID){};
		AccountableEntry(DataLayer::accountableEntryCollection);
		~AccountableEntry(){};

		std::string errorMessage = "";
		//AccountableEntry class Accessors
		int GetID();
		int GetDebitAccountID();
		int GetDebitSubaccountID();
		double GetValue();
		int GetCreditAccountID();
		int GetCreditSubaccountID();
		int GetAccountableDocumentID();


		//AccountableEntry class Mutators
		void SetID(int);
		void SetDebitAccountID(int);
		void SetDebitSubaccountID(int);
		void SetValue(double);
		void SetCreditAccountID(int);
		void SetCreditSubaccountID(int);
		void SetAccountableDocumentID(int);

		//Create, delete, update methods
		bool CreateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableEntryByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID, std::string& errorMessage);
		bool UpdateAccountableEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID, std::string& errorMessage);

		bool ExecuteEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool ExecuteEntryReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableEntryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		std::vector<int> GetAllEntryByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);

		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, int dsID, double eValue, int caID, int csID, int aDocumentID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);

		
	};
}

#endif //ACCOUNTABLEENTRYCLASS_H