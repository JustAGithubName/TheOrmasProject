#ifndef CAHSBOXEMPLOYEERELATIONCLASS_H
#define CAHSBOXEMPLOYEERELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class CashboxEmployeeRelation
	{
	protected:
		int id = 0;
		int cashboxID = 0;
		int employeeID = 0;
	public:
		CashboxEmployeeRelation();
		CashboxEmployeeRelation(int ceID, int cID, int aID) :id(ceID), cashboxID(cID), employeeID(aID){};
		CashboxEmployeeRelation(DataLayer::cashboxEmployeeCollection);
		~CashboxEmployeeRelation(){};

		std::string errorMessage = "";
		//Cashbox-Employee relation class Accessors
		int GetID();
		int GetCashboxID();
		int GetEmployeeID();

		//Cashbox-Employee relation  class Mutators
		void SetID(int);
		void SetCashboxID(int);
		void SetEmployeeID(int);

		// Create, delete  Cashbox-Employee relation
		bool CreateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, std::string& errorMessage);
		bool UpdateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCashboxEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int eID, std::string& errorMessage);


		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCashboxEmployeeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int id, std::string& errorMessage);
		bool GetCashboxEmployeeByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		int GetCashboxIDByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		int GetEmployeeIDByCashboxID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, int aID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif