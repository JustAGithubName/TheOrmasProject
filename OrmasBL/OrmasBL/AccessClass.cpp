#include "stdafx.h"
#include "AccessClass.h"
#include "AccessItemClass.h"
#include "UserClass.h"
#include "RoleClass.h"

namespace BusinessLayer{
	Access::Access(DataLayer::accessesCollection aCollection)
	{
		id = std::get<0>(aCollection);
		roleID = std::get<1>(aCollection);
		accessItemID = std::get<2>(aCollection);
	}
	Access::Access()
	{
		roleID = 0;
		accessItemID = 0;
	}
	int Access::GetID()
	{
		return id;
	}

	int Access::GetRoleID()
	{
		return roleID;
	}

	int Access::GetAccessItemID()
	{
		return accessItemID;
	}

	void Access::SetID(int cID)
	{
		id = cID;
	}
	void Access::SetRoleID(int rID)
	{
		roleID = rID;
	}
	void Access::SetAccessItemID(int aiID)
	{
		accessItemID = aiID;
	}

	bool Access::CreateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int aiID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, rID, aiID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		roleID = rID;
		accessItemID = aiID;

		if (0 != id && ormasDal.CreateAccess(id, roleID, accessItemID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Access::CreateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateAccess(id, roleID, accessItemID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Access::DeleteAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteAccess(id, errorMessage))
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

	bool Access::UpdateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int aiID, std::string& errorMessage)
	{
		roleID = rID;
		accessItemID = aiID;
		if (0 != id && ormasDal.UpdateAccess(id, roleID, accessItemID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Access::UpdateAccess(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateAccess(id, roleID, accessItemID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Access::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != roleID || 0 != accessItemID)
		{
			return ormasDal.GetFilterForAccess(id, roleID, accessItemID);
		}
		return "";
	}

	bool Access::GetAccessByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accessesViewCollection> accessVector = ormasDal.GetAccesses(errorMessage, filter);
		if (0 != accessVector.size())
		{
			id = std::get<0>(accessVector.at(0));
			roleID = std::get<5>(accessVector.at(0));
			accessItemID = std::get<6>(accessVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Access with this id";
		}
		return false;
	}

	bool Access::IsEmpty()
	{
		if (0 == id && 0 == roleID && 0 == accessItemID)
			return true;
		return false;
	}

	void Access::Clear()
	{
		id = 0;
		roleID = 0;
		accessItemID = 0;
	}


	bool Access::CheckAccess(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, int accessItemID, std::string checkedDivision, std::string checkingItem)
	{
		AccessItem accessItem;
		errorMessage = "";
		if (accessItem.GetAccessItemByID(globalVar, *ormasDal, accessItemID, errorMessage))
		{
			if (0 == checkedDivision.compare(accessItem.GetDivision()))
			{
				if (0 == checkingItem.compare(accessItem.GetNameEng()) || 0 == checkingItem.compare(accessItem.GetNameRu()))
				return true;
			}
		}
		return false;
	}

	bool Access::CheckAccess(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, int accessItemID, std::string checkedDivision)
	{
		AccessItem accessItem;
		errorMessage = "";
		if (accessItem.GetAccessItemByID(globalVar, *ormasDal, accessItemID, errorMessage))
		{
			if (0 == checkedDivision.compare(accessItem.GetDivision()))
			{
				return true;
			}
		}
		return false;
	}

	std::string Access::GetCRUDAccess(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, User* loggedUser, std::string accessItemName)
	{
		std::vector<int> rights;
		rights = GetRightsList(globalVar, ormasDal, loggedUser);
		if (1 == rights.size())
		{
			if (CheckAccess(globalVar, ormasDal, rights.at(0), "ALL"))
			{
				// returning 'CRUD', CREATE/READ/UPDATE/DELETE - max access rights
				return "CRUD";
			}
		}
		if (0 < rights.size())
		{
			std::string errorMessage = "";
			AccessItem itemRights;
			AccessItem itemForCheck;
			if (!itemForCheck.GetAccessItemByEngName(globalVar, *ormasDal, accessItemName, errorMessage))
				return "";
			for each (auto id in rights)
			{
				itemRights.Clear();
				if (itemRights.GetAccessItemByID(globalVar, *ormasDal, id, errorMessage))
				{
					if (itemRights.GetNameEng() == itemForCheck.GetNameEng())
					{
						if (0 != itemRights.GetDivision().compare("MENU") && 0 != itemRights.GetDivision().compare("MENUITEM"))
						{
							return itemRights.GetDivision();
						}
					}
				}
			}
		}
		return "";
	}

	std::vector<int> Access::GetRightsList(GlobalVariable* globalVar, DataLayer::OrmasDal* ormasDal, User *loggedUser)
	{
		std::vector<int> accessItemIDVector;
		SetRoleID(loggedUser->GetRoleID());
		std::string filter = GenerateFilter(*ormasDal);
		std::vector<DataLayer::accessesViewCollection> accessVector = ormasDal->GetAccesses(errorMessage, filter);
		if (0 != accessVector.size())
		{
			for each (auto item in accessVector)
			{
				accessItemIDVector.push_back(std::get<6>(item));
			}
		}
		return accessItemIDVector;
	}

	bool Access::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int rID, int aiID, std::string& errorMessage)
	{
		Access access;
		access.Clear();
		errorMessage.clear();
		access.SetRoleID(rID);
		access.SetAccessItemID(aiID);
		std::string filter = access.GenerateFilter(ormasDal);
		std::vector<DataLayer::accessesViewCollection> accessVector = ormasDal.GetAccesses(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accessVector.size())
		{
			return false;
		}
		errorMessage = "Access with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Access::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Access access;
		access.Clear();
		errorMessage.clear();
		access.SetRoleID(roleID);
		access.SetAccessItemID(accessItemID);
		std::string filter = access.GenerateFilter(ormasDal);
		std::vector<DataLayer::accessesViewCollection> accessVector = ormasDal.GetAccesses(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accessVector.size())
		{
			return false;
		}
		errorMessage = "Access with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}