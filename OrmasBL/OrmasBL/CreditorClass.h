#ifndef CREDITORCLASS_H
#define CREDITORCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Creditor{
	protected:
		int id = 0;
		std::string name = "";
		std::string address = "";
		std::string phone = "";
		int bankID = 0;
		int userID = 0;;
	public:
		Creditor();
		Creditor(int cID, std::string cName, std::string cAddress, std::string cPhone, int bID, int uID) :
			id(cID), name(cName), address(cAddress), phone(cPhone), bankID(bID), userID(uID){};
		Creditor(DataLayer::creditorsCollection);
		~Creditor(){};

		std::string errorMessage = "";

		//Creditor class Accessors
		int GetID();
		std::string GetName();
		std::string GetAddress();
		std::string GetPhone();
		int GetBankID();
		int GetUserID();

		//Creditor class Mutators
		void SetID(int);
		void SetName(std::string);
		void SetAddress(std::string);
		void SetPhone(std::string);
		void SetBankID(int);
		void SetUserID(int);

		// Create, delete and update Creditor
		bool CreateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, int bID, int uID, std::string& errorMessage);
		bool UpdateCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string cName, std::string cAddress, std::string cPhone, int bID, int uID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		std::string GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> creditorIDList);
		bool GetCreditorByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int uID, std::string& errorMessage){};
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage){};
		void TrimStrings(std::string&, std::string&, std::string&);
		bool CreateBalanceForCreditor(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //CreditorCLASS_H