#include "stdafx.h"
#include "AccountableDocumentClass.h"
#include "StatusClass.h"
#include <codecvt>

namespace BusinessLayer
{
	AccountableDocument::AccountableDocument(DataLayer::accountableDocumentCollection oCollection)
	{
		id = std::get<0>(oCollection);
		date = std::get<1>(oCollection);
		value = std::get<2>(oCollection);
		expenseAssignment = std::get<3>(oCollection);
		accountableID = std::get<4>(oCollection);
		statusID = std::get<5>(oCollection);
	}

	int AccountableDocument::GetID()
	{
		return id;
	}

	std::string AccountableDocument::GetDate()
	{
		return date;
	}

	std::string AccountableDocument::GetExpenseAssignment()
	{
		return expenseAssignment;
	}

	int AccountableDocument::GetAccountableID()
	{
		return accountableID;
	}

	double AccountableDocument::GetValue()
	{
		return value;
	}

	int AccountableDocument::GetStatusID()
	{
		return statusID;
	}


	void AccountableDocument::SetID(int oID)
	{
		id = oID;
	}
	
	void AccountableDocument::SetDate(std::string oDate)
	{
		date = oDate;
	}
	void AccountableDocument::SetExpenseAssignment(std::string oExpenseAssignment)
	{
		expenseAssignment = oExpenseAssignment;
	}
	void AccountableDocument::SetAccountableID(int oaccountableID)
	{
		accountableID = oaccountableID;
	}

	void AccountableDocument::SetValue(double oValue)
	{
		value = oValue;
	}

	void AccountableDocument::SetStatusID(int oStatusID)
	{
		statusID = oStatusID;
	}

	bool AccountableDocument::CreateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, double dValue,
		std::string dExpenseAssignment, int uID, int sID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aDate, dValue, dExpenseAssignment, uID, sID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		id = ormasDal.GenerateID();
		date = aDate;
		value = dValue;
		expenseAssignment = dExpenseAssignment;
		accountableID = uID;
		statusID = sID;
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateAccountableDocument(id, date, value, expenseAssignment, accountableID, statusID, errorMessage))
		{
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

	bool AccountableDocument::CreateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, date, value, expenseAssignment, accountableID, statusID, errorMessage))
			return false;
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		id = ormasDal.GenerateID();
		
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.CreateAccountableDocument(id, date, value, expenseAssignment, accountableID, statusID, errorMessage))
		{
			
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
	bool AccountableDocument::DeleteAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		AccountableDocument ord;
		if (!ord.GetAccountableDocumentByID(globalVar, ormasDal, id, errorMessage))
		{
			return false;
		}
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		if (ormasDal.DeleteAccountableDocument(id, errorMessage))
		{
			//ormasDal.CommitTransaction(errorMessage);
				return true;
		}
		else
		{
			//ormasDal.CancelTransaction(errorMessage);
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccountableDocument::UpdateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, double dValue,
		std::string dExpenseAssignment, int uID, int sID, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		date = aDate;
		value = dValue;
		expenseAssignment = dExpenseAssignment;
		accountableID = uID;
		statusID = sID;
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateAccountableDocument(id, aDate, dValue, dExpenseAssignment, uID, sID, errorMessage))
		{
					return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableDocument::UpdateAccountableDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = BusinessLayer::Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, id, errorMessage);
		//ormasDal.StartTransaction(errorMessage);
		globalVar->currentOperationID = id;
		if (0 != id && ormasDal.UpdateAccountableDocument(id, date, value, expenseAssignment, accountableID, statusID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string AccountableDocument::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountableID || !date.empty() || !expenseAssignment.empty() || 0 != value || 0 != statusID)
		{
			return ormasDal.GetFilterForAccountableDocument(id, date, value, expenseAssignment, accountableID, statusID);
		}
		return "";
	}

	std::string AccountableDocument::GenerateFilterFieldBiggerThen(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != accountableID || !date.empty() || !expenseAssignment.empty() || 0 != value || 0 != statusID)
		{
			return ormasDal.GetFilterForAccountableDocumentFieldBiggerThen(id, date, value, expenseAssignment, accountableID, statusID);
		}
		return "";
	}

	bool AccountableDocument::GetAccountableDocumentByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		id = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentCollection> accountableDocumentVector = ormasDal.GetAccountableDocument(errorMessage, filter);
		if (0 != accountableDocumentVector.size())
		{
			id = std::get<0>(accountableDocumentVector.at(0));
			date = std::get<1>(accountableDocumentVector.at(0));
			value = std::get<2>(accountableDocumentVector.at(0));
			expenseAssignment = std::get<3>(accountableDocumentVector.at(0));
			accountableID = std::get<4>(accountableDocumentVector.at(0));
			statusID = std::get<5>(accountableDocumentVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find accountable document with this id";
		}
		return false;
	}

	bool AccountableDocument::IsEmpty()
	{
		if (0 == id && date == "" && expenseAssignment == "" && 0 == value && 0 == accountableID  && 0 == statusID)
			return true;
		return false;
	}

	void AccountableDocument::Clear()
	{
		id = 0;
		date.clear();
		expenseAssignment.clear();
		accountableID = 0;
		statusID = 0;
	}

	bool AccountableDocument::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, double dValue,
		std::string dExpenseAssignment, int uID, int sID, std::string& errorMessage)
	{
		AccountableDocument accountableDocument;
		accountableDocument.Clear();
		errorMessage.clear();
		accountableDocument.SetDate(aDate);
		accountableDocument.SetValue(dValue);
		accountableDocument.SetExpenseAssignment(dExpenseAssignment);
		accountableDocument.SetAccountableID(uID);
		accountableDocument.SetStatusID(sID);
		std::string filter = accountableDocument.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentCollection> accountableDocumentVector = ormasDal.GetAccountableDocument(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableDocumentVector.size())
		{
			return false;
		}
		errorMessage = "Accountable document with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccountableDocument::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableDocument accountableDocument;
		accountableDocument.Clear();
		errorMessage.clear();
		accountableDocument.SetDate(date);
		accountableDocument.SetValue(value);
		accountableDocument.SetExpenseAssignment(expenseAssignment);
		accountableDocument.SetAccountableID(accountableID);
		accountableDocument.SetStatusID(statusID);
		std::string filter = accountableDocument.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentCollection> accountableDocumentVector = ormasDal.GetAccountableDocument(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableDocumentVector.size())
		{
			return false;
		}
		errorMessage = "Accountable document with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	int AccountableDocument::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		AccountableDocument AccountableDocument;
		if (AccountableDocument.GetAccountableDocumentByID(globalVar, ormasDal, oID, errorMessage))
			return AccountableDocument.GetStatusID();
		return 0;
	}
}