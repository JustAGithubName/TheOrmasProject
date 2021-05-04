#ifndef CONSUMEOTHERSTOCKSLISTVIEWCLASS_H
#define CONSUMEOTHERSTOCKSLISTVIEWCLASS_H

#include "ConsumeOtherStocksListClass.h"

namespace BusinessLayer
{
	class ConsumeOtherStocksListView : public ConsumeOtherStocksList
	{
		std::string otherStocksName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		ConsumeOtherStocksListView(DataLayer::consumeOtherStocksListViewCollection);
		ConsumeOtherStocksListView(){};
		~ConsumeOtherStocksListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//ConsumeOtherStocksListView class Accessors
		std::string GetOtherStocksName();
		double GetPrice();
		std::string GetCurrencyName();
		double GetVolume();
		std::string GetMeasureName();
		std::string GetSumCurrencyName();
		std::string GetStatusName();

		void SetOtherStocksName(std::string);
		void SetPrice(double);
		void SetCurrencyName(std::string);
		void SetVolume(double);
		void SetMeasureName(std::string);
		void SetSumCurrencyName(std::string);
		void SetStatusName(std::string);
	};
}
#endif //ConsumeOtherStocksLISTVIEWCLASS_H