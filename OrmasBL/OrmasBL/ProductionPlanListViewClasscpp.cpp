#include "stdafx.h"
#include "ProductionPlanListViewClass.h"

namespace BusinessLayer
{
	ProductionPlanListView::ProductionPlanListView(DataLayer::productionPlanListViewCollection ppCollection)
	{
		id = std::get<0>(ppCollection);
		productionPlanID = std::get<1>(ppCollection);
		productName = std::get<2>(ppCollection);
		price = std::get<3>(ppCollection);
		currencyName = std::get<4>(ppCollection);
		volume = std::get<5>(ppCollection);
		measureName = std::get<6>(ppCollection);
		count = std::get<7>(ppCollection);
		sum = std::get<8>(ppCollection);
		sumCurrencyName = std::get<9>(ppCollection);
		statusName = std::get<10>(ppCollection);
		productID = std::get<11>(ppCollection);
		statusID = std::get<12>(ppCollection);
		currencyID = std::get<13>(ppCollection);
	}

	std::string ProductionPlanListView::GetProductName()
	{
		return productName;
	}
	double ProductionPlanListView::GetPrice()
	{
		return price;
	}
	std::string ProductionPlanListView::GetCurrencyName()
	{
		return currencyName;
	}
	double ProductionPlanListView::GetVolume()
	{
		return volume;
	}
	std::string ProductionPlanListView::GetStatusName()
	{
		return statusName;
	}
	std::string ProductionPlanListView::GetSumCurrencyName()
	{
		return sumCurrencyName;
	}
	std::string ProductionPlanListView::GetMeasureName()
	{
		return measureName;
	}

	void ProductionPlanListView::SetProductName(std::string cProductName)
	{
		productName = cProductName;
	}
	void ProductionPlanListView::SetPrice(double cPrice)
	{
		price = cPrice;
	}
	void  ProductionPlanListView::SetCurrencyName(std::string cCurrencyName)
	{
		currencyName = cCurrencyName;
	}
	void ProductionPlanListView::SetVolume(double cVolume)
	{
		volume = cVolume;
	}
	void ProductionPlanListView::SetStatusName(std::string cStatusName)
	{
		statusName = cStatusName;
	}
	void ProductionPlanListView::SetSumCurrencyName(std::string cSumCurrencyName)
	{
		sumCurrencyName = cSumCurrencyName;
	}
	void ProductionPlanListView::SetMeasureName(std::string cMeasureName)
	{
		measureName = cMeasureName;
	}

	std::string ProductionPlanListView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != productionPlanID || !productName.empty() || 0 != price || !currencyName.empty() || 0 != volume || !measureName.empty()
			|| 0 != count || 0 != sum || !sumCurrencyName.empty() || !statusName.empty() || 0 != productID || 0 != statusID || 0 != currencyID)
		{
			return ormasDal.GetFilterForProdnPlanListView(id, productionPlanID, productName, price, currencyName, volume, measureName, count, sum,
				sumCurrencyName, statusName, productID, statusID, currencyID);
		}
		return "";
	}
}