#ifndef STATECLASS_H
#define STATECLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class State
	{
		int id = 0;
		int universalID = 0;
		int statusID = 0;
		std::string lastChange = "";
	public:
		State(int sID, int uID, int stsID, std::string sLastChange) :id(sID), universalID(uID),
			statusID(stsID), lastChange(sLastChange){};
		State(DataLayer::stateCollection);
		State(){};
		~State(){};

		//State class Accessors
		int GetID();
		int GetUniversalID();
		int GetStatusID();
		std::string GetLastChange();

		//Mutators
		void SetID(int);
		void SetUniversalID(int);
		void SetStatusID(int);
		void SetLastChange(std::string);

		//Create, delete, update methods
		bool CreateState(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateState(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteState(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateState(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int stsID, std::string sLastChange,
			std::string& errorMessage);
		bool UpdateState(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int stsID, std::string sLastChange,
			std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetStateByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		bool GetStateByUniversalID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int stsID, std::string sLastChange, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif // StateCLASS_H