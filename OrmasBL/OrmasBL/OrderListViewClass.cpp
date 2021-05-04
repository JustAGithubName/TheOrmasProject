#include "stdafx.h"
#include "OrderListViewClass.h"

namespace BusinessLayer
{
	OrderListView::OrderListView(DataLayer::orderListViewCollection oCollection)
	{
		id = std::get<0>(oCollection);
		orderID = std::get<1>(oCollection);
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

	std::string OrderListView::GetProductName()
	{
		return productName;
	}
	double OrderListView::GetPrice()
	{
		return price;
	}
	std::string OrderListView::GetCurrencyName()
	{
		return currencyName;
	}
	double OrderListView::GetVolume()
	{
		return volume;
	}
	std::string OrderListView::GetStatusName()
	{
		return statusName;
	}
	std::string OrderListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string OrderListView::GetMeasureName()
	{
		return measureName;
	}

	void OrderListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void OrderListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  OrderListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void OrderListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void OrderListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void OrderListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void OrderListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string OrderListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != orderID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForOrderListView(id, orderID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}