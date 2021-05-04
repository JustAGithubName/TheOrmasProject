#include "stdafx.h"
#include "StockHistoryViewClass.h"

namespace BusinessLayer
{
	StockHistoryView::StockHistoryView(DataLayer::stockHistoryViewCollection sCollection)
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
		historyDate = std::get<16>(sCollection);
	}

	std::string StockHistoryView::GetProductName()
	{
		return productName;
	}
	double StockHistoryView::GetPrice()
	{
		return price;
	}
	std::string StockHistoryView::GetCurrencyName()
	{
		return currencyName;
	}
	double StockHistoryView::GetVolume()
	{
		return volume;
	}
	std::string StockHistoryView::GetStatusName()
	{
		return statusName;
	}
	std::string StockHistoryView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string StockHistoryView::GetMeasureName()
	{
		return measureName;
	}
	std::string StockHistoryView::GetWarehouseName()
	{
		return warehouseName;
	}
	std::string StockHistoryView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	void StockHistoryView::SetProductName(std::string pName)
	{
		productName = pName;
	}
	void StockHistoryView::SetPrice(double sPrice)
	{
		price = sPrice;
	}
	void StockHistoryView::SetCurrencyName(std::string cName)
	{
		currencyName = cName;
	}
	void StockHistoryView::SetVolume(double sVolume)
	{
		volume = sVolume;
	}
	void StockHistoryView::SetMeasureName(std::string sMeasure)
	{
		measureName = sMeasure;
	}
	void StockHistoryView::SetSumCurrencyName(std::string sCur)
	{
		sumCurrencyName = sCur;
	}
	void StockHistoryView::SetWarehouseName(std::string swarehouseName)
	{
		warehouseName = swarehouseName;
	}
	void StockHistoryView::SetSubaccountNumber(std::string subNumber)
	{
		subaccountNumber = subNumber;
	}
	void StockHistoryView::SetStatusName(std::string stName)
	{
		statusName = stName;
	}

	std::string StockHistoryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !productName.empty() || 0.0 != price || !currencyName.empty() || 0.0 != volume || !measureName.empty() || 0.0 != count
			|| 0.0 != sum || !sumCurrencyName.empty() || !warehouseName.empty() || !subaccountNumber.empty() || !statusName.empty()
			|| 0 != productID || 0 != currencyID || 0 != statusID || 0 != warehouseID)
		{
			return ormasDal.GetFilterForStockHistoryView(id, productName, price, currencyName, volume, measureName, count, sum, sumCurrencyName,
				warehouseName, subaccountNumber, statusName, productID, currencyID, statusID, warehouseID, historyDate);
		}
		return "";
	}
}