#ifndef STOCKCLASS_H
#define STOCKCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Stock
	{
	protected:
		int id = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		int warehouseID = 0;
	public:
		Stock(int sID, int pID, double sCount, double sSum, int stsID, int cID, int wID) :id(sID),
			productID(pID),	count(sCount), sum(sSum), statusID(stsID), currencyID(cID), warehouseID(wID){};
		Stock(DataLayer::stockCollection);
		Stock(){};
		~Stock(){};

		//Stock class Accessors
		int GetID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetWarehouseID();


		//Stock class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetWarehouseID(int);

		//Create, delete, update methods
		bool CreateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string& errorMessage);
		bool UpdateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string& errorMessage);

		bool CreateStockChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockID, int pID, double sCount, double sSum,
			int sID, int cID, int wID, std::string& errorMessage);
		
		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStockByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetStockByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetStockByProductAndWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		std::vector<int> GetAllProductIDByWarehouseID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();

		bool ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::string& errorMessage);
		bool ChangingByConsumeProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::string& errorMessage);
		bool ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::string& errorMessage);
		bool ChangingByConsumeRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::string& errorMessage);
		bool ChangingByConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByConsumeRawAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int debWerID, std::string& errorMessage);
		bool ChangingByConsumeRawAtSecondStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int debWerID, std::string& errorMessage);
		bool ChangingByConsumeRawAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int debWerID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByProdConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int stockEmpID, std::string& errorMessage);
		bool ChangingByProdConsumeRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int stockEmpID, std::string& errorMessage);
		bool ChangingByProdConsumeRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage);
		bool ChangingByOrderRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage);
		bool ChangingByOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByOrderRawForMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage);
		bool ChangingByOrderRawReverseForMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::string& errorMessage);
		bool ChangingByOrderRawForMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int orID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int empID, int stockEmpID, std::string& errorMessage);
		bool ChangingByReceiptProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int empID, int stockEmpID, std::string& errorMessage);
		bool ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByReceiptProductAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::string& errorMessage);
		bool ChangingByReceiptProductAtSecondStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::string& errorMessage);
		bool ChangingByReceiptProductAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int empID, int stockEmpID, std::string& errorMessage);
		bool ChangingByStockTransferReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int empID, int stockEmpID, std::string& errorMessage);
		bool ChangingByStockTransfer(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rrID, int empID, int stockEmpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByStockTransferAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::string& errorMessage);
		bool ChangingByStockTransferAtSecondStockReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::string& errorMessage);
		bool ChangingByStockTransferAtSecondStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int credWerID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByReturnProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int cID, int empID, std::string& errorMessage);
		bool ChangingByReturnProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int cID, int empID, std::string& errorMessage);
		bool ChangingByReturnProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int cID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wpID, int empID, std::string& errorMessage);
		bool ChangingByWriteOffReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wpID, int empID, std::string& errorMessage);
		bool ChangingByWriteOff(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wpID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wrID, int empID, std::string& errorMessage);
		bool ChangingByWriteOffRawReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wrID, int empID, std::string& errorMessage);
		bool ChangingByWriteOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wrID, int empID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int warID, std::string& errorMessage);
		bool ChangingByProduction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int warID, std::map<int, double> pProdCountMap, std::string& errorMessage);
		bool RecalculateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int operationID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage);
		bool CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, int debAccID, double currentSum, int credAccID, std::string& errorMessage);
		bool CreateCorrectongEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);

		bool GetSubIDAndWerhIDFromConProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockEmpID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromConRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int stockEmpID, int& debWerID, int& credWerID, int& debSaccID, int& credSaccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromOrderRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromRcpRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int stockEmpID, int& debWerID, int& credWerID, int& debSaccID, int& credSaccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromRcpProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int stockEmpID, int& debWerID, int& credWerID, int& debSaccID, int& credSaccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromRtrnProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromWOffProd(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromWOffRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int empID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool GetSubIDAndWerhIDFromProdnConRaw(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stockEmpID, int& warehouseID, int& subAccID, std::string& errorMessage);
		bool IsStockValid(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
	};
}
#endif