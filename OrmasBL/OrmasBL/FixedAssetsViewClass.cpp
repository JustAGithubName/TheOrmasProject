#include "stdafx.h"
#include "FixedAssetsViewClass.h"

namespace BusinessLayer
{
	FixedAssetsView::FixedAssetsView(DataLayer::fixedAssetsViewCollection fCollection)
	{
		id = std::get<0>(fCollection);
		name = std::get<1>(fCollection);
		inventoryNumber = std::get<2>(fCollection);
		primaryCost = std::get<3>(fCollection);
		stopCost = std::get<4>(fCollection);
		primaryCostValue = std::get<5>(fCollection);
		amortizeValue = std::get<6>(fCollection);
		divisionName = std::get<7>(fCollection);
		statusName = std::get<8>(fCollection);
		serviceLife = std::get<9>(fCollection);
		isAmortize = std::get<10>(fCollection);
		buyDate = std::get<11>(fCollection);
		startOfOperationDate = std::get<12>(fCollection);
		endOfOperationDate = std::get<13>(fCollection);
		specificationID = std::get<14>(fCollection);
		statusID = std::get<15>(fCollection);
		fixedAssetsDetailsID = std::get<16>(fCollection);
		primaryParentAccID = std::get<17>(fCollection);
		amortizePrimeAccID = std::get<18>(fCollection);
	}

	std::string FixedAssetsView::GetName()
	{
		return name;
	}
	double FixedAssetsView::GetPrimaryCostValue()
	{
		return primaryCostValue;
	}
	double FixedAssetsView::GetAmortizeValue()
	{
		return amortizeValue;
	}
	std::string FixedAssetsView::GetDivisionName()
	{
		return divisionName;
	}
	std::string FixedAssetsView::GetStatusName()
	{
		return statusName;
	}
	int FixedAssetsView::GetPrimaryParentAccID()
	{
		return primaryParentAccID;
	}
	int FixedAssetsView::GetAmortizePrimeAccID()
	{
		return amortizePrimeAccID;
	}

	void FixedAssetsView::SetName(std::string dName)
	{
		name = dName;
	}
	void FixedAssetsView::SetPrimaryCostValue(double fPrimaryCostValue)
	{
		primaryCostValue = fPrimaryCostValue;
	}
	void FixedAssetsView::SetAmortizeValue(double fAmortizeValue)
	{
		amortizeValue = fAmortizeValue;
	}
	void FixedAssetsView::SetDivisionName(std::string fDivisionName)
	{
		divisionName = fDivisionName;
	}
	void FixedAssetsView::SetStatusName(std::string dStatusName)
	{
		statusName = dStatusName;
	}
	void FixedAssetsView::SetPrimaryParentAccID(int pPrimaryParentAccID)
	{
		primaryParentAccID = pPrimaryParentAccID;
	}
	void FixedAssetsView::SetAmortizePrimeAccID(int aAmortizePrimeAccID)
	{
		amortizePrimeAccID = aAmortizePrimeAccID;
	}

	std::string FixedAssetsView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !name.empty() || !inventoryNumber.empty() || 0.0 != primaryCost || 0.0 != stopCost || 0.0 != primaryCostValue || 0.0 != amortizeValue 
			|| !divisionName.empty() || !statusName.empty() || 0 != serviceLife
			|| !buyDate.empty() || !startOfOperationDate.empty() || !endOfOperationDate.empty() || 0 != specificationID || 0 != statusID || 0 != fixedAssetsDetailsID
			|| 0 != primaryParentAccID || 0 != amortizePrimeAccID)
		{
			return ormasDal.GetFilterForFixedAssView(id, name, inventoryNumber, primaryCost, stopCost, primaryCostValue, amortizeValue, 
				divisionName, statusName, serviceLife, buyDate, startOfOperationDate, endOfOperationDate, specificationID, statusID, fixedAssetsDetailsID, primaryParentAccID, amortizePrimeAccID);
		}
		return "";
	}
}

