#ifndef STOCKHISTORYVIEWCLASS_H
#define STOCKHISTORYVIEWCLASS_H

#include "StockHistoryClass.h"

namespace BusinessLayer
{
	class StockHistoryView : public StockHistory
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
		StockHistoryView(DataLayer::stockHistoryViewCollection);
		StockHistoryView(){};
		~StockHistoryView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//StockHistoryView class Accessors
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
#endif //StockHistoryVIEWCLASS_H