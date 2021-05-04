#ifndef INVENTORIZATIONLISTCLASS_H
#define INVENTORIZATIONLISTCLASS_H
#include "OrmasDAL.h"

namespace BusinessLayer
{
	class InventorizationList
	{
	protected:
		int id = 0;
		int inventorizationID = 0;
		int productID = 0;
		double count = 0;
		double sum = 0;
		int statusID = 0;
		int currencyID = 0;
	public:
		InventorizationList(int ilID, int iID, int pID, double ilCount, double ilSum, int sID, int cID) :id(ilID), inventorizationID(iID),
			productID(pID),	count(ilCount), sum(ilSum), statusID(sID), currencyID(cID){};
		InventorizationList(DataLayer::inventorizationListCollection);
		InventorizationList(){};
		~InventorizationList(){};

		//InventorizationList class Accessors
		int GetID();
		int GetInventorizationID();
		int GetProductID();
		double GetCount();
		double GetSum();
		int GetStatusID();
		int GetCurrencyID();

		//InventorizationList class Mutators
		void SetID(int);
		void SetInventorizationID(int);
		void SetProductID(int);
		void SetCount(double);
		void SetSum(double);
		void SetStatusID(int);
		void SetCurrencyID(int);

		//Create, delete, update methods
		bool CreateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteListByInventorizationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage);
		bool CreateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, int pID, double ilCount, double ilSum,
			int sID, int cID, std::string& errorMessage);
		bool UpdateInventorizationList(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, int pID, double ilCount, double ilSum,
			int sID, int cID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetInventorizationListByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, int pID, double ilCount, double ilSum,
			int cID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif