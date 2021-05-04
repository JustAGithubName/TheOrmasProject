#include "stdafx.h"
#include "TaxClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Tax::Tax(DataLayer::taxesCollection tCollection)
	{
		id = std::get<0>(tCollection);
		name = std::get<1>(tCollection);
		code = std::get<2>(tCollection);
		fixedValue = std::get<3>(tCollection);
		percentValue = std::get<4>(tCollection);
		formulaValue = std::get<5>(tCollection);
	}
	Tax::Tax()
	{
		id = 0;
		name = "";
		code = "";
		fixedValue = 0.0;
		percentValue = 0;
		formulaValue = "";
	}

	int Tax::GetID()
	{
		return id;
	}

	std::string Tax::GetName()
	{
		return name;
	}

	std::string Tax::GetCode()
	{
		return code;
	}
	
	double Tax::GetFixedValue()
	{
		return fixedValue;
	}

	int Tax::GetPercentValue()
	{
		return percentValue;
	}

	std::string Tax::GetFormulaValue()
	{
		return formulaValue;
	}

	void Tax::SetID(int tID)
	{
		id = tID;
	}

	void Tax::SetName(std::string tName)
	{
		name = tName;
		if (!tName.empty())
			boost::trim(tName);
		name = tName;
	}

	void Tax::SetCode(std::string tCode)
	{
		code = tCode;
		if (!tCode.empty())
			boost::trim(tCode);
		code = boost::to_upper_copy(tCode);
	}

	void Tax::SetFixedValue(double tFixedValue)
	{
		fixedValue = tFixedValue;
	}

	void Tax::SetPercentValue(int tPercentValue)
	{
		percentValue = tPercentValue;
	}

	void Tax::SetFormulaValue(std::string tFormulaValue)
	{
		formulaValue = tFormulaValue;
	}

	

	bool Tax::CreateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string tName, std::string tCode, double tFixedValue, int tPercentValue,
		std::string tFormulaValue, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, tName, tCode, errorMessage))
			return false;
		TrimStrings(tName, tCode);
		id = ormasDal.GenerateID();
		name = tName;
		code = boost::to_upper_copy(tCode);
		fixedValue = tFixedValue;
		percentValue = tPercentValue;
		formulaValue = tFormulaValue;
		if (0 != id && ormasDal.CreateTax(id, name, code, fixedValue, percentValue, formulaValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Tax::CreateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateTax(id, name, code, fixedValue, percentValue, formulaValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Tax::DeleteTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteTax(id, errorMessage))
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

	bool Tax::UpdateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string tName, std::string tCode, double tFixedValue, int tPercentValue,
		std::string tFormulaValue, std::string& errorMessage)
	{
		TrimStrings(tName, tCode);
		name = tName;
		code = boost::to_upper_copy(tCode);
		fixedValue = tFixedValue;
		percentValue = tPercentValue;
		formulaValue = tFormulaValue;
		if (0 != id && ormasDal.UpdateTax(id, name, code, fixedValue, percentValue, formulaValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Tax::UpdateTax(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateTax(id, name, code, fixedValue, percentValue, formulaValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Tax::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != percentValue || 0.0 != fixedValue || !formulaValue.empty() || !name.empty() || !code.empty())
		{
			return ormasDal.GetFilterForTax(id, name, code, fixedValue, percentValue, formulaValue);
		}
		return "";
	}

	bool Tax::GetTaxByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::taxesCollection> taxVector = ormasDal.GetTaxes(errorMessage, filter);
		if (0 != taxVector.size())
		{
			id = std::get<0>(taxVector.at(0));
			name = std::get<1>(taxVector.at(0));
			code = std::get<2>(taxVector.at(0));
			fixedValue = std::get<3>(taxVector.at(0));
			percentValue = std::get<4>(taxVector.at(0));
			formulaValue = std::get<5>(taxVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find tax with this id";
		}
		return false;
	}

	bool Tax::IsEmpty()
	{
		if (0 == id && 0 == percentValue && 0.0 == fixedValue && formulaValue.empty() && name.empty() && code.empty())
			return true;
		return false;
	}

	void Tax::Clear()
	{
		id = 0;
		name = "";
		code = "";
		fixedValue = 0.0;
		percentValue = 0;
		formulaValue = "";
	}

	void Tax::TrimStrings(std::string& tName, std::string& tCode)
	{
		if (!tName.empty())
			boost::trim(tName);
		if (!tCode.empty())
			boost::trim(tCode);
	}

	bool Tax::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string tName, std::string tCode, std::string& errorMessage)
	{
		Tax tax;
		tax.Clear();
		errorMessage.clear();
		tax.SetName(tName);
		tax.SetCode(tCode);
		std::string filter = tax.GenerateFilter(ormasDal);
		std::vector<DataLayer::taxesCollection> taxVector = ormasDal.GetTaxes(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == taxVector.size())
		{
			return false;
		}
		errorMessage = "Tax with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Tax::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Tax tax;
		tax.Clear();
		errorMessage.clear();
		tax.SetName(name);
		tax.SetCode(code);
		std::string filter = tax.GenerateFilter(ormasDal);
		std::vector<DataLayer::taxesCollection> taxVector = ormasDal.GetTaxes(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == taxVector.size())
		{
			return false;
		}
		errorMessage = "Tax with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}