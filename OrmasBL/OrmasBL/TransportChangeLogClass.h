#ifndef TRANSPORTCHANGELOGCLASS_H
#define TRANSPORTCHANGELOGCLASS_H
#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class TransportChangeLog
	{
	protected:
		int id = 0;
		int transportID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
		std::string logDate = "";
		int userID = 0;
		int operationID = 0;
	public:
		TransportChangeLog(int thID, int tID, int pID, int sCount, double sSum, int stsID, int cID, int wID, std::string tLogDate, int tUserID, int tOperationID) :id(thID),
			transportID(tID), productID(pID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID), logDate(tLogDate),
			userID(tUserID), operationID(tOperationID){};
		TransportChangeLog(DataLayer::transportChangeLogCollection);
		TransportChangeLog(){};
		~TransportChangeLog(){};

		//TransportChangeLog class Accessors
		int GetID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();
		int GetTransportID();
		std::string GetLogDate();
		int GetUserID();
		int GetOperationID();


		//TransportChangeLog class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);
		void SetTransportID(int);
		void SetLogDate(std::string);
		void SetUserID(int);
		void SetOperationID(int);

		//Create, delete, update methods
		bool CreateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
			int sID, int cID,  std::string sLogDate,int tUserID, int tOperationID, std::string& errorMessage);
		bool UpdateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
			int sID, int cID, std::string sLogDate, int tUserID, int tOperationID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForDateLess(DataLayer::OrmasDal& ormasDal);
		std::string GenerateFilterForPeriod(DataLayer::OrmasDal& ormasDal, std::string fromDate, std::string tillDate);
		bool GetTransportChangeLogByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetTransportChangeLogByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetTransportChangeLogByProductAndtransportID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool GetTransportChangeLogByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetTransportChangeLogByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();


	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double sCount, double sSum,
			int sID, int cID, std::string sLogDate, int tUserID, int tOperationID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif