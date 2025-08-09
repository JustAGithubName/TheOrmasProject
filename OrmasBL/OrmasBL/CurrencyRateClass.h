#ifndef CURRENCYRATECLASS_H
#define CURRENCYRATECLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer
{
	class CurrencyRate
	{
	protected:
		int id = 0;
		int fromCurrencyID = 0;
		double fromValue = 0.0;
		int toCurrencyID = 0;
		double toValue = 0.0;
		std::string changeDate = "";
	public:
		CurrencyRate(){};
		CurrencyRate(int crID, int fCurrID, double fValue, int tCurrID, double tValue, std::string cDate) :id(crID), fromCurrencyID(fCurrID),
			fromValue(fValue), toCurrencyID(tCurrID), toValue(tValue), changeDate(cDate){};
		CurrencyRate(DataLayer::currenciesRateCollection);
		~CurrencyRate(){};

		//currencyRate class Accessors
		int GetID();
		int GetFromCurrencyID();
		double GetFromValue();
		int GetToCurrencyID();
		double GetToValue();
		std::string GetChangeDate();
		

		//currencyRate class Mutators
		void SetID(int);
		void SetFromCurrencyID(int);
		void SetFromValue(double);
		void SetToCurrencyID(int);
		void SetToValue(double);
		void SetChangeDate(std::string);

		// Create, delete and update company
		bool CreateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fCurrID, double fValue, 
			int tCurrID, double tValue, std::string cDate, std::string& errorMessage);
		bool UpdateCurrencyRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fCurrID, double fValue,
			int tCurrID, double tValue, std::string cDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCurrencyRateByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool GetCurrencyRateByFromCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fcID, std::string& errorMessage);
		bool GetCurrencyRateByToCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int tcID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fCurrID, double fValue,
			int tCurrID, double tValue, std::string cDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool RecalculateSubaccounts(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double value, int debSubID, int credSubID, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}
#endif //currencyRateCLASS_H