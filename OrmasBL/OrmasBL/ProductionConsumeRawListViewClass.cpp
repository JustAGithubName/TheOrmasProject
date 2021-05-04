#include "stdafx.h"
#include "ProductionConsumeRawListViewClass.h"

namespace BusinessLayer
{
	ProductionConsumeRawListView::ProductionConsumeRawListView(DataLayer::productionConsumeRawListViewCollection cCollection)
	{
		id = std::get<0>(cCollection);
		productionConsumeRawID = std::get<1>(cCollection);
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

	std::string ProductionConsumeRawListView::GetProductName()
	{
		return productName;
	}
	double ProductionConsumeRawListView::GetPrice()
	{
		return price;
	}
	std::string ProductionConsumeRawListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ProductionConsumeRawListView::GetVolume()
	{
		return volume;
	}
	std::string ProductionConsumeRawListView::GetStatusName()
	{
		return statusName;
	}
	std::string ProductionConsumeRawListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ProductionConsumeRawListView::GetMeasureName()
	{
		return measureName;
	}

	void ProductionConsumeRawListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ProductionConsumeRawListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ProductionConsumeRawListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ProductionConsumeRawListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ProductionConsumeRawListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ProductionConsumeRawListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ProductionConsumeRawListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ProductionConsumeRawListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productionConsumeRawID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForConProdnListView(id, productionConsumeRawID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}

}