#ifndef BranchSubaccountRELATIONVIEW_H
#define BranchSubaccountRELATIONVIEW_H

#include "BranchSubaccountRelationClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class BranchSubaccountRelationView : public BranchSubaccountRelation
	{
		std::string branchName = "";
		std::string subaccountNumber = "";
		
	public:
		BranchSubaccountRelationView(DataLayer::branchSubaccountViewCollection);
		BranchSubaccountRelationView(){};
		~BranchSubaccountRelationView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// Chart Of Accounts View class Accessors
		std::string GetBranchName();
		std::string GetSubaccountNumber();

		void SetBranchName(std::string);
		void SetSubaccountNumber(std::string);
		
	};
}

#endif