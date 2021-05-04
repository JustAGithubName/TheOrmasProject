#ifndef ORDERRAWLISTVIEWCLASS_H
#define ORDERRAWLISTVIEWCLASS_H

#include "OrderRawListClass.h"

namespace BusinessLayer
{
	class OrderRawListView : public OrderRawList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		OrderRawListView(DataLayer::orderRawListViewCollection);
		OrderRawListView(){};
		~OrderRawListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//OrderRawListView class Accessors
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
#endif //OrderRawLISTVIEWCLASS_H