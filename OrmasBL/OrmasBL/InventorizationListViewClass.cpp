#include "stdafx.h"
#include "InventorizationListViewClass.h"

namespace BusinessLayer
{
	InventorizationListView::InventorizationListView(DataLayer::inventorizationListViewCollection iCollection)
	{
		id = std::get<0>(iCollection);
		inventorizationID = std::get<1>(iCollection);
		productName = std::get<2>(iCollection);
		price = std::get<3>(iCollection);
		currencyName = std::get<4>(iCollection);
		volume = std::get<5>(iCollection);
		measureName = std::get<6>(iCollection);
		count = std::get<7>(iCollection);
		sum = std::get<8>(iCollection);
		sumCurrencyName = std::get<9>(iCollection);
		statusName = std::get<10>(iCollection);
		productID = std::get<11>(iCollection);
		statusID = std::get<12>(iCollection);
		currencyID = std::get<13>(iCollection);
	}

	std::string InventorizationListView::GetProductName()
	{
		return productName;
	}
	double InventorizationListView::GetPrice()
	{
		return price;
	}
	std::string InventorizationListView::GetCurrencyName()
	{
		return currencyName;
	}
	double InventorizationListView::GetVolume()
	{
		return volume;
	}
	std::string InventorizationListView::GetStatusName()
	{
		return statusName;
	}
	std::string InventorizationListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string InventorizationListView::GetMeasureName()
	{
		return measureName;
	}

	void InventorizationListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void InventorizationListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  InventorizationListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void InventorizationListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void InventorizationListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void InventorizationListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void InventorizationListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string InventorizationListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != inventorizationID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForInvListView(id, inventorizationID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}