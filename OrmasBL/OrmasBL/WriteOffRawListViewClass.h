#ifndef WRITEOFFRAWLISTVIEWCLASS_H
#define WRITEOFFRAWLISTVIEWCLASS_H

#include "WriteOffRawListClass.h"

namespace BusinessLayer
{
	class WriteOffRawListView : public WriteOffRawList
	{
		std::string productName = "";
		double price = 0;
		std::string currencyName = "";
		double volume = 0;
		std::string measureName = "";
		std::string sumCurrencyName = "";
		std::string statusName = "";
	public:
		WriteOffRawListView(DataLayer::writeOffRawListViewCollection);
		WriteOffRawListView(){};
		~WriteOffRawListView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//WriteOffRawListView class Accessors
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
#endif //WRITEOFFRAWLISTVIEWCLASS_H