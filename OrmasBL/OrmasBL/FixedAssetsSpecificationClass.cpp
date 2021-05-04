#include "stdafx.h"
#include "FixedAssetsSpecificationClass.h"

namespace BusinessLayer
{
	FixedAssetsSpecification::FixedAssetsSpecification(DataLayer::fixedAssetsSpecificationCollection fCollection)
	{
		id = std::get<0>(fCollection);
		name = std::get<1>(fCollection);
		factoryNumber = std::get<2>(fCollection);
		developer = std::get<3>(fCollection);
		document = std::get<4>(fCollection);
		objectCharacters = std::get<5>(fCollection);
		condition = std::get<6>(fCollection);
		dateOfConstruction = std::get<7>(fCollection);
	}

	int FixedAssetsSpecification::GetID()
	{
		return id;
	}

	std::string FixedAssetsSpecification::GetName()
	{
		return name;
	}

	std::string FixedAssetsSpecification::GetFactoryNumber()
	{
		return factoryNumber;
	}

	std::string FixedAssetsSpecification::GetDeveloper()
	{
		return developer;
	}

	std::string FixedAssetsSpecification::GetDocument()
	{
		return document;
	}

	std::string FixedAssetsSpecification::GetObjectCharacters()
	{
		return objectCharacters;
	}

	std::string FixedAssetsSpecification::GetCondition()
	{
		return condition;
	}

	std::string FixedAssetsSpecification::GetDateOfConstruction()
	{
		return dateOfConstruction;
	}

	void FixedAssetsSpecification::SetID(int fID)
	{
		id = fID;
	}

	void FixedAssetsSpecification::SetName(std::string sName)
	{
		name = sName;
	}

	void FixedAssetsSpecification::SetFactoryNumber(std::string sFactoryNumber)
	{
		factoryNumber = sFactoryNumber;
	}

	void FixedAssetsSpecification::SetDeveloper(std::string sDeveloper)
	{
		developer = sDeveloper;
	}

	void FixedAssetsSpecification::SetDocument(std::string sDocument)
	{
		document = sDocument;
	}

	void FixedAssetsSpecification::SetObjectCharacters(std::string sObjectCharacters)
	{
		objectCharacters = sObjectCharacters;
	}

	void FixedAssetsSpecification::SetCondition(std::string sCondition)
	{
		condition = sCondition;
	}
	void FixedAssetsSpecification::SetDateOfConstruction(std::string sDateOfConstruction)
	{
		dateOfConstruction = sDateOfConstruction;
	}


	bool FixedAssetsSpecification::CreateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sName, std::string sFactoryNumber, 
		std::string sDeveloper, std::string sDocument, std::string sObjChar, std::string sCondition, std::string sDateOfConst, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, sFactoryNumber, errorMessage))
			//return false;
		id = ormasDal.GenerateID();
		name = sName;
		factoryNumber = sFactoryNumber;
		developer = sDeveloper;
		document = sDocument;
		objectCharacters = sObjChar;
		condition = sCondition;
		dateOfConstruction = sDateOfConst;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateFixedAssetsSpecification(id, name, factoryNumber, developer, document,
			objectCharacters, condition, dateOfConstruction, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool FixedAssetsSpecification::CreateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
			//return false;
		id = ormasDal.GenerateID();
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.CreateFixedAssetsSpecification(id, name, factoryNumber, developer, document,
			objectCharacters, condition, dateOfConstruction, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool FixedAssetsSpecification::DeleteFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//if (!ormasDal.StartTransaction(errorMessage))
		//	return false;
		if (ormasDal.DeleteFixedAssetsOperation(id, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool FixedAssetsSpecification::UpdateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sName, std::string sFactoryNumber, std::string sDeveloper, std::string sDocument,
		std::string sObjChar, std::string sCondition, std::string sDateOfConst, std::string& errorMessage)
	{
		name = sName;
		factoryNumber = sFactoryNumber;
		developer = sDeveloper;
		document = sDocument;
		objectCharacters = sObjChar;
		condition = sCondition;
		dateOfConstruction = sDateOfConst;
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateFixedAssetsSpecification(id, name, factoryNumber, developer, document,
			objectCharacters, condition, dateOfConstruction, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool FixedAssetsSpecification::UpdateFixedAssetsSpecification(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (0 != id && ormasDal.UpdateFixedAssetsSpecification(id, name, factoryNumber, developer, document,
			objectCharacters, condition, dateOfConstruction, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	std::string FixedAssetsSpecification::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !factoryNumber.empty() || !developer.empty() || !document.empty() || !objectCharacters.empty() 
			|| !condition.empty() || !dateOfConstruction.empty())
		{
			return ormasDal.GetFilterForFixedAssetsSpecification(id, name, factoryNumber, developer, document,
				objectCharacters, condition, dateOfConstruction);
		}
		return "";
	}

	bool FixedAssetsSpecification::GetFixedAssetsSpecificationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fID, std::string& errorMessage)
	{
		if (fID <= 0)
			return false;
		id = fID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsSpecificationCollection> FixedAssetsSpecificationVector = ormasDal.GetFixedAssetsSpecification(errorMessage, filter);
		if (0 != FixedAssetsSpecificationVector.size())
		{
			id = std::get<0>(FixedAssetsSpecificationVector.at(0));
			name = std::get<1>(FixedAssetsSpecificationVector.at(0));
			factoryNumber = std::get<2>(FixedAssetsSpecificationVector.at(0));
			developer = std::get<3>(FixedAssetsSpecificationVector.at(0));
			document = std::get<4>(FixedAssetsSpecificationVector.at(0));
			objectCharacters = std::get<5>(FixedAssetsSpecificationVector.at(0));
			condition = std::get<6>(FixedAssetsSpecificationVector.at(0));
			dateOfConstruction = std::get<7>(FixedAssetsSpecificationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find fixed assets operations with this id";
		}
		return false;
	}

	bool FixedAssetsSpecification::IsEmpty()
	{
		if (0 == id && name == "" && factoryNumber == "" && developer == "" && document == "" && objectCharacters == "" 
			&& condition == "" && dateOfConstruction == "")
			return true;
		return false;
	}

	void FixedAssetsSpecification::Clear()
	{
		id = 0;
		name = "";
		factoryNumber = "";
		developer = "";
		document = "";
		objectCharacters = "";
		condition = "";
		dateOfConstruction = "";
	}

	/*bool FixedAssetsSpecification::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string sFactoryNumber, std::string& errorMessage)
	{
		FixedAssetsSpecification fixedAssetsSpecification;
		fixedAssetsSpecification.Clear();
		errorMessage.clear();
		fixedAssetsSpecification.SetFactoryNumber(sFactoryNumber);
		std::string filter = fixedAssetsSpecification.GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsSpecificationCollection> fixedAssetsSpecificationVector = ormasDal.GetFixedAssetsSpecification(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == fixedAssetsSpecificationVector.size())
		{
			return false;
		}
		errorMessage = "Fixed assets specification with these parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool FixedAssetsSpecification::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		FixedAssetsSpecification fixedAssetsSpecification;
		fixedAssetsSpecification.Clear();
		errorMessage.clear();
		fixedAssetsSpecification.SetFactoryNumber(factoryNumber);
		std::string filter = fixedAssetsSpecification.GenerateFilter(ormasDal);
		std::vector<DataLayer::fixedAssetsSpecificationCollection> fixedAssetsSpecificationVector = ormasDal.GetFixedAssetsSpecification(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == fixedAssetsSpecificationVector.size())
		{
			return false;
		}
		errorMessage = "Fixed assets specification with these parameters are already exist! Please avoid the duplication!";
		return true;
	}*/
}
