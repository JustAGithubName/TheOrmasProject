#ifndef STOCKCHANGELOGCLASS_H
#define STOCKCHANGELOGCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class StockChangeLog
	{
	protected:
		int id = 0;
		int stockID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		int warehouseID = 0;
		std::string logDate = "";
		int userID = 0;
		int operationID = 0;
	public:
		StockChangeLog(int sID, int sStockID, int pID, int sCount, double sSum, int stsID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID) :id(sID),
			stockID(sStockID), productID(pID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), warehouseID(wID), logDate(sLogDate),
			userID(sUserID), operationID(sOperationID){};
		StockChangeLog(DataLayer::stockChangeLogCollection);
		StockChangeLog(){};
		~StockChangeLog(){};

		//StockChangeLog class Accessors
		int GetID();
		int GetStockID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetWarehouseID();
		std::string GetLogDate();
		int GetUserID();
		int GetOperationID();

		//StockChangeLog class Mutators
		void SetID(int);
		void SetStockID(int sStockID);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetWarehouseID(int);
		void SetLogDate(std::string);
		void SetUserID(int);
		void SetOperationID(int);

		//Create, delete, update methods
		bool CreateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,int sStockID, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID, std::string& errorMessage);
		bool UpdateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sStockID, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStockChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetStockChangeLogByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetStockChangeLogByProductAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool GetStockChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetStockChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool GetStockChangeLogByStockID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sStockID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();


	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sStockID, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sLogDate, int sUserID, int sOperationID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif