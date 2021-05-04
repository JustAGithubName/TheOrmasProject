#ifndef PHOTOCLASS_H
#define PHOTOCLASS_H

#include "OrmasDAL.h"

namespace BusinessLayer{
	class Photo{
	protected:
		int id = 0;
		int userID = 0;
		int productID = 0;
		std::string source = "";
	public:
		Photo();
		Photo(int pID, int uID, int pdID, std::string pSource) :id(pID), userID(uID), productID(pdID), source(pSource){};
		Photo(DataLayer::photosCollection);
		~Photo(){};

		std::string errorMessage = "";
		//Photo class Accessors
		int GetID();
		int GetUserID();
		int GetProductID();
		std::string GetSource();

		//Photo class Mutators
		void SetID(int);
		void SetUserID(int);
		void SetProductID(int);
		void SetSource(std::string);

		// Create, delete and update Photo
		bool CreatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeletePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int pID, std::string pSource, std::string& errorMessage);
		bool UpdatePhoto(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int pID, std::string pSource, std::string& errorMessage);

		//Generate filter string for class
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);
		bool GetPhotoByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int pID, std::string& errorMessage);
		bool IsEmpty();
		void Clear();
	private:
		void TrimStrings(std::string&);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int uID, int pID, std::string pSource, std::string& errorMessage);
		bool IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
	};
}
#endif