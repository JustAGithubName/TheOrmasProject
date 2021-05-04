#include "stdafx.h"
#include "PaymentClass.h"
#include "UserClass.h"
#include "BalanceClass.h"
#include "SubaccountClass.h"
#include "BalancePaymentRelationClass.h"
#include "EntryClass.h"
#include "EntryOperationRelationClass.h"
#include "CashboxEmployeeRelationClass.h"
#include "CashboxClass.h"
#include "StatusClass.h"
#include "AccountableWithdrawalRelationClass.h"
#include "AccountableTransactionClass.h"
#include <codecvt>

namespace BusinessLayer{
	Payment::Payment(DataLayer::paymentsCollection pCollection)
	{
		id = std::get<0>(pCollection);
		date = std::get<1>(pCollection);
		value = std::get<2>(pCollection);
		target = std::get<3>(pCollection);
		userID = std::get<4>(pCollection);
		currencyID = std::get<5>(pCollection);
		statusID = std::get<6>(pCollection);
		accountID = std::get<7>(pCollection);
		subaccountID = std::get<8>(pCollection);
		who = std::get<9>(pCollection);
		cashboxAccountID = std::get<10>(pCollection);
	}
	Payment::Payment()
	{
		date = "";
		value = 0.0;
		target = "";
		userID = 0;
		currencyID = 0;
		statusID = 0;
		accountID = 0;
		subaccountID = 0;
		who = "";
		cashboxAccountID = 0;
	}
	int Payment::GetID()
	{
		return id;
	}

	std::string Payment::GetDate()
	{
		return date;
	}	
	
	double Payment::GetValue()
	{
		return value;
	}

	std::string Payment::GetTarget()
	{
		return target;
	}

	int Payment::GetUserID()
	{
		return userID;
	}

	int Payment::GetCurrencyID()
	{
		return currencyID;
	}

	int Payment::GetStatusID()
	{
		return statusID;
	}

	int Payment::GetAccountID()
	{
		return accountID;
	}

	int Payment::GetSubaccountID()
	{
		return subaccountID;
	}

	std::string Payment::GetWho()
	{
		return who;
	}

	int Payment::GetCashboxAccountID()
	{
		return cashboxAccountID;
	}

	void Payment::SetID(int pID)
	{
		id = pID;
	}

	void Payment::SetDate(std::string pDate)
	{
		date = pDate;
	}

	void Payment::SetValue(double pValue)
	{
		value = pValue;
	}
	
	void Payment::SetTarget(std::string pTarget)
	{
		target = pTarget;
	}

	void Payment::SetUserID(int uID)
	{
		userID = uID;
	}
	void Payment::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	void Payment::SetStatusID(int sID)
	{
		statusID = sID;
	}

	void Payment::SetAccountID(int aID)
	{
		accountID = aID;
	}

	void Payment::SetSubaccountID(int subID)
	{
		subaccountID = subID;
	}

	void Payment::SetWho(std::string pWho)
	{
		who = pWho;
	}

	void Payment::SetCashboxAccountID(int cbID)
	{
		cashboxAccountID = cbID;
	}

	bool Payment::CreatePayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, std::string pTarget, int uID,
		int cID, int sID, int aID, int subaID, std::string pWho, int cashboxAccID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pDate, pValue, uID, cID, aID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		id = ormasDal.GenerateID();
		date = pDate;
		value = pValue;
		target = pTarget;
		userID = uID;
		currencyID = cID;
		statusID = sID;
		accountID = aID;
		subaccountID = subaID;
		who = pWho;
		cashboxAccountID = cashboxAccID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (accountID == 0)
		{
			if (subaccountID > 0)
			{
				Subaccount subaccount;
				if (!subaccount.GetSubaccountByID(globalVar, ormasDal, subaccountID, errorMessage))
					return false;
				accountID = subaccount.GetParentAccountID();
			}
		}
		if (0 != id && ormasDal.CreatePayment(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID, errorMessage))
		{
			//if (!ormasDal.CreateCashboxTransaction(ormasDal.GenerateID(),))
			//	return false;
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (subaccountID > 0 && userID <= 0)
				{
					if (Replenishment(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else if (userID > 0 || accountID > 0)
				{
					if (Replenishment(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Payment::CreatePayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (accountID == 0)
		{
			if (subaccountID > 0)
			{
				Subaccount subaccount;
				if (!subaccount.GetSubaccountByID(globalVar, ormasDal, subaccountID, errorMessage))
					return false;
				accountID = subaccount.GetParentAccountID();
			}
		}
		if (0 != id && ormasDal.CreatePayment(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (subaccountID > 0 && userID <= 0)
				{
					if (Replenishment(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else if (userID > 0 || accountID > 0)
				{
					if (Replenishment(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						//ormasDal.CancelTransaction(errorMessage);
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Payment::DeletePayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (!this->GetPaymentByID(globalVar, ormasDal, id, errorMessage))
			return false;
		if (this->GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (this->GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}
		if (ormasDal.DeletePayment(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool Payment::UpdatePayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, std::string pTarget, int uID,
		int cID, int sID, int aID, int subaID, std::string pWho, int cashboxAccID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		date = pDate;
		value = pValue;
		target = pTarget;
		userID = uID;
		currencyID = cID;
		statusID = sID;
		accountID = aID;
		subaccountID = subaID;
		who = pWho;
		cashboxAccountID = cashboxAccID;
		currentValue = GetCurrentValue(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (accountID == 0)
		{
			if (subaccountID > 0)
			{
				Subaccount subaccount;
				if (!subaccount.GetSubaccountByID(globalVar, ormasDal, subaccountID, errorMessage))
					return false;
				accountID = subaccount.GetParentAccountID();
			}
		}
		if (0 != id && ormasDal.UpdatePayment(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID, errorMessage))
		{
			if (previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (subaccountID > 0 && userID <= 0)
					{
						if (Replenishment(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					else if (userID > 0 || accountID > 0)
					{
						if (Replenishment(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return true;
				}
			}
			else
			{
				if (statusID == statusMap.find("ERROR")->second)
				{
					AccountableTransaction aTranaction;
					AccountableWithdrawalRelation aWithdrawal;
					aWithdrawal.SetWithdrawalID(id);
					std::string filter = aWithdrawal.GenerateFilter(ormasDal);
					std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
					if (accountableWithdrawalVector.size() > 0)
					{
						if (!aTranaction.IncCascadeTransactionUpdate(globalVar, ormasDal, std::get<1>(accountableWithdrawalVector.at(0)), value, errorMessage))
						{
							return false;
						}
					}
					if (subaccountID > 0 && userID <= 0)
					{
						if (CancelPayment(globalVar, ormasDal, subaccountID,cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					else
					{
						if (CancelPayment(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					
				}
				else
				{
					errorMessage = "Cannot update this document, only \"Error\" status is acceptable!";
					return false;
				}
			}
			/*if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (Replenishment(globalVar, ormasDal, userID, currencyID, aID, currentValue, errorMessage))
				{
					currentValue = 0.0;
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool Payment::UpdatePayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		currentValue = GetCurrentValue(globalVar, ormasDal, id, errorMessage);
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (accountID == 0)
		{
			if (subaccountID > 0)
			{
				Subaccount subaccount;
				if (!subaccount.GetSubaccountByID(globalVar, ormasDal, subaccountID, errorMessage))
					return false;
				accountID = subaccount.GetParentAccountID();
			}
		}
		if (0 != id && ormasDal.UpdatePayment(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID, errorMessage))
		{
			if (previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (subaccountID > 0 && userID <= 0)
					{
						if (Replenishment(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					else if (userID > 0 || accountID > 0)
					{
						if (Replenishment(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return true;
				}
			}
			else
			{
				if (statusID == statusMap.find("ERROR")->second)
				{
					AccountableTransaction aTranaction;
					AccountableWithdrawalRelation aWithdrawal;
					aWithdrawal.SetWithdrawalID(id);
					std::string filter = aWithdrawal.GenerateFilter(ormasDal);
					std::vector<DataLayer::accountableWithdrawalCollection> accountableWithdrawalVector = ormasDal.GetAccountableWithdrawal(errorMessage, filter);
					if (accountableWithdrawalVector.size() > 0)
					{
						if (!aTranaction.IncCascadeTransactionUpdate(globalVar, ormasDal, std::get<1>(accountableWithdrawalVector.at(0)), value, errorMessage))
						{
							return false;
						}
					}
					if (subaccountID > 0 && userID <= 0)
					{
						if (CancelPayment(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
					else
					{
						if (CancelPayment(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
						{
							currentValue = 0.0;
							//ormasDal.CommitTransaction(errorMessage);
							return true;
						}
						else
						{
							//ormasDal.CancelTransaction(errorMessage);
							return false;
						}
					}
				}
				else
				{
					errorMessage = "Cannot update this document, only \"Error\" status is acceptable!";
					return false;
				}
			}
			/*if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (Replenishment(globalVar, ormasDal, userID, currencyID, accountID, errorMessage))
				{
					//ormasDal.CommitTransaction(errorMessage);
					return true;
				}
				else
				{
					//ormasDal.CancelTransaction(errorMessage);
					return false;
				}
			}
			//ormasDal.CommitTransaction(errorMessage);
			return true;*/
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string Payment::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != userID || target.empty() || 0 != currencyID || 0 != value || 0 != statusID 
			|| 0 != accountID || 0 != subaccountID || !who.empty() || 0 != cashboxAccountID)
		{
			return ormasDal.GetFilterForPayment(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID);
		}
		return "";
	}

	std::string Payment::GenerateFilterFieldBiggerThen(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != userID || target.empty() || 0 != currencyID || 0 != value || 0 != statusID
			|| 0 != accountID || 0 != subaccountID || !who.empty() || 0 != cashboxAccountID)
		{
			return ormasDal.GetFilterForPaymentFieldBiggerThen(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID);
		}
		return "";
	}

	std::string Payment::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForPaymentForPeriod(id, date, value, target, userID, currencyID, statusID, accountID, subaccountID, who, cashboxAccountID, fromDate, toDate);
		}
		return "";
	}

	bool Payment::GetPaymentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentsViewCollection> paymentVector = ormasDal.GetPayments(errorMessage, filter);
		if (0 != paymentVector.size())
		{
			id = std::get<0>(paymentVector.at(0));
			date = std::get<1>(paymentVector.at(0));
			value = std::get<5>(paymentVector.at(0));
			target = std::get<7>(paymentVector.at(0));
			who = std::get<10>(paymentVector.at(0));
			userID = std::get<12>(paymentVector.at(0));
			currencyID = std::get<13>(paymentVector.at(0));
			statusID = std::get<14>(paymentVector.at(0));
			accountID = std::get<15>(paymentVector.at(0));
			subaccountID = std::get<16>(paymentVector.at(0));
			cashboxAccountID = std::get<17>(paymentVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Payment with this id";
		}
		return false;
	}

	bool Payment::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && target.empty() && 0 == userID && 0 == currencyID
			&& 0 == statusID && 0 != accountID && 0 != subaccountID && who.empty() && 0 != cashboxAccountID)
			return true;
		return false;
	}

	void Payment::Clear()
	{
		id = 0;
		date.clear();
		value = 0;
		target.clear();
		userID = 0;
		currencyID = 0;
		statusID = 0;
		accountID = 0;
		subaccountID = 0;
		who = "";
		cashboxAccountID = 0;
	}

	bool Payment::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID, int aID,
		std::string& errorMessage)
	{
		Payment payment;
		payment.Clear();
		errorMessage.clear();
		payment.SetDate(pDate);
		payment.SetValue(pValue);
		payment.SetUserID(uID);
		payment.SetCurrencyID(cID);
		payment.SetAccountID(aID);
		std::string filter = payment.GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentsViewCollection> paymentVector = ormasDal.GetPayments(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == paymentVector.size())
		{
			return false;
		}
		errorMessage = "Payment with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Payment::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Payment payment;
		payment.Clear();
		errorMessage.clear();
		payment.SetDate(date);
		payment.SetValue(value);
		payment.SetUserID(userID);
		payment.SetCurrencyID(currencyID);
		payment.SetAccountID(accountID);
		std::string filter = payment.GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentsViewCollection> paymentVector = ormasDal.GetPayments(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == paymentVector.size())
		{
			return false;
		}
		errorMessage = "Payment with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Payment::Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cbAccID, std::string& errorMessage)
	{
		/*CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}*/

		if (uID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Payment payment;
			payment.SetUserID(uID);
			std::string filter = payment.GenerateFilter(ormasDal);
			std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
			if (0 < balanceVector.size())
			{
				for each (auto item in balanceVector)
				{
					sub.Clear();
					tempBalance.Clear();
					if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
						return false;
					if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
					{
						if (sub.GetParentAccountID() == aID)
						{
							balance.SetSubaccountID(sub.GetID());
						}
					}
				}
			}
			else
			{
				return false;
			}
			if (balance.GetSubaccountID() <= 0)
				return false;
			if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			{
				int credAccID = balance.GetSubaccountID();
				int debAccID = cashboxAccountID;
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
				{
					BalancePaymentRelation bpRelation;
					bpRelation.SetBalanceID(balance.GetID());
					bpRelation.SetPaymentID(this->id);
					if (bpRelation.CreateBalancePaymentRelation(globalVar, ormasDal, errorMessage))
						return true;
				}
			}
		}
		else if (aID > 0)
		{
			int credAccID = aID;
			int debAccID = cashboxAccountID;
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
					return true;
			}
		}
		return false;
	}

	bool Payment::Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cbAccID, std::string& errorMessage)
	{
		/*CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}*/
		int debAccID = cashboxAccountID;
		int credAccID = sID;
		if (0 == debAccID || 0 == credAccID)
		{
			return false;
		}
		if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
		{
			return true;
		}
		return false;
	}

	bool Payment::Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cbAccID, double previousValue, std::string& errorMessage)
	{
		/*CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}*/

		if (uID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Payment payment;
			payment.SetUserID(uID);
			std::string filter = payment.GenerateFilter(ormasDal);
			std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
			if (0 < balanceVector.size())
			{
				for each (auto item in balanceVector)
				{
					sub.Clear();
					tempBalance.Clear();
					if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
						return false;
					if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
					{
						if (sub.GetParentAccountID() == aID)
						{
							balance.SetSubaccountID(sub.GetID());
						}
					}
				}
			}
			else
			{
				return false;
			}
			if (balance.GetSubaccountID() <= 0)
				return false;
			if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			{
				int credAccID = balance.GetSubaccountID();
				int debAccID = cashboxAccountID;
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, previousValue, ormasDal.GetSystemDateTime(), errorMessage))
				{
					return true;
				}
			}
		}
		else if (aID > 0)
		{
			int credAccID = aID;
			int debAccID = cashboxAccountID;
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

	bool Payment::Replenishment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cbAccID, double previousValue, std::string& errorMessage)
	{
		/*CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}

		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}*/

		int debAccID = cashboxAccountID;
		int credAccID = sID;
		if (0 == debAccID || 0 == credAccID)
		{
			return false;
		}
		if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, previousValue, ormasDal.GetSystemDateTime(), errorMessage))
		{
			return true;
		}
		return false;
	}

	double Payment::GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Payment payment;
		if (payment.GetPaymentByID(globalVar, ormasDal, pID, errorMessage))
			return payment.GetValue();
		return 0;
	}

	bool Payment::CancelPayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cbAccID, std::string& errorMessage)
	{
		/*CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}
		Cashbox cashbox;
		if (!cashbox.GetCashboxByID(globalVar, ormasDal, cashEmpRel.GetCashboxID(), errorMessage))
		{
			errorMessage = "Access denied! You haven't rights for doing operations with cashbox!";
			return false;
		}*/
		
		if (uID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Payment payment;
			payment.SetUserID(uID);
			std::string filter = payment.GenerateFilter(ormasDal);
			std::vector<DataLayer::balancesViewCollection> balanceVector = ormasDal.GetBalances(errorMessage, filter);
			if (0 < balanceVector.size())
			{
				for each (auto item in balanceVector)
				{
					sub.Clear();
					tempBalance.Clear();
					if (!tempBalance.GetBalanceByID(globalVar, ormasDal, std::get<0>(item), errorMessage))
						return false;
					if (sub.GetSubaccountByID(globalVar, ormasDal, tempBalance.GetSubaccountID(), errorMessage))
					{
						if (sub.GetParentAccountID() == aID)
						{
							balance.SetSubaccountID(sub.GetID());
						}
					}
				}
			}
			else
			{
				return false;
			}
			if (balance.GetSubaccountID() <= 0)
				return false;
			if (balance.GetBalanceBySubaccountID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			{
				int debAccID = balance.GetSubaccountID();
				int credAccID = cashboxAccountID;
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CorrectingEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
				{
					BalancePaymentRelation bpRelation;
					bpRelation.SetBalanceID(balance.GetID());
					bpRelation.SetPaymentID(this->id);
					if (bpRelation.DeleteBalancePaymentRelation(globalVar, ormasDal, errorMessage))
						return true;
				}
			}
		}
		else if (aID > 0)
		{
			int debAccID = aID;
			int credAccID = cashboxAccountID;
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CorrectingEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
					return true;
			}
		}
		return false;
	}

	bool Payment::CancelPayment(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, std::string& errorMessage)
	{
		int debAccID = sID;
		int credAccID = cashboxAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			return false;
		}
		if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
		{
			return true;
		}
		return false;
	}

	bool Payment::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(target);
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
	bool Payment::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена оплаты, для коррекции"));
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
		entry.SetDescription(target);
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
	bool Payment::CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(debAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(credAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена оплаты"));
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
	
	int Payment::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Payment payment;
		if (payment.GetPaymentByID(globalVar, ormasDal, pID, errorMessage))
			return payment.GetStatusID();
		return 0;
	}

	std::string Payment::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}

