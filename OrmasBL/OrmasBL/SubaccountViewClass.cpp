#include "stdafx.h"
#include "SubaccountViewClass.h"

namespace BusinessLayer{
	SubaccountView::SubaccountView(DataLayer::subaccountsViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		parentSubaccountID = std::get<1>(sCollection);
		parentAccountNumber = std::get<2>(sCollection);
		number = std::get<3>(sCollection);
		startBalance = std::get<4>(sCollection);
		currentBalance = std::get<5>(sCollection);
		currencyName = std::get<6>(sCollection);
		statusName = std::get<7>(sCollection);
		currencyID = std::get<8>(sCollection);
		statusID = std::get<9>(sCollection);
		openedDate = std::get<10>(sCollection);
		closedDate = std::get<11>(sCollection);
		details = std::get<12>(sCollection);
	}

	std::string SubaccountView::GetParentAccountNumber()
	{
		return parentAccountNumber;
	}
	std::string SubaccountView::GetCurrencyName()
	{
		return currencyName;
	}
	std::string SubaccountView::GetStatusName()
	{
		return statusName;
	}

	void SubaccountView::SetParentAccountNumber(std::string sParentAccountNumber)
	{
		parentAccountNumber = sParentAccountNumber;
	}
	void SubaccountView::SetCurrencyName(std::string sCurrencyName)
	{
		currencyName = sCurrencyName;
	}
	void SubaccountView::SetStatusName(std::string sStatusName)
	{
		statusName = sStatusName;
	}

	std::string SubaccountView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != parentSubaccountID || !parentAccountNumber.empty() || !number.empty() || 0.0 != startBalance || 0.0 != currentBalance || !currencyName.empty()
			|| !statusName.empty() || 0 != currencyID || 0 != statusID 	|| !openedDate.empty() || !closedDate.empty() || !details.empty())
		{
			return ormasDal.GetFilterForSubaccountView(id, parentSubaccountID, parentAccountNumber, number, startBalance, currentBalance, statusName, currencyName,
				currencyID, statusID, openedDate, closedDate, details);
		}
		return "";
	}

}