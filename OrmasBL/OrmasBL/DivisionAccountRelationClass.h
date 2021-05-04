#ifndef DIVISIONACCOUNTRELATIONCLASS_H
#define DIVISIONACCOUNTRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class DivisionAccountRelation
	{
	protected:
		int id = 0;
		int divisionID = 0;
		int accountID = 0;
		std::string code = "";
	public:
		DivisionAccountRelation();
		DivisionAccountRelation(int dID, int dDivisionID, int dAccountID, std::string dCode) :id(dID), divisionID(dDivisionID), 
			accountID(dAccountID), code(dCode){};
		DivisionAccountRelation(DataLayer::divisionAccountCollection);
		~DivisionAccountRelation(){};

		std::string errorMessage = "";
		//DivisionAccountRelation class Accessors
		int GetID();
		int GetDivisionID();
		int GetAccountID();
		std::string GetCode();

		//DivisionAccountRelation class Mutators
		void SetID(int);
		void SetDivisionID(int);
		void SetAccountID(int);
		void SetCode(std::string);

		// Create, delete and update DivisionAccountRelation
		bool CreateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dAccountID, std::string dCode, std::string& errorMessage);
		bool UpdateDivisionAccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dAccountID, std::string dCode, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetDivisionAccountRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int daID, std::string& errorMessage);
		bool GetDARelationByDivisionIDAndCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string code, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, std::string cCode, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //DIVISIONACCOUNTRELATIONCLASS_H