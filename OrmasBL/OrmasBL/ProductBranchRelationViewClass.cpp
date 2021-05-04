#include "stdafx.h"
#include "ProductBranchRelationViewClass.h"

namespace BusinessLayer{
	ProductBranchRelationView::ProductBranchRelationView(DataLayer::productBranchViewCollection wCollection)
	{
		id = std::get<0>(wCollection);
		branchName = std::get<1>(wCollection);
		branchAddress = std::get<2>(wCollection);
		productName = std::get<3>(wCollection);
		price = std::get<4>(wCollection);
		productID = std::get<5>(wCollection);
		branchID = std::get<6>(wCollection);
	}

	std::string ProductBranchRelationView::GetBranchName()
	{
		return branchName;
	}
	std::string ProductBranchRelationView::GetBranchAddress()
	{
		return branchAddress;
	}
	std::string ProductBranchRelationView::GetProductName()
	{
		return productName;
	}
	double ProductBranchRelationView::GetPrice()
	{
		return price;
	}

	void ProductBranchRelationView::SetBranchName(std::string pBranchName)
	{
		branchName = pBranchName;
	}
	void ProductBranchRelationView::SetBranchAddress(std::string pBranchAddress)
	{
		branchAddress = pBranchAddress;
	}
	void ProductBranchRelationView::SetProductName(std::string pProductName)
	{
		productName = pProductName;
	}
	void ProductBranchRelationView::SetPrice(double pPrice)
	{
		price = pPrice;
	}

	std::string ProductBranchRelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{

		if (0 != id || !branchName.empty() || !branchAddress.empty() || !productName.empty() || 0 != price || 0 != branchID || 0 != productID)
		{
			return ormasDal.GetFilterForProductBranchView(id, branchName, branchAddress, productName, price, branchID, productID);
		}
		return "";
	}
}