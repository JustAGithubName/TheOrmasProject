#include "stdafx.h"
#include "MeasureClass.h"
#include <boost/algorithm/string.hpp>

namespace BusinessLayer{
	Measure::Measure(DataLayer::measuresCollection mCollection)
	{
		id = std::get<0>(mCollection);
		name = std::get<1>(mCollection);
		shortName = std::get<2>(mCollection);
		unit = std::get<3>(mCollection);
	}

	int Measure::GetID()
	{
		return id;
	}

	std::string Measure::GetName()
	{
		return name;
	}

	std::string Measure::GetShortName()
	{
		return shortName;
	}

	int Measure::GetUnit()
	{
		return unit;
	}

	void Measure::SetID(int mID)
	{
		id = mID;
	}
	void Measure::SetName(std::string mName)
	{
		if (!mName.empty())
			boost::trim(mName);
		name = mName;
	}
	void Measure::SetShortName(std::string mShortName)
	{
		if (!mShortName.empty())
			boost::trim(mShortName);
		shortName = mShortName;
	}

	void Measure::SetUnit(int mUnit)
	{
		unit = mUnit;
	}

	bool Measure::CreateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string mName, std::string mShortName, int mUnit, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, mName, mShortName, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(mName, mShortName);
		name = mName;
		shortName = mShortName;
		unit = mUnit;
		if (0 != id && ormasDal.CreateMeasure(id, name, shortName, unit, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Measure::CreateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateMeasure(id, name, shortName, unit, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Measure::DeleteMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteMeasure(id, errorMessage))
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
	bool Measure::UpdateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string mName, std::string mShortName, int mUnit, std::string& errorMessage)
	{
		TrimStrings(mName, mShortName);
		name = mName;
		shortName = mShortName;
		if (0 != id && ormasDal.UpdateMeasure(id, name, shortName, mUnit, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Measure::UpdateMeasure(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateMeasure(id, name, shortName, unit, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Measure::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() ||  !shortName.empty())
		{
			return ormasDal.GetFilterForMeasure(id, name, shortName, unit);
		}
		return "";
	}

	bool Measure::GetMeasureByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int mID, std::string& errorMessage)
	{
		if (mID <= 0)
			return false;
		id = mID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::measuresCollection> measuresVector = ormasDal.GetMeasures(errorMessage, filter);
		if (0 != measuresVector.size())
		{
			id = std::get<0>(measuresVector.at(0));
			name = std::get<1>(measuresVector.at(0));
			shortName = std::get<2>(measuresVector.at(0));
			unit = std::get<3>(measuresVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find measure with this id";
		}
		return false;
	}
	
	bool Measure::IsEmpty()
	{
		if (0 == id && name == "" && shortName == "" && 0 == unit)
			return true;
		return false;
	}

	void Measure::Clear()
	{
		id = 0;
		name.clear();
		shortName.clear();
		unit = 0;
	}

	void Measure::TrimStrings(std::string& mName, std::string& mShortName)
	{
		if (!mName.empty())
			boost::trim(mName);
		if (!mShortName.empty())
			boost::trim(mShortName);
	}

	bool Measure::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string mName, std::string mShortName, std::string& errorMessage)
	{
		Measure measure;
		measure.Clear();
		errorMessage.clear();
		measure.SetName(mName);
		measure.SetShortName(mShortName);
		std::string filter = measure.GenerateFilter(ormasDal);
		std::vector<DataLayer::measuresCollection> measuresVector = ormasDal.GetMeasures(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == measuresVector.size())
		{
			return false;
		}
		errorMessage = "Measure with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Measure::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Measure measure;
		measure.Clear();
		errorMessage.clear();
		measure.SetName(name);
		measure.SetShortName(shortName);
		std::string filter = measure.GenerateFilter(ormasDal);
		std::vector<DataLayer::measuresCollection> measuresVector = ormasDal.GetMeasures(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == measuresVector.size())
		{
			return false;
		}
		errorMessage = "Measure with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}