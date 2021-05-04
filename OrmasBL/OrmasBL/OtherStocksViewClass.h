#ifndef OTHERSTOCKSVIEWCLASS_H
#define OTHERSTOCKSVIEWCLASS_H
#include "OtherStocksClass.h"

namespace BusinessLayer
{
	class OtherStocksView : public OtherStocks
	{
		std::string companyName = "";
		std::string currencyName = "";
		std::string measureName = "";
		std::string otherStocksTypeName = "";
	public:
		OtherStocksView(DataLayer::otherStocksViewCollection);
		OtherStocksView(){};
		~OtherStocksView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//UserView class Accessors
		std::string GetCompanyName();
		std::string GetMeasureName();
		std::string GetCurrencyName();
		std::string GetOtherStocksTypeName();

		void SetCompanyName(std::string);
		void SetMeasureName(std::string);
		void SetCurrencyName(std::string);
		void SetOtherStocksTypeName(std::string);
	};
}
#endif //OtherStocksVIEWCLASS_H