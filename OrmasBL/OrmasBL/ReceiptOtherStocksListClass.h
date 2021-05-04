#ifndef RECEIPTOTHERSTOCKSLISTCLASS_H
#define RECEIPTOTHERSTOCKSLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class ReceiptOtherStocksList
	{
	protected:
		int id = 0;
		int receiptOtherStocksID = 0;
		int otherStocksID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ReceiptOtherStocksList(int olID, int oID, int osID, double olCount, double olSum, int sID, int cID) :id(olID), receiptOtherStocksID(oID),
			otherStocksID(osID), count(olCount), sum(olSum), statusID(sID), currencyID(cID){};
		ReceiptOtherStocksList(DataLayer::receiptOtherStocksListCollection);
		ReceiptOtherStocksList(){};
		~ReceiptOtherStocksList(){};

		int employeeID = 0;
		//ReceiptOtherStocksList class Accessors
		int GetID();
		int GetReceiptOtherStocksID();
		int GetOtherStocksID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ReceiptOtherStocksList class Mutators
		void SetID(int);
		void SetReceiptOtherStocksID(int);
		void SetOtherStocksID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByReceiptOtherStocksID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool CreateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateReceiptOtherStocksList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetReceiptOtherStocksListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int pID, double olCount, double olSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
		int GetSubaccountIDForEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif