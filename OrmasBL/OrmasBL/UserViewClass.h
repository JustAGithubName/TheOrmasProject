#ifndef USERVIEWCLASS_H
#define USERVIEWCLASS_H
#include "UserClass.h"

namespace BusinessLayer
{
	class UserView : public User
	{
		std::string countryName = "";
		std::string countryCode = "";
		std::string regionName = "";
		std::string cityName = "";
		std::string roleName = "";
	public:
		UserView(DataLayer::usersViewCollection);
		UserView(){};
		~UserView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		//UserView class Accessors
		std::string GetCountryName();
		std::string GetCountryCode();
		std::string GetRegionName();
		std::string GetCityName();
		std::string GetRoleName();

		void SetCountryName(std::string);
		void SetCountryCode(std::string);
		void SetRegionName(std::string);
		void SetCityName(std::string);
		void SetRoleName(std::string);

		
	};
}

#endif //USERVIEWCLASS_H