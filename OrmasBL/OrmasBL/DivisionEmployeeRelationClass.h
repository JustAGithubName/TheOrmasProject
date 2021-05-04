#ifndef DIVISIONEMPLOYEERELATIONCLASS_H
#define DIVISIONEMPLOYEERELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class DivisionEmployeeRelation
	{
		int id = 0;
		int divisionID = 0;
		int employeeID = 0;
		bool isContract = false;
	public:
		DivisionEmployeeRelation();
		DivisionEmployeeRelation(int dID, int dDivisionID, int dEmployeeID, bool dIsContract) :id(dID), divisionID(dDivisionID),
			employeeID(dEmployeeID), isContract(dIsContract){};
		DivisionEmployeeRelation(DataLayer::divisionEmployeeCollection);
		~DivisionEmployeeRelation(){};

		std::string errorMessage = "";
		//DivisionEmployeeRelation class Accessors
		int GetID();
		int GetDivisionID();
		int GetEmployeeID();
		bool GetIsContract();

		//DivisionEmployeeRelation class Mutators
		void SetID(int);
		void SetDivisionID(int);
		void SetEmployeeID(int);
		void SetIsContract(bool);

		// Create, delete and update DivisionEmployeeRelation
		bool CreateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dEmployeeID, bool dIsContract, std::string& errorMessage);
		bool UpdateDivisionEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dEmployeeID, bool dIsContract, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetDivisionEmployeeRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int deID, std::string& errorMessage);
		bool GetDivisionEmployeeRelationByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dDivisionID, int dAccountID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //DIVISIONEMPLOYEERELATIONCLASS_H