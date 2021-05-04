#include "stdafx.h"
#include "AccountableTransactionClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AccountableTransaction::AccountableTransaction(DataLayer::accountableTransactionCollection aCollection)
	{
		id = std::get<0>(aCollection);
		residualValue = std::get<1>(aCollection);
		totalValue = std::get<2>(aCollection);
		spentValue = std::get<3>(aCollection);
		differenceValue = std::get<4>(aCollection);
		accountableDocumentID = std::get<5>(aCollection);
	}
	AccountableTransaction::AccountableTransaction()
	{
		id = 0;
		residualValue = 0;
		totalValue = 0.0;
		spentValue = 0.0;
		differenceValue = 0;
		accountableDocumentID = 0;
	}

	int AccountableTransaction::GetID()
	{
		return id;
	}

	double AccountableTransaction::GetResidualValue()
	{
		return residualValue;
	}

	double AccountableTransaction::GetTotalValue()
	{
		return totalValue;
	}

	double AccountableTransaction::GetSpentValue()
	{
		return spentValue;
	}

	double AccountableTransaction::GetDifferenceValue()
	{
		return differenceValue;
	}



	int AccountableTransaction::GeAccountableDocumentID()
	{
		return accountableDocumentID;
	}


	void AccountableTransaction::SetID(int aID)
	{
		id = aID;
	}

	void AccountableTransaction::SetResidualValue(double aResValue)
	{
		residualValue = aResValue;
	}

	void AccountableTransaction::SetTotalValue(double aTotalValue)
	{
		totalValue = aTotalValue;
	}

	void AccountableTransaction::SetSpentValue(double aSpentValue)
	{
		spentValue = aSpentValue;
	}

	void AccountableTransaction::SetDifferenceValue(double aDiffValue)
	{
		differenceValue = aDiffValue;
	}

	void AccountableTransaction::SetAccountableDocumentID(int docID)
	{
		accountableDocumentID
			= docID;
	}


	bool AccountableTransaction::CreateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double resValue, double totValue, 
		double speValue, double diffValue, int aID, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, resValue, totValue, speValue, diffValue, aID, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		residualValue = resValue;
		totalValue = totValue;
		spentValue = speValue;
		differenceValue = diffValue;
		accountableDocumentID = aID;
		if (0 != id && ormasDal.CreateAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableTransaction::CreateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
		//	return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableTransaction::DeleteAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountableTransaction(id, errorMessage))
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
	bool AccountableTransaction::DeleteAccountableTransactionByDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccountableTransactionByDocumentID(accountableDocumentID, errorMessage))
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

	bool AccountableTransaction::UpdateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double resValue, double totValue, double speValue, double diffValue, int aID, std::string& errorMessage)
	{
		residualValue = resValue;
		totalValue = totValue;
		spentValue = speValue;
		differenceValue = diffValue;
		accountableDocumentID = aID;
		if (0 != id && ormasDal.UpdateAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableTransaction::UpdateAccountableTransaction(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	bool AccountableTransaction::IncCascadeTransactionUpdate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int docID, double value, std::string& errorMessage)
	{
		AccountableTransaction aTrans;
		aTrans.SetAccountableDocumentID(docID);
		std::string filter = aTrans.GenerateFieldBiggerThenFilter(ormasDal);
		std::vector<DataLayer::accountableTransactionCollection> accountableTransactionVector = ormasDal.GetAccountableTransaction(errorMessage, filter);
		if (accountableTransactionVector.size() <= 0)
		{
			return true;
		}
		else
		{
			id = std::get<0>(accountableTransactionVector.at(0));
			residualValue = std::get<1>(accountableTransactionVector.at(0));
			totalValue = std::get<2>(accountableTransactionVector.at(0));
			spentValue = std::get<3>(accountableTransactionVector.at(0));
			differenceValue = std::get<4>(accountableTransactionVector.at(0));
			accountableDocumentID = std::get<5>(accountableTransactionVector.at(0));
			residualValue += value;
			totalValue += value;
			differenceValue += value;
			if (0 != id && ormasDal.UpdateAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID, errorMessage))
			{
				return true;
			}
			if (errorMessage.empty())
			{
				errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
			}
			return false;
		}
	}

	bool AccountableTransaction::DecCascadeTransactionUpdate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int docID, double value, std::string& errorMessage)
	{
		AccountableTransaction aTrans;
		aTrans.SetAccountableDocumentID(docID);
		std::string filter = aTrans.GenerateFieldBiggerThenFilter(ormasDal);
		std::vector<DataLayer::accountableTransactionCollection> accountableTransactionVector = ormasDal.GetAccountableTransaction(errorMessage, filter);
		if (accountableTransactionVector.size() <= 0)
		{
			return true;
		}
		else
		{
			id = std::get<0>(accountableTransactionVector.at(0));
			residualValue = std::get<1>(accountableTransactionVector.at(0));
			totalValue = std::get<2>(accountableTransactionVector.at(0));
			spentValue = std::get<3>(accountableTransactionVector.at(0));
			differenceValue = std::get<4>(accountableTransactionVector.at(0));
			accountableDocumentID = std::get<5>(accountableTransactionVector.at(0));
			residualValue -= value;
			totalValue -= value;
			differenceValue -= value;
			if (0 != id && ormasDal.UpdateAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID, errorMessage))
			{
				return true;
			}
			if (errorMessage.empty())
			{
				errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
			}
			return false;
		}
	}

	std::string AccountableTransaction::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != residualValue || 0.0 != totalValue || 0.0 != spentValue || 0 != differenceValue || 0 != accountableDocumentID)
		{
			return ormasDal.GetFilterForAccountableTransaction(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID);
		}
		return "";
	}

	std::string AccountableTransaction::GenerateFieldBiggerThenFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != residualValue || 0.0 != totalValue || 0.0 != spentValue || 0 != differenceValue || 0 != accountableDocumentID)
		{
			return ormasDal.GetFilterForAccTransFieldBiggerThen(id, residualValue, totalValue, spentValue, differenceValue, accountableDocumentID);
		}
		return "";
	}

	bool AccountableTransaction::GetAccountableTransactionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int atID, std::string& errorMessage)
	{
		if (atID <= 0)
			return false;
		id = atID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableTransactionCollection> accountableTransactionVector = ormasDal.GetAccountableTransaction(errorMessage, filter);
		if (0 != accountableTransactionVector.size())
		{
			id = std::get<0>(accountableTransactionVector.at(0));
			residualValue = std::get<1>(accountableTransactionVector.at(0));
			totalValue = std::get<2>(accountableTransactionVector.at(0));
			spentValue = std::get<3>(accountableTransactionVector.at(0));
			differenceValue = std::get<4>(accountableTransactionVector.at(0));
			accountableDocumentID = std::get<5>(accountableTransactionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find accountable transaction with this id";
		}
		return false;
	}

	bool AccountableTransaction::GetAccountableTransactionByAccountableDocumentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		accountableDocumentID = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableTransactionCollection> accountableTransactionVector = ormasDal.GetAccountableTransaction(errorMessage, filter);
		if (0 != accountableTransactionVector.size())
		{
			id = std::get<0>(accountableTransactionVector.at(0));
			residualValue = std::get<1>(accountableTransactionVector.at(0));
			totalValue = std::get<2>(accountableTransactionVector.at(0));
			spentValue = std::get<3>(accountableTransactionVector.at(0));
			differenceValue = std::get<4>(accountableTransactionVector.at(0));
			accountableDocumentID = std::get<5>(accountableTransactionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find accountable transaction with this id";
		}
		return false;
	}

	bool AccountableTransaction::IsEmpty()
	{
		if (0 == id && 0 == residualValue && 0.0 == totalValue && 0.0 == spentValue && 0.0 == differenceValue && 0.0 == accountableDocumentID)
			return true;
		return false;
	}

	

	void AccountableTransaction::Clear()
	{
		id = 0;
		residualValue = 0;
		totalValue = 0.0;
		spentValue = 0.0;
		differenceValue = 0;
		accountableDocumentID = 0;
	}

	bool AccountableTransaction::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double resValue, double totValue, double speValue, double diffValue, int aID, std::string& errorMessage)
	{
		AccountableTransaction accountableTransaction;
		accountableTransaction.Clear();
		errorMessage.clear();
		accountableTransaction.SetResidualValue(resValue);
		accountableTransaction.SetTotalValue(totValue);
		accountableTransaction.SetSpentValue(speValue);
		accountableTransaction.SetDifferenceValue(diffValue);
		accountableTransaction.SetAccountableDocumentID(aID);
		std::string filter = accountableTransaction.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableTransactionCollection> accountableTransactionVector = ormasDal.GetAccountableTransaction(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableTransactionVector.size())
		{
			return false;
		}
		errorMessage = "Accountable transaction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableTransaction::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableTransaction accountableTransaction;
		accountableTransaction.Clear();
		errorMessage.clear();
		accountableTransaction.SetResidualValue(residualValue);
		accountableTransaction.SetTotalValue(totalValue);
		accountableTransaction.SetSpentValue(spentValue);
		accountableTransaction.SetDifferenceValue(differenceValue);
		accountableTransaction.SetAccountableDocumentID(accountableDocumentID);
		std::string filter = accountableTransaction.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableTransactionCollection> accountableTransactionVector = ormasDal.GetAccountableTransaction(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableTransactionVector.size())
		{
			return false;
		}
		errorMessage = "Accountable transaction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}