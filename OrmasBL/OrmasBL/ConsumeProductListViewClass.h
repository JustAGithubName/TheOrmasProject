#ifndef CONSUMEPRODUCTLISTVIEWCLASS_H
#define CONSUMEPRODUCTLISTVIEWCLASS_H

#include "ConsumeProductListClass.h"

namespace BusinessLayer
{
	class ConsumeProductListView : public ConsumeProductList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		ConsumeProductListView(DataLayer::consumeProductListViewCollection);
		ConsumeProductListView(){};
		~ConsumeProductListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//ConsumeProductListView class Accessors
		std::string GetProductName();
		double GetPrice();
		std::string GetCurrencyName();
		double GetVolume();
		std::string GetMeasureName();
		std::string GetSumCurrencyName();
		std::string GetStatusName();

		void SetProductName(std::string);
		void SetPrice(double);
		void SetCurrencyName(std::string);
		void SetVolume(double);
		void SetMeasureName(std::string);
		void SetSumCurrencyName(std::string);
		void SetStatusName(std::string);
	};
}
#endif //ConsumeProductLISTVIEWCLASS_H