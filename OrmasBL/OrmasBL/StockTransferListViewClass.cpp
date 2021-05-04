#include "stdafx.h"
#include "StockTransferListViewClass.h"

namespace BusinessLayer
{
	StockTransferListView::StockTransferListView(DataLayer::stockTransferListViewCollection rCollection)
	{
		id = std::get<0>(rCollection);
		stockTransferID = std::get<1>(rCollection);
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

	std::string StockTransferListView::GetProductName()
	{
		return productName;
	}
	double StockTransferListView::GetPrice()
	{
		return price;
	}
	std::string StockTransferListView::GetCurrencyName()
	{
		return currencyName;
	}
	double StockTransferListView::GetVolume()
	{
		return volume;
	}
	std::string StockTransferListView::GetStatusName()
	{
		return statusName;
	}
	std::string StockTransferListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string StockTransferListView::GetMeasureName()
	{
		return measureName;
	}

	void StockTransferListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void StockTransferListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  StockTransferListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void StockTransferListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void StockTransferListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void StockTransferListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void StockTransferListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string StockTransferListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != stockTransferID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForStTranListView(id, stockTransferID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}