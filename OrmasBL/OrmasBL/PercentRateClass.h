#ifndef PERCENTRATECLASS_H
#define PERCENTRATECLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class PercentRate{
	protected:
		int id = 0;
		double value = 0;
		std::string condition = "";
		int positionID = 0;
	public:
		PercentRate();
		PercentRate(int prID, int pValue, std::string pCondition, int pID) :id(prID), value(pValue), condition(pCondition), positionID(pID){};
		PercentRate(DataLayer::percentRateCollection);
		~PercentRate(){};

		std::string errorMessage = "";
		//PercentRate class Accessors
		int GetID();
		double GetValue();
		std::string GetCondition();
		int GetPositionID();
		
		//PercentRate class Mutators
		void SetID(int);
		void SetValue(double);
		void SetCondition(std::string);
		void SetPositionID(int);
		
		// Create, delete and update PercentRate
		bool CreatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double pValue, std::string pCondition, int pID, std::string& errorMessage);
		bool UpdatePercentRate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double pValue, std::string pCondition, int pID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetPercentRateByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double pValue, std::string pCondition, int pID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif