#include "stdafx.h"
#include "FullExtendedEntryViewClass.h"

namespace BusinessLayer{
	FullExtendedEntryView::FullExtendedEntryView(DataLayer::entriesFullJoinViewCollection eCollection)
	{
		id = std::get<0>(eCollection);
		date = std::get<1>(eCollection);
		debitingAccountNumber = std::get<2>(eCollection);
		value = std::get<3>(eCollection);
		creditingAccountNumber = std::get<4>(eCollection);
		operationID = std::get<5>(eCollection);
		subaccountID = std::get<6>(eCollection);
		debitingAccountID = std::get<7>(eCollection);
		creditingAccountID = std::get<8>(eCollection);
		description = std::get<9>(eCollection);
		consumeProductID = std::get<10>(eCollection);
		consumeRawID = std::get<11>(eCollection);
		fixedAssetsID = std::get<12>(eCollection);
		fixedAssetsOperID = std::get<13>(eCollection);
		inventoryID = std::get<14>(eCollection);
		orderID = std::get<15>(eCollection);
		orderRawID = std::get<16>(eCollection);
		paymentID = std::get<17>(eCollection);
		payslipID = std::get<18>(eCollection);
		productionConRawID = std::get<19>(eCollection);
		receiptProductID = std::get<20>(eCollection);
		returnID = std::get<21>(eCollection);
		spoilageID = std::get<22>(eCollection);
		stockTransferID = std::get<23>(eCollection);
		withdrawalID = std::get<24>(eCollection);
		writeOffID = std::get<25>(eCollection);
		writeOffRawID = std::get<26>(eCollection);
		productID = std::get<27>(eCollection);
		otherStocksID = std::get<28>(eCollection);
		receiptOtherStocksID = std::get<29>(eCollection);
		consumeOtherStocksID = std::get<30>(eCollection);
		accDocumentID = std::get<31>(eCollection);
	}

	std::string FullExtendedEntryView::GetDebitingAccountNumber()
	{
		return debitingAccountNumber;
	}

	std::string FullExtendedEntryView::GetCreditingAccountNumber()
	{
		return creditingAccountNumber;
	}

	int FullExtendedEntryView::GetOperationID()
	{
		return operationID;
	}

	int FullExtendedEntryView::GetSubaccountID()
	{
		return subaccountID;
	}

	int FullExtendedEntryView::GetConsumeRawID()
	{
		return consumeRawID;
	}

	int FullExtendedEntryView::GetConsumeProductID()
	{
		return productID;
	}

	int FullExtendedEntryView::GetConsumeOtherStocksID()
	{
		return otherStocksID;
	}

	int FullExtendedEntryView::GetFixedAssetsID()
	{
		return fixedAssetsID;
	}

	int FullExtendedEntryView::GetFixedAssetsOperID()
	{
		return fixedAssetsOperID;
	}

	int FullExtendedEntryView::GetInventoryID()
	{
		return inventoryID;
	}


	int FullExtendedEntryView::GetOrderID()
	{
		return orderID;
	}

	int FullExtendedEntryView::GetOrderRawID()
	{
		return orderRawID;
	}

	int FullExtendedEntryView::GetPaymentID()
	{
		return paymentID;
	}

	int FullExtendedEntryView::GetPayslipID()
	{
		return payslipID;
	}

	int FullExtendedEntryView::GetProductionConRawID()
	{
		return productionConRawID;
	}

	int FullExtendedEntryView::GetReceiptProductID()
	{
		return receiptProductID;
	}


	int FullExtendedEntryView::GetReceiptOtherStocksID()
	{
		return otherStocksID;
	}

	int FullExtendedEntryView::GetReturnID()
	{
		return returnID;
	}

	int FullExtendedEntryView::GetSpoilageID()
	{
		return spoilageID;
	}

	int FullExtendedEntryView::GetStockTransferID()
	{
		return stockTransferID;
	}

	int FullExtendedEntryView::GetWithdrawalID()
	{
		return withdrawalID;
	}

	int FullExtendedEntryView::GetWriteOFFID()
	{
		return writeOffID;
	}

	int FullExtendedEntryView::GetWriteOFFRawID()
	{
		return writeOffRawID;
	}

	int FullExtendedEntryView::GetProductID()
	{
		return productID;
	}

	int FullExtendedEntryView::GetOtherStocksID()
	{
		return otherStocksID;
	}

	int FullExtendedEntryView::GetAccountableDocumentID()
	{
		return accDocumentID;
	}

	void FullExtendedEntryView::SetDebitingAccountNumber(std::string eDebitingAccountNumber)
	{
		debitingAccountNumber = eDebitingAccountNumber;
	}

	void FullExtendedEntryView::SetCreditingAccountNumber(std::string eCreditingAccountNumber)
	{
		creditingAccountNumber = eCreditingAccountNumber;
	}

	void FullExtendedEntryView::SetOperationID(int eOperationID)
	{
		operationID = eOperationID;
	}

	void FullExtendedEntryView::SetSubaccountID(int eSubaccountID)
	{
		subaccountID = eSubaccountID;
	}

	void FullExtendedEntryView::SetConsumeRawID(int eConsumeRawID)
	{
		consumeRawID = eConsumeRawID;
	}

	void FullExtendedEntryView::SetConsumeProductID(int eProductID)
	{
		productID = eProductID;
	}

	void FullExtendedEntryView::SetConsumeOtherStocksID(int eOtherStocksID)
	{
		otherStocksID = eOtherStocksID;
	}

	void FullExtendedEntryView::SetFixedAssetsID(int cFixedAssetsID)
	{
		fixedAssetsID = cFixedAssetsID;
	}

	void FullExtendedEntryView::SetFixedAssetsOperID(int cFixedAssetsOperID)
	{
		fixedAssetsOperID = cFixedAssetsOperID;
	}

	void FullExtendedEntryView::SetInventoryID(int eInventoryID)
	{
		inventoryID = eInventoryID;
	}


	void FullExtendedEntryView::SetOrderID(int epOrderID)
	{
		orderID = epOrderID;
	}

	void FullExtendedEntryView::SetOrderRawID(int eOrderRawID)
	{
		orderRawID = eOrderRawID;
	}

	void FullExtendedEntryView::SetPaymentID(int epaymentID)
	{
		paymentID = epaymentID;
	}

	void FullExtendedEntryView::SetPayslipID(int ePayslipID)
	{
		payslipID = ePayslipID;
	}

	void FullExtendedEntryView::SetProductionConRawID(int eProductionConRawID)
	{
		productionConRawID = eProductionConRawID;
	}

	void FullExtendedEntryView::SetReceiptProductID(int eReceiptProductID)
	{
		receiptProductID = eReceiptProductID;
	}


	void FullExtendedEntryView::SetReceiptOtherStocksID(int eOtherStocksID)
	{
		otherStocksID = eOtherStocksID;
	}

	void FullExtendedEntryView::SetReturnID(int eReturnID)
	{
		returnID = eReturnID;
	}

	void FullExtendedEntryView::SetSpoilageID(int eSpoilageID)
	{
		spoilageID = eSpoilageID;
	}

	void FullExtendedEntryView::SetStockTransferID(int eStockTransferID)
	{
		stockTransferID = eStockTransferID;
	}

	void FullExtendedEntryView::SetWithdrawalID(int eWithdrawalID)
	{
		withdrawalID = eWithdrawalID;
	}

	void FullExtendedEntryView::SetWriteOFFID(int eWriteOffID)
	{
		writeOffID = eWriteOffID;
	}

	void FullExtendedEntryView::SetWriteOFFRawID(int eWriteOffRawID)
	{
		writeOffRawID = eWriteOffRawID;
	}

	void FullExtendedEntryView::SetProductID(int eProductID)
	{
		productID = eProductID;
	}

	void FullExtendedEntryView::SetOtherStocksID(int eEtherStocksID)
	{
		otherStocksID = eEtherStocksID;
	}

	void FullExtendedEntryView::SetAccountableDocumentID(int eAccDocumentID)
	{
		accDocumentID = eAccDocumentID;
	}

	std::string FullExtendedEntryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !debitingAccountNumber.empty() || 0.0 != value || !creditingAccountNumber.empty() || 0 != operationID || 0 != subaccountID
			|| 0 != debitingAccountID || 0 != creditingAccountID || !description.empty() || 0 != creditingAccountID || 0 != consumeRawID || 0 != fixedAssetsID
			|| 0 != fixedAssetsOperID || 0 != inventoryID || 0 != orderID || 0 != orderRawID || 0 != paymentID || 0 != payslipID
			|| 0 != productionConRawID || 0 != receiptProductID || 0 != returnID || 0 != spoilageID || 0 != stockTransferID || 0 != withdrawalID
			|| 0 != writeOffID || 0 != writeOffRawID || 0 != otherStocksID || 0 != receiptOtherStocksID || 0 != consumeOtherStocksID || 0 != accDocumentID)
		{
			return ormasDal.GetFilterForEntryAllView(id, date, debitingAccountNumber, value, creditingAccountNumber, operationID, subaccountID,
				debitingAccountID, creditingAccountID, description, consumeProductID, consumeRawID, fixedAssetsID, fixedAssetsOperID, inventoryID,
				orderID, orderRawID, paymentID, payslipID, productionConRawID, receiptProductID, returnID, spoilageID, stockTransferID, withdrawalID,
				writeOffID, writeOffRawID, productID, otherStocksID, receiptOtherStocksID, consumeOtherStocksID, accDocumentID);
		}
		return "";
	}
}