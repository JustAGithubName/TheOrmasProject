#include "stdafx.h"
#include "ProductBranchRelationClass.h"


namespace BusinessLayer{
	ProductBranchRelation::ProductBranchRelation(DataLayer::productBranchCollection aeCollection)
	{
		id = std::get<0>(aeCollection);
		productID = std::get<1>(aeCollection);
		branchID = std::get<2>(aeCollection);
	}
	ProductBranchRelation::ProductBranchRelation()
	{
		id = 0;
		productID = 0;
		branchID = 0;
	}

	int ProductBranchRelation::GetID()
	{
		return id;
	}

	int ProductBranchRelation::GetProductID()
	{
		return productID;
	}

	int ProductBranchRelation::GetBranchID()
	{
		return branchID;
	}

	void ProductBranchRelation::SetID(int pbID)
	{
		id = pbID;
	}
	void ProductBranchRelation::SetProductID(int pID)
	{
		productID = pID;
	}
	void ProductBranchRelation::SetBranchID(int bID)
	{
		branchID = bID;
	}

	bool ProductBranchRelation::CreateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int bID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, bID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		branchID = bID;
		productID = pID;

		if (ormasDal.CreateProductBranch(id, productID, branchID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ProductBranchRelation::CreateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateProductBranch(id, productID, branchID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ProductBranchRelation::DeleteProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteProductBranch(productID, branchID, errorMessage))
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

	bool ProductBranchRelation::UpdateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int bID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, bID, errorMessage))
			return false;
		branchID = bID;
		productID = pID;
		if (ormasDal.UpdateProductBranch(id, productID, branchID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ProductBranchRelation::UpdateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (ormasDal.UpdateProductBranch(id, productID, branchID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string ProductBranchRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != branchID || 0 != productID)
		{
			return ormasDal.GetFilterForProductBranch(id, productID, branchID);
		}
		return "";
	}

	bool ProductBranchRelation::GetProductBranchByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pbID, std::string& errorMessage)
	{
		if (pbID <= 0)
			return false;
		id = pbID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::productBranchViewCollection> productBranchVector = ormasDal.GetProductBranch(errorMessage, filter);
		if (0 != productBranchVector.size())
		{
			id = std::get<0>(productBranchVector.at(0));
			productID = std::get<5>(productBranchVector.at(0));
			branchID = std::get<6>(productBranchVector.at(0)); 
			return true;
		}
		return false;
	}
	std::vector<int> ProductBranchRelation::GetAllBranchByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> branchIDVector;
		ProductBranchRelation aeRelation;
		aeRelation.SetProductID(pID);
		aeRelation.SetBranchID(0);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::productBranchViewCollection> ProductBranchVector = ormasDal.GetProductBranch(errorMessage, filter);
		if (0 != ProductBranchVector.size())
		{
			for each (auto item in ProductBranchVector)
			{
				branchIDVector.push_back(std::get<6>(item));
			}
		}
		return branchIDVector;
	}

	std::vector<int> ProductBranchRelation::GetAllProductByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> productIDVector;
		ProductBranchRelation aeRelation;
		aeRelation.SetBranchID(bID);
		aeRelation.SetProductID(0);
		std::string filter = aeRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::productBranchViewCollection> ProductBranchVector = ormasDal.GetProductBranch(errorMessage, filter);
		if (0 != ProductBranchVector.size())
		{
			for each (auto item in ProductBranchVector)
			{
				productIDVector.push_back(std::get<5>(item));
			}
		}
		return productIDVector;
	}


	bool ProductBranchRelation::IsEmpty()
	{
		if (0 == id && 0 == branchID && 0 == productID)
			return true;
		return false;
	}

	void ProductBranchRelation::Clear()
	{
		id = 0;
		branchID = 0;
		productID = 0;
	}

	bool ProductBranchRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int bID, std::string& errorMessage)
	{
		ProductBranchRelation apRelation;
		apRelation.Clear();
		errorMessage.clear();
		apRelation.SetBranchID(pID);
		apRelation.SetProductID(pID);
		std::string filter = apRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::productBranchViewCollection> productBranchVector = ormasDal.GetProductBranch(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productBranchVector.size())
		{
			return false;
		}
		errorMessage = "Product-Branch Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ProductBranchRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ProductBranchRelation apRelation;
		apRelation.Clear();
		errorMessage.clear();
		apRelation.SetBranchID(branchID);
		apRelation.SetProductID(productID);
		std::string filter = apRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::productBranchViewCollection> productBranchVector = ormasDal.GetProductBranch(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == productBranchVector.size())
		{
			return false;
		}
		errorMessage = "Product-Branch Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}