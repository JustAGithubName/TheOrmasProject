#include "stdafx.h"
#include "NetCostCoefficientViewClass.h"

namespace BusinessLayer{
	NetCostCoefficientView::NetCostCoefficientView(DataLayer::netCostCoefficientViewCollection nCollection)
	{
		id = std::get<0>(nCollection);
		productName = std::get<1>(nCollection);
		value = std::get<2>(nCollection);
		productID = std::get<3>(nCollection);
		comment = std::get<4>(nCollection);
	}

	std::string NetCostCoefficientView::GetProductName()
	{
		return productName;
	}


	void NetCostCoefficientView::SetProductName(std::string jProductName)
	{
		productName = jProductName;
	}


	std::string NetCostCoefficientView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || comment.empty() || productName.empty() || 0 != value || 0 != productID)
		{
			return ormasDal.GetFilterForNetCostCoefficientView(id, productName, value, productID, comment);
		}
		return "";
	}
}