#include "stdafx.h"
#include "ReturnListViewClass.h"

namespace BusinessLayer
{
	ReturnListView::ReturnListView(DataLayer::returnListViewCollection rCollection)
	{
		id = std::get<0>(rCollection);
		returnID = std::get<1>(rCollection);
		productName = std::get<2>(rCollection);
		price = std::get<3>(rCollection);
		currencyName = std::get<4>(rCollection);
		volume = std::get<5>(rCollection);
		measureName = std::get<6>(rCollection);
		count = std::get<7>(rCollection);
		sum = std::get<8>(rCollection);
		sumCurrencyName = std::get<9>(rCollection);
		statusName = std::get<10>(rCollection);
		productID = std::get<11>(rCollection);
		statusID = std::get<12>(rCollection);
		currencyID = std::get<13>(rCollection);
	}

	std::string ReturnListView::GetProductName()
	{
		return productName;
	}
	double ReturnListView::GetPrice()
	{
		return price;
	}
	std::string ReturnListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ReturnListView::GetVolume()
	{
		return volume;
	}
	std::string ReturnListView::GetStatusName()
	{
		return statusName;
	}
	std::string ReturnListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ReturnListView::GetMeasureName()
	{
		return measureName;
	}

	void ReturnListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ReturnListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ReturnListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ReturnListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ReturnListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ReturnListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ReturnListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ReturnListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != returnID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForReturnListView(id, returnID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}