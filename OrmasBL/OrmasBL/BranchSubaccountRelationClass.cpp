#include "stdafx.h"
#include "BranchSubaccountRelationClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	BranchSubaccountRelation::BranchSubaccountRelation(DataLayer::branchSubaccountCollection dCollection)
	{
		id = std::get<0>(dCollection);
		branchID = std::get<1>(dCollection);
		subaccountID = std::get<2>(dCollection);
		
	}
	BranchSubaccountRelation::BranchSubaccountRelation()
	{
		branchID = 0;
		subaccountID = 0;
		
	}

	int BranchSubaccountRelation::GetID()
	{
		return id;
	}

	int BranchSubaccountRelation::GetBranchID()
	{
		return branchID;
	}

	int BranchSubaccountRelation::GetSubaccountID()
	{
		return subaccountID;
	}

	void BranchSubaccountRelation::SetID(int dID)
	{
		id = dID;
	}
	void BranchSubaccountRelation::SetBranchID(int bBranchID)
	{
		branchID = bBranchID;
	}
	void BranchSubaccountRelation::SetSubaccountID(int bSubaccountID)
	{
		subaccountID = bSubaccountID;
	}
	
	bool BranchSubaccountRelation::CreateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bBranchID, int bSubaccountID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bBranchID, bSubaccountID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		branchID = bBranchID;
		subaccountID = bSubaccountID;
		if (0 != id && ormasDal.CreateBranchSubaccount(id, branchID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BranchSubaccountRelation::CreateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateBranchSubaccount(id, branchID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BranchSubaccountRelation::DeleteBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBranchSubaccount(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool BranchSubaccountRelation::UpdateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bBranchID, int bSubaccountID, std::string& errorMessage)
	{
		branchID = bBranchID;
		subaccountID = bSubaccountID;
		if (0 != id && ormasDal.UpdateBranchSubaccount(id, branchID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BranchSubaccountRelation::UpdateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateBranchSubaccount(id, branchID, subaccountID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string BranchSubaccountRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != branchID || 0 != subaccountID)
		{
			return ormasDal.GetFilterForBranchSubaccount(id, branchID, subaccountID);
		}
		return "";
	}

	

	bool BranchSubaccountRelation::GetBranchSubaccountRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int dID, std::string& errorMessage)
	{
		if (dID <= 0)
			return false;
		id = dID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::branchSubaccountViewCollection> branchSubaccountRelationVector = ormasDal.GetBranchSubaccount(errorMessage, filter);
		if (0 != branchSubaccountRelationVector.size())
		{
			id = std::get<0>(branchSubaccountRelationVector.at(0));
			branchID = std::get<3>(branchSubaccountRelationVector.at(0));
			subaccountID = std::get<4>(branchSubaccountRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find branch subaccount with this id";
		}
		return false;
	}

	bool BranchSubaccountRelation::GetBSRelationByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		branchID = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::branchSubaccountViewCollection> branchSubaccountRelationVector = ormasDal.GetBranchSubaccount(errorMessage, filter);
		if (0 != branchSubaccountRelationVector.size())
		{
			id = std::get<0>(branchSubaccountRelationVector.at(0));
			branchID = std::get<3>(branchSubaccountRelationVector.at(0));
			subaccountID = std::get<4>(branchSubaccountRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find branch subaccount relation with this id";
		}
		return false;
	}

	bool BranchSubaccountRelation::GetBSRelationBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		subaccountID = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::branchSubaccountViewCollection> branchSubaccountRelationVector = ormasDal.GetBranchSubaccount(errorMessage, filter);
		if (0 != branchSubaccountRelationVector.size())
		{
			id = std::get<0>(branchSubaccountRelationVector.at(0));
			branchID = std::get<3>(branchSubaccountRelationVector.at(0));
			subaccountID = std::get<4>(branchSubaccountRelationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find branch subaccount relation with this id";
		}
		return false;
	}

	std::vector<int> BranchSubaccountRelation::GetSubaccountIDsbyBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> subaccounIDVector;
		if (bID <= 0)
			return subaccounIDVector;
		
		BranchSubaccountRelation bsRelation;
		bsRelation.SetBranchID(bID);
		bsRelation.SetSubaccountID(0);
		std::string filter = bsRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::branchSubaccountViewCollection> branchSubaccountVector = ormasDal.GetBranchSubaccount(errorMessage, filter);
		if (0 != branchSubaccountVector.size())
		{
			for each (auto item in branchSubaccountVector)
			{
				subaccounIDVector.push_back(std::get<4>(item));
			}
		}
		return subaccounIDVector;
	}

	bool BranchSubaccountRelation::IsEmpty()
	{
		if (0 == id && 0 == branchID && 0 == subaccountID)
			return true;
		return false;
	}

	void BranchSubaccountRelation::Clear()
	{
		id = 0;
		branchID = 0;
		subaccountID = 0;
	}

	bool BranchSubaccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bBranchID, int bSubaccountID, std::string& errorMessage)
	{
		BranchSubaccountRelation branchSubaccountRelation;
		branchSubaccountRelation.Clear();
		errorMessage.clear();
		branchSubaccountRelation.SetBranchID(bBranchID);
		branchSubaccountRelation.SetSubaccountID(bSubaccountID);
		std::string filter = branchSubaccountRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::branchSubaccountViewCollection> branchSubaccountRelationVector = ormasDal.GetBranchSubaccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == branchSubaccountRelationVector.size())
		{
			return false;
		}
		errorMessage = "Branch subaccount relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool BranchSubaccountRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		BranchSubaccountRelation branchSubaccountRelation;
		branchSubaccountRelation.Clear();
		errorMessage.clear();
		branchSubaccountRelation.SetBranchID(branchID);
		branchSubaccountRelation.SetSubaccountID(subaccountID);
		std::string filter = branchSubaccountRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::branchSubaccountViewCollection> branchSubaccountRelationVector = ormasDal.GetBranchSubaccount(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == branchSubaccountRelationVector.size())
		{
			return false;
		}
		errorMessage = "Branch subaccount relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}
