#ifndef EMPLOYEECLASS_H
#define EMPLOYEECLASS_H

#include "OrmasDAL.h"
#include "UserClass.h"
#include "DivisionEmployeeRelationClass.h"


namespace BusinessLayer{
	class Employee : public User
	{
	protected:
		int userID = 0;
		int positionID = 0;
		std::string birthDate = "";
		std::string hireDate = "";
	public:
		Employee(){};
		Employee(int uID, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone, std::string uAddress,
			int uRoleID, std::string uPassword, bool uActivated, int ePositionID, std::string eBirthDate, std::string eHireDate) :
			User(uID, uEmail, uName, uSurname, uPhone, uAddress, uRoleID, uPassword, uActivated), positionID(ePositionID), 
			birthDate(eBirthDate), hireDate(eHireDate){};
		Employee(DataLayer::employeesCollection);
		~Employee(){};

		std::string errorMessage = "";
		//Employee class Accessors
		int GetUserID();
		int GetPositionID();
		std::string GetBirthDate();
		std::string GetHireDate();
		

		//Employee class Mutators
		void SetUserID(int);
		void SetPositionID(int);
		void SetBirthDate(std::string);
		void SetHireDate(std::string);
		

		//Create, delete, update methods
		bool CreateEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
			std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, int pID, std::string eBirthDate,
			std::string eHireDate, std::string& errorMessage);
		bool UpdateEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
			std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, int pID, std::string eBirthDate,
			std::string eHireDate, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateINFilterForEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> empIDList);
		std::string GenerateINFilterForStockEmployee(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> empIDList);
		bool GetEmployeeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetEmployeeByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uEmail, std::string uPassword);
		bool IsEmpty();
		void Clear();
		bool CreateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, DivisionEmployeeRelation deRelation, std::string& errorMessage);
		bool UpdateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, DivisionEmployeeRelation deRelation, std::string& errorMessage);
		bool CreateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	private:
		void TrimStrings(std::string&, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone,
			int uRoleID, std::string eBirthDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
	};
}

#endif //EMPLOYEECLASS_H
