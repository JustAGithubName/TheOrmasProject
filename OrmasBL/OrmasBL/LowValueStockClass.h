#ifndef LOWVALUESTOCKCLASS_H
#define LOWVALUESTOCKCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class LowValueStock
	{
	protected:
		int id = 0;
		int otherStocksID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		int warehouseID = 0;
	public:
		LowValueStock(int sID, int osID, int sCount, double sSum, int stsID, int cID, int wID) :id(sID),
			otherStocksID(osID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), warehouseID(wID){};
		LowValueStock(DataLayer::lowValueStockCollection);
		LowValueStock(){};
		~LowValueStock(){};

		//LowValueStock class Accessors
		int GetID();
		int GetOtherStocksID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetWarehouseID();


		//LowValueStock class Mutators
		void SetID(int);
		void SetOtherStocksID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetWarehouseID(int);

		//Create, delete, update methods
		bool CreateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string& errorMessage);
		bool UpdateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string& errorMessage);

		bool CreateLowValueStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int losID, int osID, double sCount, double sSum,
			int sID, int cID, int wID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetLowValueStockByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetLowValueStockByOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, std::string& errorMessage);
		bool GetLowValueStockByOtherStocksAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, int wID, std::string& errorMessage);
		std::vector<int> GetAllOtherStocksIDByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();

		bool ChangingByConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int lowValueStockEmpID, std::string& errorMessage);
		bool ChangingByConsumeOtherStocksReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int lowValueStockEmpID, std::string& errorMessage);
		bool ChangingByConsumeOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int lowValueStockEmpID, std::map<int, double> pOtherStockCountMap, double pSum, std::string& errorMessage);
		bool ChangingByReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage);
		bool ChangingByReceiptOtherStocksReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage);
		bool ChangingByReceiptOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::map<int, double> pOtherStockCountMap, double pSum, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage);
		bool CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, int debAccID, double currentSum, int credAccID, std::string& errorMessage);
		bool CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage);
		bool RecalculateLowValueStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);

		bool GetSubIDAndWerhIDFromConOthSt(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lowValueStockEmpID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromRcpOthSt(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage);
	};
}
#endif