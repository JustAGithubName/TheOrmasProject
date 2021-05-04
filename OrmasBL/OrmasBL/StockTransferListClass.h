#ifndef StockTransferLISTCLASS_H
#define StockTransferLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class StockTransferList
	{
	protected:
		int id = 0;
		int stockTransferID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		StockTransferList(int rlID, int rpID, int pID, double rlCount, double rlSum, int sID, int cID) :id(rlID), stockTransferID(rpID),
			productID(pID),	count(rlCount), sum(rlSum), statusID(sID), currencyID(cID){};
		StockTransferList(DataLayer::stockTransferListCollection);
		StockTransferList(){};
		~StockTransferList(){};

		int stockEmployeeID = 0 ;
		//StockTransferList class Accessors
		int GetID();
		int GetStockTransferID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//StockTransferList class Mutators
		void SetID(int);
		void SetStockTransferID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByStockTransferID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		bool CreateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateStockTransferList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStockTransferListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int pID, double rlCount, double rlSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif