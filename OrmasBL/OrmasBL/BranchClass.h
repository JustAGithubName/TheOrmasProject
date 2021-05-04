#ifndef BRANCHCLASS_H
#define BRANCHCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Branch
	{
		int id = 0;
		std::string name = "";
		std::string address = "";
		std::string phone = "";
		std::string comment = "";
	public:
		Branch();
		Branch(int cID, std::string cName, std::string cAddress, std::string cPhone, std::string cComment) :id(cID),
			name(cName), address(cAddress), phone(cPhone), comment(cComment){};
		Branch(DataLayer::branchesCollection);
		~Branch(){};

		std::string errorMessage = "";
		//Branch class Accessors
		int GetID();
		std::string GetName();
		std::string GetAddress();
		std::string GetPhone();
		std::string GetComment();

		//Branch class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetAddress(std::string);
		void SetPhone(std::string);
		void SetComment(std::string);

		// Create, delete and update Branch
		bool CreateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone,
			std::string cComment, std::string& errorMessage);
		bool UpdateBranch(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone,
			std::string cComment, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetBranchByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		int GetBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&, std::string&, std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //BranchCLASS_H