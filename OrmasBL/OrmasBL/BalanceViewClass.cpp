#include "stdafx.h"
#include "BalanceViewClass.h"

namespace BusinessLayer{
	BalanceView::BalanceView(DataLayer::balancesViewCollection bCollection)
	{
		id = std::get<0>(bCollection);
		userName = std::get<1>(bCollection);
		userSurname = std::get<2>(bCollection);
		subaccountNumber = std::get<3>(bCollection);
		currentBalance = std::get<4>(bCollection);
		currencyName = std::get<5>(bCollection);
		userID = std::get<6>(bCollection);
		subaccountID = std::get<7>(bCollection);
	}

	std::string BalanceView::GetUsername()
	{
		return userName;
	}
	std::string BalanceView::GetUserSurname()
	{
		return userSurname;
	}
	std::string BalanceView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}
	double BalanceView::GetCurrentBalance()
	{
		return currentBalance;
	}
	std::string BalanceView::GetCurrencyName()
	{
		return currencyName;
	}

	void BalanceView::SetUsername(std::string bUserName)
	{
		userName = bUserName;
	}
	void BalanceView::SetUserSurname(std::string bUserSurname)
	{
		userSurname = bUserSurname;
	}
	void BalanceView::SetSubaccountNumber(std::string bSubaccountNumber)
	{
		subaccountNumber = bSubaccountNumber;
	}
	void BalanceView::SetCurrentBalance(double bCurrentBalance)
	{
		currentBalance = bCurrentBalance;
	}
	void BalanceView::SetCurrencyName(std::string bCurrencyName)
	{
		currencyName = bCurrencyName;
	}

	std::string BalanceView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !userName.empty() || !userSurname.empty() || !subaccountNumber.empty() || 0 != currentBalance || !currencyName.empty() || 0 != userID || 0 != subaccountID)
		{
			return ormasDal.GetFilterForBalancesView(id, userName, userSurname, subaccountNumber, currentBalance, currencyName,   userID, subaccountID);
		}
		return "";
	}
}