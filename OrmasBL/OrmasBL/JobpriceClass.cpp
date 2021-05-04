#include "stdafx.h"
#include "JobpriceClass.h"

namespace BusinessLayer{
	Jobprice::Jobprice(DataLayer::jobpriceCollection jCollection)
	{
		id = std::get<0>(jCollection);
		productID = std::get<1>(jCollection);
		value = std::get<2>(jCollection);
		currencyID = std::get<3>(jCollection);
		volume = std::get<4>(jCollection);
		measureID = std::get<5>(jCollection);
		positionID = std::get<6>(jCollection);
	}
	Jobprice::Jobprice()
	{
		id = 0;
		productID = 0;
		value = 0.0;
		currencyID = 0;
		volume = 0.0;
		measureID = 0;
		positionID = 0;
	}

	int Jobprice::GetID()
	{
		return id;
	}

	int Jobprice::GetProductID()
	{
		return productID;
	}

	double Jobprice::GetValue()
	{
		return value;
	}

	int Jobprice::GetCurrencyID()
	{
		return currencyID;
	}

	double Jobprice::GetVolume()
	{
		return volume;
	}

	int Jobprice::GetMeasureID()
	{
		return measureID;
	}

	int Jobprice::GetPositionID()
	{
		return positionID;
	}

	void Jobprice::SetID(int jID)
	{
		id = jID;
	}

	void Jobprice::SetProductID(int pID)
	{
		productID = pID;
	}
	void Jobprice::SetValue(double jValue)
	{
		value = jValue;
	}
	void Jobprice::SetCurrencyID(int cID)
	{
		currencyID = cID;
	}

	void Jobprice::SetVolume(double jVolume)
	{
		volume = jVolume;
	}

	void Jobprice::SetMeasureID(int mID)
	{
		measureID = mID;
	}

	void Jobprice::SetPositionID(int posID)
	{
		positionID = posID;
	}

	bool Jobprice::CreateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double jValue, int cID, double jVolume, int mID,
		int posID, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, pID, jValue, cID, jVolume, mID, posID, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		productID = pID;
		value = jValue;
		currencyID = cID;
		volume = jVolume;
		measureID = mID;
		positionID = posID;
		if (0 != id && ormasDal.CreateJobprice(id, productID, value, currencyID, volume, measureID, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Jobprice::CreateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (ormasDal.CreateJobprice(id, productID, value, currencyID, volume, measureID, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Jobprice::DeleteJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteJobprice(id, errorMessage))
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

	bool Jobprice::UpdateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double jValue, int cID, double jVolume, int mID,
		int posID, std::string& errorMessage)
	{
		productID = pID;
		value = jValue;
		currencyID = cID;
		volume = jVolume;
		measureID = mID;
		positionID = posID;
		if (0 != id && ormasDal.UpdateJobprice(id, productID, value, currencyID, volume, measureID, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Jobprice::UpdateJobprice(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.UpdateJobprice(id, productID, value, currencyID, volume, measureID, positionID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Jobprice::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productID || 0 != value || 0 != currencyID || 0 != volume || 0 != measureID || 0 != positionID)
		{
			return ormasDal.GetFilterForJobprice(id, productID, value, currencyID, volume, measureID, positionID);
		}
		return "";
	}

	bool Jobprice::GetJobpriceByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int sID, std::string& errorMessage)
	{
		if (sID <= 0)
			return false;
		id = sID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::jobpriceViewCollection> jobpriceVector = ormasDal.GetJobprice(errorMessage, filter);
		if (0 != jobpriceVector.size())
		{
			id = std::get<0>(jobpriceVector.at(0));
			productID = std::get<7>(jobpriceVector.at(0));
			value = std::get<2>(jobpriceVector.at(0));
			currencyID = std::get<8>(jobpriceVector.at(0));
			volume = std::get<4>(jobpriceVector.at(0));
			measureID = std::get<9>(jobpriceVector.at(0));
			positionID = std::get<10>(jobpriceVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Jobprice with this id";
		}
		return false;
	}

	bool Jobprice::IsEmpty()
	{
		if (0 == id && 0 == productID && 0.0 == value && 0 == currencyID && 0.0 == volume && 0 == measureID && 0 == positionID)
			return true;
		return false;
	}

	void Jobprice::Clear()
	{
		id = 0;
		productID = 0;
		value = 0;
		currencyID = 0;
		volume = 0;
		measureID = 0;
		positionID = 0;
	}

	bool Jobprice::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, double jValue, int cID, double jVolume, int mID,
		int posID, std::string& errorMessage)
	{
		Jobprice jobprice;
		jobprice.Clear();
		errorMessage.clear();
		jobprice.SetProductID(pID);
		jobprice.SetValue(jValue);
		jobprice.SetCurrencyID(cID);
		jobprice.SetVolume(jVolume);
		jobprice.SetMeasureID(mID);
		jobprice.SetPositionID(posID);
		std::string filter = jobprice.GenerateFilter(ormasDal);
		std::vector<DataLayer::jobpriceViewCollection> jobpriceVector = ormasDal.GetJobprice(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == jobpriceVector.size())
		{
			return false;
		}
		errorMessage = "Jobprice with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Jobprice::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Jobprice jobprice;
		jobprice.Clear();
		errorMessage.clear();
		jobprice.SetProductID(productID);
		jobprice.SetValue(value);
		jobprice.SetCurrencyID(currencyID);
		jobprice.SetVolume(volume);
		jobprice.SetMeasureID(measureID);
		jobprice.SetPositionID(positionID);
		std::string filter = jobprice.GenerateFilter(ormasDal);
		std::vector<DataLayer::jobpriceViewCollection> jobpriceVector = ormasDal.GetJobprice(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == jobpriceVector.size())
		{
			return false;
		}
		errorMessage = "Jobprice with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}