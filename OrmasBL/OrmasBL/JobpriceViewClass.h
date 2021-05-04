#ifndef JOBPRICEVIEWCLASS_H
#define JOBPRICEVIEWCLASS_H

#include "JobpriceClass.h"

namespace BusinessLayer{
	class JobpriceView : public Jobprice
	{
		std::string productName = "";
		std::string currencyName = "";
		std::string measureName = "";
		std::string positionName = "";
	public:
		JobpriceView(DataLayer::jobpriceViewCollection);
		JobpriceView(){};
		~JobpriceView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// BalanceView class Accessors
		std::string GetProductName();
		std::string GetCurrencyName();
		std::string GetMeasureName();
		std::string GetPositionName();

		void SetProductName(std::string);
		void SetCurrencyName(std::string);
		void SetMeasureName(std::string);
		void SetPositionName(std::string);
	};
}

#endif //JOBPRICEVIEWCLASS_H