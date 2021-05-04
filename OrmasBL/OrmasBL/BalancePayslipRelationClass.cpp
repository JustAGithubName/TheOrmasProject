#include "stdafx.h"
#include "BalancePayslipRelationClass.h"


namespace BusinessLayer{
	BalancePayslipRelation::BalancePayslipRelation(DataLayer::balancePayslipCollection bpCollection)
	{
		id = std::get<0>(bpCollection);
		balanceID = std::get<1>(bpCollection);
		payslipID = std::get<2>(bpCollection);
	}
	BalancePayslipRelation::BalancePayslipRelation()
	{
		id = 0;
		balanceID = 0;
		payslipID = 0;
	}

	int BalancePayslipRelation::GetID()
	{
		return id;
	}

	int BalancePayslipRelation::GetBalanceID()
	{
		return balanceID;
	}

	int BalancePayslipRelation::GetPayslipID()
	{
		return payslipID;
	}

	void BalancePayslipRelation::SetID(int bpID)
	{
		id = bpID;
	}
	void BalancePayslipRelation::SetBalanceID(int bID)
	{
		balanceID = bID;
	}
	void BalancePayslipRelation::SetPayslipID(int pID)
	{
		payslipID = pID;
	}

	bool BalancePayslipRelation::CreateBalancePayslipRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, bID, pID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		balanceID = bID;
		payslipID = pID;

		if (ormasDal.CreateBalancePayslip(id, balanceID, payslipID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalancePayslipRelation::CreateBalancePayslipRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateBalancePayslip(id, balanceID, payslipID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool BalancePayslipRelation::DeleteBalancePayslipRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteBalancePayslip(balanceID, payslipID, errorMessage))
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



	std::string BalancePayslipRelation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != balanceID || 0 != payslipID)
		{
			return ormasDal.GetFilterForBalancePayslip(id, balanceID, payslipID);
		}
		return "";
	}

	std::vector<int> BalancePayslipRelation::GetAllPayslipByBalanceID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		std::vector<int> payslipIDVector;
		if (bID <= 0)
			return payslipIDVector;

		
		BalancePayslipRelation bpRelation;
		bpRelation.SetBalanceID(bID);
		bpRelation.SetPayslipID(0);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePayslipCollection> balancePayslipVector = ormasDal.GetBalancePayslip(errorMessage, filter);
		if (0 != balancePayslipVector.size())
		{
			for each (auto item in balancePayslipVector)
			{
				payslipIDVector.push_back(std::get<1>(item));
			}
		}
		return payslipIDVector;
	}

	std::vector<int> BalancePayslipRelation::GetAllBalanceByPayslipID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		std::vector<int> balanceIDVector;
		if (pID <= 0)
			return balanceIDVector;
		
		BalancePayslipRelation bpRelation;
		bpRelation.SetBalanceID(0);
		bpRelation.SetPayslipID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePayslipCollection> balancePayslipVector = ormasDal.GetBalancePayslip(errorMessage, filter);
		if (0 != balancePayslipVector.size())
		{
			for each (auto item in balancePayslipVector)
			{
				balanceIDVector.push_back(std::get<0>(item));
			}
		}
		return balanceIDVector;
	}


	bool BalancePayslipRelation::IsEmpty()
	{
		if (0 == id && 0 == balanceID && 0 == payslipID)
			return true;
		return false;
	}

	void BalancePayslipRelation::Clear()
	{
		id = 0;
		balanceID = 0;
		payslipID = 0;
	}


	bool BalancePayslipRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, int pID, std::string& errorMessage)
	{
		BalancePayslipRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(bID);
		bpRelation.SetPayslipID(pID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePayslipCollection> balancePayslipVector = ormasDal.GetBalancePayslip(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balancePayslipVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Payslip Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool BalancePayslipRelation::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		BalancePayslipRelation bpRelation;
		bpRelation.Clear();
		errorMessage.clear();
		bpRelation.SetBalanceID(balanceID);
		bpRelation.SetPayslipID(payslipID);
		std::string filter = bpRelation.GenerateFilter(ormasDal);
		std::vector<DataLayer::balancePayslipCollection> balancePayslipVector = ormasDal.GetBalancePayslip(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == balancePayslipVector.size())
		{
			return false;
		}
		errorMessage = "Balance-Payslip Relation with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}