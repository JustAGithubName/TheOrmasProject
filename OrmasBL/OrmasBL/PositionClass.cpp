#include "stdafx.h"
#include "PositionClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Position::Position(DataLayer::positionsCollection pCollection)
	{
		id = std::get<0>(pCollection);
		name = std::get<1>(pCollection);
	}
	Position::Position()
	{
		name = "";
	}
	int Position::GetID()
	{
		return id;
	}

	std::string Position::GetName()
	{
		return name;
	}

	void Position::SetID(int cID)
	{
		id = cID;
	}
	void Position::SetName(std::string pName)
	{
		if (!pName.empty())
			boost::trim(pName);
		name = pName;
	}

	bool Position::CreatePosition(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pName, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(pName);
		name = pName;
		if (0 != id && ormasDal.CreatePosition(id, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Position::CreatePosition(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreatePosition(id, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Position::DeletePosition(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeletePosition(id, errorMessage))
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

	bool Position::UpdatePosition(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pName, std::string& errorMessage)
	{
		TrimStrings(pName);
		name = pName;
		if (0 != id && ormasDal.UpdatePosition(id, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Position::UpdatePosition(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdatePosition(id, name, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Position::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty())
		{
			return ormasDal.GetFilterForPosition(id, name);
		}
		return "";
	}

	bool Position::GetPositionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::positionsCollection> positionVector = ormasDal.GetPositions(errorMessage, filter);
		if (0 != positionVector.size())
		{
			id = std::get<0>(positionVector.at(0));
			name = std::get<1>(positionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Position with this id";
		}
		return false;
	}

	bool Position::IsEmpty()
	{
		if (0 == id  && name.empty())
			return true;
		return false;
	}

	void Position::Clear()
	{
		id = 0;
		name.clear();
	}

	void Position::TrimStrings(std::string& pName)
	{
		if (!pName.empty())
			boost::trim(pName);
	}

	bool Position::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string pName, std::string& errorMessage)
	{
		Position position;
		position.Clear();
		errorMessage.clear();
		position.SetName(pName);
		std::string filter = position.GenerateFilter(ormasDal);
		std::vector<DataLayer::positionsCollection> positionVector = ormasDal.GetPositions(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == positionVector.size())
		{
			return false;
		}
		errorMessage = "Position with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Position::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Position position;
		position.Clear();
		errorMessage.clear();
		position.SetName(name);
		std::string filter = position.GenerateFilter(ormasDal);
		std::vector<DataLayer::positionsCollection> positionVector = ormasDal.GetPositions(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == positionVector.size())
		{
			return false;
		}
		errorMessage = "Position with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}