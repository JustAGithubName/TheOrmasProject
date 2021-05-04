#ifndef SALARYTYPECLASS_H
#define SALARYTYPECLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class SalaryType
	{
		int id = 0;
		std::string code = "";
		std::string name = "";
	public:
		SalaryType(int stID, std::string stCode, std::string stName) :id(stID), code(stCode), name(stName){};
		SalaryType(DataLayer::salaryTypeCollection);
		SalaryType(){};
		~SalaryType(){};

		//SalaryType class Accessors
		int GetID();
		std::string GetCode();
		std::string GetName();
		
		//Please implement Mutators
		void SetID(int);
		void SetCode(std::string);
		void SetName(std::string);

		//Create, delete, update methods
		bool CreateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string stCode, std::string stName, std::string& errorMessage);
		bool UpdateSalaryType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string stCode, std::string stName, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetSalaryTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int stID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		static std::map<std::string, int> GetSalaryTypesAsMap(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	private:
		void TrimStrings(std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string stCode, std::string stName, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif