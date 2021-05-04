#ifndef REFUNDVIEWCLASS_H
#define REFUNDVIEWCLASS_H

#include "RefundClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class RefundView : public Refund
	{
		std::string currencyName = "";
	public:
		RefundView(DataLayer::refundsViewCollection);
		RefundView(){};
		~RefundView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// RefundView class Accessors
		std::string GetCurrencyName();

		void SetCurrencyName(std::string);
	};
}

#endif