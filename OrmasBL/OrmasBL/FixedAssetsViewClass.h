#ifndef FIXEDASSETSVIEWCLASS_H
#define FIXEDASSETSVIEWCLASS_H

#include "FixedAssetsClass.h"

namespace BusinessLayer
{
	class FixedAssetsView : public FixedAssets
	{
		std::string name = "";
		double primaryCostValue = 0;
		double amortizeValue = 0;
		std::string divisionName = "";
		std::string statusName = "";
		int primaryParentAccID = 0;
		int amortizePrimeAccID = 0;
	public:
		FixedAssetsView(DataLayer::fixedAssetsViewCollection);
		FixedAssetsView(){};
		~FixedAssetsView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// OrderView class Accessors
		std::string GetName();
		double GetPrimaryCostValue();
		double GetAmortizeValue();
		std::string GetDivisionName();
		std::string GetStatusName();
		int GetPrimaryParentAccID();
		int GetAmortizePrimeAccID();

		void SetName(std::string);
		void SetPrimaryCostValue(double);
		void SetAmortizeValue(double);
		void SetDivisionName(std::string);
		void SetStatusName(std::string);
		void SetPrimaryParentAccID(int);
		void SetAmortizePrimeAccID(int);
	};
}
#endif //FixedAssetsVIEWCLASS_H
