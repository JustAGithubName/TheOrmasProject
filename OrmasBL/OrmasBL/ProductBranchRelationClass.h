#ifndef ProductBranchRELATIONCLASS_H
#define ProductBranchRELATIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class ProductBranchRelation
	{
	protected:
		int id = 0;
		int productID = 0;
		int branchID = 0;
	public:
		ProductBranchRelation();
		ProductBranchRelation(int pbID, int pID, int bID) : id(pbID), productID(pID), branchID(bID){};
		ProductBranchRelation(DataLayer::productBranchCollection);
		~ProductBranchRelation(){};

		std::string errorMessage = "";
		//Access class Accessors
		int GetID();
		int GetBranchID();
		int GetProductID();

		//Access class Mutators
		void SetID(int);
		void SetBranchID(int);
		void SetProductID(int);

		// Create, delete and update Access
		bool CreateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int bID, std::string& errorMessage);
		bool UpdateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateProductBranchRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int bID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetProductBranchByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pbID, std::string& errorMessage);
		std::vector<int> GetAllProductByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		std::vector<int> GetAllBranchByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int bID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif