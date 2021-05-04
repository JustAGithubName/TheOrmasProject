#include "stdafx.h"
#include "PaymentViewClass.h"

namespace BusinessLayer{
	PaymentView::PaymentView(DataLayer::paymentsViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		userName = std::get<2>(pCollection);
		userSurname = std::get<3>(pCollection);
		userPhone = std::get<4>(pCollection);
		value = std::get<5>(pCollection);
		currencyName = std::get<6>(pCollection);
		target = std::get<7>(pCollection);
		accountNumber = std::get<8>(pCollection);
		subaccountNumber = std::get<9>(pCollection);
		who = std::get<10>(pCollection);
		statusName = std::get<11>(pCollection);
		userID = std::get<12>(pCollection);
		currencyID = std::get<13>(pCollection);
		statusID = std::get<14>(pCollection);
		accountID = std::get<15>(pCollection);
		subaccountID = std::get<16>(pCollection);
		cashboxAccountID = std::get<17>(pCollection);
	}

	std::string PaymentView::GetUsername()
	{
		return userName;
	}
	std::string PaymentView::GetUserSurname()
	{
		return userSurname;
	}
	std::string PaymentView::GetUserPhone()
	{
		return userPhone;
	}
	std::string PaymentView::GetCurrencyName()
	{
		return currencyName;
	}
	std::string PaymentView::GetAccountNumber()
	{
		return accountNumber;
	}
	std::string PaymentView::GetStatusName()
	{
		return statusName;
	}
	std::string PaymentView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	void PaymentView::SetUsername(std::string oUserName)
	{
		userName = oUserName;
	}
	void PaymentView::SetUserSurname(std::string oUserSurname)
	{
		userSurname = oUserSurname;
	}
	void PaymentView::SetUserPhone(std::string oUserPhone)
	{
		userPhone = oUserPhone;
	}
	void PaymentView::SetCurrencyName(std::string oCurrencyName)
	{
		currencyName = oCurrencyName;
	}
	void PaymentView::SetAccountNumber(std::string oAccountNumber)
	{
		accountNumber = oAccountNumber;
	}
	void PaymentView::SetStatusName(std::string oStatusName)
	{
		statusName = oStatusName;
	}
	void PaymentView::SetSubaccountNumber(std::string oSubaccountNumber)
	{
		subaccountNumber = oSubaccountNumber;
	}

	std::string PaymentView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || userName.empty() || userSurname.empty() || userPhone.empty() || 0 != value || currencyName.empty() || target.empty() 
			|| accountNumber.empty() || subaccountNumber.empty() || !who.empty() || !statusName.empty() || 0 != userID || 0 != currencyID || 0 != statusID
			|| 0 != accountID || 0 != subaccountID || 0 != cashboxAccountID)
		{
			return ormasDal.GetFilterForPaymentView(id, date, userName, userSurname, userPhone, value, currencyName, target, accountNumber, subaccountNumber
				, who, statusName, userID, currencyID, statusID, accountID, subaccountID, cashboxAccountID);
		}
		return "";
	}
}