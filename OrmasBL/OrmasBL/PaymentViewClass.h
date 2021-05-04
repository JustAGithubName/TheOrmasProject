#ifndef PAYMENTVIEWCLASS_H
#define PAYMENTVIEWCLASS_H

#include "PaymentClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class PaymentView : public Payment
	{
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
		std::string currencyName = "";
		std::string accountNumber = "";
		std::string subaccountNumber = "";
		std::string statusName = "";
	public:
		PaymentView(DataLayer::paymentsViewCollection);
		PaymentView(){};
		~PaymentView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// PaymentView class Accessors
		std::string GetUsername();
		std::string GetCurrencyName();
		std::string GetUserSurname();
		std::string GetUserPhone();
		std::string GetAccountNumber();
		std::string GetStatusName();
		std::string GetSubaccountNumber();

		void SetUsername(std::string);
		void SetCurrencyName(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
		void SetAccountNumber(std::string);
		void SetStatusName(std::string);
		void SetSubaccountNumber(std::string);
	};
}

#endif
