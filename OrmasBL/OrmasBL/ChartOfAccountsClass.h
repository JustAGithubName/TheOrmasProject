#ifndef CHARTOFACCOUNTSCLASS_H
#define CHARTOFACCOUNTSCLASS_H

#include "OrmasDAL.h"
namespace BusinessLayer
{
	class ChartOfAccounts
	{
	protected:
		int id = 0;
		std::string number = "";
		std::string name = "";
		int accountTypeID = 0;
	public:
		ChartOfAccounts(){};
		ChartOfAccounts(int cID, std::string cNumber, std::string cName, int cAccountTypeID) :id(cID),
			number(cNumber), name(cName),  accountTypeID(cAccountTypeID){};
		ChartOfAccounts(DataLayer::chartOfAccountsCollection);
		~ChartOfAccounts(){};

		//ChartOfAccounts class Accessors
		int GetID();
		std::string GetNumber();
		std::string GetName();
		int GetAccountTypeID();
		

		//ChartOfAccounts class Mutators
		void SetID(int);
		void SetNumber(std::string);
		void SetName(std::string);
		void SetAccountTypeID(int);

		//Create, delete and update methods 
		bool CreateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string cName, int cAccountTypeID, std::string& errorMessage);
		bool UpdateChartOfAccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string cName, int cAccountTypeID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetChartOfAccountsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool GetChartOfAccountsByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cNumber, std::string cName, int cAccountTypeID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //ChartOfAccountsCLASS_H