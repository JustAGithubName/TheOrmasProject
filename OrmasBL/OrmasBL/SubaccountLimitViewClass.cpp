#include "stdafx.h"
#include "SubaccountLimitViewClass.h"

namespace BusinessLayer{
	SubaccountLimitView::SubaccountLimitView(DataLayer::subaccountLimitViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		subaccountNumber = std::get<1>(sCollection);
		subaccountID = std::get<2>(sCollection);
		minValue = std::get<3>(sCollection);
		maxValue = std::get<4>(sCollection);
	}

	std::string SubaccountLimitView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	void SubaccountLimitView::SetSubaccountNumber(std::string sSubaccountNumber)
	{
		subaccountNumber = sSubaccountNumber;
	}

	std::string SubaccountLimitView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountID || 0.0 != minValue || 0.0 != maxValue)
		{
			return ormasDal.GetFilterForSubaccountLimitView(id, subaccountNumber, subaccountID, minValue, maxValue);
		}
		return "";
	}
}