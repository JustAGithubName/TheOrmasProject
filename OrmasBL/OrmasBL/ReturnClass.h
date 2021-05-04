#ifndef RETURNCLASS_H
#define RETURNCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Return
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
		Return(int rID, int clID, std::string rDate, std::string rExecDate, int eID, double oCount, double oSum, int sID, int cID) :
			id(rID), clientID(clID), date(rDate), executionDate(rExecDate), employeeID(eID), count(oCount), sum(oSum), statusID(sID),
			currencyID(cID){};
		Return(DataLayer::returnsCollection);
		Return(){};
		~Return(){};
		
		int warehouseID = 0;

		//Return class Accessors
		int GetID();
		int GetClientID();
		std::string GetDate();
		std::string GetExecutionDate();
		int GetEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		
		//Please implement Mutators
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
		bool CreateReturn(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateReturn(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteReturn(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateReturn(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string rDate, std::string rExecDate, int eID, double rCount,
			double rSum, int sID, int cID, std::string& errorMessage);
		bool UpdateReturn(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string rDate, std::string rExecDate, int eID, double rCount,
			double rSum, int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string formDate, std::string toDate);
		bool GetReturnByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double previousSum = 0.0;
		double previousCount = 0;
		int previousStatusID = 0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int clID, std::string oDate, double oCount, double oSum,
			 int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int cID, int wID, std::string& errorMessage);
		bool ChangesAtStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int cID, int wID, std::string& errorMessage);
		bool ChangesAtStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int cID, int wID, std::map<int, double> pProdCountMap, double rSum, std::string& errorMessage);
		double GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		double GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		std::map<int, double> GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool CheckDocumentCorrectness(DataLayer::OrmasDal& ormasDal);
	};
}
#endif //RETURNCLASS_H