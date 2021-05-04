#ifndef EMPLOYEEPRODUCTRELATIONVIEWCLASS_H
#define EMPLOYEEPRODUCTRELATIONVIEWCLASS_H

#include "EmployeeProductRelationClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class EmployeeProductRelationView : public EmployeeProductRelation
	{
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
		std::string productName = "";
		double price = 0;
	public:
		EmployeeProductRelationView(DataLayer::employeeProductViewCollection);
		EmployeeProductRelationView(){};
		~EmployeeProductRelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// EmployeeProductRelationView class EmployeeProductRelationors
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();
		std::string GetProductName();
		double GetPrice();

		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
		void SetProductName(std::string);
		void SetPrice(double);
	};
}
#endif