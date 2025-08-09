
#include "stdafx.h"
#include "MulticurrencyViewClass.h"

namespace BusinessLayer{
	MulticurrencyView::MulticurrencyView(DataLayer::multicurrencyViewCollection dCollection)
	{
		id = std::get<0>(dCollection);
		exhangeCurrencyNumber = std::get<1>(dCollection);
		exhangeCurrencyValue = std::get<2>(dCollection);
		exhangeCurShortName = std::get<3>(dCollection);
		mainCurrencyNumber = std::get<4>(dCollection);
		mainCurrencyValue = std::get<5>(dCollection);
		mainCurShortName = std::get<6>(dCollection);
		subaccountCurrencyID = std::get<7>(dCollection);
		subaccountMainCurrencyID = std::get<8>(dCollection);
		comment = std::get<9>(dCollection);
	}

	std::string MulticurrencyView::GetExchangeCurrencyNumber()
	{
		return exhangeCurrencyNumber;
	}

	double MulticurrencyView::GetExchangeCurrencyValue()
	{
		return exhangeCurrencyValue;
	}

	std::string MulticurrencyView::GetExchangeCurShortName()
	{
		return exhangeCurShortName;
	}

	std::string MulticurrencyView::GetMainCurrencyNumber()
	{
		return mainCurrencyNumber;
	}

	double MulticurrencyView::GetMainCurrencyValue()
	{
		return mainCurrencyValue;
	}

	std::string MulticurrencyView::GetMainCurShortName()
	{
		return mainCurShortName;
	}


	void MulticurrencyView::SetExchangeCurrencyNumber(std::string eCurNumber)
	{
		exhangeCurrencyNumber = eCurNumber;
	}

	void MulticurrencyView::SetExchangeCurrencyValue(double eCurValue)
	{
		exhangeCurrencyValue = eCurValue;
	}

	void MulticurrencyView::SetExchangeCurShortName(std::string eCurShortName)
	{
		exhangeCurShortName = eCurShortName;
	}


	void MulticurrencyView::SetMainCurrencyNumber(std::string mCurNumber)
	{
		mainCurrencyNumber = mCurNumber;
	}

	void MulticurrencyView::SetMainCurrencyValue(double mCurValue)
	{
		mainCurrencyValue = mCurValue;
	}

	void MulticurrencyView::SetMainCurShortName(std::string mCurShortName)
	{
		mainCurShortName = mCurShortName;
	}


	std::string MulticurrencyView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{

		if (0 != id || !exhangeCurrencyNumber.empty() || !exhangeCurShortName.empty() || 0 != exhangeCurrencyValue
			|| !exhangeCurShortName.empty() || !mainCurrencyNumber.empty() || 0 != mainCurrencyValue || !mainCurShortName.empty() || 0 != subaccountCurrencyID || 0 != subaccountMainCurrencyID || !comment.empty())
		{
			return ormasDal.GetFilterForMulticurrencyView(id, exhangeCurrencyNumber, exhangeCurrencyValue, exhangeCurShortName, mainCurrencyNumber,
				mainCurrencyValue, mainCurShortName, subaccountCurrencyID, subaccountMainCurrencyID, comment);
		}
		return "";
	}
}