#ifndef CURRENCYRATRVIEW_H
#define CURRENCYRATRVIEW_H

#include "CurrencyRateClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class CurrencyRateView : public CurrencyRate
	{
		std::string fromCurrencyShortName = "";
		std::string toCurrencyShortName = "";
	public:
		CurrencyRateView(DataLayer::currenciesRateViewCollection);
		CurrencyRateView(){};
		~CurrencyRateView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// Chart Of Accounts View class Accessors
		std::string GetFromCurrencyShortName();
		std::string GetToCurrencyShortName();
		
		void SetFromCurrencyShortName(std::string);
		void SetToCurrencyShortName(std::string);

		
	};
}

#endif