#include "stdafx.h"
#include "PaymentEmployeeRelationClass.h"


namespace BusinessLayer{
	PaymentEmployeeRelation::PaymentEmployeeRelation(DataLayer::paymentEmployeeCollection peCollection)
	{
		id = std::get<0>(peCollection);
		paymentID = std::get<1>(peCollection);
		employeeID = std::get<2>(peCollection);
	}
	PaymentEmployeeRelation::PaymentEmployeeRelation()
	{
		id = 0;
		employeeID = 0;
		paymentID = 0;
	}

	int PaymentEmployeeRelation::GetID()
	{
		return id;
	}

	int PaymentEmployeeRelation::GetEmployeeID()
	{
		return employeeID;
	}

	int PaymentEmployeeRelation::GetPaymentID()
	{
		return paymentID;
	}

	void PaymentEmployeeRelation::SetID(int peID)
	{
		id = peID;
	}
	void PaymentEmployeeRelation::SetEmployeeID(int eID)
	{
		employeeID = eID;
	}
	void PaymentEmployeeRelation::SetPaymentID(int pID)
	{
		paymentID = pID;
	}

	bool PaymentEmployeeRelation::CreatePaymentEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int eID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, eID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		employeeID = eID;
		paymentID = pID;

		if (ormasDal.CreatePaymentEmployee(id, paymentID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PaymentEmployeeRelation::CreatePaymentEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreatePaymentEmployee(id, paymentID, employeeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PaymentEmployeeRelation::DeletePaymentEmployeeRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeletePaymentEmployee(paymentID, employeeID, errorMessage))
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



	std::string PaymentEmployeeRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != employeeID || 0 != paymentID)
		{
			return ormasDal.GetFilterForPaymentEmployee(id, paymentID, employeeID);
		}
		return "";
	}

	std::vector<int> PaymentEmployeeRelation::GetAllPaymentByEmployeeID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int eID, std::string& errorMessage)
	{
		std::vector<int> paymentIDVector;
		PaymentEmployeeRelation peRelation;
		peRelation.SetEmployeeID(eID);
		peRelation.SetPaymentID(0);
		std::string filter = peRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentEmployeeCollection> paymentEmployeeVector = ormasDal.GetPaymentEmployee(errorMessage, filter);
		if (0 != paymentEmployeeVector.size())
		{
			for each (auto item in paymentEmployeeVector)
			{
				paymentIDVector.push_back(std::get<1>(item));
			}
		}
		return paymentIDVector;
	}

	std::vector<int> PaymentEmployeeRelation::GetAllEmployeeByPaymentID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> employeeIDVector;
		PaymentEmployeeRelation peRelation;
		peRelation.SetEmployeeID(0);
		peRelation.SetPaymentID(pID);
		std::string filter = peRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentEmployeeCollection> paymentEmployeeVector = ormasDal.GetPaymentEmployee(errorMessage, filter);
		if (0 != paymentEmployeeVector.size())
		{
			for each (auto item in paymentEmployeeVector)
			{
				employeeIDVector.push_back(std::get<0>(item));
			}
		}
		return employeeIDVector;
	}


	bool PaymentEmployeeRelation::IsEmpty()
	{
		if (0 == id && 0 == employeeID && 0 == paymentID)
			return true;
		return false;
	}

	void PaymentEmployeeRelation::Clear()
	{
		id = 0;
		employeeID = 0;
		paymentID = 0;
	}

	bool PaymentEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int eID, std::string& errorMessage)
	{
		PaymentEmployeeRelation peRelation;
		peRelation.Clear();
		errorMessage.clear();
		peRelation.SetEmployeeID(eID);
		peRelation.SetPaymentID(pID);
		std::string filter = peRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentEmployeeCollection> paymentEmployeeVector = ormasDal.GetPaymentEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == paymentEmployeeVector.size())
		{
			return false;
		}
		errorMessage = "Payment-Employee Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool PaymentEmployeeRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		PaymentEmployeeRelation peRelation;
		peRelation.Clear();
		errorMessage.clear();
		peRelation.SetEmployeeID(employeeID);
		peRelation.SetPaymentID(paymentID);
		std::string filter = peRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::paymentEmployeeCollection> paymentEmployeeVector = ormasDal.GetPaymentEmployee(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == paymentEmployeeVector.size())
		{
			return false;
		}
		errorMessage = "Payment-Employee Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}