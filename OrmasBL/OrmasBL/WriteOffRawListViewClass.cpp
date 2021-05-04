#include "stdafx.h"
#include "WriteOffRawListViewClass.h"

namespace BusinessLayer
{
	WriteOffRawListView::WriteOffRawListView(DataLayer::writeOffRawListViewCollection wCollection)
	{
		id = std::get<0>(wCollection);
		writeOffRawID = std::get<1>(wCollection);
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

	std::string WriteOffRawListView::GetProductName()
	{
		return productName;
	}
	double WriteOffRawListView::GetPrice()
	{
		return price;
	}
	std::string WriteOffRawListView::GetCurrencyName()
	{
		return currencyName;
	}
	double WriteOffRawListView::GetVolume()
	{
		return volume;
	}
	std::string WriteOffRawListView::GetStatusName()
	{
		return statusName;
	}
	std::string WriteOffRawListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string WriteOffRawListView::GetMeasureName()
	{
		return measureName;
	}

	void WriteOffRawListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void WriteOffRawListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  WriteOffRawListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void WriteOffRawListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void WriteOffRawListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void WriteOffRawListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void WriteOffRawListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string WriteOffRawListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != writeOffRawID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForWOffRawListView(id, writeOffRawID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}

}