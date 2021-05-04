#include "stdafx.h"
#include "PhotoClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	Photo::Photo(DataLayer::photosCollection pCollection)
	{
		id = std::get<0>(pCollection);
		userID = std::get<1>(pCollection);
		productID = std::get<2>(pCollection);
		source = std::get<3>(pCollection);
	}
	Photo::Photo()
	{
		userID = 0;
		productID = 0;
		source = "";
	}
	int Photo::GetID()
	{
		return id;
	}

	int Photo::GetUserID()
	{
		return userID;
	}

	int Photo::GetProductID()
	{
		return productID;
	}
	std::string Photo::GetSource()
	{
		return source;
	}

	void Photo::SetID(int cID)
	{
		id = cID;
	}
	void Photo::SetUserID(int uID)
	{
		userID = uID;
	}
	void Photo::SetProductID(int pID)
	{
		productID = pID;
	}

	void Photo::SetSource(std::string pSource)
	{
		if (!pSource.empty())
			boost::trim(pSource);
		source = pSource;
	}

	bool Photo::CreatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int pID, std::string pSource, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, uID, pID, pSource, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		TrimStrings(pSource);
		userID = uID;
		productID = pID;
		source = pSource;

		if (0 != id && ormasDal.CreatePhoto(id, userID, productID, source, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Photo::CreatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (IsDuplicate(globalVar, ormasDal, errorMessage))
			return false;
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreatePhoto(id, userID, productID, source, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Photo::DeletePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeletePhoto(id, errorMessage))
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

	bool Photo::UpdatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int pID, std::string pSource, std::string& errorMessage)
	{
		TrimStrings(pSource);
		userID = uID;
		productID = pID;
		source = pSource;
		if (0 != id && ormasDal.UpdatePhoto(id, userID, productID, source, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Photo::UpdatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdatePhoto(id, userID, productID, source, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Photo::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != userID || 0 != productID || !source.empty())
		{
			return ormasDal.GetFilterForPhoto(id, userID, productID, source);
		}
		return "";
	}

	bool Photo::GetPhotoByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::photosCollection> photoVector = ormasDal.GetPhotos(errorMessage, filter);
		if (0 != photoVector.size())
		{
			id = std::get<0>(photoVector.at(0));
			userID = std::get<1>(photoVector.at(0));
			productID = std::get<2>(photoVector.at(0));
			source = std::get<3>(photoVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Photo with this id";
		}
		return false;
	}

	bool Photo::IsEmpty()
	{
		if (0 == id && 0 == userID && 0 == productID && source.empty())
			return true;
		return false;
	}

	void Photo::Clear()
	{
		id = 0;
		userID = 0;
		productID = 0;
		source.clear();
	}

	void Photo::TrimStrings(std::string& pSource)
	{
		if (!pSource.empty())
			boost::trim(pSource);
	}

	bool Photo::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int pID, std::string pSource, std::string& errorMessage)
	{
		Photo photo;
		photo.Clear();
		errorMessage.clear();
		photo.SetUserID(uID);
		photo.SetSource(pSource);
		std::string filter = photo.GenerateFilter(ormasDal);
		std::vector<DataLayer::photosCollection> photoVector = ormasDal.GetPhotos(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == photoVector.size())
		{
			return false;
		}
		photo.SetUserID(0);
		photo.SetProductID(pID);
		photo.SetSource(pSource);
		std::string filter2 = photo.GenerateFilter(ormasDal);
		std::vector<DataLayer::photosCollection> photoVector2 = ormasDal.GetPhotos(errorMessage, filter2);
		if (!errorMessage.empty())
			return true;
		if (0 == photoVector2.size())
		{
			return false;
		}
		errorMessage = "Photo with this parameters are already exist! Please avoid the duplication!";
		return true;
	}

	bool Photo::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		Photo photo;
		photo.Clear();
		errorMessage.clear();
		photo.SetUserID(userID);
		photo.SetSource(source);
		std::string filter = photo.GenerateFilter(ormasDal);
		std::vector<DataLayer::photosCollection> photoVector = ormasDal.GetPhotos(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == photoVector.size())
		{
			return false;
		}
		photo.SetUserID(0);
		photo.SetProductID(userID);
		photo.SetSource(source);
		std::string filter2 = photo.GenerateFilter(ormasDal);
		std::vector<DataLayer::photosCollection> photoVector2 = ormasDal.GetPhotos(errorMessage, filter2);
		if (!errorMessage.empty())
			return true;
		if (0 == photoVector2.size())
		{
			return false;
		}
		errorMessage = "Photo with this parameters are already exist! Please avoid the duplication!";
		return true;
	}
}