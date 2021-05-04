#ifndef BALANCEPAYMENTRELATIONCLASS_H
#define BALANCEPAYMENTRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class BalancePaymentRelation
	{
	protected:
		int id = 0;
		int balanceID = 0;
		int paymentID = 0;
	public:
		BalancePaymentRelation();
		BalancePaymentRelation(int bpID, int bID, int pID) :id(bpID), balanceID(bID), paymentID(pID){};
		BalancePaymentRelation(DataLayer::balancePaymentCollection);
		~BalancePaymentRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetBalanceID();
		int GetPaymentID();

		//Access class Mutators
		void SetID(int);
		void SetBalanceID(int);
		void SetPaymentID(int);

		// Create, delete and update Access
		bool CreateBalancePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteBalancePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateBalancePaymentRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage);
		

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::vector<int> GetAllPaymentByBalanceID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		std::vector<int> GetAllBalanceByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif