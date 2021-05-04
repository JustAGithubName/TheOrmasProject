#ifndef BranchSubaccountRELATIONCLASS_H
#define BranchSubaccountRELATIONCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"

namespace BusinessLayer{
	class BranchSubaccountRelation
	{
	protected:
		int id = 0;
		int branchID = 0;
		int subaccountID = 0;
	public:
		BranchSubaccountRelation();
		BranchSubaccountRelation(int bID, int bBranchID, int bSubaccountID) :id(bID), branchID(bBranchID),
			subaccountID(bSubaccountID){};
		BranchSubaccountRelation(DataLayer::branchSubaccountCollection);
		~BranchSubaccountRelation(){};

		std::string errorMessage = "";
		//BranchSubaccountRelation class Accessors
		int GetID();
		int GetBranchID();
		int GetSubaccountID();
		

		//BranchSubaccountRelation class Mutators
		void SetID(int);
		void SetBranchID(int);
		void SetSubaccountID(int);

		// Create, delete and update BranchSubaccountRelation
		bool CreateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bBranchID, int bSubaccountID, std::string& errorMessage);
		bool UpdateBranchSubaccountRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bBranchID, int bSubaccountID, std::string& errorMessage);

		//Generate filter string for class
		virtual std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetBranchSubaccountRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bsID, std::string& errorMessage);
		bool GetBSRelationByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		bool GetBSRelationBySubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage);
		std::vector<int> GetSubaccountIDsbyBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bBranchID, int bSubaccountID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //BranchSubaccountRELATIONCLASS_H