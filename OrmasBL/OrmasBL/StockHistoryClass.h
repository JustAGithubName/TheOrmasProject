#ifndef STOCKHISTORYCLASS_H
#define STOCKHISTORYCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class StockHistory
	{
	protected:
		int id = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		int warehouseID = 0;
		std::string historyDate = "";
	public:
		StockHistory(int sID, int pID, int sCount, double sSum, int stsID, int cID, int wID, std::string sHistoryDate) :id(sID),
			productID(pID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), warehouseID(wID), historyDate(sHistoryDate){};
		StockHistory(DataLayer::stockHistoryCollection);
		StockHistory(){};
		~StockHistory(){};

		//StockHistory class Accessors
		int GetID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetWarehouseID();
		std::string GetHistoryDate();


		//StockHistory class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetWarehouseID(int);
		void SetHistoryDate(std::string);

		//Create, delete, update methods
		bool CreateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage);
		bool UpdateStockHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string sHistoryDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStockHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetStockHistoryByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetStockHistoryByProductAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();

		
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif