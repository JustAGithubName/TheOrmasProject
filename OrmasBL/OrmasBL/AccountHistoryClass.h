#ifndef ACCOUNTHISTORYCLASS_H
#define ACCOUNTHISTORYCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class AccountHistory{
	protected:
		int id = 0;
		int accountID = 0;
		std::string number = "";
		double startBalance = 0.0;
		double currentBalance = 0.0;
		std::string fromDate = "";
		std::string tillDate = "";
	public:
		AccountHistory();
		AccountHistory(int ahID, int aID, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string aFromDate,
			std::string aTillDate) :id(ahID), accountID(aID), number(aNumber), startBalance(aStartBalance),
			currentBalance(aCurrentBalance), fromDate(aFromDate), tillDate(aTillDate){};
		AccountHistory(DataLayer::accountHistoryCollection);
		~AccountHistory(){};

		std::string errorMessage = "";

		//AccountHistory class Accessors
		int GetID();
		int GetAccountID();
		std::string GetNumber();
		double GetStartBalance();
		double GetCurrentBalance();
		std::string GetFromDate();
		std::string GetTillDate();

		//AccountHistory class Mutators
		void SetID(int);
		void SetAccountID(int);
		void SetNumber(std::string);
		void SetStartBalance(double);
		void SetCurrentBalance(double);
		void SetFromDate(std::string);
		void SetTillDate(std::string);

		// Create, delete and update AccountHistory
		bool CreateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance, 
			double aCurrentBalance, std::string aFromDate, std::string aTillDate, std::string& errorMessage);
		bool UpdateAccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
			double aCurrentBalance, std::string aFromDate, std::string aTillDate, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ahID, std::string& errorMessage);
		bool GetAccountHistoryByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aAccountID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aFromDate, std::string aTillDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //ACCOUNTHISTORYCLASS_H