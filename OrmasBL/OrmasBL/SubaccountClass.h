#ifndef SUBACCOUNTCLASS_H
#define SUBACCOUNTCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Subaccount{
	protected:
		int id = 0;
		int parentSubaccountID = 0;
		std::string number = "";
		double startBalance = 0.0;
		double currentBalance = 0.0;
		int currencyID = 0;		
		int statusID = 0;
		std::string openedDate = "";
		std::string closedDate = "";
		std::string details = "";
	public:
		Subaccount();
		Subaccount(int aID, int paID, std::string aNumber, double aStartBalance, double aCurrentBalance, int cID, int sID, std::string aOpenedDate,
			std::string aClosedDate, std::string aDetails) :id(aID), parentSubaccountID(paID), number(aNumber), startBalance(aStartBalance),
			currentBalance(aCurrentBalance), currencyID(cID), statusID(sID), openedDate(aOpenedDate), closedDate(aClosedDate), 
			details(aDetails){};
		Subaccount(DataLayer::subaccountsCollection);
		~Subaccount(){};

		std::string errorMessage = "";

		//Subaccount class Accessors
		int GetID();
		int GetParentAccountID();
		std::string GetNumber();
		double GetStartBalance();
		double GetCurrentBalance();
		int GetCurrencyID();
		int GetStatusID();
		std::string GetOpenedDate();
		std::string GetClosedDate();
		std::string GetDetails();

		//Subaccount class Mutators
		void SetID(int);
		void SetParentAccountID(int);
		void SetNumber(std::string);
		void SetStartBalance(double);
		void SetCurrentBalance(double);
		void SetCurrencyID(int);
		void SetStatusID(int);
		void SetOpenedDate(std::string);
		void SetClosedDate(std::string);
		void SetDetails(std::string);

		// Create, delete and update Subaccount
		bool CreateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int paID, std::string aNumber, double aStartBalance, double aCurrentBalance, int cID,
			int sID, std::string aOpenedDate, std::string aClosedDate, std::string aDetails, std::string& errorMessage);
		bool UpdateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int paID, std::string aNumber, double aStartBalance, double aCurrentBalance, int cID,
			int sID, std::string aOpenedDate, std::string aClosedDate, std::string aDetails, std::string& errorMessage);

		bool CreateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int subaccountID, double aStartBalance, double aCurrentBalance,
			std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList);
		std::string GenerateNotINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList);
		bool GetSubaccountByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetSubaccountByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage);
		std::string GenerateRawNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string GetName(DataLayer::OrmasDal& ormasDal);
		std::string GetSubaccountParentNumber(DataLayer::OrmasDal& ormasDal);
		int GetSubaccountTypeNumber(DataLayer::OrmasDal& ormasDal);
		bool SubaccountOperationValidation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double aValue);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //SUBACCOUNTCLASS_H