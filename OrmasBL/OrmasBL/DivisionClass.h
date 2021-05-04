#ifndef DIVISIONCLASS_H
#define DIVISIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Division
	{
		int id = 0;
		std::string name = "";
		std::string code = "";
	public:
		Division();
		Division(int dID, std::string dName, std::string dCode) :id(dID), name(dName), code(dCode){};
		Division(DataLayer::divisionsCollection);
		~Division(){};

		std::string errorMessage = "";
		//Division class Accessors
		int GetID();
		std::string GetName();
		std::string GetCode();

		//Division class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetCode(std::string);

		// Create, delete and update Division
		bool CreateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cCode, std::string& errorMessage);
		bool UpdateDivision(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cCode, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetDivisionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cCode, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //DIVISIONCLASS_H