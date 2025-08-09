#include "stdafx.h"
#include "PriceExtensionViewClass.h"

namespace BusinessLayer{
	PriceExtensionView::PriceExtensionView(DataLayer::priceExtensionViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		productName = std::get<1>(pCollection);
		value = std::get<2>(pCollection);
		date = std::get<3>(pCollection);
		dayCount = std::get<4>(pCollection);
		locationName = std::get<5>(pCollection);
		branchName = std::get<6>(pCollection);
		expeditorName = std::get<7>(pCollection);
		clientName = std::get<8>(pCollection);
		productID = std::get<9>(pCollection);
		locationID = std::get<10>(pCollection);
		expeditorID = std::get<11>(pCollection);
		branchID = std::get<12>(pCollection);
		clientID = std::get<13>(pCollection);
	}

	std::string PriceExtensionView::GetProductName()
	{
		return productName;
	}

	std::string PriceExtensionView::GetBranchName()
	{
		return branchName;
	}

	std::string PriceExtensionView::GetLocationName()
	{
		return locationName;
	}

	std::string PriceExtensionView::GetClientName()
	{
		return clientName;
	}

	std::string PriceExtensionView::GetExpeditorName()
	{
		return expeditorName;
	}

	


	
	void PriceExtensionView::SetProductName(std::string pProductName)
	{
		productName = pProductName;
	}
	
	void PriceExtensionView::SetBranchName(std::string pBranchName)
	{
		branchName = pBranchName;
	}

	void PriceExtensionView::SetLocationName(std::string pLocationName)
	{
		locationName = pLocationName;
	}
	
	void PriceExtensionView::SetClientName(std::string pClientName)
	{
		clientName = pClientName;
	}

	void PriceExtensionView::SetExpeditorName(std::string pExpeditorName)
	{
		expeditorName = pExpeditorName;
	}


	std::string PriceExtensionView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != branchID || 0 != value || 0 != clientID || 0 != dayCount || 0 != locationID 
			|| !productName.empty() || !branchName.empty() || !locationName.empty() || !expeditorName.empty()|| !clientName.empty() || 0!=productID)
		{
			return ormasDal.GetFilterForPriceExtensionView(id, productID, productName, value, date, dayCount, locationName, branchName,
				expeditorName, clientName, locationID, expeditorID, branchID, clientID);
		}
		return "";
	}
}