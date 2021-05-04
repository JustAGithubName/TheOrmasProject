#include "stdafx.h"
#include "BranchSubaccountRelationViewClass.h"

namespace BusinessLayer{
	BranchSubaccountRelationView::BranchSubaccountRelationView(DataLayer::branchSubaccountViewCollection bCollection)
	{
		id = std::get<0>(bCollection);
		branchName = std::get<1>(bCollection);
		subaccountNumber = std::get<2>(bCollection);
		branchID = std::get<3>(bCollection);
		subaccountID = std::get<4>(bCollection);
		
	}

	std::string BranchSubaccountRelationView::GetBranchName()
	{
		return branchName;
	}

	std::string BranchSubaccountRelationView::GetSubaccountNumber()
	{
		return subaccountNumber;
	}

	void BranchSubaccountRelationView::SetBranchName(std::string bBranchName)
	{
		branchName = bBranchName;
	}

	void BranchSubaccountRelationView::SetSubaccountNumber(std::string bSubaccountNumber)
	{
		subaccountNumber = bSubaccountNumber;
	}

	std::string BranchSubaccountRelationView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != branchID || 0 != subaccountID || !branchName.empty() || !subaccountNumber.empty())
		{
			return ormasDal.GetFilterForBranchSubaccountView(id, branchName, subaccountNumber, branchID, subaccountID);
		}
		return "";
	}
}