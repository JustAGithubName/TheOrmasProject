#ifndef MULTICURRENCYVIEW_H
#define MULTICURRENCYVIEW_H

#include "MulticurrencyClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class MulticurrencyView : public Multicurrency
	{
		std::string exhangeCurrencyNumber = "";
		double exhangeCurrencyValue = 0;
		std::string exhangeCurShortName = "";
		std::string mainCurrencyNumber = "";
		double mainCurrencyValue = 0;
		std::string mainCurShortName = "";
	public:
		MulticurrencyView(DataLayer::multicurrencyViewCollection);
		MulticurrencyView(){};
		~MulticurrencyView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// Chart Of Accounts View class Accessors
		std::string GetExchangeCurrencyNumber();
		double GetExchangeCurrencyValue();
		std::string GetExchangeCurShortName();
		std::string GetMainCurrencyNumber();
		double GetMainCurrencyValue();
		std::string GetMainCurShortName();

		void SetExchangeCurrencyNumber(std::string);
		void SetExchangeCurrencyValue(double);
		void SetExchangeCurShortName(std::string);
		void SetMainCurrencyNumber(std::string);
		void SetMainCurrencyValue(double);
		void SetMainCurShortName(std::string);
	};
}

#endif //MULTICURRENCYVIEW_H