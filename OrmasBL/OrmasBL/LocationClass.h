#ifndef LOCATIONCLASS_H
#define LOCATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer
{
	class Location
	{
		int id = 0;
		std::string countryName = "";
		std::string countryCode = "";
		std::string regionName = "";
		std::string cityName = "";
	public:
		Location(int lID, std::string lCountryName, std::string lCountryCode, std::string lRegionName, std::string lCityName) 
			:id(lID), countryName(lCountryName), countryCode(lCountryCode), regionName(lRegionName), cityName(lCityName){};
		Location(DataLayer::locationsCollection);
		Location(){};
		~Location(){};
		
		//Location class Accessors
		int GetID();
		std::string GetCountryName();
		std::string GetCountryCode();
		std::string GetRegionName();
		std::string GetCityName();

		//Please implement Mutators
		void SetID(int);
		void SetCountryName(std::string);
		void SetCountryCode(std::string);
		void SetRegionName(std::string);
		void SetCityName(std::string);
		
		//Create, delete, update methods
		bool CreateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string lCountryName, std::string lCountryCode,
			std::string lRegionName, std::string lCityName, std::string& errorMessage);
		bool UpdateLocation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string lCountryName, std::string lCountryCode,
			std::string lRegionName, std::string lCityName, std::string& errorMessage);
		
		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetLocationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&, std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string lCountryName, 
			std::string lRegionName, std::string lCityName, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif // LOCATIONCLASS_H