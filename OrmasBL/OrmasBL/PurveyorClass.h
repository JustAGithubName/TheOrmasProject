#ifndef PurveyorCLASS_H
#define PurveyorCLASS_H

#include "OrmasDAL.h"
#include "UserClass.h"

namespace BusinessLayer{
	class Purveyor : public User
	{
	protected:
		int userID = 0;
		std::string companyName = "";
		int locationID = 0;
	public:
		Purveyor(){};
		Purveyor(int uID, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone, std::string uAddress,
			int uRoleID, std::string uPassword, bool uActivated, std::string pCompanyName, int lID) :
			User(uID, uEmail, uName, uSurname, uPhone, uAddress, uRoleID, uPassword, uActivated), companyName(pCompanyName),
			locationID(lID) {};
		Purveyor(DataLayer::purveyorsCollection);
		~Purveyor(){};

		std::string errorMessage = "";
		//Purveyor class Accessors
		int GetUserID();
		std::string GetCompanyName();
		int GetLocationID();

		//Purveyor class Mutators
		void SetUserID(int);
		void SetCompanyName(std::string);
		void SetLocationID(int);

		//Create, delete, update methods
		bool CreatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
			std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string pCompanyName,
			int lID, std::string& errorMessage);
		bool UpdatePurveyor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uEmail, std::string uName, std::string uSurname, std::string uPhone,
			std::string uAddress, int uRoleID, std::string uPassword, bool uActivated, std::string pCompanyName,
			int lID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetPurveyorByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool GetPurveyorByCredentials(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uPhone, std::string uEmail, std::string uPassword);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string uName, std::string uSurname, std::string uPhone,
			int uRoleID, std::string pCompanyName, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string GetCurrentPhone(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
	};
}
#endif
