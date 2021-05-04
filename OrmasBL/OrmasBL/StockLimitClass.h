#ifndef STOCKLIMITCLASS_H
#define STOCKLIMITCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class StockLimit
	{
	protected:
		int id = 0;
		int stockID = 0;
		int productID = 0;
		double minValue = 0;
		double maxValue = 0;
	public:
		StockLimit(int stlID, int stID, int pID, double sMin, double sMax) :id(stlID), stockID(stID),
			productID(pID), minValue(sMin), maxValue(sMax){};
		StockLimit(DataLayer::stockLimitCollection);
		StockLimit(){};
		~StockLimit(){};

		//StockLimit class Accessors
		int GetID();
		int GetStockID();
		int GetProductID();
		double GetMinValue();
		double GetMaxValue();
		
		//StockLimit class Mutators
		void SetID(int);
		void SetStockID(int);
		void SetProductID(int);
		void SetMinValue(double);
		void SetMaxValue(double);

		//Create, delete, update methods
		bool CreateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,int stID, int pID, double sMin, double sMax, std::string& errorMessage);
		bool UpdateStockLimit(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stID, int pID, double sMin, double sMax, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStockLimitByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetStockLimitByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetStockLimitByStockID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();

	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int sID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif