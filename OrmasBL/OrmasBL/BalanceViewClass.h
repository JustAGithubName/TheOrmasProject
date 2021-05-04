#ifndef BALANCEVIEWCLASS_H
#define BALANCEVIEWCLASS_H

#include "BalanceClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class BalanceView : public Balance
	{
		std::string userName = "";
		std::string userSurname = "";
		std::string subaccountNumber = "";
		double currentBalance = 0.0;
		std::string currencyName = "";
	public:
		BalanceView(DataLayer::balancesViewCollection);
		BalanceView(){};
		~BalanceView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// BalanceView class Accessors
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetSubaccountNumber();
		double GetCurrentBalance();
		std::string GetCurrencyName();

		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetSubaccountNumber(std::string);
		void SetCurrentBalance(double);
		void SetCurrencyName(std::string);
	};
}
#endif //BALANCEVIEWCLASS_H