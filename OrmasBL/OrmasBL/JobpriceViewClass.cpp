#include "stdafx.h"
#include "JobpriceViewClass.h"

namespace BusinessLayer{
	JobpriceView::JobpriceView(DataLayer::jobpriceViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		productName = std::get<1>(sCollection);
		value = std::get<2>(sCollection);
		currencyName = std::get<3>(sCollection);
		volume = std::get<4>(sCollection);
		measureName = std::get<5>(sCollection);
		positionName = std::get<6>(sCollection);
		productID = std::get<7>(sCollection);
		currencyID = std::get<8>(sCollection);
		measureID = std::get<9>(sCollection);
		positionID = std::get<10>(sCollection);
	}

	std::string JobpriceView::GetProductName()
	{
		return productName;
	}
	std::string JobpriceView::GetCurrencyName()
	{
		return currencyName;
	}
	std::string JobpriceView::GetMeasureName()
	{
		return measureName;
	}
	std::string JobpriceView::GetPositionName()
	{
		return positionName;
	}

	void JobpriceView::SetProductName(std::string jProductName)
	{
		productName = jProductName;
	}
	void JobpriceView::SetCurrencyName(std::string jCurrencyName)
	{
		currencyName = jCurrencyName;
	}
	void JobpriceView::SetMeasureName(std::string jMeasureName)
	{
		measureName = jMeasureName;
	}
	void JobpriceView::SetPositionName(std::string jPositionName)
	{
		positionName = jPositionName;
	}
	std::string JobpriceView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !productName.empty() || 0 != value || !currencyName.empty() || 0 != volume || !measureName.empty() || !positionName.empty() 
			|| 0 != productID || 0 != currencyID || 0 != measureID || 0 != positionID)
		{
			return ormasDal.GetFilterForJobpriceView(id, productName, value, currencyName, volume, measureName, positionName, productID, currencyID,
				measureID, positionID);
		}
		return "";
	}
}