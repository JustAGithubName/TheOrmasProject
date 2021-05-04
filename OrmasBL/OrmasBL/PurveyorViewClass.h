#ifndef PurveyorVIEWCLASS_H
#define PurveyorVIEWCLASS_H

#include "PurveyorClass.h"

namespace BusinessLayer{
	class PurveyorView : public Purveyor
	{
		std::string countryName = "";
		std::string regionName = "";
		std::string cityName = "";
		std::string roleName = "";
	public:
		PurveyorView(DataLayer::purveyorsViewCollection);
		PurveyorView(){};
		~PurveyorView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// PurveyorView class Accessors
		std::string GetCountryName();
		std::string GetRegionName();
		std::string GetCityName();
		std::string GetRoleName();

		void SetCountryName(std::string);
		void SetRegionName(std::string);
		void SetCityName(std::string);
		void SetRoleName(std::string);
	};
}

#endif