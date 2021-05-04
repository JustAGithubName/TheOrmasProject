#ifndef PRODUCTIONPLANCLASS_H
#define PRODUCTIONPLANCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class ProductionPlan
	{
	protected:
		int id = 0;
		std::string date = "";
		int employeeID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ProductionPlan(int pID, std::string pDate, int eID, double pCount, double pSum, int sID, int cID) :
			id(pID), date(pDate), employeeID(eID), count(pCount), sum(pSum), statusID(sID), currencyID(cID){};
		ProductionPlan(DataLayer::productionPlanCollection);
		ProductionPlan(){};
		~ProductionPlan(){};

		//ProductionPlan class Accessors
		int GetID();
		std::string GetDate();
		int GetEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ProductionPlan class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetEmployeeID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, int eID, double oCount,
			double oSum, int sID, int cID, std::string& errorMessage);
		bool UpdateProductionPlan(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, int eID, double oCount,
			double oSum, int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetProductionPlanByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string oDate, double oCount, double oSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //PRODUCTIONPLANCLASS_H