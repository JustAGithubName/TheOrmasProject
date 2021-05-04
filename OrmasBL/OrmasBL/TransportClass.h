#ifndef TRANSPORTCLASS_H
#define TRANSPORTCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Transport
	{
	protected:
		int id = 0;
		int userID = 0;
		std::string date = "";
		std::string executionDate = "";
		int employeeID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		Transport(int tID, int uID, std::string tDate, std::string tExecDate, int eID, double tCount, double tSum, int sID, int cID) :
			id(tID), userID(uID), date(tDate), executionDate(tExecDate), employeeID(eID), count(tCount), sum(tSum),
			statusID(sID), currencyID(cID){};
		Transport(DataLayer::transportsCollection);
		Transport(){};
		~Transport(){};

		//Consume Product class Accessors
		int GetID();
		int GetUserID();
		std::string GetDate();
		std::string GetExecutionDate();
		int GetEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//Consume Product class Mutators
		void SetID(int);
		void SetUserID(int);
		void SetDate(std::string);
		void SetExecutionDate(std::string);
		void SetEmployeeID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string tDate, std::string tExecDate, int eID,
			double tCount, double tSum, int sID, int cID, std::string& errorMessage);
		bool UpdateTransport(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string tDate, std::string tExecDate, int eID, 
			double tCount, double tSum, int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetTransportByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage);
		bool GetTransportByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		bool ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool ChangingByConsumeProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool ChangingByConsumeProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
		bool ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool ChangingByReceiptProductReverse(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::string& errorMessage);
		bool ChangingByReceiptProduct(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cpID, std::map<int, double> pProdCountMap, double pSum, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int debAccID, double currentSum, int credAccID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}
#endif //TransportCLASS_H
