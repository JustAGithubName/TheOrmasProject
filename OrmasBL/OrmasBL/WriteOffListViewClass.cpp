#include "stdafx.h"
#include "WriteOffListViewClass.h"

namespace BusinessLayer
{
	WriteOffListView::WriteOffListView(DataLayer::writeOffListViewCollection wCollection)
	{
		id = std::get<0>(wCollection);
		writeOffID = std::get<1>(wCollection);
		productName = std::get<2>(wCollection);
		price = std::get<3>(wCollection);
		currencyName = std::get<4>(wCollection);
		volume = std::get<5>(wCollection);
		measureName = std::get<6>(wCollection);
		count = std::get<7>(wCollection);
		sum = std::get<8>(wCollection);
		sumCurrencyName = std::get<9>(wCollection);
		statusName = std::get<10>(wCollection);
		productID = std::get<11>(wCollection);
		statusID = std::get<12>(wCollection);
		currencyID = std::get<13>(wCollection);
	}

	std::string WriteOffListView::GetProductName()
	{
		return productName;
	}
	double WriteOffListView::GetPrice()
	{
		return price;
	}
	std::string WriteOffListView::GetCurrencyName()
	{
		return currencyName;
	}
	double WriteOffListView::GetVolume()
	{
		return volume;
	}
	std::string WriteOffListView::GetStatusName()
	{
		return statusName;
	}
	std::string WriteOffListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string WriteOffListView::GetMeasureName()
	{
		return measureName;
	}

	void WriteOffListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void WriteOffListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  WriteOffListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void WriteOffListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void WriteOffListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void WriteOffListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void WriteOffListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string WriteOffListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != writeOffID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForOrderListView(id, writeOffID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}