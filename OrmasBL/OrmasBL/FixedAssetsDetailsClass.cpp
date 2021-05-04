#include "stdafx.h"
#include "FixedAssetsDetailsClass.h"
#include "SubaccountClass.h"
#include "AccountClass.h"
#include "CurrencyClass.h"
#include "StatusClass.h"

namespace BusinessLayer
{
	FixedAssetsDetails::FixedAssetsDetails(DataLayer::fixedAssetsDetailsCollection fCollection)
	{
		id = std::get<0>(fCollection);
		amortizeGroupID = std::get<1>(fCollection);
		amortizeTypeID = std::get<2>(fCollection);
		departmentID = std::get<3>(fCollection);
		fixedAssetsLocation = std::get<4>(fCollection);
		primaryCostAccountID = std::get<5>(fCollection);
		amortizeAccountID = std::get<6>(fCollection);
		barcodeNumber = std::get<7>(fCollection);
		amortizeValue = std::get<8>(fCollection);
	}

	int FixedAssetsDetails::GetID()
	{
		return id;
	}

	int FixedAssetsDetails::GetAmortizeGroupID()
	{
		return amortizeGroupID;
	}

	int FixedAssetsDetails::GetAmortizeTypeID()
	{
		return amortizeTypeID;
	}

	int FixedAssetsDetails::GetDepartmentID()
	{
		return departmentID;
	}

	std::string FixedAssetsDetails::GetFixedAssetsLocation()
	{
		return fixedAssetsLocation;
	}

	int FixedAssetsDetails::GetPrimaryCostAccountID()
	{
		return primaryCostAccountID;
	}

	int FixedAssetsDetails::GetAmortizeAccountID()
	{
		return amortizeAccountID;
	}

	std::string FixedAssetsDetails::GetBarcodeNumber()
	{
		return barcodeNumber;
	}
	
	double FixedAssetsDetails::GetAmortizeValue()
	{
		return amortizeValue;
	}

	void FixedAssetsDetails::SetID(int fID)
	{
		id = fID;
	}

	void FixedAssetsDetails::SetAmortizeGroupID(int agID)
	{
		amortizeGroupID = agID;
	}

	void FixedAssetsDetails::SetAmortizeTypeID(int atID)
	{
		amortizeTypeID = atID;
	}

	void FixedAssetsDetails::SetDepartmentID(int dID)
	{
		departmentID = dID;
	}

	void FixedAssetsDetails::SetFixedAssetsLocation(std::string location)
	{
		fixedAssetsLocation = location;
	}

	void FixedAssetsDetails::SetPrimaryCostAccountID(int paID)
	{
		primaryCostAccountID = paID;
	}

	void FixedAssetsDetails::SetAmortizeAccountID(int aaID)
	{
		amortizeAccountID = aaID;
	}

	void FixedAssetsDetails::SetBarcodeNumber(std::string bNumber)
	{
		barcodeNumber = bNumber;
	}

	void FixedAssetsDetails::SetAmortizeValue(double amValue)
	{
		amortizeValue = amValue;
	}

	bool FixedAssetsDetails::CreateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int agID, int atID, int dID, std::string faLocation,
		int paID, int aaID, std::string bNumber, double amValue, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, paID, aaID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		amortizeGroupID = agID;
		amortizeTypeID = atID;
		departmentID = dID;
		fixedAssetsLocation = faLocation;
		primaryCostAccountID = paID;
		amortizeAccountID = aaID;
		barcodeNumber = bNumber;
		amortizeValue = amValue;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateFixedAssetsDetails(id, amortizeGroupID, amortizeTypeID, departmentID, fixedAssetsLocation,
			primaryCostAccountID, amortizeAccountID, barcodeNumber, amortizeValue, errorMessage))
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

	bool FixedAssetsDetails::CreateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateFixedAssetsDetails(id, amortizeGroupID, amortizeTypeID, departmentID, fixedAssetsLocation,
			primaryCostAccountID, amortizeAccountID, barcodeNumber, amortizeValue, errorMessage))
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
	bool FixedAssetsDetails::DeleteFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		FixedAssetsDetails fxd;
		if (!fxd.GetFixedAssetsDetailsByID(globalVar, ormasDal, id, errorMessage))
			return false;
		Subaccount primSub;
		Subaccount amSub;
		if (!primSub.GetSubaccountByID(globalVar, ormasDal, fxd.GetPrimaryCostAccountID(), errorMessage))
			return false;
		if (!amSub.GetSubaccountByID(globalVar, ormasDal, fxd.GetAmortizeAccountID(), errorMessage))
			return false;
		if (primSub.GetCurrentBalance() !=0 || amSub.GetCurrentBalance()!= 0)
			return false;
		if (ormasDal.DeleteFixedAssetsDetails(id, errorMessage))
		{
			if (primSub.DeleteSubaccount(globalVar, ormasDal, errorMessage) && amSub.DeleteSubaccount(globalVar, ormasDal, errorMessage))
				return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool FixedAssetsDetails::UpdateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int agID, int atID, int dID, std::string faLocation,
		int paID, int aaID, std::string bNumber, double amValue, std::string& errorMessage)
	{
		amortizeGroupID = agID;
		amortizeTypeID = atID;
		departmentID = dID;
		fixedAssetsLocation = faLocation;
		primaryCostAccountID = paID;
		amortizeAccountID = aaID;
		barcodeNumber = bNumber;
		amortizeValue = amValue;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateFixedAssetsDetails(id, amortizeGroupID, amortizeTypeID, departmentID, fixedAssetsLocation,
			primaryCostAccountID, amortizeAccountID, barcodeNumber, amortizeValue, errorMessage))
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
	bool FixedAssetsDetails::UpdateFixedAssetsDetails(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateFixedAssetsDetails(id, amortizeGroupID, amortizeTypeID, departmentID, fixedAssetsLocation,
			primaryCostAccountID, amortizeAccountID, barcodeNumber, amortizeValue, errorMessage))
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

	std::string FixedAssetsDetails::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != amortizeGroupID || !fixedAssetsLocation.empty() ||0 != amortizeTypeID || 0 != departmentID 
			|| !barcodeNumber.empty() || 0 != primaryCostAccountID || 0 != amortizeAccountID || 0 != amortizeValue)
		{
			return ormasDal.GetFilterForFixedAssetsDetails(id, amortizeGroupID, amortizeTypeID, departmentID, fixedAssetsLocation,
				primaryCostAccountID, amortizeAccountID, barcodeNumber, amortizeValue);
		}
		return "";
	}

	bool FixedAssetsDetails::GetFixedAssetsDetailsByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fID, std::string& errorMessage)
	{
		if (fID <= 0)
			return false;
		id = fID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsDetailsViewCollection> fixedAssetsDetailsVector = ormasDal.GetFixedAssetsDetails(errorMessage, filter);
		if (0 != fixedAssetsDetailsVector.size())
		{
			id = std::get<0>(fixedAssetsDetailsVector.at(0));
			amortizeGroupID = std::get<12>(fixedAssetsDetailsVector.at(0));
			amortizeTypeID = std::get<13>(fixedAssetsDetailsVector.at(0));
			departmentID = std::get<14>(fixedAssetsDetailsVector.at(0));
			fixedAssetsLocation = std::get<9>(fixedAssetsDetailsVector.at(0));
			primaryCostAccountID = std::get<10>(fixedAssetsDetailsVector.at(0));
			amortizeAccountID = std::get<11>(fixedAssetsDetailsVector.at(0));
			barcodeNumber = std::get<8>(fixedAssetsDetailsVector.at(0));
			amortizeValue = std::get<4>(fixedAssetsDetailsVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find fixed assets details with this id";
		}
		return false;
	}

	bool FixedAssetsDetails::IsEmpty()
	{
		if (0 == id && 0 == amortizeGroupID && 0 == amortizeTypeID && 0 == departmentID && fixedAssetsLocation == ""
			&& 0 == primaryCostAccountID && 0 == amortizeAccountID && barcodeNumber == "" && 0 !=amortizeValue)
			return true;
		return false;
	}

	void FixedAssetsDetails::Clear()
	{
		id = 0;
		amortizeGroupID = 0;
		amortizeTypeID = 0;
		departmentID = 0;
		fixedAssetsLocation = "";
		primaryCostAccountID = 0;
		amortizeAccountID = 0;
		barcodeNumber = "";
		amortizeValue = 0;
	}

	bool FixedAssetsDetails::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int aID, std::string& errorMessage)
	{
		FixedAssetsDetails fixedAssetsDetails;
		fixedAssetsDetails.Clear();
		errorMessage.clear();
		fixedAssetsDetails.SetPrimaryCostAccountID(pID);
		fixedAssetsDetails.SetAmortizeAccountID(aID);
		std::string filter = fixedAssetsDetails.GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsDetailsViewCollection> fixedAssetsDetailsVector = ormasDal.GetFixedAssetsDetails(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == fixedAssetsDetailsVector.size())
		{
			return false;
		}
		errorMessage = "Fixed assets details with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool FixedAssetsDetails::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		FixedAssetsDetails fixedAssetsDetails;
		fixedAssetsDetails.Clear();
		errorMessage.clear();
		fixedAssetsDetails.SetPrimaryCostAccountID(primaryCostAccountID);
		fixedAssetsDetails.SetAmortizeAccountID(amortizeAccountID);
		std::string filter = fixedAssetsDetails.GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsDetailsViewCollection> fixedAssetsDetailsVector = ormasDal.GetFixedAssetsDetails(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == fixedAssetsDetailsVector.size())
		{
			return false;
		}
		errorMessage = "Fixed assets details with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	int FixedAssetsDetails::GeneratePrimeSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double currentValue, std::string& errorMessage)
	{
		Account account;
		Subaccount subaccount;
		if (!account.GetAccountByID(globalVar, ormasDal, fixedAssetsAccountID, errorMessage))
			return 0;
		Currency currency;
		std::string number = "";
		std::string genAccRawNumber = "";
		int currID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 != currID)
		{
			Status status;
			if (!status.GetStatusByName(globalVar, ormasDal, "OPEN", errorMessage))
				return false;
			if (!currency.GetCurrencyByID(globalVar, ormasDal, currID, errorMessage))
				return false;
			number = account.GetNumber();
			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);
			subaccount.SetParentAccountID(account.GetID());
			subaccount.SetNumber(number);
			subaccount.SetStartBalance(currentValue);
			subaccount.SetCurrentBalance(currentValue);
			subaccount.SetCurrencyID(currID);
			subaccount.SetStatusID(status.GetID());
			subaccount.SetOpenedDate(ormasDal.GetSystemDate());
			subaccount.SetClosedDate("");
			subaccount.SetDetails("Generated by system");
			if (!subaccount.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return 0;
			return subaccount.GetID();
		}
		return 0;
	}

	int FixedAssetsDetails::GenerateAmortizeSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, double currentValue, std::string& errorMessage)
	{
		Account fxAccount;
		Subaccount subaccount;
		if (!fxAccount.GetAccountByID(globalVar, ormasDal, fixedAssetsAccountID, errorMessage))
			return 0;
		std::string fxNumber = fxAccount.GetNumber().substr(3,5);
		std::string amNumber = "111";
		amNumber.append(fxNumber);
		Account account;
		if (!account.GetAccountByNumber(globalVar, ormasDal, amNumber, errorMessage))
			return 0;
		Currency currency;
		std::string number = "";
		std::string genAccRawNumber = "";
		int currID = currency.GetMainTradeCurrencyID(globalVar, ormasDal, errorMessage);
		if (0 != currID)
		{
			Status status;
			if (!status.GetStatusByName(globalVar, ormasDal, "OPEN", errorMessage))
				return false;
			if (!currency.GetCurrencyByID(globalVar, ormasDal, currID, errorMessage))
				return false;
			number = account.GetNumber();
			number.append(std::to_string(currency.GetCode()));
			genAccRawNumber = subaccount.GenerateRawNumber(globalVar, ormasDal, errorMessage);
			if (genAccRawNumber.empty())
				return false;
			number.append(genAccRawNumber);
			subaccount.SetParentAccountID(account.GetID());
			subaccount.SetNumber(number);
			subaccount.SetStartBalance(currentValue*(-1));
			subaccount.SetCurrentBalance(currentValue*(-1));
			subaccount.SetCurrencyID(currID);
			subaccount.SetStatusID(status.GetID());
			subaccount.SetOpenedDate(ormasDal.GetSystemDate());
			subaccount.SetClosedDate("");
			subaccount.SetDetails("Generated by system");
			if (!subaccount.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return 0;
			return subaccount.GetID();
		}
		return 0;
	}
}
