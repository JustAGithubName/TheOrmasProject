#ifndef PRICEVIEWCLASS_H
#define PRICEVIEWCLASS_H

#include "PriceClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class PriceView : public Price
	{
		std::string productName = ""; 
		double volume = 0.0;
		std::string measureName = "";
		std::string currencyName = "";
	public:
		PriceView(DataLayer::pricesViewCollection);
		PriceView(){};
		~PriceView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// PriceView class Accessors
		std::string GetProductName();
		double GetVolume();
		std::string GetMeasureName();
		std::string GetCurrencyName();

		void SetProductName(std::string);
		void SetVolume(double);
		void SetMeasureName(std::string);
		void SetCurrencyName(std::string);
		
	};
}

#endif