#ifndef StockTransferLISTVIEWCLASS_H
#define StockTransferLISTVIEWCLASS_H

#include "StockTransferListClass.h"

namespace BusinessLayer
{
	class StockTransferListView : public StockTransferList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		StockTransferListView(DataLayer::stockTransferListViewCollection);
		StockTransferListView(){};
		~StockTransferListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//StockTransferListView class Accessors
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
#endif //StockTransferLISTVIEWCLASS_H