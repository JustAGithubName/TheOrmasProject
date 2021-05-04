#ifndef CONSUMEPRODUCTLISTCLASS_H
#define CONSUMEPRODUCTLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class ConsumeProductList
	{
	protected:
		int id = 0;
		int consumeProductID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ConsumeProductList(int clID, int cpID, int pID, double clCount, double clSum, int sID, int cID) :id(clID), consumeProductID(cpID),
			productID(pID),	count(clCount), sum(clSum), statusID(sID), currencyID(cID){};
		ConsumeProductList(DataLayer::consumeProductListCollection);
		ConsumeProductList(){};
		~ConsumeProductList(){};

		int stockEmployeeID = 0;
		//ConsumeProductList class Accessors
		int GetID();
		int GetConsumeProductID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ConsumeProductList class Mutators
		void SetID(int);
		void SetConsumeProductID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByConsumeProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool CreateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int pID, double clCount, double clSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateConsumeProductList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int pID, double clCount, double clSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetConsumeProductListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, int pID, double clCount, double clSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif