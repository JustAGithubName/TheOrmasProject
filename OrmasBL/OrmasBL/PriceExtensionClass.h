#ifndef PRICEEXTENSIONCLASS_H
#define PRICEEXTENSIONCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class PriceExtension{
	protected:
		int id = 0;
		int productID = 0;
		double value = 0.0;
		std::string date = "";
		int dayCount = 0;
		int locationID = 0;
		int expeditorID = 0;
		int branchID = 0;
		int clientID = 0;
	public:
		PriceExtension();
		PriceExtension(int pID, int prID, double pValue, std::string pDate, int count, int lID, int eID, int bID, int cID) :id(pID), productID(prID), value(pValue),
			date(pDate), dayCount(count), locationID(lID), expeditorID(eID), branchID(bID), clientID(cID){};
		PriceExtension(DataLayer::priceExtensionCollection);
		~PriceExtension(){};

		std::string errorMessage = "";
		//PriceExtension class PriceExtensionors
		int GetID();
		int GetProductID();
		double GetValue();
		std::string GetDate();
		int GetBranchID();
		int GetClientID();
		int GetDayCount();
		int GetExpeditorID();
		int GetLocationID();

		//PriceExtension class Mutators
		void SetID(int);
		void SetProductID(int);
		void SetValue(double);
		void SetDate(std::string);
		void SetBranchID(int);
		void SetClientID(int);
		void SetDayCount(int);
		void SetExpeditorID(int);
		void SetLocationID(int);


		// Create, delete and update PriceExtension
		bool CreatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int prID, double pValue, std::string pDate, int count,
			int lID, int eID, int bID, int cID, std::string& errorMessage);
		bool UpdatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int prID, double pValue, std::string pDate, int count,
			int lID, int eID, int bID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetPriceExtensionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetPriceExtensionByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, std::string& errorMessage);
		bool GetPriceExtensionByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		bool GetPriceExtensionByClientID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool GetPriceExtensionByLocationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lID, std::string& errorMessage);
		bool GetPriceExtensionByExpeditorID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lID, std::string& errorMessage);

		bool GetPriceExtensionByProductIDAndExpeditorID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int expID, std::string& errorMessage);
		bool GetPriceExtensionByProductIDAndClientID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int clID, std::string& errorMessage);
		bool GetPriceExtensionByProductIDAndBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int brID, std::string& errorMessage);
		bool GetPriceExtensionByProductIDAndLocationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, int locID, std::string& errorMessage);
		

		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, double pValue, std::string pDate, int bID, int cID, int count, int pExpeditorID, int lID,
			std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //PRICEEXTENSIONCLASS_H