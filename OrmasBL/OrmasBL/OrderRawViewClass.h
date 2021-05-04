#ifndef ORDERRAWVIEWCLASS_H
#define ORDERRAWVIEWCLASS_H

#include "OrderRawClass.h"

namespace BusinessLayer
{
	class OrderRawView : public OrderRaw
	{
		std::string statusCode = "";
		std::string statusName = "";
		std::string purveyorName = "";
		std::string purveyorSurname = "";
		std::string purveyorPhone = "";
		std::string purveyorCompanyName = "";
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string employeePosition = "";
		std::string currencyName = "";
	public:
		OrderRawView(DataLayer::orderRawsViewCollection);
		OrderRawView(){};
		~OrderRawView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// OrderView class Accessors
		std::string GetStatusCode();
		std::string GetStatusName();
		std::string GetPurveyorName();
		std::string GetPurveyorSurname();
		std::string GetPurveyorPhone();
		std::string GetPurveyorCompanyName();
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetEmployeePosition();
		std::string GetCurrencyName();

		void SetStatusCode(std::string);
		void SetStatusName(std::string);
		void SetPurveyorName(std::string);
		void SetPurveyorSurname(std::string);
		void SetPurveyorPhone(std::string);
		void SetPurveyorCompanyName(std::string);
		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetEmployeePosition(std::string);
		void SetCurrencyName(std::string);

	};
}
#endif //ORDERRAWVIEWCLASS_H
