#ifndef PRODUCTIONCONSUMERAWLISTVIEWCLASS_H
#define PRODUCTIONCONSUMERAWLISTVIEWCLASS_H

#include "ProductionConsumeRawListClass.h"

namespace BusinessLayer
{
	class ProductionConsumeRawListView : public ProductionConsumeRawList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		ProductionConsumeRawListView(DataLayer::productionConsumeRawListViewCollection);
		ProductionConsumeRawListView(){};
		~ProductionConsumeRawListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//ProductionConsumeRawListView class Accessors
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
#endif //ProductionConsumeRawLISTVIEWCLASS_H