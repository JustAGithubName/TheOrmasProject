#include "stdafx.h"
#include "PayslipViewClass.h"

namespace BusinessLayer{
	PayslipView::PayslipView(DataLayer::payslipsViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		value = std::get<2>(pCollection);
		currencyName = std::get<3>(pCollection);
		salaryID = std::get<4>(pCollection);
		currencyID = std::get<5>(pCollection);
	}

	std::string PayslipView::GetCurrencyName()
	{
		return currencyName;
	}

	void PayslipView::SetCurrencyName(std::string pCurrencyName)
	{
		currencyName=pCurrencyName;
	}

	std::string PayslipView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != value || currencyName.empty() || 0 != salaryID || 0 != currencyID)
		{
			return ormasDal.GetFilterForPayslipView(id, date, value, currencyName, salaryID, currencyID);
		}
		return "";
	}
}