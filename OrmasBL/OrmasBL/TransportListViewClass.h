#ifndef TRANSPORTLISTVIEWCLASS_H
#define TRANSPORTLISTVIEWCLASS_H

#include "TransportListClass.h"

namespace BusinessLayer
{
	class TransportListView : public TransportList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		TransportListView(DataLayer::transportListViewCollection);
		TransportListView(){};
		~TransportListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		//TransportListView class Accessors
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
#endif //TransportLISTVIEWCLASS_H