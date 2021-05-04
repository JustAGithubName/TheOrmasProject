#ifndef WAREHOUSEVIEWCLASS_H
#define WAREHOUSEVIEWCLASS_H

#include "WarehouseClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class WarehouseView : public Warehouse
	{
		std::string warehouseTypeName = "";
		std::string subaccountNumber = "";
	public:
		WarehouseView(DataLayer::warehouseViewCollection);
		WarehouseView(){};
		~WarehouseView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		// Warehouse View class Accessors
		std::string GetWarehouseTypeName();
		std::string GetSubaccountNumber();

		void SetWarehouseTypeName(std::string);
		void SetSubaccountNumber(std::string);
	};
}

#endif