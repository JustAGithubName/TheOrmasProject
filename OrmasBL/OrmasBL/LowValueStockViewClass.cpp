#include "stdafx.h"
#include "LowValueStockViewClass.h"

namespace BusinessLayer
{
	LowValueStockView::LowValueStockView(DataLayer::lowValueStockViewCollection sCollection)
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
	}

	std::string LowValueStockView::GetOtherStocksName()
	{
		return otherStocksName;
	}
	double LowValueStockView::GetPrice()
	{
		return price;
	}
	std::string LowValueStockView::GetCurrencyName()
	{
		return currencyName;
	}
	double LowValueStockView::GetVolume()
	{
		return volume;
	}
	std::string LowValueStockView::GetStatusName()
	{
		return statusName;
	}
	std::string LowValueStockView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string LowValueStockView::GetMeasureName()
	{
		return measureName;
	}
	std::string LowValueStockView::GetWarehouseName()
	{
		return warehouseName;
	}
	std::string LowValueStockView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	void LowValueStockView::SetOtherStocksName(std::string iOtherStocksName)
	{
		otherStocksName = iOtherStocksName;
	}
	void LowValueStockView::SetPrice(double iPrice)
	{
		price = iPrice;
	}
	void LowValueStockView::SetCurrencyName(std::string jCurrencyName)
	{
		currencyName = jCurrencyName;
	}
	void LowValueStockView::SetVolume(double jVolume)
	{
		volume = jVolume;
	}
	void LowValueStockView::SetStatusName(std::string jStatusName)
	{
		statusName = jStatusName;
	}
	void LowValueStockView::SetSumCurrencyName(std::string jSumCurrencyName)
	{
		sumCurrencyName = jSumCurrencyName;
	}
	void LowValueStockView::SetMeasureName(std::string jMeasureName)
	{
		measureName = jMeasureName;
	}
	void LowValueStockView::SetWarehouseName(std::string lWarehouseName)
	{
		warehouseName = lWarehouseName;
	}
	void LowValueStockView::SetSubaccountNumber(std::string jSubaccountNumber)
	{
		subaccountNumber = jSubaccountNumber;
	}

	std::string LowValueStockView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !otherStocksName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty() || 0 != count || 0 != sum
			|| !sumCurrencyName.empty() || !warehouseName.empty() || !subaccountNumber.empty() || !statusName.empty() || 0 != otherStocksID || 0 != statusID
			|| 0 != currencyID || 0 != warehouseID)
		{
			return ormasDal.GetFilterForLowValStockView(id, otherStocksName, price, currencyName, volume, measureName, count, sum, sumCurrencyName, warehouseName,
				subaccountNumber, statusName, otherStocksID, statusID, currencyID, warehouseID);
		}
		return "";
	}
}