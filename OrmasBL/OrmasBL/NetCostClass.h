#ifndef NETCOSTCLASS_H
#define NETCOSTCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class NetCost{
	protected:
		int id = 0;
		std::string date = "";
		double value = 0.0;
		int currencyID = 0;
		int productID = 0;
		bool isOutdated = true;
	public:
		NetCost();
		NetCost(int pID, std::string pDate, double pValue, int cID, int prID, bool pIsOutdated) :id(pID), date(pDate), value(pValue),
			currencyID(cID), productID(prID), isOutdated(pIsOutdated){};
		NetCost(DataLayer::netCostCollection);
		~NetCost(){};

		std::string errorMessage = "";
		//NetCost class NetCostors
		int GetID();
		std::string GetDate();
		double GetValue();
		int GetCurrencyID();
		int GetProductID();
		bool GetIsOutdated();

		//NetCost class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetValue(double);
		void SetCurrencyID(int);
		void SetProductID(int);
		void SetIsOutdated(bool);

		// Create, delete and update NetCost
		bool CreateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID,
			bool nIsOutdated, std::string& errorMessage);
		bool UpdateNetCost(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID,
			bool nIsOutdated, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetNetCostByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, std::string& errorMessage);
		bool GetNetCostByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //NETCOSTCLASS_H