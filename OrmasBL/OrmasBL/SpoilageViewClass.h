#ifndef SPOILAGEVIEWCLASS_H
#define SPOILAGEVIEWCLASS_H

#include "SpoilageClass.h"

namespace BusinessLayer
{
	class SpoilageView : public Spoilage
	{
		std::string statusName = "";
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string employeePosition = "";
		std::string currencyName = "";
	public:
		SpoilageView(DataLayer::spoilageViewCollection);
		SpoilageView(){};
		~SpoilageView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// SpoilageView class Accessors
		std::string GetStatusName();
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetEmployeePosition();
		std::string GetCurrencyName();

		
		void SetStatusName(std::string);
		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetEmployeePosition(std::string);
		void SetCurrencyName(std::string);

	};
}
#endif //SPOILAGEVIEWCLASS_H
