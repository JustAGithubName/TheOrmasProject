#include "stdafx.h"
#include "NetCostCoefficientClass.h"

namespace BusinessLayer{
	NetCostCoefficient::NetCostCoefficient(DataLayer::netCostCoefficientCollection nCollection)
	{
		id = std::get<0>(nCollection);
		productID = std::get<1>(nCollection);
		value = std::get<2>(nCollection);
		comment = std::get<3>(nCollection);
	}
	NetCostCoefficient::NetCostCoefficient()
	{
		comment = "";
		value = 0.0;
		productID = 0;
	}
	int NetCostCoefficient::GetID()
	{
		return id;
	}

	std::string NetCostCoefficient::GetComment()
	{
		return comment;
	}

	double NetCostCoefficient::GetValue()
	{
		return value;
	}

	int NetCostCoefficient::GetProductID()
	{
		return productID;
	}

	void NetCostCoefficient::SetID(int nID)
	{
		id = nID;
	}

	void NetCostCoefficient::SetComment(std::string nComment)
	{
		comment = nComment;
	}

	void NetCostCoefficient::SetValue(double nValue)
	{
		value = nValue;
	}
	void NetCostCoefficient::SetProductID(int prID)
	{
		productID = prID;
	}

	bool NetCostCoefficient::CreateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, int pID, double pValue, std::string pComment, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		comment = pComment;
		value = pValue;
		productID = pID;
		if (0 != id && ormasDal.CreateNetCostCoefficient(id, productID, value, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCostCoefficient::CreateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateNetCostCoefficient(id, productID, value, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCostCoefficient::DeleteNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteNetCostCoefficient(id, errorMessage))
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

	bool NetCostCoefficient::UpdateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, int pID, double pValue, std::string pComment, std::string& errorMessage)
	{
		comment = pComment;
		value = pValue;
		productID = pID;
		if (0 != id && ormasDal.UpdateNetCostCoefficient(id, productID, value, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool NetCostCoefficient::UpdateNetCostCoefficient(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateNetCostCoefficient(id, productID, value, comment, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string NetCostCoefficient::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || comment.empty() || 0 != productID || 0 != value)
		{
			return ormasDal.GetFilterForNetCostCoefficient(id, productID, value, comment);
		}
		return "";
	}

	bool NetCostCoefficient::GetNetCostCoefficientByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int nID, std::string& errorMessage)
	{
		if (nID <= 0)
			return false;
		id = nID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostCoefficientViewCollection> netCostCoefficientVector = ormasDal.GetNetCostCoefficient(errorMessage, filter);
		if (0 != netCostCoefficientVector.size())
		{
			id = std::get<0>(netCostCoefficientVector.at(0));
			productID = std::get<3>(netCostCoefficientVector.at(0));
			value = std::get<2>(netCostCoefficientVector.at(0));
			comment = std::get<4>(netCostCoefficientVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find net cost with this id";
		}
		return false;
	}

	bool NetCostCoefficient::GetNetCostCoefficientByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostCoefficientViewCollection> netCostCoefficientVector = ormasDal.GetNetCostCoefficient(errorMessage, filter);
		if (0 != netCostCoefficientVector.size())
		{
			id = std::get<0>(netCostCoefficientVector.at(0));
			productID = std::get<3>(netCostCoefficientVector.at(0));
			value = std::get<2>(netCostCoefficientVector.at(0));
			comment = std::get<4>(netCostCoefficientVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find net cost with this product id";
		}
		return false;
	}

	bool NetCostCoefficient::IsEmpty()
	{
		if (0 == id && comment.empty() && 0.0 == value && 0 == productID)
			return true;
		return false;
	}

	void NetCostCoefficient::Clear()
	{
		id = 0;
		comment.clear();
		value = 0;
		productID = 0;
	}

	bool NetCostCoefficient::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID,
		std::string& errorMessage)
	{
		NetCostCoefficient netCostCoefficient;
		netCostCoefficient.Clear();
		errorMessage.clear();
		netCostCoefficient.SetProductID(pID);
		std::string filter = netCostCoefficient.GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostCoefficientViewCollection> netCostCoefficientVector = ormasDal.GetNetCostCoefficient(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == netCostCoefficientVector.size())
		{
			return false;
		}
		errorMessage = "Net cost with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool NetCostCoefficient::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		NetCostCoefficient netCostCoefficient;
		netCostCoefficient.Clear();
		errorMessage.clear();
		netCostCoefficient.SetProductID(productID);
		std::string filter = netCostCoefficient.GenerateFilter(ormasDal);
		std::vector<DataLayer::netCostCoefficientViewCollection> netCostCoefficientVector = ormasDal.GetNetCostCoefficient(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == netCostCoefficientVector.size())
		{
			return false;
		}
		errorMessage = "Net cost with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}