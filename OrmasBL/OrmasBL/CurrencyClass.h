#ifndef CURRENCYCLASS_H
#define CURRENCYCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer
{
	class Currency
	{
		int id = 0;
		int code = 0;
		std::string shortName = "";
		std::string name = "";
		int unit = 0;
		bool mainTrade = false;
	public:
		Currency(){};
		Currency(int cID, int cCode, std::string cShortName, std::string cName, int cUnit, bool cMainTrade) :id(cID), code(cCode),
			shortName(cShortName), name(cName), unit(cUnit), mainTrade(cMainTrade){};
		Currency(DataLayer::currenciesCollection);
		~Currency(){};
		
		//Currency class Accessors
		int GetID();
		int GetCode();
		std::string GetShortName();
		std::string GetName();
		int GetUnit();
		bool GetMainTrade();

		//Currency class Mutators
		void SetID(int);
		void SetCode(int);
		void SetShortName(std::string);
		void SetName(std::string);
		void SetUnit(int);
		void SetMainTrade(bool);
		
		// Create, delete and update company
		bool CreateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cCode, std::string cShortName, std::string cName, int cUnit,
			bool cMainTrade, std::string& errorMessage);
		bool UpdateCurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cCode, std::string cShortName, std::string cName, int cUnit,
			bool cMainTrade, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCurrencyByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		int GetMainTradeCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cShortName, std::string cName, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //CURRENCYCLASS_H