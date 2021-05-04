#include "stdafx.h"
#include "ExtendedEntryViewClass.h"

namespace BusinessLayer{
	ExtendedEntryView::ExtendedEntryView(DataLayer::entriesFullViewCollection eCollection)
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
	}

	std::string ExtendedEntryView::GetDebitingAccountNumber()
	{
		return debitingAccountNumber;
	}

	std::string ExtendedEntryView::GetCreditingAccountNumber()
	{
		return creditingAccountNumber;
	}

	int ExtendedEntryView::GetOperationID()
	{
		return operationID;
	}

	int ExtendedEntryView::GetSubaccountID()
	{
		return subaccountID;
	}

	void ExtendedEntryView::SetDebitingAccountNumber(std::string eDebitingAccountNumber)
	{
		debitingAccountNumber = eDebitingAccountNumber;
	}

	void ExtendedEntryView::SetCreditingAccountNumber(std::string eCreditingAccountNumber)
	{
		creditingAccountNumber = eCreditingAccountNumber;
	}

	void ExtendedEntryView::SetOperationID(int eOperationID)
	{
		operationID = eOperationID;
	}

	void ExtendedEntryView::SetSubaccountID(int eSubaccountID)
	{
		subaccountID = eSubaccountID;
	}

	std::string ExtendedEntryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !debitingAccountNumber.empty() || 0.0 != value || !creditingAccountNumber.empty() || 0 != operationID || 0 != subaccountID 
			|| 0 != debitingAccountID || 0 != creditingAccountID || !description.empty())
		{
			return ormasDal.GetFilterForEntryFullView(id, date, debitingAccountNumber, value, creditingAccountNumber, operationID, subaccountID,
				debitingAccountID, creditingAccountID, description);
		}
		return "";
	}
}