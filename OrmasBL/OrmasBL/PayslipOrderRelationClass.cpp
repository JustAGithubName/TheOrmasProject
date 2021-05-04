#include "stdafx.h"
#include "PayslipOrderRelationClass.h"


namespace BusinessLayer{
	PayslipOrderRelation::PayslipOrderRelation(DataLayer::payslipOrderCollection poCollection)
	{
		id = std::get<0>(poCollection);
		payslipID = std::get<1>(poCollection);
		orderID = std::get<2>(poCollection);
	}
	PayslipOrderRelation::PayslipOrderRelation()
	{
		id = 0;
		payslipID = 0;
		orderID = 0;
	}

	int PayslipOrderRelation::GetID()
	{
		return id;
	}

	int PayslipOrderRelation::GetOrderID()
	{
		return orderID;
	}

	int PayslipOrderRelation::GetPayslipID()
	{
		return payslipID;
	}

	void PayslipOrderRelation::SetID(int poID)
	{
		id = poID;
	}
	void PayslipOrderRelation::SetOrderID(int oID)
	{
		orderID = oID;
	}
	void PayslipOrderRelation::SetPayslipID(int pID)
	{
		payslipID = pID;
	}

	bool PayslipOrderRelation::CreatePayslipOrderRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, int oID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, oID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		orderID = oID;
		payslipID = pID;

		if (ormasDal.CreatePayslipOrder(id, payslipID, orderID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PayslipOrderRelation::CreatePayslipOrderRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreatePayslipOrder(id, payslipID, orderID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool PayslipOrderRelation::DeletePayslipOrderRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeletePayslipOrder(payslipID, orderID, errorMessage))
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



	std::string PayslipOrderRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != orderID || 0 != payslipID)
		{
			return ormasDal.GetFilterForPayslipOrder(id, payslipID, orderID);
		}
		return "";
	}

	std::vector<int> PayslipOrderRelation::GetAllPayslipByOrderID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> payslipIDVector;
		PayslipOrderRelation bpRelation;
		bpRelation.SetOrderID(bID);
		bpRelation.SetPayslipID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipOrderCollection> payslipOrderVector = ormasDal.GetPayslipOrder(errorMessage, filter);
		if (0 != payslipOrderVector.size())
		{
			for each (auto item in payslipOrderVector)
			{
				payslipIDVector.push_back(std::get<1>(item));
			}
		}
		return payslipIDVector;
	}

	std::vector<int> PayslipOrderRelation::GetAllOrderByPayslipID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> OrderIDVector;
		PayslipOrderRelation bpRelation;
		bpRelation.SetOrderID(0);
		bpRelation.SetPayslipID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipOrderCollection> payslipOrderVector = ormasDal.GetPayslipOrder(errorMessage, filter);
		if (0 != payslipOrderVector.size())
		{
			for each (auto item in payslipOrderVector)
			{
				OrderIDVector.push_back(std::get<0>(item));
			}
		}
		return OrderIDVector;
	}


	bool PayslipOrderRelation::IsEmpty()
	{
		if (0 == id && 0 == orderID && 0 == payslipID)
			return true;
		return false;
	}

	void PayslipOrderRelation::Clear()
	{
		id = 0;
		orderID = 0;
		payslipID = 0;
	}


	bool PayslipOrderRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		PayslipOrderRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetOrderID(bID);
		bpRelation.SetPayslipID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipOrderCollection> payslipOrderVector = ormasDal.GetPayslipOrder(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == payslipOrderVector.size())
		{
			return false;
		}
		errorMessage = "Payslip-Order Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool PayslipOrderRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		PayslipOrderRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetOrderID(orderID);
		bpRelation.SetPayslipID(payslipID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::payslipOrderCollection> payslipOrderVector = ormasDal.GetPayslipOrder(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == payslipOrderVector.size())
		{
			return false;
		}
		errorMessage = "Payslip-Order Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}