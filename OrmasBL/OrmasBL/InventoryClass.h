#ifndef INVENTORYCLASS_H
#define INVENTORYCLASS_H

#include "OrmasDAL.h"
#include <map>

namespace BusinessLayer
{
	class Inventory
	{
	protected:
		int id = 0;
		std::string name = "";
		double cost = 0.0;
		int departmentID = 0;
		std::string location = "";
		int statusID = 0;
		std::string startOfOperationDate = "";
		std::string endOfOperationDate = "";
		std::string inventoryNumber = "";
		std::string barcodeNumber = "";
		int subaccountID = 0;
	public:
		Inventory(int iID, std::string iName, double iCost, int depID, std::string iLocation, int sID, std::string sooDate,
			std::string eooDate, std::string iNumber, std::string bNumber, int subID) : id(iID), name(iName), cost(iCost), departmentID(depID),
			location(iLocation), statusID(sID), startOfOperationDate(sooDate), endOfOperationDate(eooDate), inventoryNumber(iNumber),
			barcodeNumber(bNumber), subaccountID(subID){};
		Inventory(DataLayer::inventoryCollection);
		Inventory(){};
		~Inventory(){};

		int inventoryAccountID = 0;

		//Consume Product class Accessors
		int GetID();
		std::string GetName();
		double GetCost();
		int GetDepartmentID();
		std::string GetLocation();
		int GetStatusID();
		std::string GetStartOfOperationDate();
		std::string GetEndOfOperationDate();
		std::string GetInventoryNumber();
		std::string GetBarcodeNumber();
		int GetSubaccountID();

		//Consume Product class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetCost(double);
		void SetDepartmentID(int);
		void SetLocation(std::string);
		void SetStatusID(int);
		void SetStartOfOperationDate(std::string);
		void SetEndOfOperationDate(std::string);
		void SetInventoryNumber(std::string);
		void SetBarcodeNumber(std::string);
		void SetSubaccountID(int);

		//Create, delete, update methods
		bool CreateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string iName, double iCost, int depID, std::string iLocation, int sID, std::string sooDate,
			std::string eooDate, std::string iNumber, std::string bNumber, int subID, std::string& errorMessage);
		bool UpdateInventory(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string iName, double iCost, int depID, std::string iLocation, int sID, std::string sooDate,
			std::string eooDate, std::string iNumber, std::string bNumber, int subID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetInventoryByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int iID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
		bool CreateInventoryEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int acctbID, int purID, int accID, int debitingAccID, double value, std::string execDate, std::string& errorMessage);
		bool CreateInventoryEntryReverce(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int acctbID, int purID, int accID, int debitingAccID, double value, std::string execDate, std::string& errorMessage);
		bool CreateInventoryEntryWriteOFF(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int inventoryID, std::string& errorMessage);
		bool CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntryWriteOFF(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		bool CreateEntryCancel(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage);
		int GenerateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double currentValue, std::string& errorMessage);
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string iName, std::string iNumber, std::string bNumber, double iCost, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		std::string wstring_to_utf8(const std::wstring& str);
	};
}
#endif //InventoryCLASS_H