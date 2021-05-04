#ifndef WRITEOFFLISTVIEWCLASS_H
#define WRITEOFFLISTVIEWCLASS_H

#include "WriteOffListClass.h"

namespace BusinessLayer
{
	class WriteOffListView : public WriteOffList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		WriteOffListView(DataLayer::writeOffListViewCollection);
		WriteOffListView(){};
		~WriteOffListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//WriteOffListView class Accessors
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
#endif //WRITEOFFLISTVIEWCLASS_H