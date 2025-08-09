#include "stdafx.h"
#include "PriceExtensionClass.h"

namespace BusinessLayer{
	PriceExtension::PriceExtension(DataLayer::priceExtensionCollection pCollection)
	{
		id = std::get<0>(pCollection);
		productID = std::get<1>(pCollection);
		value = std::get<2>(pCollection);
		date = std::get<3>(pCollection);
		dayCount = std::get<4>(pCollection);
		locationID = std::get<5>(pCollection);
		expeditorID = std::get<6>(pCollection);
		branchID = std::get<7>(pCollection);
		clientID = std::get<8>(pCollection);
	}
	PriceExtension::PriceExtension()
	{
		id = 0;
		productID = 0;
		value = 0.0;
		date = "";
		branchID = 0;
		clientID = 0;
		dayCount = 0;
		expeditorID = 0;
		locationID = 0;
	}
	
	int PriceExtension::GetID()
	{
		return id;
	}

	int PriceExtension::GetProductID()
	{
		return productID;
	}

	double PriceExtension::GetValue()
	{
		return value;
	}

	std::string PriceExtension::GetDate()
	{
		return date;
	}

	int PriceExtension::GetBranchID()
	{
		return branchID;
	}

	int PriceExtension::GetClientID()
	{
		return clientID;
	}

	int PriceExtension::GetDayCount()
	{
		return dayCount;
	}

	int PriceExtension::GetExpeditorID()
	{
		return expeditorID;
	}

	int PriceExtension::GetLocationID()
	{
		return locationID;
	}


	void PriceExtension::SetID(int pID)
	{
		id = pID;
	}

	void PriceExtension::SetProductID(int pProductID)
	{
		productID = pProductID;
	}

	void PriceExtension::SetValue(double pValue)
	{
		value = pValue;
	}

	void PriceExtension::SetDate(std::string pDate)
	{
		date = pDate;
	}

	void PriceExtension::SetBranchID(int bID)
	{
		branchID = bID;
	}

	void PriceExtension::SetClientID(int cID)
	{
		clientID = cID;
	}

	void PriceExtension::SetDayCount(int dCount)
	{
		dayCount = dCount;
	}

	void PriceExtension::SetExpeditorID(int pExpeditorID)
	{
		expeditorID = pExpeditorID;
	}

	void PriceExtension::SetLocationID(int lID)
	{
		locationID = lID;
	}

	bool PriceExtension::CreatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int prID, double pValue, std::string pDate, int count,
		int lID, int eID, int bID, int cID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, prID, pValue, pDate, bID, cID, count, eID, lID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		productID = prID;
		value = pValue;
		date = pDate;
		branchID = bID;
		clientID =cID;
		dayCount = count;
		expeditorID = eID;
		locationID = lID;
		if (0 != id && ormasDal.CreatePriceExtension(id, productID, value, date, dayCount, locationID, expeditorID, branchID, clientID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PriceExtension::CreatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreatePriceExtension(id, productID, value, date, dayCount, locationID, expeditorID, branchID, clientID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PriceExtension::DeletePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeletePriceExtension(id, errorMessage))
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

	bool PriceExtension::UpdatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int prID, double pValue, std::string pDate, int count,
		int lID, int eID, int bID, int cID, std::string& errorMessage)
	{
		productID = prID;
		value = pValue;
		date = pDate;
		branchID = bID;
		clientID = cID;
		dayCount = count;
		expeditorID = eID;
		locationID = lID;
		if (0 != id && ormasDal.UpdatePriceExtension(id, productID, value, date, dayCount, locationID, expeditorID, branchID, clientID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PriceExtension::UpdatePriceExtension(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdatePriceExtension(id, productID, value, date, dayCount, locationID, expeditorID, branchID, clientID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string PriceExtension::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || date.empty() || 0 != productID || 0 != branchID || 0 != value || 0 != clientID || 0 != dayCount || 0 != locationID || 0 != expeditorID)
		{
			return ormasDal.GetFilterForPriceExtension(id, productID, value, date, dayCount, locationID, expeditorID, branchID, clientID);
		}
		return "";
	}

	bool PriceExtension::GetPriceExtensionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));		
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		branchID = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByClientID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int cID, std::string& errorMessage)
	{
		if (cID <= 0)
			return false;
		clientID = cID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByLocationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int lID, std::string& errorMessage)
	{
		if (lID <= 0)
			return false;
		locationID = lID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByExpeditorID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		if (eID <= 0)
			return false;
		expeditorID = eID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByProductIDAndExpeditorID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int empID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		expeditorID = empID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByProductIDAndClientID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int cliID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		clientID = cliID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByProductIDAndBranchID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int branID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		branchID = branID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::GetPriceExtensionByProductIDAndLocationID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int locID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		locationID = locID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (0 != priceExtensionVector.size())
		{
			id = std::get<0>(priceExtensionVector.at(0));
			productID = std::get<9>(priceExtensionVector.at(0));
			value = std::get<2>(priceExtensionVector.at(0));
			date = std::get<3>(priceExtensionVector.at(0));
			dayCount = std::get<4>(priceExtensionVector.at(0));
			locationID = std::get<10>(priceExtensionVector.at(0));
			expeditorID = std::get<11>(priceExtensionVector.at(0));
			branchID = std::get<12>(priceExtensionVector.at(0));
			clientID = std::get<13>(priceExtensionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find price extension with this id";
		}
		return false;
	}

	bool PriceExtension::IsEmpty()
	{
		if (0 == id && 0 == productID  && 0.0 == value && date.empty() && 0 == branchID && 0 == clientID && 0 == dayCount && 0 == expeditorID && 0 == locationID)
			return true;
		return false;
	}

	void PriceExtension::Clear()
	{
		id = 0;
		productID = 0;
		value = 0;
		date.clear();
		branchID = 0;
		clientID = 0;
		dayCount = 0;
		expeditorID = 0;
		locationID = 0;
	}

	bool PriceExtension::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int prID, double pValue, std::string pDate, int bID, int cID,
		int count, int pExpeditor, int lID, std::string& errorMessage)
	{
		PriceExtension priceExtension;
		priceExtension.Clear();
		errorMessage.clear();
		priceExtension.SetProductID(prID);
		priceExtension.SetValue(pValue);
		priceExtension.SetDate(pDate);
		priceExtension.SetBranchID(bID);
		priceExtension.SetClientID(cID);
		priceExtension.SetDayCount(count);
		priceExtension.SetLocationID(lID); 
		priceExtension.SetExpeditorID(pExpeditor);
		std::string filter = priceExtension.GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == priceExtensionVector.size())
		{
			return false;
		}
		errorMessage = "Price extension with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool PriceExtension::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		PriceExtension priceExtension;
		priceExtension.Clear();
		errorMessage.clear();
		priceExtension.SetProductID(productID);
		priceExtension.SetValue(value);
		priceExtension.SetDate(date);
		priceExtension.SetBranchID(branchID);
		priceExtension.SetClientID(clientID);
		priceExtension.SetDayCount(dayCount);
		priceExtension.SetLocationID(locationID);
		priceExtension.SetExpeditorID(expeditorID);
		std::string filter = priceExtension.GenerateFilter(ormasDal);
		std::vector<DataLayer::priceExtensionViewCollection> priceExtensionVector = ormasDal.GetPriceExtension(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == priceExtensionVector.size())
		{
			return false;
		}
		errorMessage = "Price extension with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}