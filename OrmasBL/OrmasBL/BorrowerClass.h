#ifndef BORROWERCLASS_H
#define BORROWERCLASS_H

#include "OrmasDAL.h"
#include "UserClass.h"


namespace BusinessLayer{
	class Borrower : public User
	{
	protected:
		int userID = 0;
		std::string comment = "";
	public:
		Borrower(){};
		Borrower(int uID, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone, std::string uAddress,
			int uRoleID, std::string uPassword, bool uActivated, std::string bComment) :
			User(uID, uEmail, uName, uSurname, uPhone, uAddress, uRoleID, uPassword, uActivated), comment(bComment){};
		Borrower(DataLayer::borrowersCollection);
		~Borrower(){};

		std::string errorMessage = "";
		//Borrower class Accessors
		int GetUserID();
		std::string GetComment();

		//Borrower class Mutators
		void SetUserID(int);
		void SetComment(std::string);


		//Create, delete, update methods
		bool CreateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
			std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string bComment, std::string& errorMessage);
		bool UpdateBorrower(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
			std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string bComment, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetBorrowerByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetBorrowerByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uEmail, std::string uPassword);
		bool CreateCompanyEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
	};
}

#endif //BorrowerCLASS_H