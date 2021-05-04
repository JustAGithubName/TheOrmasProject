#ifndef PRODUCTIONLISTCLASS_H
#define PRODUCTIONLISTCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class ProductionList
	{
	protected:
		int id = 0;
		int productionID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ProductionList(int plID, int prID, int pID, double plCount, double plSum, int sID, int cID) :id(plID), productionID(prID), productID(pID),
			count(plCount), sum(plSum), statusID(sID), currencyID(cID){};
		ProductionList(DataLayer::productionListCollection);
		ProductionList(){};
		~ProductionList(){};
		std::map<int, double> GetProductCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);

		//ProductionList class Accessors
		int GetID();
		int GetProductionID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ProductionList class Mutators
		void SetID(int);
		void SetProductionID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByProductionID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool CreateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int pID, double plCount, double plSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateProductionList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int pID, double plCount, double plSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForEnum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> vecProdnID);
		bool GetProductionListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int pID, double plCount, double plSum,
			 int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		
	};
}
#endif