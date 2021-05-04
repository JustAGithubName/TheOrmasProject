#include "stdafx.h"
#include "InventoryViewClass.h"

namespace BusinessLayer{
	InventoryView::InventoryView(DataLayer::inventoryViewCollection iCollection)
	{
		id = std::get<0>(iCollection);
		name = std::get<1>(iCollection);
		cost = std::get<2>(iCollection);
		divisionName = std::get<5>(iCollection);
		statusName = std::get<6>(iCollection);
		departmentID = std::get<11>(iCollection);
		location = std::get<7>(iCollection);
		statusID = std::get<10>(iCollection);
		startOfOperationDate = std::get<8>(iCollection);
		endOfOperationDate = std::get<9>(iCollection);
		inventoryNumber = std::get<3>(iCollection);
		barcodeNumber = std::get<4>(iCollection);
		subaccountID = std::get<12>(iCollection);
	}

	std::string InventoryView::GetDivisionName()
	{
		return divisionName;
	}

	std::string InventoryView::GetStatusName()
	{
		return statusName;
	}

	void InventoryView::SetDivisionName(std::string iDivisionName)
	{
		divisionName = iDivisionName;
	}

	void InventoryView::SetStatusName(std::string iStatusName)
	{
		statusName = iStatusName;
	}


	std::string InventoryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || 0 != cost || 0 != departmentID || !location.empty() || 0 != statusID || !startOfOperationDate.empty()
			|| !endOfOperationDate.empty() || !inventoryNumber.empty() || !barcodeNumber.empty() || !divisionName.empty() || !statusName.empty() || 0 != subaccountID)
		{
			return ormasDal.GetFilterForInvnentoryView(id, name, cost, inventoryNumber, barcodeNumber, divisionName, statusName, location, startOfOperationDate,
				endOfOperationDate, statusID, departmentID, subaccountID);
		}
		return "";
	}

}