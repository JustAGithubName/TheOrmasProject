#include "stdafx.h"
#include "AccessItemClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	AccessItem::AccessItem(DataLayer::accessItemsCollection aCollection)
	{
		id = std::get<0>(aCollection);
		nameEng = std::get<1>(aCollection);
		nameRu = std::get<2>(aCollection);
		division = std::get<3>(aCollection);
	}
	AccessItem::AccessItem()
	{
		nameEng = "";
		nameRu = "";
		division = "";
	}
	int AccessItem::GetID()
	{
		return id;
	}

	std::string AccessItem::GetNameEng()
	{
		return nameEng;
	}
	std::string AccessItem::GetNameRu()
	{
		return nameRu;
	}
	std::string AccessItem::GetDivision()
	{
		return division;
	}


	void AccessItem::SetID(int cID)
	{
		id = cID;
	}
	void AccessItem::SetNameEng(std::string aNameEng)
	{
		if (!aNameEng.empty())
			boost::trim(aNameEng);
		nameEng = aNameEng;
	}
	void AccessItem::SetNameRu(std::string aNameRu)
	{
		if (!aNameRu.empty())
			boost::trim(aNameRu);
		nameRu = aNameRu;
	}
	void AccessItem::SetDivision(std::string aDivision)
	{
		if (!aDivision.empty())
			boost::trim(aDivision);
		division = boost::to_upper_copy(aDivision);
	}

	bool AccessItem::CreateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNameEng, std::string aNameRu, std::string aDivision, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, aNameEng, aNameRu, aDivision, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(aNameEng, aNameRu, aDivision);
		nameEng = aNameEng;
		nameRu = aNameRu;
		division = boost::to_upper_copy(aDivision);
		if (0 != id && ormasDal.CreateAccessItem(id, nameEng, nameRu, division, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccessItem::CreateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateAccessItem(id, nameEng, nameRu, division, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccessItem::DeleteAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccessItem(id, errorMessage))
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

	bool AccessItem::UpdateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNameEng, std::string aNameRu, std::string aDivision, std::string& errorMessage)
	{
		TrimStrings(aNameEng, aNameRu, aDivision);
		nameEng =aNameEng;
		nameRu = aNameRu;
		division = boost::to_upper_copy(aDivision);
		if (0 != id && ormasDal.UpdateAccessItem(id, nameEng, nameRu, division, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool AccessItem::UpdateAccessItem(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateAccessItem(id, nameEng, nameRu, division, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string AccessItem::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !nameEng.empty() || !nameRu.empty() || !division.empty())
		{
			return ormasDal.GetFilterForAccessItem(id, nameEng, nameRu, division);
		}
		return "";
	}

	bool AccessItem::GetAccessItemByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector = ormasDal.GetAccessItems(errorMessage, filter);
		if (0 != accessItemVector.size())
		{
			id = std::get<0>(accessItemVector.at(0));
			nameEng = std::get<1>(accessItemVector.at(0));
			nameRu = std::get<2>(accessItemVector.at(0));
			division = std::get<3>(accessItemVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find access item with this id";
		}
		return false;
	}

	bool AccessItem::GetAccessItemByEngName(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string engName, std::string& errorMessage)
	{
		nameEng = engName;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector = ormasDal.GetAccessItems(errorMessage, filter);
		if (0 != accessItemVector.size())
		{
			id = std::get<0>(accessItemVector.at(0));
			nameEng = std::get<1>(accessItemVector.at(0));
			nameRu = std::get<2>(accessItemVector.at(0));
			division = std::get<3>(accessItemVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find access item with this id";
		}
		return false;
	}

	bool AccessItem::GetAccessItemByRuName(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string ruName, std::string& errorMessage)
	{
		nameRu = ruName;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector = ormasDal.GetAccessItems(errorMessage, filter);
		if (0 != accessItemVector.size())
		{
			id = std::get<0>(accessItemVector.at(0));
			nameEng = std::get<1>(accessItemVector.at(0));
			nameRu = std::get<2>(accessItemVector.at(0));
			division = std::get<3>(accessItemVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find access item with this id";
		}
		return false;
	}

	bool AccessItem::IsEmpty()
	{
		if (0 == id && nameEng.empty() && nameRu.empty() && division.empty())
			return true;
		return false;
	}


	void AccessItem::Clear()
	{
		id = 0;
		nameEng.clear();
		nameRu.clear();
		division.clear();
	}

	void AccessItem::TrimStrings(std::string& aNameEng, std::string& aNameRu, std::string& aDivision)
	{
		if (!aNameEng.empty())
			boost::trim(aNameEng);
		if (!aNameRu.empty())
			boost::trim(aNameRu);
		if (!aDivision.empty())
			boost::trim(aDivision);
	}

	bool AccessItem::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aNameEng, std::string aNameRu, std::string aDivision, std::string& errorMessage)
	{
		AccessItem accessItem;
		accessItem.Clear();
		errorMessage.clear();
		accessItem.SetNameEng(aNameEng);
		accessItem.SetDivision(aDivision);
		std::string filter = accessItem.GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector = ormasDal.GetAccessItems(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accessItemVector.size())
		{
			return false;
		}
		accessItem.SetNameEng("");
		accessItem.SetNameRu(aNameRu);
		std::string filter2 = accessItem.GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector2 = ormasDal.GetAccessItems(errorMessage, filter2);
		if (!errorMessage.empty())
			return true;
		if (0 == accessItemVector2.size())
		{
			return false;
		}
		errorMessage = "Access item with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool AccessItem::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccessItem accessItem;
		accessItem.Clear();
		errorMessage.clear();
		accessItem.SetNameEng(nameEng);
		accessItem.SetDivision(division);
		std::string filter = accessItem.GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector = ormasDal.GetAccessItems(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accessItemVector.size())
		{
			return false;
		}
		accessItem.SetNameEng("");
		accessItem.SetNameRu(nameRu);
		std::string filter2 = accessItem.GenerateFilter(ormasDal);
		std::vector<DataLayer::accessItemsCollection> accessItemVector2 = ormasDal.GetAccessItems(errorMessage, filter2);
		if (!errorMessage.empty())
			return true;
		if (0 == accessItemVector2.size())
		{
			return false;
		}
		errorMessage = "Access item with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}