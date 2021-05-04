#ifndef PAYSLIPCLASS_H
#define PAYSLIPCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Payslip{
	protected:
		int id = 0;
		std::string date = "";
		double value = 0.0;
		int salaryID = 0;
		int currencyID = 0;
	public:
		Payslip();
		Payslip(int pID, std::string pDate, double pValue, int sID, int cID) :id(pID), date(pDate), value(pValue), salaryID(sID),
			currencyID(cID){};
		Payslip(DataLayer::payslipsCollection);
		~Payslip(){};

		std::string errorMessage = "";
		//Payslip class Accessors
		int GetID();
		std::string GetDate();
		double GetValue();
		int GetSalaryID();
		int GetCurrencyID();

		//Payslip class Mutators
		void SetID(int);
		void SetSalaryID(int);
		void SetDate(std::string);
		void SetValue(double);
		void SetCurrencyID(int);

		// Create, delete and update Payslip
		bool CreatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int sID, int cID,
			std::string& errorMessage);
		bool UpdatePayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int sID, int cID,
			std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetPayslipByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double currentValue = 0.0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int sID, int cID,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, std::string& errorMessage);
		bool Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, double previousValue, std::string& errorMessage);
		double GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool CancelPayslip(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage);
		bool CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}

#endif