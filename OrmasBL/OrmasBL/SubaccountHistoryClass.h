#ifndef SUBACCOUNTHISTORYCLASS_H
#define SUBACCOUNTHISTORYCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class SubaccountHistory{
	protected:
		int id = 0;
		int subaccountID = 0;
		double startBalance = 0.0;
		double currentBalance = 0.0;
		std::string fromDate = "";
		std::string tillDate = "";
	public:
		SubaccountHistory();
		SubaccountHistory(int ahID, int aID, double aStartBalance, double aCurrentBalance, std::string aFromDate,
			std::string aTillDate) :id(ahID), subaccountID(aID), startBalance(aStartBalance),
			currentBalance(aCurrentBalance), fromDate(aFromDate), tillDate(aTillDate){};
		SubaccountHistory(DataLayer::subaccountHistoryCollection);
		~SubaccountHistory(){};

		std::string errorMessage = "";

		//SubaccountHistory class Accessors
		int GetID();
		int GetSubaccountID();
		double GetStartBalance();
		double GetCurrentBalance();
		std::string GetFromDate();
		std::string GetTillDate();

		//SubaccountHistory class Mutators
		void SetID(int);
		void SetSubaccountID(int);
		void SetStartBalance(double);
		void SetCurrentBalance(double);
		void SetFromDate(std::string);
		void SetTillDate(std::string);

		// Create, delete and update SubaccountHistory
		bool CreateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
			double saCurrentBalance, std::string saFromDate, std::string saTillDate, std::string& errorMessage);
		bool UpdateSubaccountHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, double saStartBalance,
			double saCurrentBalance, std::string saFromDate, std::string saTillDate, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSubaccountHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int shID, std::string& errorMessage);
		bool GetSubaccountHistoryBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aSubaccountID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string aFromDate, std::string aTillDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //SUBACCOUNTHISTORYCLASS_H