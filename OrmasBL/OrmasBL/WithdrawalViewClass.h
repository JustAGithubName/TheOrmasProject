#ifndef WITHDRAWALVIEWCLASS_H
#define WITHDRAWALVIEWCLASS_H

#include "WithdrawalClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class WithdrawalView : public Withdrawal
	{
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
		std::string subaccountNumber = "";
		std::string currencyName = "";
		std::string statusName = "";
		std::string accountNumber = "";
	public:
		WithdrawalView(DataLayer::withdrawalsViewCollection);
		WithdrawalView(){};
		~WithdrawalView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// WithdrawalView class Accessors
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();
		std::string GetCurrencyName();
		std::string GetStatusName();
		std::string GetAccountNumber();
		std::string GetSubaccountNumber();

		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
		void SetCurrencyName(std::string);
		void SetStatusName(std::string);
		void SetAccountNumber(std::string);
		void SetSubaccountNumber(std::string);
	};
}

#endif