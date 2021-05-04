#ifndef ACCOUNTABLEDOCUMENTCLASS_H
#define ACCOUNTABLEDOCUMENTCLASS_H

#include "OrmasDAL.h"
#include <map>
#include "GlobalVariableClass.h"

namespace BusinessLayer
{
	class AccountableDocument
	{
	protected:
		int id = 0;
		std::string date = "";
		double value = 0;
		std::string expenseAssignment = "";
		int accountableID = 0;
		int statusID = 0;
	public:
		AccountableDocument(int dID, std::string dDate, double dValue, std::string oExpenseAssingment, int accblID, int sID) :
			id(dID), date(dDate), value(dValue), expenseAssignment(oExpenseAssingment), accountableID(accblID), statusID(sID){};
		AccountableDocument(DataLayer::accountableDocumentCollection);
		AccountableDocument(){};
		~AccountableDocument(){};

		//AccountableDocument class Accessors
		int GetID();
		std::string GetDate();
		double GetValue();
		std::string GetExpenseAssignment();
		int GetStatusID();
		int GetAccountableID();

		//AccountableDocument class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetValue(double);
		void SetExpenseAssignment(std::string);
		void SetStatusID(int);
		void SetAccountableID(int);

		//Create, delete, update methods
		bool CreateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, double dValue,
			std::string dExpenseAssignment, int accblID, int sID, std::string& errorMessage);
		bool UpdateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, double dValue,
			std::string dExpenseAssignment, int accblID, int sID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterFieldBiggerThen(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableDocumentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		int previousStatusID = 0;
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, double dValue,
			std::string dExpenseAssignment, int accblID, int sID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //ACCOUNTABLEDOCUMENTCLASS_H