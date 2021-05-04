#ifndef PRODUCTVIEWCLASS_H
#define PRODUCTVIEWCLASS_H
#include "ProductClass.h"

namespace BusinessLayer
{
	class ProductView : public Product
	{
		std::string companyName = "";
		std::string currencyName = "";
		std::string measureName = "";
		std::string productTypeName = "";
	public:
		ProductView(DataLayer::productsViewCollection);
		ProductView(){};
		~ProductView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//UserView class Accessors
		std::string GetCompanyName();
		std::string GetMeasureName();
		std::string GetProductTypeName();
		std::string GetCurrencyName();

		void SetCompanyName(std::string);
		void SetMeasureName(std::string);
		void SetProductTypeName(std::string);
		void SetCurrencyName(std::string);


	};
}
#endif //PRODUCTVIEWCLASS_H