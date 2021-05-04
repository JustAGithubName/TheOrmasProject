#ifndef PRODUCTIONCONSUMERAWLISTCLASS_H
#define PRODUCTIONCONSUMERAWLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class ProductionConsumeRawList
	{
	protected:
		int id = 0;
		int productionConsumeRawID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		ProductionConsumeRawList(int clID, int crID, int pID, double clCount, double clSum, int sID, int cID) :id(clID), productionConsumeRawID(crID),
			productID(pID),	count(clCount), sum(clSum), statusID(sID), currencyID(cID){};
		ProductionConsumeRawList(DataLayer::productionConsumeRawListCollection);
		ProductionConsumeRawList(){};
		~ProductionConsumeRawList(){};

		int stockEmployeeID = 0;
		//ProductionConsumeRawList class Accessors
		int GetID();
		int GetProductionConsumeRawID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//ProductionConsumeRawList class Mutators
		void SetID(int);
		void SetProductionConsumeRawID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateProductionConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProductionConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProductionConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByProductionConsumeRawID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool CreateProductionConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int pID, double clCount, double clSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateProductionConsumeRawList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int pID, double clCount, double clSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetProductionConsumeRawListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, int pID, double clCount, double clSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		double CalculateMiddleSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pcrID, int pID, std::string& errorMessage);
	};
}
#endif