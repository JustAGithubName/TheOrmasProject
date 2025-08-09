#ifndef MULTICURRENCYCLASS_H
#define MULTICURRENCYCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"
#include "SubaccountClass.h"

namespace BusinessLayer
{
	class Multicurrency
	{
	private:
		Subaccount exchangeSubaccount;
		Subaccount mainSubaccount;
	protected:
		int id = 0;
		int subaccountCurrencyID = 0;
		int subaccountMainCurrencyID = 0;
		std::string comment = "";
	public:
		Multicurrency(){};
		Multicurrency(int mID, int scID, int smID, std::string mComment) :id(mID), subaccountCurrencyID(scID),
			subaccountMainCurrencyID(smID), comment(mComment){};
		Multicurrency(DataLayer::multicurrencyCollection);
		~Multicurrency(){};
		

		//Multicurrency class Accessors
		int GetID();
		int GetSubaccountCurrencyID();
		int GetSubaccountMainCurrencyID();
		std::string GetComment();

		Subaccount GetExchangeSubaccount();
		Subaccount GetMainSubaccount();

		bool CheckMulticurrencyCorrectness(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);

		//Multicurrency class Mutators
		void SetID(int);
		void SetSubaccountCurrencyID(int);
		void SetSubaccountMainCurrencyID(int);
		void SetComment(std::string);

		void SetExchangeSubaccount(Subaccount&);
		void SetMainSubaccount(Subaccount&);

		// Create, delete and update company
		bool CreateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int scID, int smID, std::string mComment, std::string& errorMessage);
		bool UpdateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int scID, int smID, std::string mComment, std::string& errorMessage);
		int CreateExchangeSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Subaccount exchSub, std::string& errorMessage);
		int CreateMainSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Subaccount mainSub, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		virtual std::string GenerateINFilterForExchangeSub(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList);
		virtual std::string GenerateINFilterForMainSub(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList);
		bool GetMulticurrencyByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool GetMulticurrencyBySubCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetMulticurrencyByMainCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int msID, std::string& errorMessage);
		std::vector<int> GetAllExchSubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,  std::string& errorMessage);
		std::vector<int> GetAllMainSubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		bool IsUserHaveMulticurrencySubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int scID, int smID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CheckMulticurrencyCorrectnessByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,int id, std::string& errorMessage);
	
	};
}
#endif //MulticurrencyCLASS_H