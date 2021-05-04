#include "stdafx.h"
#include "NetCostViewClass.h"

namespace BusinessLayer{
	NetCostView::NetCostView(DataLayer::netCostViewCollection nCollection)
	{
		id = std::get<0>(nCollection);
		date = std::get<1>(nCollection);
		productName = std::get<2>(nCollection);
		volume = std::get<3>(nCollection);
		measureName = std::get<4>(nCollection);
		value = std::get<5>(nCollection);
		currencyName = std::get<6>(nCollection);
		currencyID = std::get<7>(nCollection);
		productID = std::get<8>(nCollection);
		isOutdated = std::get<9>(nCollection);
	}

	std::string NetCostView::GetProductName()
	{
		return productName;
	}

	double NetCostView::GetVolume()
	{
		return volume;
	}

	std::string NetCostView::GetMeasureName()
	{
		return measureName;
	}


	std::string NetCostView::GetCurrencyName()
	{
		return currencyName;
	}

	void NetCostView::SetProductName(std::string jProductName)
	{
		productName = jProductName;
	}

	void NetCostView::SetVolume(double jVolume)
	{
		volume = jVolume;
	}

	void NetCostView::SetMeasureName(std::string jMeasureName)
	{
		measureName = jMeasureName;
	}


	void NetCostView::SetCurrencyName(std::string jCurrencyName)
	{
		currencyName = jCurrencyName;
	}


	std::string NetCostView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || productName.empty() || 0 != volume || measureName.empty() || 0 != value || currencyName.empty()  || 0 != currencyID 
			|| 0 != productID)
		{
			return ormasDal.GetFilterForNetCostView(id, date, productName, volume, measureName, value, currencyName, currencyID, productID);
		}
		return "";
	}
}