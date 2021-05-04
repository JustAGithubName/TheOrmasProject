#ifndef CONSUMERAWLISTVIEWCLASS_H
#define CONSUMERAWLISTVIEWCLASS_H

#include "ConsumeRawListClass.h"

namespace BusinessLayer
{
	class ConsumeRawListView : public ConsumeRawList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		ConsumeRawListView(DataLayer::consumeRawListViewCollection);
		ConsumeRawListView(){};
		~ConsumeRawListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//ConsumeRawListView class Accessors
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
#endif //ConsumeRawLISTVIEWCLASS_H