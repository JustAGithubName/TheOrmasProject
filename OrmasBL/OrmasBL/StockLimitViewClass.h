#ifndef STOCKLIMITVIEWCLASS_H
#define STOCKLIMITVIEWCLASS_H

#include "StockLimitClass.h"

namespace BusinessLayer
{
	class StockLimitView : public StockLimit
	{
		std::string productName = "";
		std::string warehouseName = "";
	public:
		StockLimitView(DataLayer::stockLimitViewCollection);
		StockLimitView(){};
		~StockLimitView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		//StockLimitView class Accessors
		std::string GetProductName();
		std::string GetWarehouseName();

		void SetProductName(std::string);
		void SetWarehouseName(std::string);
	};
}
#endif //StockLimitVIEWCLASS_H