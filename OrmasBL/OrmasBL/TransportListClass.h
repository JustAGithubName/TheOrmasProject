#ifndef TransportLISTCLASS_H
#define TransportLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class TransportList
	{
	protected:
		int id = 0;
		int transportID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		TransportList(int tlID, int tID, int pID, double tlCount, double tlSum, int sID, int cID) :id(tlID), transportID(tID),
			productID(pID),	count(tlCount), sum(tlSum), statusID(sID), currencyID(cID){};
		TransportList(DataLayer::transportListCollection);
		TransportList(){};
		~TransportList(){};

		//TransportList class Accessors
		int GetID();
		int GetTransportID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//TransportList class Mutators
		void SetID(int);
		void SetTransportID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByTransportID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage);
		bool CreateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateTransportList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
			int sID, int cID, std::string& errorMessage);

		bool CreateTransportChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetTransportListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, std::string& errorMessage);
		bool GetTransportListByTransportAndProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, std::string& errorMessage);

		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string& errorMessage);
		
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tID, int pID, double tlCount, double tlSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}
#endif