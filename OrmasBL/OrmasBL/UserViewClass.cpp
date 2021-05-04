#include "stdafx.h"
#include "UserViewClass.h"

namespace BusinessLayer
{
	UserView::UserView(DataLayer::usersViewCollection uCollection)
	{
		id = std::get<0>(uCollection);
		email = std::get<1>(uCollection);
		name = std::get<2>(uCollection);
		surname = std::get<3>(uCollection);
		phone = std::get<4>(uCollection);
		address = std::get<5>(uCollection);
		roleName = std::get<6>(uCollection);
		password = std::get<7>(uCollection);
		activated = std::get<8>(uCollection);
		roleID = std::get<9>(uCollection);
	}

	std::string UserView::GetCountryName()
	{
		return countryName;
	}
	std::string UserView::GetCountryCode()
	{
		return countryCode;
	}
	std::string UserView::GetRegionName()
	{
		return regionName;
	}
	std::string UserView::GetCityName()
	{
		return cityName;
	}
	std::string UserView::GetRoleName()
	{
		return roleName;
	}

	void UserView::SetCountryName(std::string uCountryName)
	{
		countryName = uCountryName;
	}
	void UserView::SetCountryCode(std::string uCountryCode)
	{
		countryCode = uCountryCode;
	}
	void UserView::SetRegionName(std::string uRegionName)
	{
		regionName = uRegionName;
	}
	void UserView::SetCityName(std::string uCityName)
	{
		cityName = uCityName;
	}
	void UserView::SetRoleName(std::string uRoleName)
	{
		roleName = uRoleName;
	}

	std::string UserView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !email.empty() || !name.empty() || !surname.empty() || !phone.empty() || !address.empty() || !roleName.empty() || !password.empty()
			|| 0 != roleID)
		{
			return ormasDal.GetFilterForUserView(id, email, name, surname, phone, address, roleName, password, roleID);
		}
		return "";
	}
}