#include "stdafx.h"
#include "PostingFixedAssetsViewClass.h"

namespace BusinessLayer
{
	PostingFixedAssetsView::PostingFixedAssetsView(DataLayer::postingFixedAssetsViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		surname = std::get<1>(pCollection);
		accountName = std::get<2>(pCollection);
		userID = std::get<3>(pCollection);
		subaccountID = std::get<4>(pCollection);
		accountID = std::get<5>(pCollection);
		fixedAssetsID = std::get<6>(pCollection);
		inventoryID = std::get<7>(pCollection);
	}

	std::string PostingFixedAssetsView::GetSurname()
	{
		return surname;
	}
	std::string PostingFixedAssetsView::GetAccountName()
	{
		return accountName;
	}

	void PostingFixedAssetsView::SetSurname(std::string pSurname)
	{
		surname = pSurname;
	}
	void PostingFixedAssetsView::SetAccountName(std::string pAccountName)
	{
		accountName = pAccountName;
	}

	std::string PostingFixedAssetsView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !surname.empty() || !accountName.empty() || 0 != userID || 0 != subaccountID || 0 != accountID || 0 != fixedAssetsID || 0 != inventoryID)
		{
			return ormasDal.GetFilterForPostingFixAssetView(id, surname, accountName, userID, subaccountID, accountID, fixedAssetsID, inventoryID);
		}
		return "";
	}
}

