#ifndef FIXEDASSETSUNIONCLASS_H
#define FIXEDASSETSUNIONCLASS_H

#include "OrmasDAL.h"
#include <map>
#include "FixedAssetsClass.h"
#include "FixedAssetsDetailsClass.h"
#include "FixedAssetsSpecificationClass.h"
#include "PostingFixedAssetsClass.h"

namespace BusinessLayer
{
	class FixedAssetsUnion
	{
	protected:
		FixedAssets *fixedAssets = new FixedAssets();
		FixedAssetsDetails *fixedAssetsDetails = new FixedAssetsDetails();
		FixedAssetsSpecification *fixedAssetsSpecification = new FixedAssetsSpecification();
		PostingFixedAssets *postingFixedAssets = new PostingFixedAssets();
	public:
		FixedAssetsUnion(FixedAssets* fAssets, FixedAssetsDetails* faDetails, FixedAssetsSpecification* faSpecification, PostingFixedAssets* pfAssets) :
			fixedAssets(fAssets), fixedAssetsDetails(faDetails), fixedAssetsSpecification(faSpecification), postingFixedAssets(pfAssets){};
		FixedAssetsUnion(DataLayer::fixedAssetsUnionCollection);
		FixedAssetsUnion(){};
		~FixedAssetsUnion(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		bool isNewFixedAssets = false;
		double amortizeValue = 0;
		double primaryValue = 0;
		int fixedAssetsAccountID = 0;
		int purveyorID = 0;
		int accountableID = 0;
		int accountID = 0;
		//FixedAssetsUnion class Accessors
		FixedAssets* GetFixedAssets();
		FixedAssetsDetails* GetFixedAssetsDetails();
		FixedAssetsSpecification* GetFixedAssetsSpecification();
		PostingFixedAssets* GetPostingFixedAssets();

		//FixedAssetsUnion class Mutators
		void SetFixedAssets(FixedAssets*);
		void SetFixedAssetsDetails(FixedAssetsDetails*);
		void SetFixedAssetsSpecification(FixedAssetsSpecification*);
		void SetPostingFixedAssets(PostingFixedAssets*);

		//Create, delete, update methods
		bool CreateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool UpdateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool DeleteFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		bool CreateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, FixedAssets* fAssets, FixedAssetsDetails* faDetails, FixedAssetsSpecification* faSpecification, PostingFixedAssets* pfAssets, std::string& errorMessage);
		bool UpdateFixedAssetsUnion(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, FixedAssets* fAssets, FixedAssetsDetails* faDetails, FixedAssetsSpecification* faSpecification, PostingFixedAssets* pfAssets, std::string& errorMessage);

		//Generate filter string for class
		bool IsEmpty();
		void Clear();
		std::string GenerateInventoryNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int divID);
	private:
		std::string GenerateInvRawNumber(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage);
		int GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int fxID, std::string& errorMessage);
		int previousStatusID = 0;
	};
}
#endif //FixedAssetsUnionCLASS_H