#include "stdafx.h"
#include "AccessViewClass.h"

namespace BusinessLayer{
	AccessView::AccessView(DataLayer::accessesViewCollection aCollection)
	{
		id = std::get<0>(aCollection);
		roleName = std::get<1>(aCollection);
		accessItemEng = std::get<2>(aCollection);
		accessItemRu = std::get<3>(aCollection);
		division = std::get<4>(aCollection);
		roleID = std::get<5>(aCollection);
		accessItemID = std::get<6>(aCollection);
	}

	std::string AccessView::GetRoleName()
	{
		return roleName;
	}
	std::string AccessView::GetAccessItemEng()
	{
		return accessItemEng;
	}
	std::string AccessView::GetAccessItemRu()
	{
		return accessItemRu;
	}
	std::string AccessView::GetDivision()
	{
		return division;
	}

	void AccessView::SetRoleName(std::string aRoleName)
	{
		roleName = aRoleName;
	}
	void AccessView::SetAccessItemEng(std::string aAccItemEng)
	{
		accessItemEng = aAccItemEng;
	}
	void AccessView::SetAccessItemRu(std::string aAccItemRu)
	{
		accessItemRu = aAccItemRu;
	}
	void AccessView::SetDivision(std::string aDiv)
	{
		division=aDiv;
	}

	std::string AccessView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !roleName.empty() || !accessItemEng.empty() || !accessItemRu.empty() || !division.empty() || 0 != roleID || 0 != accessItemID)
		{
			return ormasDal.GetFilterForAccessView(id, roleName, accessItemEng, accessItemRu, division,   roleID, accessItemID);
		}
		return "";
	}
}