#include "stdafx.h"
#include "StatusRuleViewClass.h"

namespace BusinessLayer{
	StatusRuleView::StatusRuleView(DataLayer::statusRuleViewCollection sCollection)
	{
		id = std::get<0>(sCollection);
		operation = std::get<1>(sCollection);
		statusName = std::get<2>(sCollection);
		statusID = std::get<3>(sCollection);
	}

	std::string StatusRuleView::GetStatusName()
	{
		return statusName;
	}

	void StatusRuleView::SetStatusName(std::string aStatusName)
	{
		statusName = aStatusName;
	}

	std::string StatusRuleView::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || !operation.empty() || !statusName.empty() || 0 != statusID)
		{
			return ormasDal.GetFilterForStatusRuleView(id, operation, statusName, statusID);
		}
		return "";
	}
}