#ifndef ACCOUNTCLASS_H
#define ACCOUNTCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Account{
	protected:
		int id = 0;
		std::string number = "";
		double startBalance = 0.0;
		double currentBalance = 0.0;
	public:
		Account();
		Account(int aID, std::string aNumber, double aStartBalance, double aCurrentBalance) :id(aID), number(aNumber), startBalance(aStartBalance),
			currentBalance(aCurrentBalance){};
		Account(DataLayer::accountsCollection);
		~Account(){};

		std::string errorMessage = "";

		//Account class Accessors
		int GetID();
		std::string GetNumber();
		double GetStartBalance();
		double GetCurrentBalance();

		//Account class Mutators
		void SetID(int);
		void SetNumber(std::string);
		void SetStartBalance(double);
		void SetCurrentBalance(double);

		// Create, delete and update Account
		bool CreateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string& errorMessage);
		bool UpdateAccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string& errorMessage);

		bool CreateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int accountID, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateLikeFilterForNumber(DataLayer::OrmasDal& ormasDal);
		bool GetAccountByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetAccountByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage);
		std::vector<int> GetChildAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string GetName(DataLayer::OrmasDal& ormasDal);
		bool AccountOperationValidation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double aValue);
		bool IsEmpty();
		bool HaveSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int accountID);
		void Clear();
		void BalanceShortInfo(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double &active, double &passive, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //ACCOUNTCLASS_H