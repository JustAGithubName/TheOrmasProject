#include "stdafx.h"
#include "ClientViewClass.h"

namespace BusinessLayer{
	ClientView::ClientView(DataLayer::clientsViewCollection cCollection)
	{
		id = std::get<0>(cCollection);
		name = std::get<1>(cCollection);
		surname = std::get<2>(cCollection);
		phone = std::get<3>(cCollection);
		countryName = std::get<4>(cCollection);
		regionName = std::get<5>(cCollection);
		cityName = std::get<6>(cCollection);
		address = std::get<7>(cCollection);
		firm = std::get<8>(cCollection);
		firmNumber = std::get<9>(cCollection);
		roleName = std::get<10>(cCollection);
		password = std::get<11>(cCollection);
		email = std::get<12>(cCollection);
		activated = std::get<13>(cCollection);
		roleID = std::get<14>(cCollection);
		locationID = std::get<15>(cCollection);
	}

	std::string ClientView::GetCountryName()
	{
		return countryName;
	}
	std::string ClientView::GetRegionName()
	{
		return regionName;
	}
	std::string ClientView::GetCityName()
	{
		return cityName;
	}
	std::string ClientView::GetRoleName()
	{
		return roleName;
	}

	void ClientView::SetCountryName(std::string cCountryName)
	{
		countryName = cCountryName;
	}
	void ClientView::SetRegionName(std::string cRegionName)
	{
		regionName = cRegionName;
	}
	void ClientView::SetCityName(std::string cCityName)
	{
		cityName = cCityName;
	}
	void ClientView::SetRoleName(std::string cRoleName)
	{
		roleName = cRoleName;
	}

	std::string ClientView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !address.empty() || !phone.empty() || !countryName.empty() || !regionName.empty() || !cityName.empty()
			|| !firm.empty() || !firmNumber.empty() || !roleName.empty() || !password.empty() || !email.empty() || 0 != roleID || 0 != locationID)
		{
			return ormasDal.GetFilterForClientView(id, name, surname, phone, countryName, regionName, cityName, address, firm, firmNumber, roleName, password, email, 
				roleID, locationID);
		}
		return "";
	}
}