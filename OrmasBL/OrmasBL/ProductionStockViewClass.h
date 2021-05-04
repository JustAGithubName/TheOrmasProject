#ifndef ProductionStockVIEWCLASS_H
#define ProductionStockVIEWCLASS_H

#include "ProductionStockClass.h"

namespace BusinessLayer
{
	class ProductionStockView : public ProductionStock
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
		ProductionStockView(DataLayer::productionStockViewCollection);
		ProductionStockView(){};
		~ProductionStockView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//ProductionStockView class Accessors
		std::string GetProductName();
		double GetPrice();
		std::string GetCurrencyName();
		double GetVolume();
		std::string GetMeasureName();
		std::string GetSumCurrencyName();
		std::string GetWarehouseName();
		std::string GetSubaccountNumber();
		std::string GetStatusName();

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
#endif //ProductionStockVIEWCLASS_H