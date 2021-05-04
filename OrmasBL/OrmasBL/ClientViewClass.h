#ifndef CLIENTVIEWCLASS_H
#define CLIENTVIEWCLASS_H

#include "ClientClass.h"

namespace BusinessLayer{
	class ClientView : public Client
	{
		std::string countryName = "";
		std::string regionName = "";
		std::string cityName = "";
		std::string roleName = "";
	public:
		ClientView(DataLayer::clientsViewCollection);
		ClientView(){};
		~ClientView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// ClientView class Accessors
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