#ifndef FIXEDASSETSDETAILSVIEWCLASS_H
#define FIXEDASSETSDETAILSVIEWCLASS_H

#include "FixedAssetsDetailsClass.h"

namespace BusinessLayer
{
	class FixedAssetsDetailsView : public FixedAssetsDetails
	{
	protected:
		int groupNumber = 0;
		std::string amortizeTypeName = "";
		std::string amortizeTypeCode = "";
		std::string divisionName = "";
		double primaryAccValue = 0;
		double amortizeAccValue = 0;
	public:
		FixedAssetsDetailsView(DataLayer::fixedAssetsDetailsViewCollection);
		FixedAssetsDetailsView(){};
		~FixedAssetsDetailsView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// OrderView class Accessors
		int GetGroupNumber();
		std::string GetAmortizeTypeName();
		std::string GetAmortizeTypeCode();
		std::string GetDivisionName();
		double GetPrimaryAccValue();
		double GetAmortizeAccValue();

		void SetGroupNumber(int);
		void SetAmortizeTypeName(std::string);
		void SetAmortizeTypeCode(std::string);
		void SetDivisionName(std::string);
		void SetPrimaryAccValue(double);
		void SetAmortizeAccValue(double);
	};
}
#endif //FixedAssetsDetailsVIEWCLASS_H
