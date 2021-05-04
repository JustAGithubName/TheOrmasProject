#include "stdafx.h"
#include "WithdrawalClass.h"
#include "UserClass.h"
#include "BalanceClass.h"
#include "BalanceWithdrawalRelationClass.h"
#include "EntryClass.h"
#include "CashboxEmployeeRelationClass.h"
#include "CashboxClass.h"
#include "StatusClass.h"
#include "SubaccountClass.h"
#include "EntryOperationRelationClass.h"
#include "AccountableTransactionClass.h"
#include "AccountablePaymentRelationClass.h"
#include <codecvt>

namespace BusinessLayer{
	Withdrawal::Withdrawal(DataLayer::withdrawalsCollection wCollection)
	{
		id = std::get<0>(wCollection);
		date = std::get<1>(wCollection);
		value = std::get<2>(wCollection);
		userID = std::get<3>(wCollection);
		subaccountID = std::get<4>(wCollection);
		target = std::get<5>(wCollection);
		currencyID = std::get<6>(wCollection);
		statusID = std::get<7>(wCollection);
		accountID = std::get<8>(wCollection);
		who = std::get<9>(wCollection);
		cashboxAccountID = std::get<10>(wCollection);
	}
	Withdrawal::Withdrawal()
	{
		date = "";
		target = "";
		value = 0.0;
		userID = 0;
		currencyID = 0;
		subaccountID = 0;
		accountID = 0;
		statusID = 0;
		cashboxAccountID = 0;
	}
	int Withdrawal::GetID()
	{
		return id;
	}

	std::string Withdrawal::GetDate()
	{
		return date;
	}

	std::string Withdrawal::GetTarget()
	{
		return target;
	}

	double Withdrawal::GetValue()
	{
		return value;
	}

	int Withdrawal::GetUserID()
	{
		return userID;
	}

	int Withdrawal::GetCurrencyID()
	{
		return currencyID;
	}

	int Withdrawal::GetSubaccountID()
	{
		return subaccountID;
	}
	
	int Withdrawal::GetAccountID()
	{
		return accountID;
	}
	
	int Withdrawal::GetStatusID()
	{
		return statusID;
	}

	std::string Withdrawal::GetWho()
	{
		return who;
	}

	int Withdrawal::GetCashboxAccountID()
	{
		return cashboxAccountID;
	}

	void Withdrawal::SetID(int wID)
	{
		id = wID;
	}

	void Withdrawal::SetDate(std::string wDate)
	{
		date = wDate;
	}

	void Withdrawal::SetTarget(std::string wTarget)
	{
		target = wTarget;
	}

	void Withdrawal::SetValue(double wValue)
	{
		value = wValue;
	}

	void Withdrawal::SetUserID(int uID)
	{
		userID = uID;
	}
	void Withdrawal::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}
	void Withdrawal::SetSubaccountID(int sID)
	{
		subaccountID = sID;
	}
	void Withdrawal::SetAccountID(int aID)
	{
		accountID = aID;
	}
	void Withdrawal::SetStatusID(int stsID)
	{
		statusID = stsID;
	}

	void Withdrawal::SetWho(std::string wWho)
	{
		who = wWho;
	}

	void Withdrawal::SetCashboxAccountID(int cbID)
	{
		cashboxAccountID = cbID;
	}
	bool Withdrawal::CreateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wDate, double wValue, int uID, int sID, std::string wTaeget,
		int cID, int stsID, int aID, std::string wWho, int cashboxAccID,std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, wDate, wValue, uID, cID, aID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		id = ormasDal.GenerateID();
		date = wDate;
		value = wValue;
		userID = uID;
		currencyID = cID;
		target = wTaeget;
		subaccountID = sID;
		statusID = stsID;
		accountID = aID;
		who = wWho;
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
		if (0 != id && ormasDal.CreateWithdrawal(id, date, value, userID,subaccountID,target, currencyID, statusID, accountID, who, cashboxAccountID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (subaccountID > 0 && userID <= 0)
				{
					if (Payout(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (userID > 0 || accountID > 0)
				{
					if (Payout(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
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
	bool Withdrawal::CreateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
		if (0 != id && ormasDal.CreateWithdrawal(id, date, value, userID, subaccountID, target, currencyID, statusID, accountID, who, cashboxAccountID, errorMessage))
		{
			if (statusID == statusMap.find("EXECUTED")->second)
			{
				if (subaccountID > 0 && userID <= 0)
				{
					if (Payout(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						return false;
					}
				}
				else if (userID > 0 || accountID > 0)
				{
					if (Payout(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
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
	bool Withdrawal::DeleteWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (!this->GetWithdrawalByID(globalVar, ormasDal, id, errorMessage))
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
		if (ormasDal.DeleteWithdrawal(id, errorMessage))
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

	bool Withdrawal::UpdateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string wDate, double wValue, int uID, int sID, std::string wTaeget,
		int cID, int stsID, int aID, std::string wWho, int cashboxAccID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		date = wDate;
		value = wValue;
		userID = uID;
		currencyID = cID;
		target = wTaeget;
		subaccountID = sID;
		statusID = stsID;
		accountID = aID;
		who = wWho;
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
		if (0 != id && ormasDal.UpdateWithdrawal(id, date, value, userID, subaccountID, target, currencyID, statusID, accountID, who, cashboxAccountID, errorMessage))
		{
			if (previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (subaccountID > 0 && userID <= 0)
					{
						if (Payout(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
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
						if (Payout(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
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
					AccountablePaymentRelation aPayment;
					aPayment.SetPaymentID(id);
					std::string filter = aPayment.GenerateFilter(ormasDal);
					std::vector<DataLayer::accountableWithdrawalCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
					if (accountablePaymentVector.size() > 0)
					{
						if (!aTranaction.DecCascadeTransactionUpdate(globalVar, ormasDal, std::get<1>(accountablePaymentVector.at(0)), value, errorMessage))
						{
							return false;
						}
					}
					if (subaccountID > 0 && userID <= 0)
					{
						if (CancelWithdrawal(globalVar, ormasDal, subaccountID,cashboxAccountID, errorMessage))
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

						if (CancelWithdrawal(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
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
				if (0 != subaccountID)
				{
					if (Payout(globalVar, ormasDal, subaccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (Payout(globalVar, ormasDal, userID, currencyID, accountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						return false;
					}
				}
			}*/
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
	bool Withdrawal::UpdateWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
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
		if (0 != id && ormasDal.UpdateWithdrawal(id, date, value, userID, subaccountID, target, currencyID, statusID, accountID, who, cashboxAccountID, errorMessage))
		{
			if (previousStatusID != statusMap.find("EXECUTED")->second)
			{
				if (statusID == statusMap.find("EXECUTED")->second)
				{
					if (subaccountID > 0 && userID <= 0)
					{
						if (Payout(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
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
						if (Payout(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
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
					AccountablePaymentRelation aPayment;
					aPayment.SetPaymentID(id);
					std::string filter = aPayment.GenerateFilter(ormasDal);
					std::vector<DataLayer::accountableWithdrawalCollection> accountablePaymentVector = ormasDal.GetAccountablePayment(errorMessage, filter);
					if (accountablePaymentVector.size() > 0)
					{
						if (!aTranaction.DecCascadeTransactionUpdate(globalVar, ormasDal, std::get<1>(accountablePaymentVector.at(0)), value, errorMessage))
						{
							return false;
						}
					}
					if (subaccountID > 0 && userID <= 0)
					{
						if (CancelWithdrawal(globalVar, ormasDal, subaccountID, cashboxAccountID, errorMessage))
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

						if (CancelWithdrawal(globalVar, ormasDal, userID, currencyID, accountID, cashboxAccountID, errorMessage))
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
				if (0 != subaccountID)
				{
					if (Payout(globalVar, ormasDal, subaccountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					if (Payout(globalVar, ormasDal, userID, currencyID, accountID, errorMessage))
					{
						//ormasDal.CommitTransaction(errorMessage);
						return true;
					}
					else
					{
						return false;
					}
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

	std::string Withdrawal::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !target.empty() || 0 != userID || 0 != subaccountID || 0 != currencyID || 0 != value
			|| 0 != statusID || 0 != accountID || !who.empty() || 0 != cashboxAccountID)
		{
			return ormasDal.GetFilterForWithdrawal(id, date, value, userID, subaccountID, target, currencyID, statusID, accountID, who, cashboxAccountID);
		}
		return "";
	}

	std::string Withdrawal::GenerateFilterForPeriod(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string fromDate, std::string toDate)
	{
		if (!toDate.empty() && !fromDate.empty())
		{
			return ormasDal.GetFilterForWithdrawalForPeriod(id, date, value, userID, subaccountID, target, currencyID, statusID, accountID, who, cashboxAccountID, fromDate, toDate);
		}
		return "";
	}

	std::string Withdrawal::GenerateFilterFieldBiggerThen(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !date.empty() || !target.empty() || 0 != userID || 0 != subaccountID || 0 != currencyID || 0 != value
			|| 0 != statusID || 0 != accountID || !who.empty() || 0 != cashboxAccountID)
		{
			return ormasDal.GetFilterForWithdrawalFieldBiggerThen(id, date, value, userID, subaccountID, target, currencyID, statusID, accountID, who, cashboxAccountID);
		}
		return "";
	}

	bool Withdrawal::GetWithdrawalByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::withdrawalsViewCollection> withdrawalVector = ormasDal.GetWithdrawals(errorMessage, filter);
		if (0 != withdrawalVector.size())
		{
			id = std::get<0>(withdrawalVector.at(0));
			date = std::get<1>(withdrawalVector.at(0));
			value = std::get<2>(withdrawalVector.at(0));
			who = std::get<10>(withdrawalVector.at(0));
			userID = std::get<12>(withdrawalVector.at(0));
			subaccountID = std::get<14>(withdrawalVector.at(0));
			target = std::get<11>(withdrawalVector.at(0));
			currencyID = std::get<13>(withdrawalVector.at(0));
			statusID = std::get<15>(withdrawalVector.at(0));
			accountID = std::get<16>(withdrawalVector.at(0));
			cashboxAccountID = std::get<16>(withdrawalVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Withdrawal with this id";
		}
		return false;
	}

	bool Withdrawal::IsEmpty()
	{
		if (0 == id && date.empty() && 0.0 == value && 0 == userID && 0 == currencyID && 0== subaccountID && target.empty() 
			&& 0 == statusID && 0 == accountID && who.empty() && 0 == cashboxAccountID)
			return true;
		return false;
	}

	void Withdrawal::Clear()
	{
		id = 0;
		date.clear();
		target.clear();
		value = 0;
		userID = 0;
		currencyID = 0;
		subaccountID = 0;
		statusID = 0;
		accountID = 0;
		who = "";
		cashboxAccountID = 0;
	}

	bool Withdrawal::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pDate, double pValue, int uID, int cID, int aID,
		std::string& errorMessage)
	{
		Withdrawal withdrawal;
		withdrawal.Clear();
		errorMessage.clear();
		withdrawal.SetDate(pDate);
		withdrawal.SetValue(pValue);
		withdrawal.SetUserID(uID);
		withdrawal.SetCurrencyID(cID);
		withdrawal.SetAccountID(aID);
		std::string filter = withdrawal.GenerateFilter(ormasDal);
		std::vector<DataLayer::withdrawalsViewCollection> withdrawalVector = ormasDal.GetWithdrawals(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == withdrawalVector.size())
		{
			return false;
		}
		errorMessage = "Withdrawal with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Withdrawal::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Withdrawal withdrawal;
		withdrawal.Clear();
		errorMessage.clear();
		withdrawal.SetDate(date);
		withdrawal.SetValue(value);
		withdrawal.SetUserID(userID);
		withdrawal.SetCurrencyID(currencyID);
		withdrawal.SetAccountID(accountID);
		std::string filter = withdrawal.GenerateFilter(ormasDal);
		std::vector<DataLayer::withdrawalsViewCollection> withdrawalVector = ormasDal.GetWithdrawals(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == withdrawalVector.size())
		{
			return false;
		}
		errorMessage = "Withdrawal with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Withdrawal::Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cashboxAccID, std::string& errorMessage)
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
			Withdrawal withdrawal;
			withdrawal.SetUserID(uID);
			std::string filter = withdrawal.GenerateFilter(ormasDal);
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
				int credAccID = cashboxAccID;
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CreateEntry(globalVar, ormasDal, debAccID, value, credAccID, ormasDal.GetSystemDateTime(), errorMessage))
				{
					BalanceWithdrawalRelation bwRelation;
					bwRelation.SetBalanceID(balance.GetID());
					bwRelation.SetWithdrawalID(this->id);
					if (bwRelation.CreateBalanceWithdrawalRelation(globalVar, ormasDal, errorMessage))
						return true;
				}
			}
		}
		else if (aID > 0)
		{
			int debAccID = aID;
			int credAccID = cashboxAccID;
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

	bool Withdrawal::Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, std::string& errorMessage)
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

	bool Withdrawal::Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cashboxAccID, double previousValue, std::string& errorMessage)
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
		
		if (userID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Withdrawal withdrawal;
			withdrawal.SetUserID(uID);
			std::string filter = withdrawal.GenerateFilter(ormasDal);
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
				int credAccID = cashboxAccID;
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
			int debAccID = aID;
			int credAccID = cashboxAccID;
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

	bool Withdrawal::Payout(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, double previousValue, std::string& errorMessage)
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
		
		int debAccID = sID;
		int credAccID = cashboxAccID;
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

	double Withdrawal::GetCurrentValue(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Withdrawal payslip;
		if (payslip.GetWithdrawalByID(globalVar, ormasDal, pID, errorMessage))
			return payslip.GetValue();
		return 0;
	}

	bool Withdrawal::CancelWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int cID, int aID, int cashboxAccID, std::string& errorMessage)
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

		if (userID > 0)
		{
			Balance balance;
			Balance tempBalance;
			Subaccount sub;
			Withdrawal withdrawal;
			withdrawal.SetUserID(uID);
			std::string filter = withdrawal.GenerateFilter(ormasDal);
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
				int debAccID = cashboxAccID;
				if (0 == debAccID || 0 == credAccID)
				{
					return false;
				}
				if (this->CorrectingEntry(globalVar, ormasDal, credAccID, value, debAccID, ormasDal.GetSystemDateTime(), errorMessage))
				{
					BalanceWithdrawalRelation bwRelation;
					bwRelation.SetBalanceID(balance.GetID());
					bwRelation.SetWithdrawalID(this->id);
					if (bwRelation.DeleteBalanceWithdrawalRelation(globalVar, ormasDal, errorMessage))
						return true;
				}
			}
		}
		else if (aID > 0)
		{
			int credAccID = aID;
			int debAccID = cashboxAccID;
			if (0 == debAccID || 0 == credAccID)
			{
				return false;
			}
			if (this->CorrectingEntry(globalVar, ormasDal, credAccID, value, debAccID, ormasDal.GetSystemDateTime(), errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	bool Withdrawal::CancelWithdrawal(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, int cashboxAccID, std::string& errorMessage)
	{
		/*CashboxEmployeeRelation cashEmpRel;
		if (!cashEmpRel.GetCashboxEmployeeByEmployeeID(globalVar, ormasDal, loggedUserID, errorMessage))
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
		
		int credAccID = sID;
		int debAccID = cashboxAccID;
		if (0 == debAccID || 0 == credAccID)
		{
			return false;
		}
		if (this->CorrectingEntry(globalVar, ormasDal, credAccID, value, debAccID, ormasDal.GetSystemDateTime(), errorMessage))
		{
				return true;
		}
		return false;
	}

	bool Withdrawal::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
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
	bool Withdrawal::CreateEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, double previousSum, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(previousSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена снятие суммы со счета"));
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
		return true;
	}
	bool Withdrawal::CorrectingEntry(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int debAccID, double currentSum, int credAccID, std::string oExecDate, std::string& errorMessage)
	{
		Entry entry;
		EntryOperationRelation eoRelation;
		entry.SetDate(oExecDate);
		entry.SetDebitingAccountID(credAccID);
		entry.SetValue(currentSum);
		entry.SetCreditingAccountID(debAccID);
		entry.SetDescription(wstring_to_utf8(L"Отмена снятие суммы со счета"));
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

	int Withdrawal::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		Withdrawal withdrawal;
		if (withdrawal.GetWithdrawalByID(globalVar, ormasDal, pID, errorMessage))
			return withdrawal.GetStatusID();
		return 0;
	}
	
	std::string Withdrawal::wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}

