#include "stdafx.h"
#include "MulticurrencyClass.h"
#include <boost/algorithm/string.hpp>
#include "CurrencyRateClass.h"
#include "SubaccountClass.h"
#include "BalanceClass.h"

namespace BusinessLayer
{
	Multicurrency::Multicurrency(DataLayer::multicurrencyCollection curCollection)
	{
		id = std::get<0>(curCollection);
		subaccountCurrencyID = std::get<1>(curCollection);
		subaccountMainCurrencyID = std::get<2>(curCollection);
		comment = std::get<3>(curCollection);
	}

	int Multicurrency::GetID()
	{
		return id;
	}

	int Multicurrency::GetSubaccountCurrencyID()
	{
		return subaccountCurrencyID;
	}

	int Multicurrency::GetSubaccountMainCurrencyID()
	{
		return subaccountMainCurrencyID;
	}

	std::string Multicurrency::GetComment()
	{
		return comment;
	}


	Subaccount Multicurrency::GetExchangeSubaccount()
	{
		return exchangeSubaccount;
	}

	Subaccount Multicurrency::GetMainSubaccount()
	{
		return mainSubaccount;
	}


	void Multicurrency::SetID(int cID)
	{
		id = cID;
	}
	void Multicurrency::SetSubaccountCurrencyID(int sID)
	{
		subaccountCurrencyID = sID;
	}
	void Multicurrency::SetSubaccountMainCurrencyID(int smID)
	{
		subaccountMainCurrencyID = smID;
	}
	void Multicurrency::SetComment(std::string sComment)
	{
		if (!sComment.empty())
			boost::trim(sComment);
		comment = sComment;
	}

	void Multicurrency::SetExchangeSubaccount(Subaccount& eSub)
	{
		exchangeSubaccount = eSub;
	}

	void Multicurrency::SetMainSubaccount(Subaccount& mSub)
	{
		mainSubaccount = mSub;
	}

	bool Multicurrency::CreateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int scID, int smID, std::string mComment, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, scID, smID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(mComment);
		subaccountCurrencyID = scID;
		comment = mComment;
		subaccountMainCurrencyID = smID;
		if (0 != id && ormasDal.CreateMulticurrency(id, subaccountCurrencyID, subaccountMainCurrencyID, comment,  errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Multicurrency::CreateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateMulticurrency(id, subaccountCurrencyID, subaccountMainCurrencyID, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Multicurrency::DeleteMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Multicurrency multicur;
		if (!multicur.GetMulticurrencyByID(globalVar, ormasDal, id, errorMessage))
			return false;
		Subaccount subacc;
		subacc.SetID(multicur.GetSubaccountCurrencyID());
		if (!subacc.DeleteSubaccount(globalVar, ormasDal, errorMessage))
			return false;
		if (ormasDal.DeleteMulticurrency(id, errorMessage))
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
	bool Multicurrency::UpdateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int scID, int smID, std::string mComment, std::string& errorMessage)
	{

		TrimStrings(mComment);
		subaccountCurrencyID = scID;
		comment = mComment;
		subaccountMainCurrencyID = smID;
		if (0 != id && ormasDal.UpdateMulticurrency(id, subaccountCurrencyID, subaccountMainCurrencyID, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Multicurrency::UpdateMulticurrency(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateMulticurrency(id, subaccountCurrencyID, subaccountMainCurrencyID, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	int Multicurrency::CreateExchangeSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Subaccount exchSub, std::string& errorMessage)
	{
		if (!exchSub.IsEmpty())
		{
			if (!exchSub.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return 0;
			return exchSub.GetID();
		}
		return 0;
	}

	int Multicurrency::CreateMainSubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, Subaccount mainSub, std::string& errorMessage)
	{
		if (!mainSub.IsEmpty())
		{
			if (!mainSub.CreateSubaccount(globalVar, ormasDal, errorMessage))
				return 0;
			return mainSub.GetID();
		}
		return 0;
	}

	std::string Multicurrency::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountCurrencyID || 0 != subaccountMainCurrencyID || !comment.empty())
		{
			return ormasDal.GetFilterForMulticurrency(id, subaccountCurrencyID, subaccountMainCurrencyID, comment);
		}
		return "";
	}
	
	std::string Multicurrency::GenerateINFilterForExchangeSub(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList)
	{
		if (subaccountIDList.size()>0)
		{
			return ormasDal.GetINFilterForExchangeSubaccount(subaccountIDList);
		}
		return "";
	}

	std::string Multicurrency::GenerateINFilterForMainSub(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::vector<int> subaccountIDList)
	{
		if (subaccountIDList.size()>0)
		{
			return ormasDal.GetINFilterForMainSubaccount(subaccountIDList);
		}
		return "";
	}

	bool Multicurrency::GetMulticurrencyByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (0 != multicurrencyVector.size())
		{
			id = std::get<0>(multicurrencyVector.at(0));
			subaccountCurrencyID = std::get<7>(multicurrencyVector.at(0));
			subaccountMainCurrencyID = std::get<8>(multicurrencyVector.at(0));
			comment = std::get<9>(multicurrencyVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find mulricurrency rate with this id";
		}
		return false;
	}

	std::vector<int> Multicurrency::GetAllExchSubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::vector<int> subIDVec;
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage);
		for each (auto item in multicurrencyVector)
		{
			subIDVec.push_back(std::get<7>(item));
			
		}
		return subIDVec;
	}

	std::vector<int> Multicurrency::GetAllMainSubaccountID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::vector<int> subIDVec;
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage);
		for each (auto item in multicurrencyVector)
		{
			subIDVec.push_back(std::get<8>(item));
		
		}
		return subIDVec;
	}

	bool Multicurrency::GetMulticurrencyBySubCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int scID, std::string& errorMessage)
	{
		if (scID <= 0)
			return false;
		subaccountCurrencyID = scID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (0 != multicurrencyVector.size())
		{
			id = std::get<0>(multicurrencyVector.at(0));
			subaccountCurrencyID = std::get<7>(multicurrencyVector.at(0));
			subaccountMainCurrencyID = std::get<8>(multicurrencyVector.at(0));
			comment = std::get<9>(multicurrencyVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find mulricurrency rate with this id";
		}
		return false;
	}

	bool Multicurrency::GetMulticurrencyByMainCurrencyID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int smID, std::string& errorMessage)
	{
		if (smID <= 0)
			return false;
		subaccountMainCurrencyID = smID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (0 != multicurrencyVector.size())
		{
			id = std::get<0>(multicurrencyVector.at(0));
			subaccountCurrencyID = std::get<7>(multicurrencyVector.at(0));
			subaccountMainCurrencyID = std::get<8>(multicurrencyVector.at(0));
			comment = std::get<9>(multicurrencyVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find mulricurrency rate with this id";
		}
		return false;
	}


	bool Multicurrency::IsEmpty()
	{
		if (0 == id && 0 == subaccountCurrencyID && 0 == subaccountMainCurrencyID && comment.empty())
			return true;
		return false;
	}

	void Multicurrency::Clear()
	{
		id = 0;
		subaccountCurrencyID = 0;
		subaccountMainCurrencyID = 0;
		comment.clear();

	}

	void Multicurrency::TrimStrings(std::string& cComment)
	{
		if (!cComment.empty())
			boost::trim(cComment);
	}

	bool Multicurrency::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sbID,
		int smID, std::string& errorMessage)
	{
		Multicurrency multicurrency;
		multicurrency.Clear();
		errorMessage.clear();
		multicurrency.SetSubaccountCurrencyID(sbID);
		multicurrency.SetSubaccountMainCurrencyID(smID);
		std::string filter = multicurrency.GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == multicurrencyVector.size())
		{
			return false;
		}
		errorMessage = "Mulricurrency rate with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Multicurrency::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Multicurrency multicurrency;
		multicurrency.Clear();
		errorMessage.clear();
		multicurrency.SetSubaccountCurrencyID(subaccountCurrencyID);
		multicurrency.SetSubaccountMainCurrencyID(subaccountMainCurrencyID);
		std::string filter = multicurrency.GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == multicurrencyVector.size())
		{
			return false;
		}
		errorMessage = "Mulricurrency rate with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Multicurrency::CheckMulticurrencyCorrectness(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Multicurrency multicurrency;
		errorMessage.clear();
		multicurrency.SetID(id);
		std::string filter = multicurrency.GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (!errorMessage.empty())
			return false;
		if (0 != multicurrencyVector.size())
		{
			CurrencyRate cRate;
			Subaccount exchSub;
			Subaccount mainSub;
			if (!exchSub.GetSubaccountByID(globalVar, ormasDal, std::get<7>(multicurrencyVector.at(0)), errorMessage))
				return false;
			if (!mainSub.GetSubaccountByID(globalVar, ormasDal, std::get<8>(multicurrencyVector.at(0)), errorMessage))
				return false;
			if (!cRate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, exchSub.GetCurrencyID(), errorMessage))
				return false;
			if (fabs(exchSub.GetCurrentBalance()*cRate.GetToValue() / cRate.GetFromValue() - mainSub.GetCurrentBalance()) < 0.1)
				return true;
		}
		errorMessage = "Mulricurrency correctness not pass, please contact with administrator!";
		return false;
	}

	bool Multicurrency::CheckMulticurrencyCorrectnessByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int mID, std::string& errorMessage)
	{
		Multicurrency multicurrency;
		errorMessage.clear();
		multicurrency.SetID(mID);
		std::string filter = multicurrency.GenerateFilter(ormasDal);
		std::vector<DataLayer::multicurrencyViewCollection> multicurrencyVector = ormasDal.GetMulticurrency(errorMessage, filter);
		if (!errorMessage.empty())
			return false;
		if (0 == multicurrencyVector.size())
		{
			CurrencyRate cRate;
			Subaccount exchSub;
			Subaccount mainSub;
			if (!exchSub.GetSubaccountByID(globalVar, ormasDal, std::get<7>(multicurrencyVector.at(0)), errorMessage))
				return false;
			if (!mainSub.GetSubaccountByID(globalVar, ormasDal, std::get<8>(multicurrencyVector.at(0)), errorMessage))
				return false;
			if (!cRate.GetCurrencyRateByFromCurrencyID(globalVar, ormasDal, exchSub.GetCurrencyID(), errorMessage))
				return false;
			if (fabs(exchSub.GetCurrentBalance()*cRate.GetToValue() / cRate.GetFromValue() - mainSub.GetCurrentBalance()) < 0.1)
				return true;
		}
		errorMessage = "Mulricurrency correctness not pass, please contact with administrator!";
		return false;
	}

	bool Multicurrency::IsUserHaveMulticurrencySubaccount(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, std::string& errorMessage)
	{
		Balance balance;
		if (!balance.GetBalanceByUserID(globalVar, ormasDal, uID, errorMessage))
			return false;
		Multicurrency multicurrency;
		if (!multicurrency.GetMulticurrencyByMainCurrencyID(globalVar, ormasDal, balance.GetSubaccountID(), errorMessage))
			return false;

		if (!multicurrency.IsEmpty())
			return true;
		
		return false;
	}
}