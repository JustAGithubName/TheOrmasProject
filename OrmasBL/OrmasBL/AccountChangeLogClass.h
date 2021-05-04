#ifndef ACCOUNTCHANGELOGCLASS_H
#define ACCOUNTCHANGELOGCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class AccountChangeLog{
	protected:
		int id = 0;
		int accountID = 0;
		std::string number = "";
		double startBalance = 0.0;
		double currentBalance = 0.0;
		std::string logDate = "";
		int userID = 0;
		int operationID = 0;
	public:
		AccountChangeLog();
		AccountChangeLog(int ahID, int aID, std::string aNumber, double aStartBalance, double aCurrentBalance, std::string aLogDate,
			int aUserID, int aOperationID) :id(ahID), accountID(aID), number(aNumber), startBalance(aStartBalance),
			currentBalance(aCurrentBalance), logDate(aLogDate), userID(aUserID), operationID(aOperationID){};
		AccountChangeLog(DataLayer::accountChangeLogCollection);
		~AccountChangeLog(){};

		std::string errorMessage = "";

		//AccountChangeLog class Accessors
		int GetID();
		int GetAccountID();
		std::string GetNumber();
		double GetStartBalance();
		double GetCurrentBalance();
		std::string GetLogDate();
		int GetUserID();
		int GetOperationID();

		//AccountChangeLog class Mutators
		void SetID(int);
		void SetAccountID(int);
		void SetNumber(std::string);
		void SetStartBalance(double);
		void SetCurrentBalance(double);
		void SetLogDate(std::string);
		void SetUserID(int);
		void SetOperationID(int);

		// Create, delete and update AccountChangeLog
		bool CreateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
			double aCurrentBalance, std::string aLogDate, int aUserID, int aOperationID, std::string& errorMessage);
		bool UpdateAccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
			double aCurrentBalance, std::string aLogDate, int aUserID, int aOperationID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ahID, std::string& errorMessage);
		bool GetAccountChangeLogByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aAccountID, std::string& errorMessage);
		bool GetAccountChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aUserID, std::string& errorMessage);
		bool GetAccountChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aOperationID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string aNumber, double aStartBalance,
			double aCurrentBalance, std::string aLogDate, int aUserID, int aOperationID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //AccountChangeLogCLASS_H