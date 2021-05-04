#ifndef ACCOUNTABLECLASS_H
#define ACCOUNTABLECLASS_H

#include "OrmasDAL.h"
#include "UserClass.h"

namespace BusinessLayer{
	class Accountable : public User
	{
	protected:
		int id = 0;
		int employeeID = 0;
		std::string information = "";
	public:
		Accountable(){};
		Accountable(int aID, int eID, std::string aInformation) :id(aID), employeeID(eID), information(aInformation) {};
		Accountable(DataLayer::accountableCollection);
		~Accountable(){};

		std::string errorMessage = "";
		//Accountable class Accessors
		int GetID();
		int GetEmployeeID();
		std::string GetInformation();


		//Accountable class Mutators
		void SetID(int);
		void SetEmployeeID(int);
		void SetInformation(std::string);


		//Create, delete, update methods
		bool CreateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,  int eID, std::string aInformation, std::string& errorMessage);
		bool UpdateAccountable(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal,  int eID, std::string aInformation, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool GetAccountableByUserID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, int eID, std::string aInfromation, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}

#endif //AccountableCLASS_H