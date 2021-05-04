#include "stdafx.h"
#include "RefundClass.h"
#include "UserClass.h"
#include "BalanceClass.h"
#include "BalanceRefundRelationClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "CashboxEmployeeRelationClass.h"
#include "CashboxClass.h"
#include <codecvt>

namespace BusinessLayer{
	Refund::Refund(DataLayer::refundsCollection rCollection)
	{
		id = std::get<0>(rCollection);
		date = std::get<1>(rCollection);
		value = std::get<2>(rCollection);
		userID = std::get<3>(rCollection);
		currencyID = std::get<4>(rCollection);
	}
	Refund::Refund()
	{
		date = "";
		value = 0.0;
		userID = 0;
		currencyID = 0;
	}
	int Refund::GetID()
	{
		return id;
	}

	std::string Refund::GetDate()
	{
		return date;
	}

	double Refund::GetValue()
	{
		return value;
	}

	int Refund::GetUserID()
	{
		return userID;
	}

	int Refund::GetCurrencyID()
	{
		return currencyID;
	}

	void Refund::SetID(int pID)
	{
		id = pID;
	}

	void Refund::SetDate(std::string pDate)
	{
		date = pDate;
	}

	void Refund::SetValue(double pValue)
	{
		value = pValue;
	}

	void Refund::SetUserID(int uID)
	{
		userID = uID;
	}
	void Refund::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	bool Refund::CreateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
		std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pDate, pValue, uID, cID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		date = pDate;
		value = pValue;
		userID = uID;
		currencyID = cID;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateRefund(id, date, value, userID, currencyID, errorMessage))
		{
			if (Replenishment(globalVar, ormasDal, userID, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Refund::CreateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateRefund(id, date, value, userID, currencyID, errorMessage))
		{
			if (Replenishment(globalVar, ormasDal, userID, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Refund::DeleteRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (!this->GetRefundByID(globalVar, ormasDal, id, errorMessage))
			return false;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.DeleteRefund(id, errorMessage))
		{
			if (CancelRefund(globalVar, ormasDal, userID, currencyID, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				Clear();
				return true;
			}	
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool Refund::UpdateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
		std::string& errorMessage)
	{
		date = pDate;
		value = pValue;
		userID = uID;
		currencyID = cID;
		currentValue = GetCurrentValue(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateRefund(id, date, value, userID, currencyID, errorMessage))
		{
			if (Replenishment(globalVar, ormasDal, userID, currencyID, currentValue, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				currentValue = 0.0;
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Refund::UpdateRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		currentValue = GetCurrentValue(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateRefund(id, date, value, userID, currencyID, errorMessage))
		{
			if (Replenishment(globalVar, ormasDal, userID, currencyID, currentValue, errorMessage))
			{
				//ormasDal.CommitTransaction(errorMessage);
				currentValue = 0.0;
				return true;
			}
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string Refund::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != userID || 0 != currencyID || 0 != value)
		{
			return ormasDal.GetFilterForRefund(id, date, value, userID, currencyID);
		}
		return "";
	}

	bool Refund::GetRefundByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::refundsViewCollection> refundVector = ormasDal.GetRefunds(errorMessage, filter);
		if (0 != refundVector.size())
		{
			id = std::get<0>(refundVector.at(0));
			date = std::get<1>(refundVector.at(0));
			value = std::get<2>(refundVector.at(0));
			userID = std::get<4>(refundVector.at(0));
			currencyID = std::get<5>(refundVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Refund with this id";
		}
		return false;
	}

	bool Refund::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && 0 == userID && 0 == currencyID)
			return true;
		return false;
	}

	void Refund::Clear()
	{
		id = 0;
		date.clear();
		value = 0;
		userID = 0;
		currencyID = 0;
	}

	bool Refund::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID,
		std::string& errorMessage)
	{
		Refund refund;
		refund.Clear();
		errorMessage.clear();
		refund.SetDate(pDate);
		refund.SetValue(pValue);
		refund.SetUserID(uID);
		refund.SetCurrencyID(cID);
		std::string filter = refund.GenerateFilter(ormasDal);
		std::vector<DataLayer::refundsViewCollection> refundVector = ormasDal.GetRefunds(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == refundVector.size())
		{
			return false;
		}
		errorMessage = "Refund with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Refund::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Refund refund;
		refund.Clear();
		errorMessage.clear();
		refund.SetDate(date);
		refund.SetValue(value);
		refund.SetUserID(userID);
		refund.SetCurrencyID(currencyID);
		std::string filter = refund.GenerateFilter(ormasDal);
		std::vector<DataLayer::refundsViewCollection> refundVector = ormasDal.GetRefunds(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == refundVector.size())
		{
			return false;
		}
		errorMessage = "Refund with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Refund::Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, std::string& errorMessage)
	{
		CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxEmployeeByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}

		Balance balance;
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		if (balance.GetBalanceByUserID(globalVar, ormasDal, uID, errorMessage))
		{
			int debAccID = balance.GetSubaccountID();
			int credAccID = cashbox.GetSubaccountID();
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
				BalanceRefundRelation brRelation;
				brRelation.SetBalanceID(balance.GetID());
				brRelation.SetRefundID(this->id);
				if (brRelation.CreateBalanceRefundRelation(globalVar, ormasDal, errorMessage))
					return true;
			}
		}
		return false;
	}

	bool Refund::Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, double previousValue, std::string& errorMessage)
	{
		CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxEmployeeByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}

		Balance balance;
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		if (balance.GetBalanceByUserID(globalVar, ormasDal, uID, errorMessage))
		{
			int debAccID = balance.GetSubaccountID();
			int credAccID = cashbox.GetSubaccountID();
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, previousValue, ormasDal.GetSystemDateTime(), errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	double Refund::GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Refund refund;
		if (refund.GetRefundByID(globalVar, ormasDal, pID, errorMessage))
			return refund.GetValue();
		return 0;
	}

	bool Refund::CancelRefund(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, std::string& errorMessage)
	{
		CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxEmployeeByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}

		Balance balance;
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		if (balance.GetBalanceByUserID(globalVar, ormasDal, uID, errorMessage))
		{
			int debAccID = balance.GetSubaccountID();
			int credAccID = cashbox.GetSubaccountID();
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CorrectingEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
				BalanceRefundRelation brRelation;
				brRelation.SetBalanceID(balance.GetID());
				brRelation.SetRefundID(this->id);
				if (brRelation.DeleteBalanceRefundRelation(globalVar, ormasDal, errorMessage))
					return true;
			}
		}
		return false;
	}

	bool Refund::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена возврата суммы клиенту"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool Refund::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена возврата суммы клиенту"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage, true))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		entry.Clear();
		eoRelation.Clear();
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена возврата суммы клиенту"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	bool Refund::CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена возврата суммы клиенту"));
		if (entry.CreateEntry(globalVar, ormasDal, errorMessage))
		{
			eoRelation.SetEntryID(entry.GetID());
			eoRelation.SetOperationID(id);
			if (!eoRelation.CreateEntryOperationRelation(globalVar, ormasDal, errorMessage))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	std::string Refund::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}