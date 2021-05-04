#include "stdafx.h"
#include "AmortizeTypeClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AmortizeType::AmortizeType(DataLayer::amortizeTypeCollection aCollection)
	{
		id = std::get<0>(aCollection);
		name = std::get<1>(aCollection);
		code = std::get<2>(aCollection);
	}
	AmortizeType::AmortizeType()
	{
		id = 0;
		name = "";
		code = "";
	}

	int AmortizeType::GetID()
	{
		return id;
	}

	std::string AmortizeType::GetName()
	{
		return name;
	}

	std::string AmortizeType::GetCode()
	{
		return code;
	}


	void AmortizeType::SetID(int aID)
	{
		id = aID;
	}

	void AmortizeType::SetName(std::string aName)
	{
		if (!aName.empty())
			boost::trim(aName);
		name = aName;
	}

	void AmortizeType::SetCode(std::string aCode)
	{
		if (!aCode.empty())
			boost::trim(aCode);
		code = aCode;
	}

	bool AmortizeType::CreateAmortizeType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aName, std::string aCode, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aCode, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(aName, aCode);
		name = aName;
		code = aCode;
		if (0 != id && ormasDal.CreateAmortizeType(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AmortizeType::CreateAmortizeType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAmortizeType(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AmortizeType::DeleteAmortizeType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAmortizeType(id, errorMessage))
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

	bool AmortizeType::UpdateAmortizeType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aName, std::string aCode, std::string& errorMessage)
	{
		TrimStrings(aName, aCode);
		name = aName;
		code = aCode;
		if (0 != id && ormasDal.UpdateAmortizeType(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AmortizeType::UpdateAmortizeType(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateAmortizeType(id, name, code, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string AmortizeType::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !code.empty() )
		{
			return ormasDal.GetFilterForAmortizeType(id, name, code);
		}
		return "";
	}

	bool AmortizeType::GetAmortizeTypeByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeTypeCollection> amortizeTypeVector = ormasDal.GetAmortizeType(errorMessage, filter);
		if (0 != amortizeTypeVector.size())
		{
			id = std::get<0>(amortizeTypeVector.at(0));
			name = std::get<1>(amortizeTypeVector.at(0));
			code = std::get<2>(amortizeTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Amortize type with this id";
		}
		return false;
	}

	bool AmortizeType::GetAmortizeTypeByCode(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aCode, std::string& errorMessage)
	{
		if (!aCode.empty())
			return false;
		code = aCode;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeTypeCollection> amortizeTypeVector = ormasDal.GetAmortizeType(errorMessage, filter);
		if (0 != amortizeTypeVector.size())
		{
			id = std::get<0>(amortizeTypeVector.at(0));
			name = std::get<1>(amortizeTypeVector.at(0));
			code = std::get<2>(amortizeTypeVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Amortize type with this id";
		}
		return false;
	}

	bool AmortizeType::IsEmpty()
	{
		if (0 == id && name.empty() && code.empty())
			return true;
		return false;
	}

	void AmortizeType::Clear()
	{
		id = 0;
		name = "";
		code="";
	}

	bool AmortizeType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aCode, std::string& errorMessage)
	{
		AmortizeType amortizeType;
		amortizeType.Clear();
		errorMessage.clear();
		amortizeType.SetCode(aCode);
		std::string filter = amortizeType.GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeTypeCollection> amortizeTypeVector = ormasDal.GetAmortizeType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == amortizeTypeVector.size())
		{
			return false;
		}
		errorMessage = "Amortize type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AmortizeType::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AmortizeType amortizeType;
		amortizeType.Clear();
		errorMessage.clear();
		amortizeType.SetCode(code);
		std::string filter = amortizeType.GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeTypeCollection> amortizeTypeVector = ormasDal.GetAmortizeType(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == amortizeTypeVector.size())
		{
			return false;
		}
		errorMessage = "Amortize type with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	void AmortizeType::TrimStrings(std::string& cName, std::string& cCode)
	{
		if (!cName.empty())
			boost::trim(cName);
		if (!cCode.empty())
			boost::trim(cCode);
	}
}