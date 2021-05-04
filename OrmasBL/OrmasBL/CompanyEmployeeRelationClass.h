#ifndef COMPANYEMPLOYEERELATIONCLASS_H
#define COMPANYEMPLOYEERELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class CompanyEmployeeRelation
	{
	protected:
		int id = 0;
		int companyID = 0;
		int employeeID = 0;
		int branchID = 0;
	public:
		CompanyEmployeeRelation();
		CompanyEmployeeRelation(int ceID, int cID, int eID, int bID) :id(ceID), companyID(cID), employeeID(eID), branchID(bID){};
		CompanyEmployeeRelation(DataLayer::companyEmployeeCollection);
		~CompanyEmployeeRelation(){};

		std::string errorMessage = "";
		//Company-Employee relation class Accessors
		int GetID();
		int GetCompanyID();
		int GetEmployeeID();
		int GetBranchID();

		//Company-Employee relation  class Mutators
		void SetID(int);
		void SetCompanyID(int);
		void SetEmployeeID(int);
		void SetBranchID(int);

		// Create, delete  Company-Employee relation
		bool CreateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, int bID, std::string& errorMessage);
		bool UpdateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, int bID, std::string& errorMessage);


		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCompanyEmployeeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, std::string& errorMessage);
		int GetCompanyByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		int GetBranchByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		int GetEmployeeByCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		std::vector<int> GetAllEmployeeIDByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif