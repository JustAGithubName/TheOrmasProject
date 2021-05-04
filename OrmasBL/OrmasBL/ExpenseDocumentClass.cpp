#include "stdafx.h"
#include "ExpenseDocumentClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	ExpenseDocument::ExpenseDocument(DataLayer::expenseDocumentCollection cCollection)
	{
		id = std::get<0>(cCollection);;
		expenseName = std::get<1>(cCollection);;
		count = std::get<2>(cCollection);
		sum = std::get<3>(cCollection);
		measureID = std::get<4>(cCollection);
		currencyID = std::get<5>(cCollection);
	}

	int ExpenseDocument::GetID()
	{
		return id;
	}
	std::string ExpenseDocument::GetExpenseName()
	{
		return expenseName;
	}
	double ExpenseDocument::GetCount()
	{
		return count;
	}
	double ExpenseDocument::GetSum()
	{
		return sum;
	}

	int ExpenseDocument::GetMeasureID()
	{
		return measureID;
	}
	int ExpenseDocument::GetCurrencyID()
	{
		return currencyID;
	}
	

	void ExpenseDocument::SetID(int aID)
	{
		id = aID;
	}
	void ExpenseDocument::SetExpenseName(std::string eName)
	{
		if (!eName.empty())
			boost::trim(eName);
		expenseName = eName;
	}

	void ExpenseDocument::SetCount(double eCount)
	{
		count = eCount;
	}
	void ExpenseDocument::SetSum(double eSum)
	{
		sum = eSum;
	}

	void ExpenseDocument::SetMeasureID(int mID)
	{
		measureID = mID;
	}
	void ExpenseDocument::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}
	

	bool ExpenseDocument::CreateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eName, double eCount, double eSum,
		int eMeasureID, int eCurrencyID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		TrimStrings(eName);
		expenseName = eName;
		count = eCount;
		sum = eSum;
		measureID = eMeasureID;
		currencyID = eCurrencyID;
		if (ormasDal.CreateExpenseDocument(id, expenseName, count, sum, measureID, currencyID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool ExpenseDocument::CreateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (ormasDal.CreateExpenseDocument(id, expenseName, count, sum, measureID, currencyID, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool ExpenseDocument::DeleteExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		if (ormasDal.DeleteExpenseDocument(id, errorMessage))
		{
			return true;
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool ExpenseDocument::UpdateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string eName, double eCount, double eSum, 
		int eMeasureID, int eCurrencyID, std::string& errorMessage)
	{
		TrimStrings(eName);
		expenseName = eName;
		count = eCount;
		sum = eSum;
		measureID = eMeasureID;
		currencyID = eCurrencyID;
		//ormasDal.StartTransaction(errorMessage);
		if (ormasDal.UpdateExpenseDocument(id, expenseName, count, sum, measureID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}
	bool ExpenseDocument::UpdateExpenseDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateExpenseDocument(id, expenseName, count, sum, measureID, currencyID, errorMessage))
		{
			return true;
		}
		return false;
	}

	std::string ExpenseDocument::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != measureID || 0 != currencyID || 0 != count || 0 != sum || !expenseName.empty())
		{
			return ormasDal.GetFilterForExpenseDocument(id, expenseName, count, sum, measureID, currencyID);
		}
		return "";
	}

	bool ExpenseDocument::GetExpenseDocumentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::expenseDocumentCollection> ExpenseDocumentVector = ormasDal.GetExpenseDocument(errorMessage, filter);
		if (0 != ExpenseDocumentVector.size())
		{
			id = std::get<0>(ExpenseDocumentVector.at(0));
			expenseName = std::get<1>(ExpenseDocumentVector.at(0));
			count = std::get<2>(ExpenseDocumentVector.at(0));
			sum = std::get<3>(ExpenseDocumentVector.at(0));
			measureID = std::get<4>(ExpenseDocumentVector.at(0));
			currencyID = std::get<5>(ExpenseDocumentVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find expense docuent with this id";
		}
		return false;
	}

	bool ExpenseDocument::IsEmpty()
	{
		if (0 == id && 0 == measureID && 0 == currencyID && 0 == count && 0 == sum && expenseName.empty())
			return true;
		return false;
	}

	void ExpenseDocument::Clear()
	{
		id = 0;
		expenseName.clear();
		count = 0;
		sum = 0;
		measureID = 0;
		currencyID = 0;
	}

	void ExpenseDocument::TrimStrings(std::string& eName)
	{
		if (!eName.empty())
			boost::trim(eName);
	}
}