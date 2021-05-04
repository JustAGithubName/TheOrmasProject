#include "stdafx.h"
#include "ProductionStockViewClass.h"

namespace BusinessLayer
{
	ProductionStockView::ProductionStockView(DataLayer::productionStockViewCollection sCollection)
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

	std::string ProductionStockView::GetProductName()
	{
		return productName;
	}
	double ProductionStockView::GetPrice()
	{
		return price;
	}
	std::string ProductionStockView::GetCurrencyName()
	{
		return currencyName;
	}
	double ProductionStockView::GetVolume()
	{
		return volume;
	}
	std::string ProductionStockView::GetStatusName()
	{
		return statusName;
	}
	std::string ProductionStockView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ProductionStockView::GetWarehouseName()
	{
		return warehouseName;
	}
	std::string ProductionStockView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}
	std::string ProductionStockView::GetMeasureName()
	{
		return measureName;
	}

	void ProductionStockView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ProductionStockView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ProductionStockView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ProductionStockView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ProductionStockView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ProductionStockView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ProductionStockView::SetWarehouseName(std::string pWarehouseName)
	{
		warehouseName = pWarehouseName;
	}
	void ProductionStockView::SetSubaccountNumber(std::string pSubaccountNumber)
	{
		subaccountNumber = pSubaccountNumber;
	}
	void ProductionStockView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ProductionStockView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForStockView(id, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, warehouseName, subaccountNumber, statusName, productID, statusID, currencyID, warehouseID);
		}
		return "";
	}

}