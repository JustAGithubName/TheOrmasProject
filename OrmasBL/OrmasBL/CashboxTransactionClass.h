#ifndef CASHBOXTRANSACTIONCLASS_H
#define CASHBOXTRANSACTIONCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class CashboxTransaction
	{
	protected:
		int id = 0;
		int cashboxID = 0;
		int cashierID = 0;
		int accountantID = 0;
		int ownerID = 0;
		int paymentID = 0;
		int withdrawalID = 0;
	public:
		CashboxTransaction();
		CashboxTransaction(int ctID, int cID, int cierID, int aID, int oID, int pID, int wID) :id(ctID), cashboxID(cID), cashierID(cierID),
			accountantID(aID), ownerID(oID), paymentID(pID), withdrawalID(wID){};
		CashboxTransaction(DataLayer::cashboxTransactionCollection);
		~CashboxTransaction(){};

		std::string errorMessage = "";
		//CashboxTransaction class Accessors
		int GetID();
		int GetCashboxID();
		int GetCashierID();
		int GetAccountantID();
		int GetOwnerID();
		int GetPaymentID();
		int GetWithdrawalID();

		//CashboxTransaction class Mutators
		void SetID(int);
		void SetCashboxID(int);
		void SetCashierID(int);
		void SetAccountantID(int);
		void SetOwnerID(int);
		void SetPaymentID(int);
		void SetWithdrawalID(int);


		// Create, delete and update CashboxTransaction
		bool CreateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cashbID, int cashiID, int accID, int ownID, int paymID, int withID, std::string& errorMessage);
		bool UpdateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cashbID, int cashiID, int accID, int ownID, int paymID, int withID, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetCashboxTransactionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage);
		bool GetCashboxTransactionByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool GetCashboxTransactionByWithdrawalID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage);
		bool GetCashboxTransactionByCashierID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cierID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif //CASHBOXTRANSACTIONCLASS_H