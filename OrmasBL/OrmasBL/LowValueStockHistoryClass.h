#ifndef LOWVALUESTOCKHISTORYCLASS_H
#define LOWVALUESTOCKHISTORYCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class LowValueStockHistory
	{
	protected:
		int id = 0;
		int otherStocksID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		int warehouseID = 0;
		std::string historyDate = "";
	public:
		LowValueStockHistory(int sID, int osID, int sCount, double sSum, int stsID, int cID, int wID, std::string sHistoryDate) :id(sID),
			otherStocksID(osID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), warehouseID(wID), historyDate(sHistoryDate){};
		LowValueStockHistory(DataLayer::lowValueStockHistoryCollection);
		LowValueStockHistory(){};
		~LowValueStockHistory(){};

		//LowValueStockHistory class Accessors
		int GetID();
		int GetOtherStocksID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetWarehouseID();
		std::string GetHistoryDate();


		//LowValueStockHistory class Mutators
		void SetID(int);
		void SetOtherStocksID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetWarehouseID(int);
		void SetHistoryDate(std::string);

		//Create, delete, update methods
		bool CreateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage);
		bool UpdateLowValueStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetLowValueStockHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetLowValueStockHistoryByOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, std::string& errorMessage);
		bool GetLowValueStockHistoryByOtherStocksAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();


	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, int wID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif