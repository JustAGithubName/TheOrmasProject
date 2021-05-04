#ifndef SUBACCOUNTCHANGELOGCLASS_H
#define SUBACCOUNTCHANGELOGCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class SubaccountChangeLog{
	protected:
		int id = 0;
		int subaccountID = 0;
		double startBalance = 0.0;
		double currentBalance = 0.0;
		std::string logDate = "";
		int userID = 0;
		int operationID = 0;
	public:
		SubaccountChangeLog();
		SubaccountChangeLog(int ahID, int aID, double aStartBalance, double aCurrentBalance, std::string aLogDate,
			int sUserID, int sOperationID) :id(ahID), subaccountID(aID), startBalance(aStartBalance),
			currentBalance(aCurrentBalance), logDate(aLogDate), userID(sUserID), operationID(sOperationID){};
		SubaccountChangeLog(DataLayer::subaccountChangeLogCollection);
		~SubaccountChangeLog(){};

		std::string errorMessage = "";

		//SubaccountChangeLog class Accessors
		int GetID();
		int GetSubaccountID();
		double GetStartBalance();
		double GetCurrentBalance();
		std::string GetLogDate();
		int GetUserID();
		int GetOperationID();

		//SubaccountChangeLog class Mutators
		void SetID(int);
		void SetSubaccountID(int);
		void SetStartBalance(double);
		void SetCurrentBalance(double);
		void SetLogDate(std::string);
		void SetUserID(int);
		void SetOperationID(int);

		// Create, delete and update SubaccountChangeLog
		bool CreateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
			double saCurrentBalance, std::string saLogDate, int sUserID, int sOperationID , std::string& errorMessage);
		bool UpdateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
			double saCurrentBalance, std::string saLogDate, int sUserID, int sOperationID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(DataLayer::OrmasDal& ormasDal, std::string fromDate, std::string tillDate);
		bool GetSubaccountChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int shID, std::string& errorMessage);
		bool GetSubaccountChangeLogBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aSubaccountID, std::string& errorMessage);
		bool GetSubaccountChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetSubaccountChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
			double saCurrentBalance, std::string saLogDate, int sUserID, int sOperationID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //SUBACCOUNTChangeLogCLASS_H