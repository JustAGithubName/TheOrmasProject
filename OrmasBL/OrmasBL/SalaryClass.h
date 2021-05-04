#ifndef SALARYCLASS_H
#define SALARYCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Salary{
	protected:
		int id = 0;
		int employeeID = 0;
		double value = 0.0;
		int currencyID = 0;
		int salaryTypeID = 0;
		std::string date = "";
		bool isBonus = false;
	public:
		Salary();
		Salary(int sID,int uID, double sValue, int cID, int stID, std::string sDate, bool sIsBonus) :id(sID), employeeID(uID), value(sValue),
			currencyID(cID), salaryTypeID(stID), date(sDate), isBonus(sIsBonus){};
		Salary(DataLayer::salariesCollection);
		~Salary(){};

		std::string errorMessage = "";
		//Salary class Accessors
		int GetID();
		int GetEmployeeID();
		double GetValue();
		int GetCurrencyID();
		int GetSalaryTypeID();
		std::string GetDate();
		bool GetIsBonus();

		//Salary class Mutators
		void SetID(int);
		void SetEmployeeID(int);
		void SetValue(double);
		void SetCurrencyID(int);
		void SetSalaryTypeID(int);
		void SetDate(std::string);
		void SetIsBonus(bool);
		// Create, delete and update Salary
		bool CreateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sValue, int cID, int stID, std::string sDate, 
			bool sIsBonus,std::string& errorMessage);
		bool UpdateSalary(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sValue, int cID, int stID, std::string sDate, 
			bool sIsBonus, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSalaryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, double sValue, int cID, std::string sDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif