#ifndef ACCOUNTABLETRANSACTIONCLASS_H
#define ACCOUNTABLETRANSACTIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class AccountableTransaction{
	protected:
		int id = 0;
		double residualValue = 0.0;
		double totalValue = 0.0;
		double spentValue = 0.0;
		double differenceValue = 0.0;
		int accountableDocumentID = 0;
	public:
		AccountableTransaction();
		AccountableTransaction(int tID, double resValue, double totValue, double speValue, double diffValue, int aID) :id(tID), residualValue(totValue),
			totalValue(totValue), spentValue(speValue), differenceValue(differenceValue), accountableDocumentID(aID){};
		AccountableTransaction(DataLayer::accountableTransactionCollection);
		~AccountableTransaction(){};

		std::string errorMessage = "";

		//AccountableTransaction class Accessors
		int GetID();
		double GetResidualValue();
		double GetTotalValue();
		double GetSpentValue();
		double GetDifferenceValue();
		int GeAccountableDocumentID();

		//AccountableTransaction class Mutators
		void SetID(int);
		void SetResidualValue(double);
		void SetTotalValue(double);
		void SetSpentValue(double);
		void SetDifferenceValue(double);
		void SetAccountableDocumentID(int);

		// Create, delete and update AccountableTransaction
		bool CreateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableTransactionByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double resValue, double totValue, double speValue, double diffValue, int aID, std::string& errorMessage);
		bool UpdateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double resValue, double totValue, double speValue, double diffValue, int aID, std::string& errorMessage);
		bool IncCascadeTransactionUpdate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int docID, double value, std::string& errorMessage);
		bool DecCascadeTransactionUpdate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int docID, double value, std::string& errorMessage);
		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFieldBiggerThenFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableTransactionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int atID, std::string& errorMessage);
		bool GetAccountableTransactionByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double resValue, double totValue, double speValue, double diffValue, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //AccountableTransactionCLASS_H