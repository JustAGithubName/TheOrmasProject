#include "stdafx.h"
#include "OtherStocksViewClass.h"

namespace BusinessLayer
{
	OtherStocksView::OtherStocksView(DataLayer::otherStocksViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		name = std::get<1>(pCollection);
		price = std::get<2>(pCollection);
		currencyName = std::get<3>(pCollection);
		volume = std::get<4>(pCollection);
		measureName = std::get<5>(pCollection);
		companyName = std::get<6>(pCollection);
		otherStocksTypeName = std::get<7>(pCollection);
		companyID = std::get<8>(pCollection);
		measureID = std::get<9>(pCollection);
		currencyID = std::get<10>(pCollection);
		otherStocksTypeID = std::get<10>(pCollection);
	}

	std::string OtherStocksView::GetCompanyName()
	{
		return companyName;
	}
	std::string OtherStocksView::GetMeasureName()
	{
		return measureName;
	}
	std::string OtherStocksView::GetCurrencyName()
	{
		return currencyName;
	}
	std::string OtherStocksView::GetOtherStocksTypeName()
	{
		return otherStocksTypeName;
	}

	void OtherStocksView::SetCompanyName(std::string oCompanyName)
	{
		companyName = oCompanyName;
	}
	void OtherStocksView::SetMeasureName(std::string oMeasureName)
	{
		measureName = oMeasureName;
	}
	void OtherStocksView::SetCurrencyName(std::string oCurrencyName)
	{
		currencyName = oCurrencyName;
	}
	void OtherStocksView::SetOtherStocksTypeName(std::string oOtherStocksTypeName)
	{
		otherStocksTypeName = oOtherStocksTypeName;
	}

	std::string OtherStocksView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty() || !companyName.empty() 
			|| 0 != companyID || 0 != measureID || 0 != currencyID || 0 != otherStocksTypeID)
		{
			return ormasDal.GetFilterForOthStView(id, name, price, currencyName, volume, measureName, companyName, otherStocksTypeName, companyID, measureID, currencyID, otherStocksTypeID);
		}
		return "";
	}
}