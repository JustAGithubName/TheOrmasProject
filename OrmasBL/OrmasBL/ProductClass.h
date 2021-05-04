#ifndef PRODUCTCLASS_H
#define PRODUCTCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer
{
	class Product
	{
	protected:
		int id = 0;
		int companyID = 0;
		std::string name = "";
		double volume = 0;
		int measureID = 0;
		double price = 0;
		int productTypeID = 0;
		int shelfLife = 0;
		int currencyID = 0;
	public:
		Product(int pID, int cID, std::string pName, double vol, int mID, double price, int pTypeID, int pShelfLife, int pCurrencyID)
			:id(pID), companyID(cID), name(pName), volume(vol), measureID(mID), price(price), productTypeID(pTypeID), 
			shelfLife(pShelfLife), currencyID(pCurrencyID){};
		Product(DataLayer::productsCollection);
		Product(){};
		~Product(){};
		
		//Product class Accessors
		int GetID();
		int GetCompanyID();
		std::string GetName();
		double GetVolume();
		int GetMeasureID();
		double GetPrice();
		int GetProductTypeID();
		int GetShelfLife();
		int GetCurrencyID();

		//Please implement Mutators
		void SetID(int);
		void SetCompanyID(int);
		void SetName(std::string);
		void SetVolume(double);
		void SetMeasureID(int);
		void SetPrice(double);
		void SetProductTypeID(int);
		void SetShelfLife(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
			int pTypeID, int shelfLife, int curID, std::string& errorMessage);
		bool UpdateProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
			int pTypeID, int shelfLife, int curID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> prodIDList);
		std::string GenerateLikeFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string searchKey);
		bool GetProductByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double oldPrice = 0.0;
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string pName, double vol, int mID, double price,
			 int curID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool AddPriceData(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double pPrice, int curID, std::string& errorMessage);
		double GetCurrentPrice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool UpdateSpecifications(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage);
		bool RecalculateStock(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage);
	};
}
#endif //PRODUCTCLASS_H