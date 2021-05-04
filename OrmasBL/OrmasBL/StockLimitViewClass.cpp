#include "stdafx.h"
#include "StockLimitViewClass.h"

namespace BusinessLayer
{
	StockLimitView::StockLimitView(DataLayer::stockLimitViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		warehouseName = std::get<1>(sCollection);
		productName = std::get<2>(sCollection);
		minValue = std::get<3>(sCollection);
		maxValue = std::get<4>(sCollection);
		stockID = std::get<5>(sCollection);
		productID = std::get<6>(sCollection);
	}

	std::string StockLimitView::GetProductName()
	{
		return productName;
	}
	std::string StockLimitView::GetWarehouseName()
	{
		return warehouseName;
	}

	void StockLimitView::SetProductName(std::string sProductName )
	{
		productName = sProductName;
	}
	void StockLimitView::SetWarehouseName(std::string sWarehouseName)
	{
		warehouseName = sWarehouseName;
	}

	std::string StockLimitView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !productName.empty() || !warehouseName.empty() || 0 != productID || 0 != minValue || 0 != maxValue || 0 != stockID)
		{
			return ormasDal.GetFilterForStockLimitView(id, warehouseName, productName, minValue, maxValue, stockID, productID);
		}
		return "";
	}
}