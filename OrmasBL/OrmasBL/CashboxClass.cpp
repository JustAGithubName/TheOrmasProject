#include "stdafx.h"
#include "CashboxClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{

	Cashbox::Cashbox(DataLayer::cashboxCollection cCollection)
	{
		id = std::get<0>(cCollection);
		subaccountID = std::get<1>(cCollection);
		information = std::get<2>(cCollection);
		address = std::get<3>(cCollection);
	}
	Cashbox::Cashbox()
	{
		subaccountID = 0;
		information = "";
		address = "";
	}
	int Cashbox::GetID()
	{
		return id;
	}

	int Cashbox::GetSubaccountID()
	{
		return subaccountID;
	}

	std::string Cashbox::GetInformation()
	{
		return information;
	}

	std::string Cashbox::GetAddress()
	{
		return address;
	}


	void Cashbox::SetID(int cID)
	{
		id = cID;
	}

	void Cashbox::SetSubaccountID(int subaccID)
	{
		subaccountID = subaccID;
	}

	void Cashbox::SetInformation(std::string cInfo)
	{
		if (!cInfo.empty())
			boost::trim(cInfo);
		information = cInfo;
	}
	void Cashbox::SetAddress(std::string cAddress)
	{
		if (!cAddress.empty())
			boost::trim(cAddress);
		address = cAddress;
	}

	bool Cashbox::CreateCashbox(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int subaccID, std::string cInfo, std::string cAddress, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, subaccID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		subaccountID = subaccID;
		TrimStrings(cInfo, cAddress);
		information = cInfo;
		address = cAddress;
		if (0 != id && ormasDal.CreateCashbox(id, subaccountID, information, address, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Cashbox::CreateCashbox(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateCashbox(id, subaccountID, information, address, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Cashbox::DeleteCashbox(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteCashbox(id, errorMessage))
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

	bool Cashbox::UpdateCashbox(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int subaccID, std::string cInfo, std::string cAddress, std::string& errorMessage)
	{
		subaccountID = subaccID;
		TrimStrings(cInfo, cAddress);
		information = cInfo;
		address = cAddress;
		if (0 != id && ormasDal.UpdateCashbox(id, subaccountID, information, address, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Cashbox::UpdateCashbox(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateCashbox(id, subaccountID, information, address, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Cashbox::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != subaccountID || !information.empty() || !address.empty())
		{
			return ormasDal.GetFilterForCashbox(id, subaccountID, information, address);
		}
		return "";
	}

	bool Cashbox::GetCashboxByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		id = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxViewCollection> cashboxVector = ormasDal.GetCashbox(errorMessage, filter);
		if (0 != cashboxVector.size())
		{
			id = std::get<0>(cashboxVector.at(0));
			subaccountID = std::get<4>(cashboxVector.at(0));
			information = std::get<2>(cashboxVector.at(0));
			address = std::get<3>(cashboxVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Cashbox with this id";
		}
		return false;
	}

	int Cashbox::GetCashboxID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::string filter = this->GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxViewCollection> cashboxVector = ormasDal.GetCashbox(errorMessage, filter);
		if (0 != cashboxVector.size())
		{
			return std::get<0>(cashboxVector.at(0));
		}
		else
		{
			errorMessage = "Cannot find Cashbox with this id";
		}
		return 0;
	}

	bool Cashbox::IsEmpty()
	{
		if (0 ==id && 0 == subaccountID && information == "" && address == "")
			return true;
		return false;
	}

	void Cashbox::Clear()
	{
		id = 0;
		subaccountID = 0;
		information.clear();
		address.clear();
		
	}

	void Cashbox::TrimStrings(std::string& cInfo, std::string& cAddress)
	{
		if (!cInfo.empty())
			boost::trim(cInfo);
		if (!cAddress.empty())
			boost::trim(cAddress);
	}

	bool Cashbox::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int subaccID, std::string& errorMessage)
	{
		Cashbox cashbox;
		cashbox.Clear();
		errorMessage.clear();
		cashbox.SetSubaccountID(subaccID);
		std::string filter = cashbox.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxViewCollection> cashboxVector = ormasDal.GetCashbox(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == cashboxVector.size())
		{
			return false;
		}
		errorMessage = "Cashbox with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Cashbox::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Cashbox cashbox;
		cashbox.Clear();
		errorMessage.clear();
		cashbox.SetSubaccountID(subaccountID);
		std::string filter = cashbox.GenerateFilter(ormasDal);
		std::vector<DataLayer::cashboxViewCollection> cashboxVector = ormasDal.GetCashbox(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == cashboxVector.size())
		{
			return false;
		}
		errorMessage = "Cashbox with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}

