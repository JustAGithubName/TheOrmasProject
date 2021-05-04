#ifndef ACCOUNTTYPECLASS_H
#define ACCOUNTTYPECLASS_H

#include "OrmasDAL.h"
namespace BusinessLayer
{
	class AccountType
	{
		int id = 0;
		std::string name = "";
		int number = 0;
		std::string comment = "";
	public:
		AccountType(){};
		AccountType(int atID, std::string atName, int atNumber, std::string atComment) :id(atID),
			name(atName), number(atNumber), comment(atComment){};
		AccountType(DataLayer::accountTypeCollection);
		~AccountType(){};

		//AccountType class Accessors
		int GetID();
		std::string GetName();
		int GetNumber();
		std::string GetComment();

		//AccountType class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetNumber(int);
		void SetComment(std::string);		

		//Create, delete and update methods 
		bool CreateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string atName, int atNumber, std::string atComment, std::string& errorMessage);
		bool UpdateAccountType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string atName, int atNumber, std::string atComment, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int atID, std::string& errorMessage);
		bool GetAccountTypeByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int atNumber, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string atName, int atNumber, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //ACCOUNTTYPECLASS_H