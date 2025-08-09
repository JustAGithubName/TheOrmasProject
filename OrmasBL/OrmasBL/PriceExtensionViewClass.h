#ifndef PRICEEXTENSIONVIEWCLASS_H
#define PRICEEXTENSIONVIEWCLASS_H

#include "PriceExtensionClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class PriceExtensionView : public PriceExtension
	{
		std::string productName = "";
		std::string branchName = "";
		std::string locationName = "";
		std::string clientName = "";
		std::string expeditorName = "";

	public:
		PriceExtensionView(DataLayer::priceExtensionViewCollection);
		PriceExtensionView(){};
		~PriceExtensionView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// PriceExtensionView class Accessors
		std::string GetProductName();
		std::string GetBranchName();
		std::string GetLocationName();
		std::string GetExpeditorName();
		std::string GetClientName();
		

		void SetProductName(std::string);
		void SetBranchName(std::string);
		void SetLocationName(std::string);
		void SetExpeditorName(std::string);
		void SetClientName(std::string);
		
		
	};
}

#endif