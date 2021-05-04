#ifndef PAYSLIPVIEWCLASS_H
#define PAYSLIPVIEWCLASS_H

#include "PayslipClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class PayslipView : public Payslip
	{
		std::string currencyName = "";
	public:
		PayslipView(DataLayer::payslipsViewCollection);
		PayslipView(){};
		~PayslipView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// PayslipView class Accessors
		std::string GetCurrencyName();

		void SetCurrencyName(std::string);
	};
}

#endif