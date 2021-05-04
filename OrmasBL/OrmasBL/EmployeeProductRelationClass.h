#ifndef EMPLOYEEPRODUCTRELATIONCLASS_H
#define EMPLOYEEPRODUCTRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class EmployeeProductRelation
	{
	protected:
		int id = 0;
		int employeeID = 0;
		int productID = 0;
	public:
		EmployeeProductRelation();
		EmployeeProductRelation(int epID, int eID, int pID) : id(epID), employeeID(eID), productID(pID){};
		EmployeeProductRelation(DataLayer::employeeProductCollection);
		~EmployeeProductRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetEmployeeID();
		int GetProductID();

		//Access class Mutators
		void SetID(int);
		void SetEmployeeID(int);
		void SetProductID(int);

		// Create, delete and update Access
		bool CreateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int pID, std::string& errorMessage);
		bool UpdateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateEmployeeProductRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int pID, std::string& errorMessage);



		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetEmployeeProductByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int epID, std::string& errorMessage);
		std::vector<int> GetAllProductByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		std::vector<int> GetAllEmployeeByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int pID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif