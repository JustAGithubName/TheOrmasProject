#ifndef ENTRYVIEWCLASS_H
#define ENTRYVIEWCLASS_H

#include "EntryClass.h"
#include "OrmasDAL.h"
namespace BusinessLayer{
	class EntryView : public Entry
	{
		std::string debitingAccountNumber = "";
		std::string creditingAccountNumber = "";
	public:
		EntryView(DataLayer::entriesViewCollection);
		EntryView(){};
		~EntryView(){};
		std::string GenerateFilter(DataLayer::OrmasDal& ormasDal) override;

		// EntryView class Accessors
		std::string GetDebitingAccountNumber();
		std::string GetCreditingAccountNumber();

		void SetDebitingAccountNumber(std::string);
		void SetCreditingAccountNumber(std::string);
	};
}

#endif