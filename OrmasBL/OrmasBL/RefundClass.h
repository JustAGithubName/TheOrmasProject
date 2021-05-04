#ifndef RefundCLASS_H
#define RefundCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Refund{
	protected:
		int id = 0;
		std::string date = "";
		double value = 0.0;
		int userID = 0;
		int currencyID = 0;
	public:
		Refund();
		Refund(int pID, std::string pDate, double pValue, int uID, int cID) :id(pID), date(pDate), value(pValue), userID(uID),
			currencyID(cID){};
		Refund(DataLayer::refundsCollection);
		~Refund(){};

		std::string errorMessage = "";
		int loggedUserID = 0;
		//Refund class Refundors
		int GetID();
		std::string GetDate();
		double GetValue();
		int GetUserID();
		int GetCurrencyID();

		//Refund class Mutators
		void SetID(int);
		void SetUserID(int);
		void SetDate(std::string);
		void SetValue(double);
		void SetCurrencyID(int);

		// Create, delete and update Refund
		bool CreateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
			std::string& errorMessage);
		bool UpdateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
			std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetRefundByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double currentValue = 0.0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, std::string& errorMessage);
		bool Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, double previousValue, std::string& errorMessage);
		double GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool CancelRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage);
		bool CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}

#endif