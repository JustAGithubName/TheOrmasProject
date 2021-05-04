#ifndef ACCOUNTABLEVIEWCLASS_H
#define ACCOUNTABLEVIEWCLASS_H

#include "AccountableClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class AccountableView : public Accountable
	{
		std::string roleName = "";
	public:
		AccountableView(DataLayer::accountableViewCollection);
		AccountableView(){};
		~AccountableView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// AccountableView class Accountableors
		std::string GetRoleName();
		

		void SetRoleName(std::string);
		
	};
}
#endif 