#ifndef WRITEOFFCLASS_H
#define WRITEOFFCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class WriteOff
	{
	protected:
		int id = 0;
		int clientID = 0;
		std::string date = "";
		std::string executionDate = "";
		int employeeID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		WriteOff(int wID, int clID, std::string wDate, std::string wExecDate, int eID, double wCount, double wSum, int sID, int cID) :id(wID),
			clientID(clID), date(wDate), executionDate(wExecDate), employeeID(eID), count(wCount), sum(wSum), statusID(sID), currencyID(cID){};
		WriteOff(DataLayer::writeOffsCollection);
		WriteOff(){};
		~WriteOff(){};

		//Order class Accessors
		int GetID();
		int GetClientID();
		std::string GetDate();
		std::string GetExecutionDate();
		int GetEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//Order class Mutators
		void SetID(int);
		void SetClientID(int);
		void SetDate(std::string);
		void SetExecutionDate(std::string);
		void SetEmployeeID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string wDate, std::string wExecDate, int eID, double wCount, double wSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string wDate, std::string wExecDate, int eID, double wCount, double wSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string formDate, std::string toDate);
		bool GetWriteOffByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double prevSum = 0;
		double prevCount = 0;
		int previousStatusID = 0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string wDate, double wCount, double wSum,
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
#endif //WRITEOFFCLASS_H