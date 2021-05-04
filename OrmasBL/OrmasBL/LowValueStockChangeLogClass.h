#ifndef LOWVALUESTOCKCHANGELOGCLASS_H
#define LOWVALUESTOCKCHANGELOGCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class LowValueStockChangeLog
	{
	protected:
		int id = 0;
		int lowValueStockID = 0;
		int otherStocksID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		int warehouseID = 0;
		std::string logDate = "";
		int userID = 0;
		int operationID = 0;
	public:
		LowValueStockChangeLog(int sID, int lvsID, int osID, int sCount, double sSum, int stsID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID) :id(sID),
			lowValueStockID(lvsID), otherStocksID(osID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), warehouseID(wID), logDate(sLogDate),
			userID(lUserID), operationID(lOperationID){};
		LowValueStockChangeLog(DataLayer::lowValueStockChangeLogCollection);
		LowValueStockChangeLog(){};
		~LowValueStockChangeLog(){};

		//LowValueStockChangeLog class Accessors
		int GetID();
		int GetLowValueStockID();
		int GetOtherStocksID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetWarehouseID();
		std::string GetLogDate();
		int GetUserID();
		int GetOperationID();

		//LowValueStockChangeLog class Mutators
		void SetID(int);
		void SetLowValueStockID(int);
		void SetOtherStocksID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetWarehouseID(int);
		void SetLogDate(std::string);
		void SetUserID(int);
		void SetOperationID(int);

		//Create, delete, update methods
		bool CreateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID, std::string& errorMessage);
		bool UpdateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetLowValueStockChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetLowValueStockChangeLogByOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, std::string& errorMessage);
		bool GetLowValueStockChangeLogByOtherStocksAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, int wID, std::string& errorMessage);
		bool GetLowValueStockChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool GetLowValueStockChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetLowValueStockChangeLogByLowValueStockID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();


	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lvsID, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sLogDate, int lUserID, int lOperationID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif