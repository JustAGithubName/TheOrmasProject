#ifndef NetCostVIEWCLASS_H
#define NetCostVIEWCLASS_H

#include "NetCostClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class NetCostView : public NetCost
	{
		std::string productName = "";
		double volume = 0.0;
		std::string measureName = "";
		std::string currencyName = "";
	public:
		NetCostView(DataLayer::netCostViewCollection);
		NetCostView(){};
		~NetCostView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// NetCostView class Accessors
		std::string GetProductName();
		double GetVolume();
		std::string GetMeasureName();
		std::string GetCurrencyName();

		void SetProductName(std::string);
		void SetVolume(double);
		void SetMeasureName(std::string);
		void SetCurrencyName(std::string);

	};
}

#endif