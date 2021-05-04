#include "stdafx.h"
#include "SubaccountClass.h"
#include "SubaccountChangeLogClass.h"
#include "ChartOfAccountsClass.h"
#include "AccountTypeClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Subaccount::Subaccount(DataLayer::subaccountsCollection saCollection)
	{
		id = std::get<0>(saCollection);
		parentSubaccountID = std::get<1>(saCollection);
		number = std::get<2>(saCollection);
		startBalance = std::get<3>(saCollection);
		currentBalance = std::get<4>(saCollection);
		currencyID = std::get<5>(saCollection);
		statusID = std::get<6>(saCollection);
		openedDate = std::get<7>(saCollection);
		closedDate = std::get<8>(saCollection);
		details = std::get<9>(saCollection);
	}
	Subaccount::Subaccount()
	{
		id = 0;
		parentSubaccountID = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
		currencyID = 0;
		statusID = 0;
		openedDate = "";
		closedDate = "";
		details = "";
	}

	int Subaccount::GetID()
	{
		return id;
	}

	int Subaccount::GetParentAccountID()
	{
		return parentSubaccountID;
	}

	std::string Subaccount::GetNumber()
	{
		return number;
	}

	double Subaccount::GetStartBalance()
	{
		return startBalance;
	}

	double Subaccount::GetCurrentBalance()
	{
		return currentBalance;
	}

	int Subaccount::GetCurrencyID()
	{
		return currencyID;
	}
	
	int Subaccount::GetStatusID()
	{
		return statusID;
	}

	std::string Subaccount::GetOpenedDate()
	{
		return openedDate;
	}

	std::string Subaccount::GetClosedDate()
	{
		return closedDate;
	}

	std::string Subaccount::GetDetails()
	{
		return details;
	}

	void Subaccount::SetID(int aID)
	{
		id = aID;
	}

	void Subaccount::SetParentAccountID(int saID)
	{
		parentSubaccountID = saID;
	}

	void Subaccount::SetNumber(std::string aNumber)
	{
		number = aNumber;
	}

	void Subaccount::SetStartBalance(double aStartBalance)
	{
		startBalance = aStartBalance;
	}

	void Subaccount::SetCurrentBalance(double aCurrentBalance)
	{
		currentBalance = aCurrentBalance;
	}

	void Subaccount::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	void Subaccount::SetStatusID(int sID)
	{
		statusID = sID;
	}

	void Subaccount::SetOpenedDate(std::string aOpenedDate)
	{
		openedDate = aOpenedDate;
	}

	void Subaccount::SetClosedDate(std::string aClosedDate)
	{
		closedDate = aClosedDate;
	}
	
	void Subaccount::SetDetails(std::string aDetails)
	{
		details = aDetails;
	}

	bool Subaccount::CreateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, std::string aNumber, double aStartBalance, double aCurrentBalance, int cID,
		int sID, std::string aOpenedDate, std::string aClosedDate, std::string aDetails, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aNumber, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		parentSubaccountID = saID;
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		currencyID = cID;
		statusID = sID;
		openedDate = aOpenedDate;
		closedDate = aClosedDate;
		details = aDetails;
		if (0 != id && ormasDal.CreateSubaccount(id, parentSubaccountID, number, startBalance, currentBalance, currencyID, statusID,
			openedDate, closedDate,	details, errorMessage))
		{
			if (CreateSubaccountChangeLog(globalVar, ormasDal, id, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Subaccount::CreateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateSubaccount(id, parentSubaccountID, number, startBalance, currentBalance, currencyID, statusID,
			openedDate, closedDate, details, errorMessage))
		{
			if (CreateSubaccountChangeLog(globalVar, ormasDal, id, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Subaccount::DeleteSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteSubaccount(id, errorMessage))
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

	bool Subaccount::UpdateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int saID, std::string aNumber, double aStartBalance, double aCurrentBalance, int cID,
		int sID, std::string aOpenedDate, std::string aClosedDate, std::string aDetails, std::string& errorMessage)
	{
		parentSubaccountID = saID;
		number = aNumber;
		startBalance = aStartBalance;
		currentBalance = aCurrentBalance;
		currencyID = cID;
		statusID = sID;
		openedDate = aOpenedDate;
		closedDate = aClosedDate;
		details = aDetails;
		if (0 != id && ormasDal.UpdateSubaccount(id, parentSubaccountID, number, startBalance, currentBalance, currencyID, statusID,
			openedDate, closedDate, details, errorMessage))
		{
			if (CreateSubaccountChangeLog(globalVar, ormasDal, id, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Subaccount::UpdateSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateSubaccount(id, parentSubaccountID, number, startBalance, currentBalance, currencyID, statusID,
			openedDate, closedDate, details, errorMessage))
		{
			if (CreateSubaccountChangeLog(globalVar, ormasDal, id, startBalance, currentBalance, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Subaccount::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != parentSubaccountID || !number.empty() || 0.0 != startBalance || 0.0 != currentBalance || 0 != currencyID || 0 != statusID
			|| !openedDate.empty() || !closedDate.empty() || !details.empty())
		{
			return ormasDal.GetFilterForSubaccount(id, parentSubaccountID, number, startBalance, currentBalance, currencyID, statusID, openedDate, closedDate,
				details);
		}
		return "";
	}

	std::string Subaccount::GenerateINFilter(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList)
	{
		if (subaccountIDList.size()>0)
		{
			return ormasDal.GetINFilterForSubaccountID(subaccountIDList);
		}
		return "";
	}

	bool Subaccount::GetSubaccountByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountsViewCollection> subaccountVector = ormasDal.GetSubaccounts(errorMessage, filter);
		if (0 != subaccountVector.size())
		{
			id = std::get<0>(subaccountVector.at(0));
			parentSubaccountID = std::get<1>(subaccountVector.at(0));
			number = std::get<3>(subaccountVector.at(0));
			startBalance = std::get<4>(subaccountVector.at(0));
			currentBalance = std::get<5>(subaccountVector.at(0));
			currencyID = std::get<8>(subaccountVector.at(0));
			statusID = std::get<9>(subaccountVector.at(0));
			openedDate = std::get<10>(subaccountVector.at(0));
			closedDate = std::get<11>(subaccountVector.at(0));
			details = std::get<12>(subaccountVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount with this id";
		}
		return false;
	}

	bool Subaccount::GetSubaccountByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage)
	{
		if (aNumber.empty())
			return false;
		number = aNumber;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountsViewCollection> subaccountVector = ormasDal.GetSubaccounts(errorMessage, filter);
		if (0 != subaccountVector.size())
		{
			id = std::get<0>(subaccountVector.at(0));
			parentSubaccountID = std::get<1>(subaccountVector.at(0));
			number = std::get<3>(subaccountVector.at(0));
			startBalance = std::get<4>(subaccountVector.at(0));
			currentBalance = std::get<5>(subaccountVector.at(0));
			currencyID = std::get<8>(subaccountVector.at(0));
			statusID = std::get<9>(subaccountVector.at(0));
			openedDate = std::get<10>(subaccountVector.at(0));
			closedDate = std::get<11>(subaccountVector.at(0));
			details = std::get<12>(subaccountVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Subaccount with this id";
		}
		return false;
	}

	std::string Subaccount::GenerateRawNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		int countOfNulls;
		int genNumber = ormasDal.GenerateAccountID();
		std::string accNumber = "";
		std::string genNumberStr = std::to_string(genNumber);
		if (genNumberStr.length() < 7)
		{
			countOfNulls = 7 - genNumberStr.length();
			for (int i = 0; i < countOfNulls; i++)
			{
				accNumber.append("0");
			}
			accNumber.append(genNumberStr);
			return accNumber;
		}
		return "";
	}

	bool Subaccount::IsEmpty()
	{
		if (0 == id && 0 == parentSubaccountID && number.empty() && 0.0 == startBalance && 0.0 == currentBalance && 0 == currencyID && 0 == statusID
			&& openedDate.empty() && closedDate.empty() && details.empty())
			return true;
		return false;
	}

	void Subaccount::Clear()
	{
		id = 0;
		parentSubaccountID = 0;
		number = "";
		startBalance = 0.0;
		currentBalance = 0.0;
		currencyID = 0;
		statusID = 0;
		openedDate = "";
		closedDate = "";
		details = "";
	}

	bool Subaccount::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNumber, std::string& errorMessage)
	{
		Subaccount subaccount;
		subaccount.Clear();
		errorMessage.clear();
		subaccount.SetNumber(aNumber);
		std::string filter = subaccount.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountsViewCollection> subaccountVector = ormasDal.GetSubaccounts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Subaccount::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Subaccount subaccount;
		subaccount.Clear();
		errorMessage.clear();
		subaccount.SetNumber(number);
		std::string filter = subaccount.GenerateFilter(ormasDal);
		std::vector<DataLayer::subaccountsViewCollection> subaccountVector = ormasDal.GetSubaccounts(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == subaccountVector.size())
		{
			return false;
		}
		errorMessage = "Subaccount with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	std::string Subaccount::GetName(DataLayer::OrmasDal& ormasDal)
	{
		ChartOfAccounts chartOfAccounts;
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountsVector;
		if (!this->GetNumber().empty() && this->GetNumber().length() > 0)
		{
			std::string numberOfSubaccount = this->GetNumber().substr(0, 5);
			chartOfAccounts.SetNumber(numberOfSubaccount);
			std::string filter = chartOfAccounts.GenerateFilter(ormasDal);
			chartOfAccountsVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
			if (0 < chartOfAccountsVector.size())
			{
				return std::get<2>(chartOfAccountsVector.at(0));
			}
		}
		return "";
	}

	std::string Subaccount::GetSubaccountParentNumber(DataLayer::OrmasDal& ormasDal)
	{
		ChartOfAccounts chartOfAccounts;
		std::vector<DataLayer::chartOfAccountsViewCollection> chartOfAccountssVector;
		if (!this->GetNumber().empty() && this->GetNumber().length() > 0)
		{
			std::string numberOfSubaccount = this->GetNumber().substr(0, 5);
			chartOfAccounts.SetNumber(numberOfSubaccount);
			std::string filter = chartOfAccounts.GenerateFilter(ormasDal);
			chartOfAccountssVector = ormasDal.GetChartOfAccounts(errorMessage, filter);
			if (0 < chartOfAccountssVector.size())
			{
				return std::get<1>(chartOfAccountssVector.at(0));
				
			}
		}
		return "";
	}

	int Subaccount::GetSubaccountTypeNumber(DataLayer::OrmasDal& ormasDal)
	{
		std::string partentNumberOfSubaccount = this->GetNumber().substr(7, 1);
		return std::stoi(partentNumberOfSubaccount);
	}

	bool Subaccount::SubaccountOperationValidation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double aValue)
	{
		/*SubaccountType atype;
		if (atype.GetSubaccountTypeByNumber(globalVar, ormasDal, GetSubaccountTypeNumber(ormasDal), errorMessage))
		{
			if (0 == atype.GetName().compare("ACTIVE"))
			{
				if (aValue > 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			if (0 == atype.GetName().compare("PASSIVE"))
			{
				if (aValue < 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			if (0 == atype.GetName().compare("ACTIVE/PASSIVE"))
			{
				return true;
			}
		}*/
		return true;
	}

	bool Subaccount::CreateSubaccountChangeLog(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int subaccountID, double aStartBalance, 
		double aCurrentBalance,  std::string& errorMessage)
	{
		SubaccountChangeLog scLog;
		scLog.SetSubaccountID(subaccountID);
		scLog.SetStartBalance(aStartBalance);
		scLog.SetCurrentBalance(aCurrentBalance);
		scLog.SetLogDate(ormasDal.GetSystemDateTime());
		scLog.SetUserID(globalVar->userID);
		scLog.SetOperationID(globalVar->currentOperationID);
		if (scLog.CreateSubaccountChangeLog(globalVar, ormasDal, errorMessage))
			return true;
		return false;
	}
}