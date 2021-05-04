#ifndef WRITEOFFRAWCLASS_H
#define WRITEOFFRAWCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class WriteOffRaw
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
		WriteOffRaw(int wID, int eID, std::string wDate, std::string wExexDate, int seID, double wCount, double wSum, int sID, int cID) :
			id(wID), employeeID(eID), date(wDate), executionDate(wExexDate), stockEmployeeID(seID), count(wCount), sum(wSum),
			statusID(sID), currencyID(cID){};
		WriteOffRaw(DataLayer::writeOffRawsCollection);
		WriteOffRaw(){};
		~WriteOffRaw(){};

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
		bool CreateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string wDate, std::string wExexDate, int seID,
			double wCount, double wSum, int sID, int cID, std::string& errorMessage);
		bool UpdateWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string wDate, std::string wExexDate, int seID,
			double wCount, double wSum, int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string formDate, std::string toDate);
		bool GetWriteOffRawByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double prevSum = 0;
		double prevCount = 0;
		int previousStatusID = 0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string wDate, int seID, double wCount, double wSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int empID, std::string& errorMessage);
		bool ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int empID, std::string& errorMessage);
		bool ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		double GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		double GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		std::map<int, double> GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal);
	};
}
#endif //WRITEOFFRAWCLASS_H