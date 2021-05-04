#ifndef INVENTORYVIEWCLASS_H
#define INVENTORYVIEWCLASS_H

#include "InventoryClass.h"

namespace BusinessLayer{
	class InventoryView : public Inventory
	{
		std::string divisionName = "";
		std::string statusName = "";
	public:
		InventoryView(DataLayer::inventoryViewCollection);
		InventoryView(){};
		~InventoryView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// InventoryView class Accessors
		std::string GetDivisionName();
		std::string GetStatusName();

		void SetDivisionName(std::string);
		void SetStatusName(std::string);
	};
}

#endif //InventoryVIEWCLASS_H