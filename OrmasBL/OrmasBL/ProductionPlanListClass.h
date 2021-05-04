#ifndef PRODUCTIONPLANLISTCLASS_H
#define PRODUCTIONPLANLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class ProductionPlanList
	{
	protected:
		int id = 0;
		int productionPlanID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ProductionPlanList(int pplID, int ppID, int pID, double pplCount, double pplSum, int sID, int cID) :id(pplID),
			productionPlanID(ppID), productID(pID), count(pplCount), sum(pplSum), statusID(sID), currencyID(cID){};
		ProductionPlanList(DataLayer::productionPlanListCollection);
		ProductionPlanList(){};
		~ProductionPlanList(){};

		//ProductionPlanList class Accessors
		int GetID();
		int GetProductionPlanID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ProductionPlanList class Mutators
		void SetID(int);
		void SetProductionPlanID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByProductionPlanID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool CreateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, int pID, double pplCount, double pplSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateProductionPlanList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, int pID, double pplCount, double pplSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetProductionPlanListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int ppID, int pID, double pplCount, double pplSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif