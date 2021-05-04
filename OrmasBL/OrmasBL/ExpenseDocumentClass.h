#ifndef EXPENSEDOCUMENTCLASS_H
#define EXPENSEDOCUMENTCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class ExpenseDocument
	{
	protected:
		int id = 0;
		std::string expenseName = "";
		double count = 0;
		double sum = 0;
		int measureID = 0;
		int currencyID = 0;
	public:
		ExpenseDocument(){};
		ExpenseDocument(int eD, std::string eName, double eCount, double eSum, int eMeasureID, int eCurrencyID) :id(eD), expenseName(eName),
			count(eCount), sum(eSum), measureID(eMeasureID), currencyID(eCurrencyID){};
		ExpenseDocument(DataLayer::expenseDocumentCollection);
		~ExpenseDocument(){};

		std::string errorMessage = "";
		//ExpenseDocument class Accessors
		int GetID();
		std::string GetExpenseName();
		double GetCount();
		double GetSum();
		int GetMeasureID();
		int GetCurrencyID();


		//ExpenseDocument class Mutators
		void SetID(int);
		void SetExpenseName(std::string);
		void SetCount(double);
		void SetSum(double);
		void SetMeasureID(int);
		void SetCurrencyID(int);


		//Create, delete, update methods
		bool CreateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eName, double eCount, double eSum, int eMeasureID, int eCurrencyID, std::string& errorMessage);
		bool UpdateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eName, double eCount, double eSum, int eMeasureID, int eCurrencyID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetExpenseDocumentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
	
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		//bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int aDocumentID, std::string& errorMessage);
		//bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //ExpenseDocumentCLASS_H