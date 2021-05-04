#ifndef TRANSPORTHISTORYCLASS_H
#define TRANSPORTHISTORYCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class TransportHistory
	{
	protected:
		int id = 0;
		int transportID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		std::string fromDate = "";
		std::string tillDate = "";
	public:
		TransportHistory(int thID, int tID, int pID, int sCount, double sSum, int stsID, int cID, std::string sFromDate, std::string sTillDate) :id(thID),
			transportID(tID), productID(pID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), fromDate(sFromDate),
			tillDate(sTillDate){};
		TransportHistory(DataLayer::transportHistoryCollection);
		TransportHistory(){};
		~TransportHistory(){};

		//TransportHistory class Accessors
		int GetID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetTransportID();
		std::string GetFromDate();
		std::string GetTillDate();


		//TransportHistory class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetTransportID(int);
		void SetFromDate(std::string);
		void SetTillDate(std::string);

		//Create, delete, update methods
		bool CreateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
			int sID, int cID,  std::string sFromDate, std::string sTillDate, std::string& errorMessage);
		bool UpdateTransportHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
			int sID, int cID, std::string sFromDate, std::string sTillDate, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetTransportHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetTransportHistoryByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetTransportHistoryByProductAndtransportID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();


	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif