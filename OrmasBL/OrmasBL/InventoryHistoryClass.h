#ifndef INVENTORYHISTORYCLASS_H
#define INVENTORYHISTORYCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class InventoryHistory
	{
	protected:
		int id = 0;
		int inventoryID = 0;
		std::string comment = "";
		std::string changeDate = "";
	public:
		InventoryHistory(int iID, int invID, std::string iComment, std::string iChangeDate) : id(iID), inventoryID(invID),
			comment(iComment), changeDate(iChangeDate){};
		InventoryHistory(DataLayer::inventoryHistoryCollection);
		InventoryHistory(){};
		~InventoryHistory(){};

		//Consume Product class Accessors
		int GetID();
		int GetInventoryID();
		std::string GetComment();
		std::string GetChangeDate();
		
		//Consume Product class Mutators
		void SetID(int);
		void SetInventoryID(int);
		void SetComment(std::string);
		void SetChangeDate(std::string);


		//Create, delete, update methods
		bool CreateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int invID, std::string iComment, std::string iChangeDate, std::string& errorMessage);
		bool UpdateInventoryHistory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int invID, std::string iComment, std::string iChangeDate, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetInventoryHistoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int invID, std::string iComment, std::string iChangeDate, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //InventoryHistoryCLASS_H