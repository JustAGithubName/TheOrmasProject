#include "stdafx.h"
#include "OrderRawListViewClass.h"

namespace BusinessLayer
{
	OrderRawListView::OrderRawListView(DataLayer::orderRawListViewCollection oCollection)
	{
		id = std::get<0>(oCollection);
		orderRawID = std::get<1>(oCollection);
		productName = std::get<2>(oCollection);
		price = std::get<3>(oCollection);
		currencyName = std::get<4>(oCollection);
		volume = std::get<5>(oCollection);
		measureName = std::get<6>(oCollection);
		count = std::get<7>(oCollection);
		sum = std::get<8>(oCollection);
		sumCurrencyName = std::get<9>(oCollection);
		statusName = std::get<10>(oCollection);
		productID = std::get<11>(oCollection);
		statusID = std::get<12>(oCollection);
		currencyID = std::get<13>(oCollection);
	}

	std::string OrderRawListView::GetProductName()
	{
		return productName;
	}
	double OrderRawListView::GetPrice()
	{
		return price;
	}
	std::string OrderRawListView::GetCurrencyName()
	{
		return currencyName;
	}
	double OrderRawListView::GetVolume()
	{
		return volume;
	}
	std::string OrderRawListView::GetStatusName()
	{
		return statusName;
	}
	std::string OrderRawListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string OrderRawListView::GetMeasureName()
	{
		return measureName;
	}

	void OrderRawListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void OrderRawListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  OrderRawListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void OrderRawListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void OrderRawListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void OrderRawListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void OrderRawListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string OrderRawListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != orderRawID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForOrdRawListView(id, orderRawID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}