#ifndef INVENTORIZATIONCLASS_H
#define INVENTORIZATIONCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Inventorization
	{
	protected:
		int id = 0;
		int employeeID = 0;
		std::string date = "";
		std::string executionDate = "";
		int stockEmployeeID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		Inventorization(int iID, int eID, std::string iDate, std::string iExecDate, int seID, double iCount, double iSum, int sID, int cID) :
			id(iID), employeeID(eID), date(iDate), executionDate(iExecDate), stockEmployeeID(seID), count(iCount), sum(iSum),
			statusID(sID), currencyID(cID){};
		Inventorization(DataLayer::inventorizationsCollection);
		Inventorization(){};
		~Inventorization(){};

		//Consume Product class Accessors
		int GetID();
		int GetEmployeeID();
		std::string GetDate();
		std::string GetExecutionDate();
		int GetStockEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//Consume Product class Mutators
		void SetID(int);
		void SetEmployeeID(int);
		void SetDate(std::string);
		void SetExecutionDate(std::string);
		void SetStockEmployeeID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string iDate, std::string iExecDate, int seID,
			double iCount, double iSum, int sID, int cID, std::string& errorMessage);
		bool UpdateInventorization(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string iDate, std::string iExecDate, int seID, 
			double iCount, double iSum, int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetInventorizationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string iDate, int seID, double iCount, double iSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //InventorizationCLASS_H