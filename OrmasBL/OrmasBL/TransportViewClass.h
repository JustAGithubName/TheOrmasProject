#ifndef TRANSPORTVIEWCLASS_H
#define TRANSPORTVIEWCLASS_H

#include "TransportClass.h"

namespace BusinessLayer
{
	class TransportView : public Transport
	{
		std::string statusCode = "";
		std::string statusName = "";
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
		std::string userPosition = "";
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string employeePosition = "";
		std::string currencyName = "";
	public:
		TransportView(DataLayer::transportsViewCollection);
		TransportView(){};
		~TransportView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// OrderView class Accessors
		std::string GetStatusCode();
		std::string GetStatusName();
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();
		std::string GetUserPosition();
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetEmployeePosition();
		std::string GetCurrencyName();

		void SetStatusCode(std::string);
		void SetStatusName(std::string);
		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetEmployeePosition(std::string);
		void SetUserName(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
		void SetUserPosition(std::string);
		void SetCurrencyName(std::string);

	};
}
#endif //TRANSPORTVIEWCLASS_H
