#include "stdafx.h"
#include "SpecificationClass.h"
#include "SpecificationListClass.h"
#include "BalanceClass.h"
#include "UserClass.h"
#include "WithdrawalClass.h"
#include "StatusClass.h"

namespace BusinessLayer
{
	Specification::Specification(DataLayer::specificationsCollection sCollection)
	{
		id = std::get<0>(sCollection);
		productID = std::get<1>(sCollection);
		sum = std::get<2>(sCollection);
		currencyID = std::get<3>(sCollection);
		employeeID = std::get<4>(sCollection);
		date = std::get<5>(sCollection);
	}

	int Specification::GetID()
	{
		return id;
	}

	int Specification::GetProductID()
	{
		return productID;
	}

	double Specification::GetSum()
	{
		return sum;
	}

	int Specification::GetCurrencyID()
	{
		return currencyID;
	}

	int Specification::GetEmployeeID()
	{
		return employeeID;
	}

	std::string Specification::GetDate()
	{
		return date;
	}

	void Specification::SetID(int sID)
	{
		id = sID;
	}
	void Specification::SetProductID(int oProductID)
	{
		productID = oProductID;
	}
	void Specification::SetSum(double oSum)
	{
		sum = oSum;
	}
	void Specification::SetCurrencyID(int oCurrencyID)
	{
		currencyID = oCurrencyID;
	}
	void Specification::SetEmployeeID(int oEmployeeID)
	{
		employeeID = oEmployeeID;
	}
	void Specification::SetDate(std::string oDate)
	{
		date = oDate;
	}	

	bool Specification::CreateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sSum, int cID, int eID, std::string sDate, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, sSum, cID, errorMessage))
			return false;
		productID = pID;
		sum = sSum;
		currencyID = cID;		
		employeeID = eID;		
		date = sDate;
		if (0 != id && ormasDal.CreateSpecification(id, productID, sum, currencyID, employeeID, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	bool Specification::CreateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		if (0 != id && ormasDal.CreateSpecification(id, productID, sum, currencyID, employeeID, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Specification::DeleteSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteSpecification(id, errorMessage))
		{
			if (ormasDal.DeleteListBySpecificationID(id, errorMessage))
			{
				Clear();
				//ormasDal.CommitTransaction(errorMessage);
				return true;
			}
			else
			{
				//ormasDal.CancelTransaction(errorMessage);
			}
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
	bool Specification::UpdateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sSum, int cID, int eID, std::string sDate, std::string& errorMessage)
	{
		productID = pID;
		sum = sSum;
		currencyID = cID;
		employeeID = eID;
		date = sDate;
		if (0 != id && ormasDal.UpdateSpecification(id, productID, sum, currencyID, employeeID, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Specification::UpdateSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateSpecification(id, productID, sum, currencyID, employeeID, date, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Specification::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != sum || 0 != currencyID || 0 != employeeID || !date.empty())
		{
			return ormasDal.GetFilterForSpecification(id, productID, sum, currencyID, employeeID, date);
		}
		return "";
	}

	bool Specification::GetSpecificationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		id = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationsViewCollection> specificationVector = ormasDal.GetSpecifications(errorMessage, filter);
		if (0 != specificationVector.size())
		{
			id = std::get<0>(specificationVector.at(0));
			productID = std::get<9>(specificationVector.at(0));
			sum = std::get<3>(specificationVector.at(0));
			currencyID = std::get<10>(specificationVector.at(0));
			employeeID = std::get<11>(specificationVector.at(0));
			date = std::get<1>(specificationVector.at(0));			
			return true;
		}
		else
		{
			errorMessage = "Cannot find specification with this id";
		}
		return false;
	}

	bool Specification::GetSpecificationByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		productID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationsViewCollection> specificationVector = ormasDal.GetSpecifications(errorMessage, filter);
		if (0 != specificationVector.size())
		{
			id = std::get<0>(specificationVector.at(0));
			productID = std::get<9>(specificationVector.at(0));
			sum = std::get<3>(specificationVector.at(0));
			currencyID = std::get<10>(specificationVector.at(0));
			employeeID = std::get<11>(specificationVector.at(0));
			date = std::get<1>(specificationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find specification with this product id";
		}
		return false;
	}

	bool Specification::IsEmpty()
	{
		if (0 == id && 0 == productID && 0 == sum && 0 == currencyID && 0 == employeeID && date == "")
			return true;
		return false;
	}

	void Specification::Clear()
	{
		id = 0;
		productID = 0;
		sum = 0;
		currencyID = 0;
		employeeID = 0;
		date.clear();
	}

	bool Specification::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double sSum, int cID, std::string& errorMessage)
	{
		Specification specification;
		specification.Clear();
		errorMessage.clear();
		specification.SetProductID(pID);
		specification.SetSum(sSum);
		specification.SetCurrencyID(cID);
		std::string filter = specification.GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationsViewCollection> specificationVector = ormasDal.GetSpecifications(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == specificationVector.size())
		{
			return false;
		}
		errorMessage = "Specification with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Specification::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Specification specification;
		specification.Clear();
		errorMessage.clear();
		specification.SetProductID(productID);
		specification.SetSum(sum);
		specification.SetCurrencyID(currencyID);
		std::string filter = specification.GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationsViewCollection> specificationVector = ormasDal.GetSpecifications(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == specificationVector.size())
		{
			return false;
		}
		errorMessage = "Specification with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Specification::UpdateSpecificationByProductID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double oldPrice, double newPrice, std::string& errorMessage)
	{
		Specification spec;
		SpecificationList sList;
		sList.SetProductID(pID);
		std::string filter = sList.GenerateFilter(ormasDal);
		std::vector<DataLayer::specificationListViewCollection> specificationListVector = ormasDal.GetSpecificationList(errorMessage, filter);
		for each (auto item in specificationListVector)
		{
			spec.Clear();
			if (spec.GetSpecificationByID(globalVar, ormasDal, std::get<1>(item), errorMessage))
			{
				spec.SetSum(spec.GetSum() + (std::get<3>(item)*newPrice - std::get<3>(item)*oldPrice));
				if (!spec.UpdateSpecification(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		return true;
	}
}