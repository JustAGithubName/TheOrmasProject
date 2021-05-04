#include "stdafx.h"
#include "ShareholderViewClass.h"

namespace BusinessLayer{
	ShareholderView::ShareholderView(DataLayer::shareholdersViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		userName = std::get<1>(sCollection);
		userSurname = std::get<2>(sCollection);
		userPhone = std::get<3>(sCollection);
		userAddress = std::get<4>(sCollection);
		countOfStock = std::get<5>(sCollection);
		information = std::get<6>(sCollection);
	}

	std::string ShareholderView::GetUsername()
	{
		return userName;
	}
	std::string ShareholderView::GetUserSurname()
	{
		return userSurname;
	}
	std::string ShareholderView::GetUserPhone()
	{
		return userPhone;
	}
	std::string ShareholderView::GetUserAddress()
	{
		return userAddress;
	}

	void ShareholderView::SetUsername(std::string sUserName)
	{
		userName = sUserName;
	}
	void ShareholderView::SetUserSurname(std::string sUserSurname)
	{
		userSurname = sUserSurname;
	}
	void ShareholderView::SetUserPhone(std::string sUserPhone)
	{
		userPhone = sUserPhone;
	}
	void ShareholderView::SetUserAddress(std::string sUserAddress)
	{
		userAddress = sUserAddress;
	}

	std::string ShareholderView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !userName.empty() || !userSurname.empty() || !userPhone.empty() || !userAddress.empty() || !information.empty() || 0 != countOfStock || 0 != userID)
		{
			return ormasDal.GetFilterForShareholderView(id, userName, userSurname, userPhone, userAddress, countOfStock, information);
		}
		return "";
	}
}