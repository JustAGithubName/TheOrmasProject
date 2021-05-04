#ifndef ORDERLISTVIEWCLASS_H
#define ORDERLISTVIEWCLASS_H

#include "OrderListClass.h"

namespace BusinessLayer
{
	class OrderListView : public OrderList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		OrderListView(DataLayer::orderListViewCollection);
		OrderListView(){};
		~OrderListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//OrderListView class Accessors
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
#endif //ORDERLISTVIEWCLASS_H