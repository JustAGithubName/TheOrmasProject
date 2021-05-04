#include "stdafx.h"
#include "ConsumeRawListViewClass.h"

namespace BusinessLayer
{
	ConsumeRawListView::ConsumeRawListView(DataLayer::consumeRawListViewCollection cCollection)
	{
		id = std::get<0>(cCollection);
		consumeRawID = std::get<1>(cCollection);
		productName = std::get<2>(cCollection);
		price = std::get<3>(cCollection);
		currencyName = std::get<4>(cCollection);
		volume = std::get<5>(cCollection);
		measureName = std::get<6>(cCollection);
		count = std::get<7>(cCollection);
		sum = std::get<8>(cCollection);
		sumCurrencyName = std::get<9>(cCollection);
		statusName = std::get<10>(cCollection);
		productID = std::get<11>(cCollection);
		statusID = std::get<12>(cCollection);
		currencyID = std::get<13>(cCollection);
	}

	std::string ConsumeRawListView::GetProductName()
	{
		return productName;
	}
	double ConsumeRawListView::GetPrice()
	{
		return price;
	}
	std::string ConsumeRawListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ConsumeRawListView::GetVolume()
	{
		return volume;
	}
	std::string ConsumeRawListView::GetStatusName()
	{
		return statusName;
	}
	std::string ConsumeRawListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ConsumeRawListView::GetMeasureName()
	{
		return measureName;
	}

	void ConsumeRawListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ConsumeRawListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ConsumeRawListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ConsumeRawListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ConsumeRawListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ConsumeRawListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ConsumeRawListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ConsumeRawListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != consumeRawID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForConRawListView(id, consumeRawID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}