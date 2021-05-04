#include "stdafx.h"
#include "LocationClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer
{
	Location::Location(DataLayer::locationsCollection rCollection)
	{
		id = std::get<0>(rCollection);
		countryName = std::get<1>(rCollection);
		countryCode = std::get<2>(rCollection);
		regionName = std::get<3>(rCollection);
		cityName = std::get<4>(rCollection);
	}

	int Location::GetID()
	{
		return id;
	}

	std::string Location::GetCountryName()
	{
		return countryName;
	}

	std::string Location::GetCountryCode()
	{
		return countryCode;
	}

	std::string Location::GetRegionName()
	{
		return regionName;
	}

	std::string Location::GetCityName()
	{
		return cityName;
	}
	void Location::SetID(int rID)
	{
		id = rID;
	}
	void Location::SetCountryName(std::string lCountryName)
	{
		if (!lCountryName.empty())
			boost::trim(lCountryName);
		countryName = lCountryName;
	}
	void Location::SetCountryCode(std::string lCountryCode)
	{
		if (!lCountryCode.empty())
			boost::trim(lCountryCode);
		countryCode = lCountryCode;
	}
	void Location::SetRegionName(std::string lRegionName)
	{
		if (!lRegionName.empty())
			boost::trim(lRegionName);
		regionName = lRegionName;
	}
	void Location::SetCityName(std::string lCityName)
	{
		if (!lCityName.empty())
			boost::trim(lCityName);
		cityName = lCityName;
	}

	bool Location::CreateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string lCountryName, std::string lCountryCode,
		std::string lRegionName, std::string lCityName, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, lCountryName, lRegionName, lCityName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(lCountryName, lCountryCode, lRegionName, lCityName);
		countryName = lCountryName;
		countryCode = lCountryCode;
		regionName = lRegionName;
		cityName = lCityName;
		if (0 != id && ormasDal.CreateLocation(id, countryName, countryCode, regionName, cityName, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Location::CreateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateLocation(id, countryName, countryCode, regionName, cityName, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Location::DeleteLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteLocation(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}
	bool Location::UpdateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string lCountryName, std::string lCountryCode,
		std::string lRegionName, std::string lCityName, std::string& errorMessage)
	{
		TrimStrings(lCountryName, lCountryCode, lRegionName, lCityName);
		countryName = lCountryName;
		countryCode = lCountryCode;
		regionName = lRegionName;
		cityName = lCityName;
		if (0 != id && ormasDal.UpdateLocation(id, countryName, countryCode, regionName, cityName, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Location::UpdateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateLocation(id, countryName, countryCode, regionName, cityName, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Location::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !countryName.empty() || !countryCode.empty() || !regionName.empty() || !cityName.empty())
		{
			return ormasDal.GetFilterForLocation(id, countryName, countryCode, regionName, cityName);
		}
		return "";
	}

	bool Location::GetLocationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lID, std::string& errorMessage)
	{
		if (lID <= 0)
			return false;
		id = lID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::locationsCollection> locationVector = ormasDal.GetLocations(errorMessage, filter);
		if (0 != locationVector.size())
		{
			id = std::get<0>(locationVector.at(0));
			countryName = std::get<1>(locationVector.at(0));
			countryCode = std::get<2>(locationVector.at(0));
			regionName = std::get<3>(locationVector.at(0));
			cityName = std::get<4>(locationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find loacation with this id";
		}
		return false;
	}
	
	bool Location::IsEmpty()
	{
		if (0 == id && countryName == "" &&	countryCode == "" && regionName == "" && cityName == "")
			return true;
		return false;
	}

	void Location::Clear()
	{
		id = 0;
		countryName.clear();
		countryCode.clear();
		regionName.clear();
		cityName.clear();
	}
	
	void Location::TrimStrings(std::string& lCountryName, std::string& lCountryCode, std::string& lRegionName, std::string& lCityName)
	{
		if (!lCountryName.empty())
			boost::trim(lCountryName);
		if (!lCountryCode.empty())
			boost::trim(lCountryCode);
		if (!lRegionName.empty())
			boost::trim(lRegionName);
		if (!lCityName.empty())
			boost::trim(lCityName);
	}

	bool Location::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string lCountryName, 
		std::string lRegionName, std::string lCityName, std::string& errorMessage)
	{
		Location location;
		location.Clear();
		errorMessage.clear();
		location.SetCountryName(lCountryName);
		location.SetRegionName(lRegionName);
		location.SetCityName(lCityName);
		std::string filter = location.GenerateFilter(ormasDal);
		std::vector<DataLayer::locationsCollection> locationVector = ormasDal.GetLocations(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == locationVector.size())
		{
			return false;
		}
		errorMessage = "Location with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Location::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Location location;
		location.Clear();
		errorMessage.clear();
		location.SetCountryName(countryName);
		location.SetRegionName(regionName);
		location.SetCityName(cityName);
		std::string filter = location.GenerateFilter(ormasDal);
		std::vector<DataLayer::locationsCollection> locationVector = ormasDal.GetLocations(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == locationVector.size())
		{
			return false;
		}
		errorMessage = "Location with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}