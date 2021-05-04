#ifndef COMPANYACCOUNTRELATIONCLASS_H
#define COMPANYACCOUNTRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class CompanyAccountRelation
	{
	protected:
		int id = 0;
		int companyID = 0;
		int accountID = 0;
	public:
		CompanyAccountRelation();
		CompanyAccountRelation(int caID, int cID, int aID) : id(caID), companyID(cID), accountID(aID){};
		CompanyAccountRelation(DataLayer::companyAccountCollection);
		~CompanyAccountRelation(){};

		std::string errorMessage = "";
		//Company-Access relation class Accessors
		int GetID();
		int GetCompanyID();
		int GetAccountID();

		//Company-Access relation class Mutators
		void SetID(int);
		void SetCompanyID(int);
		void SetAccountID(int);

		// Create, delete Company-Access relation
		bool CreateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage);
		bool UpdateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCompanyAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage);


		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCompanyAccountByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, std::string& errorMessage);
		std::vector<int> GetAllCompanyByAccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		std::vector<int> GetAllAccountByCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		int GetAccountIDByCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string parentNumber, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif