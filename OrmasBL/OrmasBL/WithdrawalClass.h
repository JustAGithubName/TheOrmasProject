#ifndef WITHDRAWALCLASS_H
#define WITHDRAWALCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Withdrawal{
	protected:
		int id = 0;
		std::string date = "";
		double value = 0.0;
		int userID = 0;
		int subaccountID = 0;
		std::string target = "";
		int currencyID = 0;
		int statusID = 0;
		int accountID = 0;
		std::string who = "";
		int cashboxAccountID = 0;
	public:
		Withdrawal();
		Withdrawal(int pID, std::string pDate, double pValue, int uID, int sID, std::string wTarget, int cID, int stsID, int aID, std::string wWho, int cashboxAccID) :id(pID), 
			date(pDate), value(pValue), userID(uID), subaccountID(sID), target(wTarget), currencyID(cID), statusID(stsID), accountID(aID),
			who(wWho), cashboxAccountID(cashboxAccID){};
		Withdrawal(DataLayer::withdrawalsCollection);
		~Withdrawal(){};

		std::string errorMessage = "";
		int loggedUserID = 0;
		//Withdrawal class Withdrawalors
		int GetID();
		std::string GetDate();
		double GetValue();
		int GetUserID();
		int GetSubaccountID();
		std::string GetTarget();
		int GetCurrencyID();
		int GetStatusID();
		int GetAccountID();
		std::string GetWho();
		int GetCashboxAccountID();

		//Withdrawal class Mutators
		void SetID(int);
		void SetUserID(int);
		void SetSubaccountID(int);
		void SetDate(std::string);
		void SetTarget(std::string);
		void SetValue(double);
		void SetCurrencyID(int);
		void SetStatusID(int);
		void SetAccountID(int);
		void SetWho(std::string);
		void SetCashboxAccountID(int);
		// Create, delete and update Withdrawal
		bool CreateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wDate, double wValue, int uID, int sID, std::string wTaeget,
			int cID, int stsID, int aID, std::string wWho,  int cashboxAccID, std::string& errorMessage);
		bool UpdateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wDate, double wValue, int uID, int sID, std::string wTaeget,
			int cID, int stsID, int aID,std::string wWho, int cashboxAccID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterFieldBiggerThen(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string formDate, std::string toDate);
		bool GetWithdrawalByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double currentValue = 0.0;
		int previousStatusID = 0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wDate, double wValue, int uID, int cID, int aID,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cashboxAccID, std::string& errorMessage);
		bool Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cashboxAccID, double previousValue, std::string& errorMessage);
		bool Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, std::string& errorMessage);
		bool Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, double previousValue, std::string& errorMessage);
		double GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool CancelWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cashboxAccID, std::string& errorMessage);
		bool CancelWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage);
		bool CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}

#endif
