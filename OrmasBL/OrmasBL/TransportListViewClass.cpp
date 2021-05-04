#include "stdafx.h"
#include "TransportListViewClass.h"

namespace BusinessLayer
{
	TransportListView::TransportListView(DataLayer::transportListViewCollection tCollection)
	{
		id = std::get<0>(tCollection);
		transportID = std::get<1>(tCollection);
		productName = std::get<2>(tCollection);
		price = std::get<3>(tCollection);
		currencyName = std::get<4>(tCollection);
		volume = std::get<5>(tCollection);
		measureName = std::get<6>(tCollection);
		count = std::get<7>(tCollection);
		sum = std::get<8>(tCollection);
		sumCurrencyName = std::get<9>(tCollection);
		statusName = std::get<10>(tCollection);
		productID = std::get<11>(tCollection);
		statusID = std::get<12>(tCollection);
		currencyID = std::get<13>(tCollection);
	}

	std::string TransportListView::GetProductName()
	{
		return productName;
	}
	double TransportListView::GetPrice()
	{
		return price;
	}
	std::string TransportListView::GetCurrencyName()
	{
		return currencyName;
	}
	double TransportListView::GetVolume()
	{
		return volume;
	}
	std::string TransportListView::GetStatusName()
	{
		return statusName;
	}
	std::string TransportListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string TransportListView::GetMeasureName()
	{
		return measureName;
	}


	void TransportListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void TransportListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  TransportListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void TransportListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void TransportListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void TransportListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void TransportListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string TransportListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != transportID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForStTranListView(id, transportID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}