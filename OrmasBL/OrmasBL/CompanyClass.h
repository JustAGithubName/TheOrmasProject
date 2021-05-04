#ifndef COMPANYCLASS_H
#define COMPANYCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Company
	{
		int id = 0;
		std::string name = "";
		std::string address = "";
		std::string phone = "";
		std::string comment = "";
	public:
		Company();
		Company(int cID, std::string cName, std::string cAddress, std::string cPhone, std::string cComment) :id(cID),
			name(cName), address(cAddress), phone(cPhone), comment(cComment){};
		Company(DataLayer::companiesCollection);
		~Company(){};
		
		std::string errorMessage = "";
		//Company class Accessors
		int GetID();
		std::string GetName();
		std::string GetAddress();
		std::string GetPhone();
		std::string GetComment();
		
		//Company class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetAddress(std::string);
		void SetPhone(std::string);
		void SetComment(std::string);

		// Create, delete and update company
		bool CreateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, 
			std::string cComment, std::string& errorMessage);
		bool UpdateCompany(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, 
			std::string cComment, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCompanyByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		int GetCompanyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //COMPANYCLASS_H