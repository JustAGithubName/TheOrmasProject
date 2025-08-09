
#include "stdafx.h"
#include "CurrencyRateViewClass.h"

namespace BusinessLayer{
	CurrencyRateView::CurrencyRateView(DataLayer::currenciesRateViewCollection dCollection)
	{
		id = std::get<0>(dCollection);
		fromCurrencyShortName = std::get<1>(dCollection);
		fromValue = std::get<2>(dCollection);
		toCurrencyShortName = std::get<3>(dCollection);
		toValue = std::get<4>(dCollection);
		fromCurrencyID = std::get<5>(dCollection);
		toCurrencyID = std::get<6>(dCollection);
		changeDate = std::get<7>(dCollection);
	}

	std::string CurrencyRateView::GetFromCurrencyShortName()
	{
		return fromCurrencyShortName;
	}

	std::string CurrencyRateView::GetToCurrencyShortName()
	{
		return toCurrencyShortName;
	}

	
	void CurrencyRateView::SetFromCurrencyShortName(std::string fShortName)
	{
		fromCurrencyShortName = fShortName;
	}

	void CurrencyRateView::SetToCurrencyShortName(std::string tShortName)
	{
		toCurrencyShortName = tShortName;
	}

	std::string CurrencyRateView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{

		if (0 != id || !fromCurrencyShortName.empty() || !toCurrencyShortName.empty() || 0 != fromCurrencyID 
			|| 0 != fromValue || 0 != toCurrencyID || 0 != toValue || !changeDate.empty())
		{
			return ormasDal.GetFilterForCurrencyRateView(id, fromCurrencyShortName, fromValue, toCurrencyShortName, toValue, fromCurrencyID, toCurrencyID, changeDate);
		}
		return "";
	}
}