#include "stdafx.h"
#include "SpoilageListViewClass.h"

namespace BusinessLayer
{
	SpoilageListView::SpoilageListView(DataLayer::spoilageListViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		spoilageID = std::get<1>(sCollection);
		productName = std::get<2>(sCollection);
		price = std::get<3>(sCollection);
		currencyName = std::get<4>(sCollection);
		volume = std::get<5>(sCollection);
		measureName = std::get<6>(sCollection);
		count = std::get<7>(sCollection);
		sum = std::get<8>(sCollection);
		sumCurrencyName = std::get<9>(sCollection);
		statusName = std::get<10>(sCollection);
		productID = std::get<11>(sCollection);
		statusID = std::get<12>(sCollection);
		currencyID = std::get<13>(sCollection);
	}

	std::string SpoilageListView::GetProductName()
	{
		return productName;
	}
	double SpoilageListView::GetPrice()
	{
		return price;
	}
	std::string SpoilageListView::GetCurrencyName()
	{
		return currencyName;
	}
	double SpoilageListView::GetVolume()
	{
		return volume;
	}
	std::string SpoilageListView::GetStatusName()
	{
		return statusName;
	}
	std::string SpoilageListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string SpoilageListView::GetMeasureName()
	{
		return measureName;
	}

	void SpoilageListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void SpoilageListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  SpoilageListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void SpoilageListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void SpoilageListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void SpoilageListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void SpoilageListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string SpoilageListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != spoilageID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForSpoilageListView(id, spoilageID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}

}