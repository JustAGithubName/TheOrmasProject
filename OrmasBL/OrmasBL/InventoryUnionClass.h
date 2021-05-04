#ifndef InventoryUNIONCLASS_H
#define InventoryUNIONCLASS_H

#include "OrmasDAL.h"
#include <map>
#include "InventoryClass.h"
#include "InventoryHistoryClass.h"
#include "PostingFixedAssetsClass.h"

namespace BusinessLayer
{
	class InventoryUnion
	{
	protected:
		Inventory *inventory = new Inventory();
		PostingFixedAssets *postingFixedAssets = new PostingFixedAssets();
	public:
		InventoryUnion(Inventory* inv, PostingFixedAssets* pFxAssets) :
			inventory(inv), postingFixedAssets(pFxAssets){};
		InventoryUnion(DataLayer::inventoryUnionViewCollection);
		InventoryUnion(){};
		~InventoryUnion(){};
		int inventoryAccountID = 0;
		double subaccValue = 0;

		bool isNewInventory = false;
		int purveyorID = 0;
		int accountableID = 0;
		int accountID = 0;
		//InventoryUnion class Accessors
		Inventory* GetInventory();
		PostingFixedAssets* GetPostingFixedAssets();

		//InventoryUnion class Mutators
		void SetInventory(Inventory*);
		void SetPostingFixedAssets(PostingFixedAssets*);

		//Create, delete, update methods
		bool CreateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Inventory* inv, PostingFixedAssets* pFxAssets, std::string& errorMessage);
		bool UpdateInventoryUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Inventory* inv, PostingFixedAssets* pFxAssets, std::string& errorMessage);

		//Generate filter string for class
		bool IsEmpty();
		void Clear();
		std::string GenerateInventoryNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int divID);
	private:
		std::string GenerateInvRawNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string& errorMessage);
		int previousStatusID = 0;
	};
}
#endif //InventoryUnionCLASS_H