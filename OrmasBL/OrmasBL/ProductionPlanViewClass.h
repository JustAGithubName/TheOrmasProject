#ifndef PRODUCTIONPLANVIEWCLASS_H
#define PRODUCTIONPLANVIEWCLASS_H

#include "ProductionPlanClass.h"

namespace BusinessLayer
{
	class ProductionPlanView : public ProductionPlan
	{
		std::string statusName = "";
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string employeePosition = "";
		std::string currencyName = "";
	public:
		ProductionPlanView(DataLayer::productionPlanViewCollection);
		ProductionPlanView(){};
		~ProductionPlanView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// ProductionPlanView class Accessors
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
#endif //ProductionPlanVIEWCLASS_H
