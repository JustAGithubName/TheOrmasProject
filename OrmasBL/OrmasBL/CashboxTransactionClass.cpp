#include "stdafx.h"
#include "CashboxTransactionClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	CashboxTransaction::CashboxTransaction(DataLayer::cashboxTransactionCollection cCollection)
	{
		id = std::get<0>(cCollection);
		cashboxID = std::get<1>(cCollection);
		cashierID = std::get<2>(cCollection);
		accountantID = std::get<3>(cCollection);
		ownerID = std::get<4>(cCollection);
		paymentID = std::get<5>(cCollection);
		withdrawalID = std::get<6>(cCollection);
	}
	CashboxTransaction::CashboxTransaction()
	{
		cashboxID = 0;
		cashierID = 0;
		accountantID = 0;
		ownerID = 0;
		paymentID = 0;
		withdrawalID = 0;
	}
	int CashboxTransaction::GetID()
	{
		return id;
	}

	int CashboxTransaction::GetCashboxID()
	{
		return cashboxID;
	}

	int CashboxTransaction::GetCashierID()
	{
		return cashierID;
	}

	int CashboxTransaction::GetAccountantID()
	{
		return accountantID;
	}

	int CashboxTransaction::GetOwnerID()
	{
		return ownerID;
	}

	int CashboxTransaction::GetPaymentID()
	{
		return paymentID;
	}
	
	int CashboxTransaction::GetWithdrawalID()
	{
		return withdrawalID;
	}


	void CashboxTransaction::SetID(int cID)
	{
		id = cID;
	}

	void CashboxTransaction::SetCashboxID(int cID)
	{
		cashboxID = cID;
	}

	void CashboxTransaction::SetCashierID(int cierID)
	{
		cashierID = cierID;
	}

	void CashboxTransaction::SetAccountantID(int aID)
	{
		accountantID = aID;
	}
	void CashboxTransaction::SetOwnerID(int oID)
	{
		ownerID = oID;
	}
	void CashboxTransaction::SetPaymentID(int pID)
	{
		paymentID = pID;
	}
	void CashboxTransaction::SetWithdrawalID(int wID)
	{
		withdrawalID = wID;
	}

	bool CashboxTransaction::CreateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cashbID, int cashiID, int accID, int ownID, int paymID, int withID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, paymID, withID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		cashboxID = cashbID;
		cashierID = cashiID;
		accountantID = accID;
		ownerID = ownID;
		paymentID = paymID;
		withdrawalID = withID;
		if (0 != id && ormasDal.CreateCashboxTransaction(id, cashboxID, cashierID, accountantID, ownerID, paymentID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CashboxTransaction::CreateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateCashboxTransaction(id, cashboxID, cashierID, accountantID, ownerID, paymentID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CashboxTransaction::DeleteCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCashboxTransaction(id, errorMessage))
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

	bool CashboxTransaction::UpdateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cashbID, int cashiID, int accID, int ownID, int paymID, int withID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, paymID, withID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		cashboxID = cashbID;
		cashierID = cashiID;
		accountantID = accID;
		ownerID = ownID;
		paymentID = paymID;
		withdrawalID = withID;
		if (0 != id && ormasDal.UpdateCashboxTransaction(id, cashboxID, cashierID, accountantID, ownerID, paymentID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool CashboxTransaction::UpdateCashboxTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateCashboxTransaction(id, cashboxID, cashierID, accountantID, ownerID, paymentID, withdrawalID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string CashboxTransaction::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != cashboxID || 0 != cashierID || 0 != accountantID || 0 != ownerID || 0 != paymentID
			|| 0 != withdrawalID)
		{
			return ormasDal.GetFilterForCashboxTransaction(id, cashboxID, cashierID, accountantID, ownerID, paymentID, withdrawalID);
		}
		return "";
	}

	bool CashboxTransaction::GetCashboxTransactionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxTransactionCollection> cashboxTransactionVector = ormasDal.GetCashboxTransaction(errorMessage, filter);
		if (0 != cashboxTransactionVector.size())
		{
			id = std::get<0>(cashboxTransactionVector.at(0));
			cashboxID = std::get<1>(cashboxTransactionVector.at(0));
			cashierID = std::get<2>(cashboxTransactionVector.at(0));
			accountantID = std::get<3>(cashboxTransactionVector.at(0));
			ownerID = std::get<4>(cashboxTransactionVector.at(0));
			paymentID = std::get<5>(cashboxTransactionVector.at(0));
			withdrawalID = std::get<6>(cashboxTransactionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find cashbox transaction with this id";
		}
		return false;
	}

	bool CashboxTransaction::GetCashboxTransactionByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		paymentID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxTransactionCollection> cashboxTransactionVector = ormasDal.GetCashboxTransaction(errorMessage, filter);
		if (0 != cashboxTransactionVector.size())
		{
			id = std::get<0>(cashboxTransactionVector.at(0));
			cashboxID = std::get<1>(cashboxTransactionVector.at(0));
			cashierID = std::get<2>(cashboxTransactionVector.at(0));
			accountantID = std::get<3>(cashboxTransactionVector.at(0));
			ownerID = std::get<4>(cashboxTransactionVector.at(0));
			paymentID = std::get<5>(cashboxTransactionVector.at(0));
			withdrawalID = std::get<6>(cashboxTransactionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find cashbox transaction with this payment id";
		}
		return false;
	}

	bool CashboxTransaction::GetCashboxTransactionByWithdrawalID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int wID, std::string& errorMessage)
	{
		if (wID <= 0)
			return false;
		withdrawalID = wID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxTransactionCollection> cashboxTransactionVector = ormasDal.GetCashboxTransaction(errorMessage, filter);
		if (0 != cashboxTransactionVector.size())
		{
			id = std::get<0>(cashboxTransactionVector.at(0));
			cashboxID = std::get<1>(cashboxTransactionVector.at(0));
			cashierID = std::get<2>(cashboxTransactionVector.at(0));
			accountantID = std::get<3>(cashboxTransactionVector.at(0));
			ownerID = std::get<4>(cashboxTransactionVector.at(0));
			paymentID = std::get<5>(cashboxTransactionVector.at(0));
			withdrawalID = std::get<6>(cashboxTransactionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find cashbox transaction with this withdrawal id";
		}
		return false;
	}

	bool CashboxTransaction::GetCashboxTransactionByCashierID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cierID, std::string& errorMessage)
	{
		if (cierID <= 0)
			return false;
		cashierID = cierID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxTransactionCollection> cashboxTransactionVector = ormasDal.GetCashboxTransaction(errorMessage, filter);
		if (0 != cashboxTransactionVector.size())
		{
			id = std::get<0>(cashboxTransactionVector.at(0));
			cashboxID = std::get<1>(cashboxTransactionVector.at(0));
			cashierID = std::get<2>(cashboxTransactionVector.at(0));
			accountantID = std::get<3>(cashboxTransactionVector.at(0));
			ownerID = std::get<4>(cashboxTransactionVector.at(0));
			paymentID = std::get<5>(cashboxTransactionVector.at(0));
			withdrawalID = std::get<6>(cashboxTransactionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find cashbox transaction with this cashier id";
		}
		return false;
	}

	bool CashboxTransaction::IsEmpty()
	{
		if (0 == id && 0 == cashboxID && 0 == cashierID && 0 == accountantID && 0 == ownerID && 0 == paymentID && 0 == withdrawalID)
			return true;
		return false;
	}

	void CashboxTransaction::Clear()
	{
		id = 0;
		cashboxID = 0;
		cashierID = 0;
		accountantID = 0;
		ownerID = 0;
		paymentID = 0;
		withdrawalID = 0;
	}

	bool CashboxTransaction::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int wID, std::string& errorMessage)
	{
		CashboxTransaction cashboxTransaction;
		cashboxTransaction.Clear();
		errorMessage.clear();
		if (pID > 0)
		{
			cashboxTransaction.SetPaymentID(pID);
		}
		else if (wID > 0)
		{
			cashboxTransaction.SetWithdrawalID(wID);
		}
		
		std::string filter = cashboxTransaction.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxTransactionCollection> cashboxTransactionVector = ormasDal.GetCashboxTransaction(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == cashboxTransactionVector.size())
		{
			return false;
		}
		errorMessage = "Cashbox transaction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool CashboxTransaction::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		CashboxTransaction cashboxTransaction;
		cashboxTransaction.Clear();
		errorMessage.clear();
		if (paymentID > 0)
		{
			cashboxTransaction.SetPaymentID(paymentID);
		}
		else if (withdrawalID > 0)
		{
			cashboxTransaction.SetWithdrawalID(withdrawalID);
		}

		std::string filter = cashboxTransaction.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxTransactionCollection> cashboxTransactionVector = ormasDal.GetCashboxTransaction(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == cashboxTransactionVector.size())
		{
			return false;
		}
		errorMessage = "Cashbox transaction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

