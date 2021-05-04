#include "stdafx.h"
#include "ProductionListViewClass.h"

namespace BusinessLayer
{
	ProductionListView::ProductionListView(DataLayer::productionListViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		productionID = std::get<1>(pCollection);
		productName = std::get<2>(pCollection);
		price = std::get<3>(pCollection);
		currencyName = std::get<4>(pCollection);
		volume = std::get<5>(pCollection);
		measureName = std::get<6>(pCollection);
		count = std::get<7>(pCollection);
		sum = std::get<8>(pCollection);
		sumCurrencyName = std::get<9>(pCollection);
		statusName = std::get<10>(pCollection);
		productID = std::get<11>(pCollection);
		statusID = std::get<12>(pCollection);
		currencyID = std::get<13>(pCollection);
	}

	std::string ProductionListView::GetProductName()
	{
		return productName;
	}
	double ProductionListView::GetPrice()
	{
		return price;
	}
	std::string ProductionListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ProductionListView::GetVolume()
	{
		return volume;
	}
	std::string ProductionListView::GetStatusName()
	{
		return statusName;
	}
	std::string ProductionListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ProductionListView::GetMeasureName()
	{
		return measureName;
	}

	void ProductionListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ProductionListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ProductionListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ProductionListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ProductionListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ProductionListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ProductionListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ProductionListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productionID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForProdnListView(id, productionID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}