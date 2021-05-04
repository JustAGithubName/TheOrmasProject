#include "stdafx.h"
#include "AmortizeGroupClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AmortizeGroup::AmortizeGroup(DataLayer::amortizeGroupCollection aCollection)
	{
		id = std::get<0>(aCollection);
		groupNumber = std::get<1>(aCollection);
		fromMonth = std::get<2>(aCollection);
		toMonth = std::get<3>(aCollection);
	}
	AmortizeGroup::AmortizeGroup()
	{
		id = 0;
		groupNumber = 0;
		fromMonth = 0;
		toMonth = 0;
	}

	int AmortizeGroup::GetID()
	{
		return id;
	}

	int AmortizeGroup::GetGroupNumber()
	{
		return groupNumber;
	}

	int AmortizeGroup::GetFromMonth()
	{
		return fromMonth;
	}

	int AmortizeGroup::GetToMonth()
	{
		return toMonth;
	}

	void AmortizeGroup::SetID(int aID)
	{
		id = aID;
	}

	void AmortizeGroup::SetGroupNumber(int gNumber)
	{
		groupNumber = gNumber;
	}

	void AmortizeGroup::SetFromMonth(int fMonth)
	{
		fromMonth = fMonth;
	}

	void AmortizeGroup::SetToMonth(int tMonth)
	{
		toMonth = tMonth;
	}

	bool AmortizeGroup::CreateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gNumber, int fMonth, int tMonth, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, gNumber, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		groupNumber = gNumber;
		fromMonth = fMonth;
		toMonth = toMonth;
		if (0 != id && ormasDal.CreateAmortizeGroup(id, groupNumber, fromMonth, toMonth, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AmortizeGroup::CreateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateAmortizeGroup(id, groupNumber, fromMonth, toMonth, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AmortizeGroup::DeleteAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAmortizeGroup(id, errorMessage))
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

	bool AmortizeGroup::UpdateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gNumber, int fMonth, int tMonth, std::string& errorMessage)
	{
		groupNumber = gNumber;
		fromMonth = fMonth;
		toMonth = toMonth;
		if (0 != id && ormasDal.UpdateAmortizeGroup(id, groupNumber, fromMonth, toMonth, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AmortizeGroup::UpdateAmortizeGroup(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateAmortizeGroup(id, groupNumber, fromMonth, toMonth, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string AmortizeGroup::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != groupNumber || 0 != fromMonth || 0 != toMonth)
		{
			return ormasDal.GetFilterForAmortizeGroup(id, groupNumber, fromMonth, toMonth);
		}
		return "";
	}

	bool AmortizeGroup::GetAmortizeGroupByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeGroupCollection> amortizeGroupVector = ormasDal.GetAmortizeGroup(errorMessage, filter);
		if (0 != amortizeGroupVector.size())
		{
			id = std::get<0>(amortizeGroupVector.at(0));
			groupNumber = std::get<1>(amortizeGroupVector.at(0));
			fromMonth = std::get<2>(amortizeGroupVector.at(0));
			toMonth = std::get<3>(amortizeGroupVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Amortize Group with this id";
		}
		return false;
	}

	bool AmortizeGroup::GetAmortizeGroupByNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aNumber, std::string& errorMessage)
	{
		if (aNumber <= 0)
			return false;
		groupNumber = aNumber;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeGroupCollection> amortizeGroupVector = ormasDal.GetAmortizeGroup(errorMessage, filter);
		if (0 != amortizeGroupVector.size())
		{
			id = std::get<0>(amortizeGroupVector.at(0));
			groupNumber = std::get<1>(amortizeGroupVector.at(0));
			fromMonth = std::get<2>(amortizeGroupVector.at(0));
			toMonth = std::get<3>(amortizeGroupVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Amortize Group with this id";
		}
		return false;
	}

	bool AmortizeGroup::IsEmpty()
	{
		if (0 == id && 0 == groupNumber && 0 == fromMonth && 0 == toMonth)
			return true;
		return false;
	}

	void AmortizeGroup::Clear()
	{
		id = 0;
		groupNumber = 0;
		fromMonth = 0;
		toMonth = 0;
	}

	bool AmortizeGroup::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int gNumber, std::string& errorMessage)
	{
		AmortizeGroup amortizeGroup;
		amortizeGroup.Clear();
		errorMessage.clear();
		amortizeGroup.SetGroupNumber(gNumber);
		std::string filter = amortizeGroup.GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeGroupCollection> amortizeGroupVector = ormasDal.GetAmortizeGroup(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == amortizeGroupVector.size())
		{
			return false;
		}
		errorMessage = "Amortize group with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AmortizeGroup::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AmortizeGroup amortizeGroup;
		amortizeGroup.Clear();
		errorMessage.clear();
		amortizeGroup.SetGroupNumber(groupNumber);
		std::string filter = amortizeGroup.GenerateFilter(ormasDal);
		std::vector<DataLayer::amortizeGroupCollection> amortizeGroupVector = ormasDal.GetAmortizeGroup(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == amortizeGroupVector.size())
		{
			return false;
		}
		errorMessage = "Amortize group with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

}