#include "stdafx.h"
#include "ConsumeProductListViewClass.h"

namespace BusinessLayer
{
	ConsumeProductListView::ConsumeProductListView(DataLayer::consumeProductListViewCollection cCollection)
	{
		id = std::get<0>(cCollection);
		consumeProductID = std::get<1>(cCollection);
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

	std::string ConsumeProductListView::GetProductName()
	{
		return productName;
	}
	double ConsumeProductListView::GetPrice()
	{
		return price;
	}
	std::string ConsumeProductListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ConsumeProductListView::GetVolume()
	{
		return volume;
	}
	std::string ConsumeProductListView::GetStatusName()
	{
		return statusName;
	}
	std::string ConsumeProductListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ConsumeProductListView::GetMeasureName()
	{
		return measureName;
	}


	void ConsumeProductListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ConsumeProductListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ConsumeProductListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ConsumeProductListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ConsumeProductListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ConsumeProductListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ConsumeProductListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ConsumeProductListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != consumeProductID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty() 
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForConProdListView(id, consumeProductID, productName, price, currencyName, volume, measureName, count, sum, 
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}