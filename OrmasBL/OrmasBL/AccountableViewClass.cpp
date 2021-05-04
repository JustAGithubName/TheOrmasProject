#include "stdafx.h"
#include "AccountableViewClass.h"

namespace BusinessLayer{
	AccountableView::AccountableView(DataLayer::accountableViewCollection aCollection)
	{
		id = std::get<0>(aCollection);
		employeeID = std::get<1>(aCollection);
		name = std::get<2>(aCollection);
		surname = std::get<3>(aCollection);
		information = std::get<4>(aCollection);
		phone = std::get<5>(aCollection);
		address = std::get<6>(aCollection);
		roleName = std::get<7>(aCollection);
	}

	std::string AccountableView::GetRoleName()
	{
		return roleName;
	}
	

	void AccountableView::SetRoleName(std::string aRoleName)
	{
		roleName = aRoleName;
	}

	std::string AccountableView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !phone.empty() || !address.empty() || !roleName.empty() || 0 != employeeID || !information.empty())
		{
			return ormasDal.GetFilterForAccountableView(id, employeeID, name, surname, information, phone, address, roleName);
		}
		return "";
	}
}