#include "stdafx.h"
#include "PurveyorViewClass.h"

namespace BusinessLayer{
	PurveyorView::PurveyorView(DataLayer::purveyorsViewCollection pCollection)
	{
		id = std::get<0>(pCollection);
		name = std::get<1>(pCollection);
		surname = std::get<2>(pCollection);
		phone = std::get<3>(pCollection);
		countryName = std::get<4>(pCollection);
		regionName = std::get<5>(pCollection);
		cityName = std::get<6>(pCollection);
		address = std::get<7>(pCollection);
		companyName = std::get<8>(pCollection);
		roleName = std::get<9>(pCollection);
		password = std::get<10>(pCollection);
		email = std::get<11>(pCollection);
		activated = std::get<12>(pCollection);
		roleID = std::get<13>(pCollection);
		locationID = std::get<14>(pCollection);
	}

	std::string PurveyorView::GetCountryName()
	{
		return countryName;
	}
	std::string PurveyorView::GetRegionName()
	{
		return regionName;
	}
	std::string PurveyorView::GetCityName()
	{
		return cityName;
	}
	std::string PurveyorView::GetRoleName()
	{
		return roleName;
	}

	void PurveyorView::SetCountryName(std::string pCountryName)
	{
		countryName = pCountryName;
	}
	void PurveyorView::SetRegionName(std::string pRegionName)
	{
		regionName = pRegionName;
	}
	void PurveyorView::SetCityName(std::string pCityName)
	{
		cityName = pCityName;
	}
	void PurveyorView::SetRoleName(std::string pRoleName)
	{
		roleName = pRoleName;
	}

	std::string PurveyorView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !surname.empty() || !phone.empty() || !countryName.empty() || !regionName.empty() || !cityName.empty() || !address.empty()
			|| !companyName.empty() || !roleName.empty() || !password.empty() || !email.empty() || 0 != roleID || 0 != locationID)
		{
			return ormasDal.GetFilterFoPurveyorView(id, name, surname, phone, countryName, regionName, cityName, address, companyName, roleName,
				password, email, roleID, locationID);
		}
		return "";
	}

}
