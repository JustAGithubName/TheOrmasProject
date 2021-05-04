#ifndef SUBACCOUNTVIEWCLASS_H
#define SUBACCOUNTVIEWCLASS_H

#include "SubaccountClass.h"

namespace BusinessLayer{
	class SubaccountView : public Subaccount
	{
		std::string parentAccountNumber = "";
		std::string currencyName = "";
		std::string statusName = "";
	public:
		SubaccountView(DataLayer::subaccountsViewCollection);
		SubaccountView(){};
		~SubaccountView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// AccountView class Accessors
		std::string GetParentAccountNumber();
		std::string GetCurrencyName();
		std::string GetStatusName();

		void SetParentAccountNumber(std::string);
		void SetCurrencyName(std::string);
		void SetStatusName(std::string);
	};
}

#endif //SUBACCOUNTVIEWCLASS_H