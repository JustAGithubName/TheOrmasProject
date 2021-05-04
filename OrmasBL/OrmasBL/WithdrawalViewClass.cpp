#include "stdafx.h"
#include "WithdrawalViewClass.h"

namespace BusinessLayer{
	WithdrawalView::WithdrawalView(DataLayer::withdrawalsViewCollection wCollection)
	{
		id = std::get<0>(wCollection);
		date = std::get<1>(wCollection);
		value = std::get<2>(wCollection);
		currencyName = std::get<3>(wCollection);
		userName = std::get<4>(wCollection);
		userSurname = std::get<5>(wCollection);
		userPhone = std::get<6>(wCollection);
		statusName = std::get<7>(wCollection);
		accountNumber = std::get<8>(wCollection);
		subaccountNumber = std::get<9>(wCollection);
		who = std::get<10>(wCollection);
		target = std::get<11>(wCollection);
		userID = std::get<12>(wCollection);
		currencyID = std::get<13>(wCollection);
		subaccountID = std::get<14>(wCollection);
		statusID = std::get<15>(wCollection);
		accountID = std::get<16>(wCollection);
		cashboxAccountID = std::get<17>(wCollection);
	}

	std::string WithdrawalView::GetUsername()
	{
		return userName;
	}
	std::string WithdrawalView::GetUserSurname()
	{
		return userSurname;
	}
	std::string WithdrawalView::GetUserPhone()
	{
		return userPhone;
	}
	std::string WithdrawalView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}
	std::string WithdrawalView::GetCurrencyName()
	{
		return currencyName;
	}
	std::string WithdrawalView::GetStatusName()
	{
		return statusName;
	}
	std::string WithdrawalView::GetAccountNumber()
	{
		return accountNumber;
	}

	void WithdrawalView::SetUsername(std::string wUserName)
	{
		userName = wUserName;
	}
	void WithdrawalView::SetUserSurname(std::string wUserSurname)
	{
		userSurname = wUserSurname;
	}
	void WithdrawalView::SetUserPhone(std::string wUserPhone)
	{
		userPhone = wUserPhone;
	}
	void WithdrawalView::SetSubaccountNumber(std::string wSubaccountNumber)
	{
		subaccountNumber = wSubaccountNumber;
	}
	void WithdrawalView::SetCurrencyName(std::string wCurrencyName)
	{
		currencyName = wCurrencyName;
	}
	void WithdrawalView::SetStatusName(std::string wStatusName)
	{
		statusName = wStatusName;
	}
	void WithdrawalView::SetAccountNumber(std::string wAccountNumber)
	{
		accountNumber = wAccountNumber;
	}

	std::string WithdrawalView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || 0 != value || !currencyName.empty() || !userName.empty() || !userSurname.empty() || !userPhone.empty() || !statusName.empty()
			|| !accountNumber.empty() || !subaccountNumber.empty() || !who.empty() || !target.empty() || 0 != userID || 0 != currencyID || 0 != subaccountID
			|| 0 != statusID || 0 != accountID  || 0 != cashboxAccountID)
		{
			return ormasDal.GetFilterForWithdrawalView(id, date, value, currencyName, userName, userSurname, userPhone, statusName, accountNumber, subaccountNumber, 
				who, target, userID, currencyID, subaccountID, statusID, accountID, cashboxAccountID);
		}
		return "";
	}
}