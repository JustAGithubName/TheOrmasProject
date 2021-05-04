#ifndef FULLEXTENDEDENTRYVIEWCLASS_H
#define FULLEXTENDEDENTRYVIEWCLASS_H

#include "EntryClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class FullExtendedEntryView : public Entry
	{
		int operationID = 0;
		int subaccountID = 0;
		std::string debitingAccountNumber = "";
		std::string creditingAccountNumber = "";
		int consumeOtherStocksID = 0;
		int consumeRawID = 0;
		int consumeProductID = 0;
		int fixedAssetsID = 0;
		int fixedAssetsOperID = 0;
		int inventoryID = 0;
		int orderID = 0;
		int orderRawID = 0;
		int paymentID = 0;
		int payslipID = 0;
		int productionConRawID = 0;
		int receiptProductID = 0;
		int receiptOtherStocksID = 0;
		int returnID = 0;
		int spoilageID = 0;
		int stockTransferID = 0;
		int withdrawalID = 0;
		int writeOffID = 0;
		int writeOffRawID = 0;
		int productID = 0;
		int otherStocksID = 0;
		int accDocumentID = 0;
	public:
		FullExtendedEntryView(DataLayer::entriesFullJoinViewCollection);
		FullExtendedEntryView(){};
		~FullExtendedEntryView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// EntryView class Accessors
		std::string GetDebitingAccountNumber();
		std::string GetCreditingAccountNumber();
		int GetOperationID();
		int GetSubaccountID();
		int GetConsumeRawID();
		int GetConsumeProductID();
		int GetConsumeOtherStocksID();
		int GetFixedAssetsID();
		int GetFixedAssetsOperID();
		int GetInventoryID();
		int GetOrderID();
		int GetOrderRawID();
		int GetPaymentID();
		int GetPayslipID();
		int GetProductionConRawID();
		int GetReceiptProductID();
		int GetReceiptOtherStocksID();
		int GetReturnID();
		int GetSpoilageID();
		int GetStockTransferID();
		int GetWithdrawalID();
		int GetWriteOFFID();
		int GetWriteOFFRawID();
		int GetProductID();
		int GetOtherStocksID();
		int GetAccountableDocumentID();

		void SetDebitingAccountNumber(std::string);
		void SetCreditingAccountNumber(std::string);
		void SetOperationID(int);
		void SetSubaccountID(int);
		void SetConsumeRawID(int);
		void SetConsumeProductID(int);
		void SetConsumeOtherStocksID(int);
		void SetFixedAssetsID(int);
		void SetFixedAssetsOperID(int);
		void SetInventoryID(int);
		void SetOrderID(int);
		void SetOrderRawID(int);
		void SetPaymentID(int);
		void SetPayslipID(int);
		void SetProductionConRawID(int);
		void SetReceiptProductID(int);
		void SetReceiptOtherStocksID(int);
		void SetReturnID(int);
		void SetSpoilageID(int);
		void SetStockTransferID(int);
		void SetWithdrawalID(int);
		void SetWriteOFFID(int);
		void SetWriteOFFRawID(int);
		void SetProductID(int);
		void SetOtherStocksID(int);
		void SetAccountableDocumentID(int);
	};
}
#endif