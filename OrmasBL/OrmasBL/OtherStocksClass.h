#ifndef OTHERSTOCKSCLASS_H
#define OTHERSTOCKSCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer
{
	class OtherStocks
	{
	protected:
		int id = 0;
		int companyID = 0;
		std::string name = "";
		double volume = 0;
		int measureID = 0;
		double price = 0;
		int currencyID = 0;
		int otherStocksTypeID = 0;
	public:
		OtherStocks(int pID, int cID, std::string pName, double vol, int mID, double price, int pTypeID, int pShelfLife, int pCurrencyID, int pOt)
			:id(pID), companyID(cID), name(pName), volume(vol), measureID(mID), price(price), currencyID(pCurrencyID),
			otherStocksTypeID(pOt){};
		OtherStocks(DataLayer::otherStocksCollection);
		OtherStocks(){};
		~OtherStocks(){};

		//OtherStocks class Accessors
		int GetID();
		int GetCompanyID();
		std::string GetName();
		double GetVolume();
		int GetMeasureID();
		double GetPrice();
		int GetCurrencyID();
		int GetOtherStocksTypeID();

		//Please implement Mutators
		void SetID(int);
		void SetCompanyID(int);
		void SetName(std::string);
		void SetVolume(double);
		void SetMeasureID(int);
		void SetPrice(double);
		void SetCurrencyID(int);
		void SetOtherStocksTypeID(int);

		//Create, delete, update methods
		bool CreateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
			int curID, int othStT, std::string& errorMessage);
		bool UpdateOtherStocks(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
			int curID, int othStT, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> othSIDList);
		std::string GenerateLikeFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string searchKey);
		bool GetOtherStocksByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double oldPrice = 0.0;
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
			int curID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		//bool AddPriceData(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int othSID, double pPrice, int curID, std::string& errorMessage);
		double GetCurrentPrice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, std::string& errorMessage);
		bool RecalculateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int osID, double oldPrice, double newPrice, std::string& errorMessage);
	};
}
#endif //OtherStocksCLASS_H