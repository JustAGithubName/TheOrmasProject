#ifndef CHARTOFACCOUNTSVIEWCLASS_H
#define CHARTOFACCOUNTSVIEWCLASS_H

#include "ChartOfAccountsClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class ChartOfAccountsView : public ChartOfAccounts
	{
		std::string accountTypeName = "";
	public:
		ChartOfAccountsView(DataLayer::chartOfAccountsViewCollection);
		ChartOfAccountsView(){};
		~ChartOfAccountsView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;
		// Chart Of Accounts View class Accessors
		std::string GetAccountTypeName();
		void SetAccountTypeName(std::string);
	};
}

#endif