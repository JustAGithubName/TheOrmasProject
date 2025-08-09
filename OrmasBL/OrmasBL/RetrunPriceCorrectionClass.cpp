#include "stdafx.h"
#include "ReturnPriceCorrectionClass.h"

namespace BusinessLayer{
	ReturnPriceCorrection::ReturnPriceCorrection(DataLayer::returnPriceCorrectionCollection pCollection)
	{
		id = std::get<0>(pCollection);
		returnID = std::get<1>(pCollection);
		priceExtensionID = std::get<2>(pCollection);
		returnListID = std::get<3>(pCollection);
		standartValue = std::get<4>(pCollection);
		newValue = std::get<5>(pCollection);
	}
	ReturnPriceCorrection::ReturnPriceCorrection()
	{
		id = 0;
		returnID = 0;
		priceExtensionID = 0;
		returnListID = 0;
		standartValue = 0;
		newValue = 0;
	}

	int ReturnPriceCorrection::GetID()
	{
		return id;
	}

	int ReturnPriceCorrection::GetReturnID()
	{
		return returnID;
	}

	int ReturnPriceCorrection::GetPriceExtensionID()
	{
		return priceExtensionID;
	}

	int ReturnPriceCorrection::GetReturnListID()
	{
		return returnListID;
	}

	double ReturnPriceCorrection::GetStandartValue()
	{
		return standartValue;
	}

	double ReturnPriceCorrection::GetNewValue()
	{
		return newValue;
	}


	void ReturnPriceCorrection::SetID(int pID)
	{
		id = pID;
	}

	void ReturnPriceCorrection::SetReturnID(int oReturnID)
	{
		returnID = oReturnID;
	}

	void ReturnPriceCorrection::SetPriceExtensionID(int pExtensionID)
	{
		priceExtensionID = pExtensionID;
	}

	void ReturnPriceCorrection::SetReturnListID(int oListID)
	{
		returnListID = oListID;
	}

	void ReturnPriceCorrection::SetStandartValue(double sValue)
	{
		standartValue = sValue;
	}

	void ReturnPriceCorrection::SetNewValue(double nValue)
	{
		newValue = nValue;
	}


	bool ReturnPriceCorrection::CreateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, oID, peID, olID, sValue, nValue, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		returnID = oID;
		priceExtensionID = peID;
		returnListID = olID;
		standartValue = sValue;
		newValue = nValue;
		if (0 != id && ormasDal.CreateReturnPriceCorrection(id, returnID, priceExtensionID, returnListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ReturnPriceCorrection::CreateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateReturnPriceCorrection(id, returnID, priceExtensionID, returnListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ReturnPriceCorrection::DeleteReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteReturnPriceCorrection(id, errorMessage))
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

	bool ReturnPriceCorrection::UpdateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage)
	{
		returnID = oID;
		priceExtensionID = peID;
		returnListID = olID;
		standartValue = sValue;
		newValue = nValue;
		if (0 != id && ormasDal.UpdateReturnPriceCorrection(id, returnID, priceExtensionID, returnListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool ReturnPriceCorrection::UpdateReturnPriceCorrection(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateReturnPriceCorrection(id, returnID, priceExtensionID, returnListID, standartValue, newValue, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string ReturnPriceCorrection::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != returnID || 0 != priceExtensionID || 0 != returnListID || 0 != standartValue || 0 != newValue)
		{
			return ormasDal.GetFilterForReturnPriceCorrection(id, returnID, priceExtensionID, returnListID, standartValue, newValue);
		}
		return "";
	}

	bool ReturnPriceCorrection::GetReturnPriceCorrectionByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::returnPriceCorrectionCollection> returnPriceCorrectionVector = ormasDal.GetReturnPriceCorrection(errorMessage, filter);
		if (0 != returnPriceCorrectionVector.size())
		{
			id = std::get<0>(returnPriceCorrectionVector.at(0));
			returnID = std::get<1>(returnPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(returnPriceCorrectionVector.at(0));
			returnListID = std::get<3>(returnPriceCorrectionVector.at(0));
			standartValue = std::get<4>(returnPriceCorrectionVector.at(0));
			newValue = std::get<5>(returnPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find return price correction with this id";
		}
		return false;
	}

	bool ReturnPriceCorrection::GetReturnPriceCorrectionByPriceExtensionID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage)
	{
		if (pID <= 0)
			return false;
		priceExtensionID = pID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::returnPriceCorrectionCollection> returnPriceCorrectionVector = ormasDal.GetReturnPriceCorrection(errorMessage, filter);
		if (0 != returnPriceCorrectionVector.size())
		{
			id = std::get<0>(returnPriceCorrectionVector.at(0));
			returnID = std::get<1>(returnPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(returnPriceCorrectionVector.at(0));
			returnListID = std::get<3>(returnPriceCorrectionVector.at(0));
			standartValue = std::get<4>(returnPriceCorrectionVector.at(0));
			newValue = std::get<5>(returnPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Return price correction with this id";
		}
		return false;
	}

	bool ReturnPriceCorrection::GetReturnPriceCorrectionByReturnListID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int olID, std::string& errorMessage)
	{
		if (olID <= 0)
			return false;
		returnListID = olID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::returnPriceCorrectionCollection> returnPriceCorrectionVector = ormasDal.GetReturnPriceCorrection(errorMessage, filter);
		if (0 != returnPriceCorrectionVector.size())
		{
			id = std::get<0>(returnPriceCorrectionVector.at(0));
			returnID = std::get<1>(returnPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(returnPriceCorrectionVector.at(0));
			returnListID = std::get<3>(returnPriceCorrectionVector.at(0));
			standartValue = std::get<4>(returnPriceCorrectionVector.at(0));
			newValue = std::get<5>(returnPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find return price correction with this id";
		}
		return false;
	}

	bool ReturnPriceCorrection::GetReturnPriceCorrectionByReturnID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		if (oID <= 0)
			return false;
		returnID = oID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::returnPriceCorrectionCollection> returnPriceCorrectionVector = ormasDal.GetReturnPriceCorrection(errorMessage, filter);
		if (0 != returnPriceCorrectionVector.size())
		{
			id = std::get<0>(returnPriceCorrectionVector.at(0));
			returnID = std::get<1>(returnPriceCorrectionVector.at(0));
			priceExtensionID = std::get<2>(returnPriceCorrectionVector.at(0));
			returnListID = std::get<3>(returnPriceCorrectionVector.at(0));
			standartValue = std::get<4>(returnPriceCorrectionVector.at(0));
			newValue = std::get<5>(returnPriceCorrectionVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Return price correction with this id";
		}
		return false;
	}



	bool ReturnPriceCorrection::IsEmpty()
	{
		if (0 == id && 0 == returnID  && 0.0 == standartValue  && 0.0 == newValue && 0 == priceExtensionID && 0 == returnListID)
			return true;
		return false;
	}

	void ReturnPriceCorrection::Clear()
	{
		id = 0;
		returnID = 0;
		priceExtensionID = 0;
		returnListID = 0;
		standartValue = 0;
		newValue = 0;
	}

	bool ReturnPriceCorrection::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, int peID, int olID, double sValue, double nValue, std::string& errorMessage)
	{
		ReturnPriceCorrection returnPriceCorrection;
		returnPriceCorrection.Clear();
		errorMessage.clear();
		returnPriceCorrection.SetReturnID(oID);
		returnPriceCorrection.SetPriceExtensionID(peID);
		returnPriceCorrection.SetReturnListID(olID);
		returnPriceCorrection.SetStandartValue(sValue);
		returnPriceCorrection.SetNewValue(nValue);
		std::string filter = returnPriceCorrection.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnPriceCorrectionCollection> returnPriceCorrectionVector = ormasDal.GetReturnPriceCorrection(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == returnPriceCorrectionVector.size())
		{
			return false;
		}
		errorMessage = "Return price correction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool ReturnPriceCorrection::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		ReturnPriceCorrection returnPriceCorrection;
		returnPriceCorrection.Clear();
		errorMessage.clear();
		returnPriceCorrection.SetReturnID(returnID);
		returnPriceCorrection.SetPriceExtensionID(priceExtensionID);
		returnPriceCorrection.SetReturnListID(returnListID);
		returnPriceCorrection.SetStandartValue(standartValue);
		returnPriceCorrection.SetNewValue(newValue);
		std::string filter = returnPriceCorrection.GenerateFilter(ormasDal);
		std::vector<DataLayer::returnPriceCorrectionCollection> returnPriceCorrectionVector = ormasDal.GetReturnPriceCorrection(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == returnPriceCorrectionVector.size())
		{
			return false;
		}
		errorMessage = "Return price correction with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}