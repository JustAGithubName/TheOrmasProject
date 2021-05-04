#include "stdafx.h"
#include "LowValueStockHistoryViewClass.h"

namespace BusinessLayer
{
	LowValueStockHistoryView::LowValueStockHistoryView(DataLayer::lowValueStockHistoryViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		otherStocksName = std::get<1>(sCollection);
		price = std::get<2>(sCollection);
		currencyName = std::get<3>(sCollection);
		volume = std::get<4>(sCollection);
		measureName = std::get<5>(sCollection);
		count = std::get<6>(sCollection);
		sum = std::get<7>(sCollection);
		sumCurrencyName = std::get<8>(sCollection);
		warehouseName = std::get<9>(sCollection);
		subaccountNumber = std::get<10>(sCollection);
		statusName = std::get<11>(sCollection);
		otherStocksID = std::get<12>(sCollection);
		statusID = std::get<13>(sCollection);
		currencyID = std::get<14>(sCollection);
		warehouseID = std::get<15>(sCollection);
		historyDate = std::get<16>(sCollection);
	}

	std::string LowValueStockHistoryView::GetOtherStocksName()
	{
		return otherStocksName;
	}
	double LowValueStockHistoryView::GetPrice()
	{
		return price;
	}
	std::string LowValueStockHistoryView::GetCurrencyName()
	{
		return currencyName;
	}
	double LowValueStockHistoryView::GetVolume()
	{
		return volume;
	}
	std::string LowValueStockHistoryView::GetStatusName()
	{
		return statusName;
	}
	std::string LowValueStockHistoryView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string LowValueStockHistoryView::GetMeasureName()
	{
		return measureName;
	}
	std::string LowValueStockHistoryView::GetWarehouseName()
	{
		return warehouseName;
	}
	std::string LowValueStockHistoryView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	void LowValueStockHistoryView::SetOtherStocksName(std::string iOtherStocksName)
	{
		otherStocksName = iOtherStocksName;
	}
	void LowValueStockHistoryView::SetPrice(double iPrice)
	{
		price = iPrice;
	}
	void LowValueStockHistoryView::SetCurrencyName(std::string jCurrencyName)
	{
		currencyName = jCurrencyName;
	}
	void LowValueStockHistoryView::SetVolume(double jVolume)
	{
		volume = jVolume;
	}
	void LowValueStockHistoryView::SetStatusName(std::string jStatusName)
	{
		statusName = jStatusName;
	}
	void LowValueStockHistoryView::SetSumCurrencyName(std::string jSumCurrencyName)
	{
		sumCurrencyName = jSumCurrencyName;
	}
	void LowValueStockHistoryView::SetMeasureName(std::string jMeasureName)
	{
		measureName = jMeasureName;
	}
	void LowValueStockHistoryView::SetWarehouseName(std::string lWarehouseName)
	{
		warehouseName = lWarehouseName;
	}
	void LowValueStockHistoryView::SetSubaccountNumber(std::string jSubaccountNumber)
	{
		subaccountNumber = jSubaccountNumber;
	}

	std::string LowValueStockHistoryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !otherStocksName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty() || 0 != count || 0 != sum
			|| !sumCurrencyName.empty() || !warehouseName.empty() || !subaccountNumber.empty() || !statusName.empty() || 0 != otherStocksID || 0 != statusID
			|| 0 != currencyID || 0 != warehouseID || !historyDate.empty())
		{
			return ormasDal.GetFilterForLowValStockHisView(id, otherStocksName, price, currencyName, volume, measureName, count, sum, sumCurrencyName, warehouseName,
				subaccountNumber, statusName, otherStocksID, statusID, currencyID, warehouseID, historyDate);
		}
		return "";
	}
}