#ifndef SPOILAGECLASS_H
#define SPOILAGECLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Spoilage
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
		Spoilage(int sID, std::string sDate, int eID, double sCount, double sSum, int stsID, int cID) :
			id(sID), date(sDate), employeeID(eID), count(sCount), sum(sSum), statusID(stsID), currencyID(cID){};
		Spoilage(DataLayer::spoilageCollection);
		Spoilage(){};
		~Spoilage(){};

		//Spoilage class Accessors
		int GetID();
		std::string GetDate();
		int GetEmployeeID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//Spoilage class Mutators
		void SetID(int);
		void SetDate(std::string);
		void SetEmployeeID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateSpoilage(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSpoilage(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSpoilage(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSpoilage(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sDate, int eID, double sCount,
			double sSum, int stsID, int cID, std::string& errorMessage);
		bool UpdateSpoilage(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sDate, int eID, double sCount,
			double sSum, int stsID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSpoilageByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		double previousSum = 0.0;
		double previousStatusID = 0;
		double prevCount = 0;
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sDate, double sCount, double sSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSpoilageEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, double oSum, int cID, std::string& errorMessage);
		bool CreateSpoilageEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, double oSum, double prevSum, int cID, std::string& errorMessage);
		double GetCurrentSum(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		double GetCurrentCount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int crID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}
#endif //SPOILAGECLASS_H