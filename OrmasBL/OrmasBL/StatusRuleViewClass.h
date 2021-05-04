#ifndef STATUSRULEVIEWCLASS_H
#define STATUSRULEVIEWCLASS_H

#include "StatusRuleClass.h"

namespace BusinessLayer{
	class StatusRuleView : public StatusRule
	{
		std::string statusName = "";
	public:
		StatusRuleView(DataLayer::statusRuleViewCollection);
		StatusRuleView(){};
		~StatusRuleView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal);

		// StatusRuleView class Accessors
		std::string GetStatusName();

		void SetStatusName(std::string);
	};
}

#endif