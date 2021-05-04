#include "stdafx.h"
#include "PriceViewClass.h"

namespace BusinessLayer{
	PriceView::PriceView(DataLayer::pricesViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		productName = std::get<2>(pCollection);
		volume = std::get<3>(pCollection);
		measureName = std::get<4>(pCollection);
		value = std::get<5>(pCollection);
		currencyName = std::get<6>(pCollection);
		currencyID = std::get<7>(pCollection);
		productID = std::get<8>(pCollection);
		isOutdated = std::get<9>(pCollection);
	}

	std::string PriceView::GetProductName()
	{
		return productName;
	}

	double PriceView::GetVolume()
	{
		return volume;
	}

	std::string PriceView::GetMeasureName()
	{
		return measureName;
	}

	std::string PriceView::GetCurrencyName()
	{
		return currencyName;
	}


	void PriceView::SetCurrencyName(std::string pCurrencyName)
	{
		currencyName = pCurrencyName;
	}

	void PriceView::SetProductName(std::string pProductName)
	{
		productName = pProductName;
	}

	void PriceView::SetVolume(double pVolume)
	{
		volume = pVolume;
	}

	void PriceView::SetMeasureName(std::string pMeasureName)
	{
		measureName = pMeasureName;
	}
	
	std::string PriceView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || productName.empty() || 0 != volume || measureName.empty() || 0 != value || currencyName.empty()
			|| 0 != currencyID || 0 != productID)
		{
			return ormasDal.GetFilterForPriceView(id, date, productName, volume, measureName, value, currencyName, currencyID, productID);
		}
		return "";
	}
}