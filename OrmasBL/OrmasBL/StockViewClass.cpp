#include "stdafx.h"
#include "StockViewClass.h"

namespace BusinessLayer
{
	StockView::StockView(DataLayer::stockViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		productName = std::get<1>(sCollection);
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
		productID = std::get<12>(sCollection);
		statusID = std::get<13>(sCollection);
		currencyID = std::get<14>(sCollection);
		warehouseID = std::get<15>(sCollection);
	}

	void StockView::SetProductName(std::string pName)
	{
		productName = pName;
	}
	void StockView::SetPrice(double sPrice)
	{
		price = sPrice;
	}
	void StockView::SetCurrencyName(std::string cName)
	{
		currencyName = cName;
	}
	void StockView::SetVolume(double sVolume)
	{
		volume = sVolume;
	}
	void StockView::SetMeasureName(std::string sMeasure)
	{
		measureName = sMeasure;
	}
	void StockView::SetSumCurrencyName(std::string sCur)
	{
		sumCurrencyName = sCur;
	}
	void StockView::SetWarehouseName(std::string swarehouseName)
	{
		warehouseName = swarehouseName;
	}
	void StockView::SetSubaccountNumber(std::string subNumber)
	{
		subaccountNumber = subNumber;
	}
	void StockView::SetStatusName(std::string stName)
	{
		statusName = stName;
	}

	std::string StockView::GetProductName()
	{
		return productName;
	}
	double StockView::GetPrice()
	{
		return price;
	}
	std::string StockView::GetCurrencyName()
	{
		return currencyName;
	}
	double StockView::GetVolume()
	{
		return volume;
	}
	std::string StockView::GetStatusName()
	{
		return statusName;
	}
	std::string StockView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string StockView::GetMeasureName()
	{
		return measureName;
	}
	std::string StockView::GetWarehouseName()
	{
		return warehouseName;
	}
	std::string StockView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	std::string StockView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !productName.empty() || 0.0 != price || !currencyName.empty() || 0.0 != volume || !measureName.empty() || 0.0 != count
			|| 0.0 != sum || !sumCurrencyName.empty() || !warehouseName.empty() || !subaccountNumber.empty() || !statusName.empty()
			|| 0 != productID || 0 != currencyID || 0 != statusID || 0 != warehouseID)
		{
			return ormasDal.GetFilterForStockView(id, productName, price, currencyName, volume, measureName, count, sum, sumCurrencyName,
				warehouseName, subaccountNumber, statusName, productID, currencyID, statusID, warehouseID);
		}
		return "";
	}
}