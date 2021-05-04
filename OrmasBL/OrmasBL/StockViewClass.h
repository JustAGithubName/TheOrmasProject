#ifndef STOCKVIEWCLASS_H
#define STOCKVIEWCLASS_H

#include "StockClass.h"

namespace BusinessLayer
{
	class StockView : public Stock
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string warehouseName = "";
		std::string subaccountNumber = "";
		std::string statusName = "";
	public:
		StockView(DataLayer::stockViewCollection);
		StockView(){};
		~StockView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//StockView class Accessors
		std::string GetProductName();
		double GetPrice();
		std::string GetCurrencyName();
		double GetVolume();
		std::string GetMeasureName();
		std::string GetSumCurrencyName();
		std::string GetWarehouseName();
		std::string GetSubaccountNumber();
		std::string GetStatusName();

		//StockView class Settor
		void SetProductName(std::string);
		void SetPrice(double);
		void SetCurrencyName(std::string);
		void SetVolume(double);
		void SetMeasureName(std::string);
		void SetSumCurrencyName(std::string);
		void SetWarehouseName(std::string);
		void SetSubaccountNumber(std::string);
		void SetStatusName(std::string);
	};
}
#endif //StockVIEWCLASS_H