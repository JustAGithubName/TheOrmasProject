#include "stdafx.h"
#include "EntryViewClass.h"

namespace BusinessLayer{
	EntryView::EntryView(DataLayer::entriesViewCollection eCollection)
	{
		id = std::get<0>(eCollection);
		date = std::get<1>(eCollection);
		debitingAccountNumber = std::get<2>(eCollection);
		value = std::get<3>(eCollection);
		creditingAccountNumber = std::get<4>(eCollection);
		debitingAccountID = std::get<5>(eCollection);
		creditingAccountID = std::get<6>(eCollection);
		description = std::get<7>(eCollection);
	}

	std::string EntryView::GetDebitingAccountNumber()
	{
		return debitingAccountNumber;
	}

	std::string EntryView::GetCreditingAccountNumber()
	{
		return creditingAccountNumber;
	}

	void EntryView::SetDebitingAccountNumber(std::string eDebitingAccountNumber)
	{
		debitingAccountNumber = eDebitingAccountNumber;
	}

	void EntryView::SetCreditingAccountNumber(std::string eCreditingAccountNumber)
	{
		creditingAccountNumber = eCreditingAccountNumber;
	}

	std::string EntryView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !debitingAccountNumber.empty() || 0.0 != value || !creditingAccountNumber.empty() || 0 != debitingAccountID || 0 != creditingAccountID || !description.empty())
		{
			return ormasDal.GetFilterForEntryView(id, date, debitingAccountNumber, value, creditingAccountNumber, debitingAccountID, creditingAccountID, description);
		}
		return "";
	}
}