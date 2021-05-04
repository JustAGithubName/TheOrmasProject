#include "stdafx.h"
#include "ReceiptProductListViewClass.h"

namespace BusinessLayer
{
	ReceiptProductListView::ReceiptProductListView(DataLayer::receiptProductListViewCollection rCollection)
	{
		id = std::get<0>(rCollection);
		receiptProductID = std::get<1>(rCollection);
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

	std::string ReceiptProductListView::GetProductName()
	{
		return productName;
	}
	double ReceiptProductListView::GetPrice()
	{
		return price;
	}
	std::string ReceiptProductListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ReceiptProductListView::GetVolume()
	{
		return volume;
	}
	std::string ReceiptProductListView::GetStatusName()
	{
		return statusName;
	}
	std::string ReceiptProductListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ReceiptProductListView::GetMeasureName()
	{
		return measureName;
	}


	void ReceiptProductListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ReceiptProductListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ReceiptProductListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ReceiptProductListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ReceiptProductListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ReceiptProductListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ReceiptProductListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ReceiptProductListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != receiptProductID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForRcpProdListView(id, receiptProductID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}