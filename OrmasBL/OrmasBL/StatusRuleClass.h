#ifndef STATUSRULECLASS_H
#define STATUSRULECLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class StatusRule
	{
	protected:
		int id = 0;
		std::string operation = "";
		int statusID = 0;
	public:
		StatusRule(int srID, std::string sOperation, int sID) :id(srID), operation(sOperation),
			statusID(sID){};
		StatusRule(DataLayer::statusRuleCollection);
		StatusRule(){};
		~StatusRule(){};

		//StatusRule class Accessors
		int GetID();
		std::string GetOperation();
		int GetStatusID();

		//Mutators
		void SetID(int);
		void SetOperation(std::string);
		void SetStatusID(int);

		//Create, delete, update methods
		bool CreateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, int sID,
			std::string& errorMessage);
		bool UpdateStatusRule(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, int sID,
			std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStatusRuleByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetStatusRuleByOperation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sOperation, int sID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif // STATUSRULECLASS_H