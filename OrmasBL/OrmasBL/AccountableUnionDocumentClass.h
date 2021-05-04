#ifndef ACCOUNTABLEUNIONDOCUMENTCLASS_H
#define ACCOUNTABLEUNIONDOCUMENTCLASS_H

#include "OrmasDAL.h"
#include "GlobalVariableClass.h"
#include "AccountableApprovementClass.h"
#include "AccountableClass.h"
#include "AccountableDocumentListClass.h"
#include "AccountableDocumentClass.h"
#include "AccountableEntryClass.h"
#include "AccountablePaymentRelationClass.h"
#include "AccountableWithdrawalRelationClass.h"
#include "AccountableTransactionClass.h"
#include "ExpenseDocumentClass.h"


namespace BusinessLayer{
	class AccountableUnionDocument
	{
	protected:
		AccountableDocument* accountableDocument;
		AccountableTransaction* accountableTransaction;
		std::vector<AccountableApprovement>* approveVec;
		std::vector<AccountableDocumentListRelation>* docListVec;
		std::vector<AccountableEntry>* entryVec;
		std::vector<AccountablePaymentRelation>* paymentVec;
		std::vector<AccountableWithdrawalRelation>* withdrawalVec;
		std::vector<ExpenseDocument>* expenseVec;
	public:
		AccountableUnionDocument(){};
		AccountableUnionDocument(AccountableDocument* aDocument, AccountableTransaction* aTransaction, std::vector<AccountableApprovement>* aApproveVec,
			std::vector<AccountableDocumentListRelation>* aDocListVec, std::vector<AccountableEntry>* aEntryVec, 
			std::vector<AccountablePaymentRelation>* aPaymentVec, std::vector<AccountableWithdrawalRelation>* aWithdrawalVec,
			std::vector<ExpenseDocument>* aExpenseVec) : accountableDocument(aDocument), accountableTransaction(aTransaction),
			approveVec(aApproveVec), docListVec(aDocListVec), entryVec(aEntryVec),
			paymentVec(aPaymentVec), withdrawalVec(aWithdrawalVec), expenseVec(aExpenseVec){};
		~AccountableUnionDocument(){};

		std::string errorMessage = "";

		//AccountableApprovement class Accessors
		AccountableDocument* GetAccountableDocument();
		AccountableTransaction* GetAccountableTransaction();
		std::vector<AccountableApprovement>* GetAccountableApprovementVector();
		std::vector<AccountableDocumentListRelation>* GetAccountableDocumentListVector();
		std::vector<AccountableEntry>* GetAccountableEntryVector();
		std::vector<AccountablePaymentRelation>* GetAccountablePaymentVector();
		std::vector<AccountableWithdrawalRelation>* GetAccountableWithdrawalVector();
		std::vector<ExpenseDocument>* GetExpenseDocumentVector();
		

		//AccountableApprovement class Mutators
		void SetAccountableDocument(AccountableDocument*);
		void SetAccountableTransaction(AccountableTransaction*);
		void SetAccountableApprovementVector(std::vector<AccountableApprovement>*);
		void SetExpenseDocumentVector(std::vector<ExpenseDocument>*);
		void SetAccountableDocumentListVector(std::vector<AccountableDocumentListRelation>*);
		void SetAccountableEntryVector(std::vector<AccountableEntry>*);
		void SetAccountablePaymentVector(std::vector<AccountablePaymentRelation>*);
		void SetAccountableWithdrawalVector(std::vector<AccountableWithdrawalRelation>*);
		

		//Create, delete, update methods
		bool CreateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, AccountableDocument* aDocument, AccountableTransaction* aTransaction, std::vector<AccountableApprovement>* aApproveVec,
			std::vector<AccountableDocumentListRelation>* aDocListVec, std::vector<AccountableEntry>* aEntryVec,
			std::vector<AccountablePaymentRelation>* aPaymentVec, std::vector<AccountableWithdrawalRelation>* aWithdrawalVec,
			std::vector<ExpenseDocument>* aExpenseVec, std::string& errorMessage);
		bool UpdateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, AccountableDocument* aDocument, AccountableTransaction* aTransaction, std::vector<AccountableApprovement>* aApproveVec,
			std::vector<AccountableDocumentListRelation>* aDocListVec, std::vector<AccountableEntry>* aEntryVec,
			std::vector<AccountablePaymentRelation>* aPaymentVec, std::vector<AccountableWithdrawalRelation>* aWithdrawalVec,
			std::vector<ExpenseDocument>* aExpenseVec, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetAccountableUnionDocumentByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage){};

		bool IsEmpty();
		void Clear();
	private:
		int previousStatusID = 0;
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int aDocumentID, std::string& errorMessage){};
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage){};
	};
}
#endif //ACCOUNTABLEUNIONDOCUMENTCLASS_H