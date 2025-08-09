#ifndef NETCOSTHISTORYCLASS_H
#define NETCOSTHISTORYCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class NetCostHistory{
	protected:
		int id = 0;
		std::string date = "";
		double value = 0.0;
		int currencyID = 0;
		int productID = 0;
		bool isOutdated = true;
		std::string historyDate = "";
	public:
		NetCostHistory();
		NetCostHistory(int pID, std::string pDate, double pValue, int cID, int prID, bool pIsOutdated, std::string hDate) :id(pID), date(pDate), value(pValue),
			currencyID(cID), productID(prID), isOutdated(pIsOutdated), historyDate(hDate){};
		NetCostHistory(DataLayer::netCostHistoryCollection);
		~NetCostHistory(){};

		std::string errorMessage = "";
		//NetCostHistory class NetCostHistoryors
		int GetID();
		std::string GetDate();
		double GetValue();
		int GetCurrencyID();
		int GetProductID();
		bool GetIsOutdated();
		std::string GetHistoryDate();

		//NetCostHistory class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetValue(double);
		void SetCurrencyID(int);
		void SetProductID(int);
		void SetIsOutdated(bool);
		void SetHistoryDate(std::string);

		// Create, delete and update NetCostHistory
		bool CreateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID,
			bool nIsOutdated, std::string hDate, std::string& errorMessage);
		bool UpdateNetCostHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID,
			bool nIsOutdated, std::string hDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetNetCostHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, std::string& errorMessage);
		bool GetNetCostHistoryByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string nDate, double nValue, int cID, int prID, std::string hDate,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //NetCostHistoryCLASS_H