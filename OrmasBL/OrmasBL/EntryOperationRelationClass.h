#ifndef ENTRYOPERATIONRELATIONCLASS_H
#define ENTRYOPERATIONRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class EntryOperationRelation
	{
	protected:
		int id = 0;
		int entryID = 0;
		int operationID = 0;
	public:
		EntryOperationRelation();
		EntryOperationRelation(int eoID, int eID, int oID) : id(eoID), entryID(eID), operationID(oID){};
		EntryOperationRelation(DataLayer::entryOperationCollection);
		~EntryOperationRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetOperationID();
		int GetEntryID();

		//Access class Mutators
		void SetID(int);
		void SetOperationID(int);
		void SetEntryID(int);

		// Create, delete and update Access
		bool CreateEntryOperationRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteEntryOperationRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateEntryOperationRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int oID, std::string& errorMessage);


		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::vector<int> GetAllOperationByEntryID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage);
		std::vector<int> GetAllEntryByOperationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, int oID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif