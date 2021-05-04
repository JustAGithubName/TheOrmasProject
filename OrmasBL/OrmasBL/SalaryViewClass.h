#ifndef SALARYVIEWCLASS_H
#define SALARYVIEWCLASS_H

#include "SalaryClass.h"

namespace BusinessLayer{
	class SalaryView : public Salary
	{
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string currencyName = "";
		std::string salaryTypeName = "";
	public:
		SalaryView(DataLayer::salariesViewCollection);
		SalaryView(){};
		~SalaryView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// BalanceView class Accessors
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetCurrencyName();
		std::string GetSalaryTypeName();

		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetCurrencyName(std::string);
		void SetSalaryTypeName(std::string);


	};
}

#endif