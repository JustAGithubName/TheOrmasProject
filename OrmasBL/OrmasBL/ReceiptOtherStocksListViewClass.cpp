#include "stdafx.h"
#include "ReceiptOtherStocksListViewClass.h"

namespace BusinessLayer
{
	ReceiptOtherStocksListView::ReceiptOtherStocksListView(DataLayer::receiptOtherStocksListViewCollection oCollection)
	{
		id = std::get<0>(oCollection);
		receiptOtherStocksID = std::get<1>(oCollection);
		otherStocksName = std::get<2>(oCollection);
		price = std::get<3>(oCollection);
		currencyName = std::get<4>(oCollection);
		volume = std::get<5>(oCollection);
		measureName = std::get<6>(oCollection);
		count = std::get<7>(oCollection);
		sum = std::get<8>(oCollection);
		sumCurrencyName = std::get<9>(oCollection);
		statusName = std::get<10>(oCollection);
		otherStocksID = std::get<11>(oCollection);
		statusID = std::get<12>(oCollection);
		currencyID = std::get<13>(oCollection);
	}

	std::string ReceiptOtherStocksListView::GetOtherStocksName()
	{
		return otherStocksName;
	}
	double ReceiptOtherStocksListView::GetPrice()
	{
		return price;
	}
	std::string ReceiptOtherStocksListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ReceiptOtherStocksListView::GetVolume()
	{
		return volume;
	}
	std::string ReceiptOtherStocksListView::GetStatusName()
	{
		return statusName;
	}
	std::string ReceiptOtherStocksListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ReceiptOtherStocksListView::GetMeasureName()
	{
		return measureName;
	}

	void ReceiptOtherStocksListView::SetOtherStocksName(std::string cOtherStocksName)
	{
		otherStocksName = cOtherStocksName;
	}
	void ReceiptOtherStocksListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ReceiptOtherStocksListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ReceiptOtherStocksListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ReceiptOtherStocksListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ReceiptOtherStocksListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ReceiptOtherStocksListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ReceiptOtherStocksListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != receiptOtherStocksID || !otherStocksName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != otherStocksID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForRcpOthStListView(id, receiptOtherStocksID, otherStocksName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, otherStocksID, statusID, currencyID);
		}
		return "";
	}
}