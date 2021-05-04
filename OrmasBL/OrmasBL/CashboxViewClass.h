#ifndef CASHBOXVIEWCLASS_H
#define CASHBOXVIEWCLASS_H

#include "CashboxClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class CashboxView : public Cashbox
	{
		std::string subaccountNumber = "";
	public:
		CashboxView(DataLayer::cashboxViewCollection);
		CashboxView(){};
		~CashboxView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// Cashbox View class Accessors
		std::string GetSubaccountNumber();
		void SetSubaccountNumber(std::string);
	};
}

#endif