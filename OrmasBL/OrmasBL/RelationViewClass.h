#ifndef RELATIONVIEWCLASS_H
#define RELATIONVIEWCLASS_H

#include "RelationClass.h"

namespace BusinessLayer
{
	class RelationView : public Relation
	{
		std::string employeeName = "";
		std::string employeeSurname = "";
		std::string employeePhone = "";
		std::string relationName = "";
		std::string userName = "";
		std::string userSurname = "";
		std::string userPhone = "";
	public:
		RelationView(DataLayer::relationsViewCollection);
		RelationView(){};
		~RelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// RelationView class Accessors
		std::string GetEmployeeName();
		std::string GetEmployeeSurname();
		std::string GetEmployeePhone();
		std::string GetRelationName();
		std::string GetUsername();
		std::string GetUserSurname();
		std::string GetUserPhone();

		void SetEmployeeName(std::string);
		void SetEmployeeSurname(std::string);
		void SetEmployeePhone(std::string);
		void SetRelationName(std::string);
		void SetUsername(std::string);
		void SetUserSurname(std::string);
		void SetUserPhone(std::string);
	};
}
#endif //RELATIONVIEWCLASS_H