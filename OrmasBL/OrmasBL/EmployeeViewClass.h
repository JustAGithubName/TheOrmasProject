#ifndef EMPLOYEEVIEWCLASS_H
#define EMPLOYEEVIEWCLASS_H

#include "EmployeeClass.h"

namespace BusinessLayer{
	class EmployeeView : public Employee
	{
		std::string positionName = "";
		std::string roleName = "";
		int divisionEmployeeID = 0;
		int divisionID = 0;
		bool isContract = false;
	public:
		EmployeeView(DataLayer::employeesViewCollection);
		EmployeeView(){};
		~EmployeeView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// EmployeeView class Accessors
		std::string GetPositionName();
		std::string GetRoleName();
		int GetDivisionEmployeeID();
		int GetDivisionID();
		bool GetIsContract();

		void SetPositionName(std::string);
		void SetRoleName(std::string);
		void SetDivisionEmployeeID(int);
		void SetDivisionID(int);
		
	};
}

#endif //EMPLOYEEVIEWCLASS_H