#ifndef RECEIPTPRODUCTLISTCLASS_H
#define RECEIPTPRODUCTLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class ReceiptProductList
	{
	protected:
		int id = 0;
		int receiptProductID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ReceiptProductList(int rlID, int rID, int pID, double rlCount, double rlSum, int sID, int cID) :id(rlID), receiptProductID(rID),
			productID(pID),	count(rlCount), sum(rlSum), statusID(sID), currencyID(cID){};
		ReceiptProductList(DataLayer::receiptProductListCollection);
		ReceiptProductList(){};
		~ReceiptProductList(){};

		int stockEmployeeID = 0;
		//ReceiptProductList class Accessors
		int GetID();
		int GetReceiptProductID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ReceiptProductList class Mutators
		void SetID(int);
		void SetReceiptProductID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByReceiptProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, std::string& errorMessage);
		bool CreateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int pID, double rlCount, double rlSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateReceiptProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int pID, double rlCount, double rlSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetReceiptProductListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rpID, int pID, double rlCount, double rlSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //RECEIPTPRODUCTLISTCLASS_H