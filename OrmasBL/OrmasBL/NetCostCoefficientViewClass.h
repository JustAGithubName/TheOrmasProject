#ifndef NETCOSTCOEFFICIENTVIEWCLASS_H
#define NETCOSTCOEFFICIENTVIEWCLASS_H

#include "NetCostCoefficientClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class NetCostCoefficientView : public NetCostCoefficient
	{
		std::string productName = "";
		double volume = 0.0;
		std::string measureName = "";
		std::string currencyName = "";
	public:
		NetCostCoefficientView(DataLayer::netCostCoefficientViewCollection);
		NetCostCoefficientView(){};
		~NetCostCoefficientView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// NetCostCoefficientView class Accessors
		std::string GetProductName();
		

		void SetProductName(std::string);
		

	};
}

#endif