#include "stdafx.h"
#include "AccountableUnionDocumentClass.h"
#include "StatusClass.h"
#include <boost/algorithm/string.hpp>


namespace BusinessLayer{
	
	std::vector<AccountableApprovement>* AccountableUnionDocument::GetAccountableApprovementVector()
	{
		return approveVec;
	}

	AccountableDocument* AccountableUnionDocument::GetAccountableDocument()
	{
		return accountableDocument;
	}

	

	std::vector<AccountableDocumentListRelation>* AccountableUnionDocument::GetAccountableDocumentListVector()
	{
		return docListVec;
	}

	std::vector<AccountableEntry>* AccountableUnionDocument::GetAccountableEntryVector()
	{
		return entryVec;
	}

	std::vector<AccountablePaymentRelation>* AccountableUnionDocument::GetAccountablePaymentVector()
	{
		return paymentVec;
	}

	std::vector<AccountableWithdrawalRelation>* AccountableUnionDocument::GetAccountableWithdrawalVector()
	{
		return withdrawalVec;
	}

	std::vector<ExpenseDocument>* AccountableUnionDocument::GetExpenseDocumentVector()
	{
		return expenseVec;
	}

	void AccountableUnionDocument::SetAccountableApprovementVector(std::vector<AccountableApprovement>* aApprovementVector)
	{
		approveVec = aApprovementVector;
	}

	void AccountableUnionDocument::SetExpenseDocumentVector(std::vector<ExpenseDocument>* eDocumentVector)
	{
		expenseVec = eDocumentVector;
	}

	void AccountableUnionDocument::SetAccountableDocumentListVector(std::vector<AccountableDocumentListRelation>* aDocumentListVector)
	{
		docListVec = aDocumentListVector;
	}

	void AccountableUnionDocument::SetAccountableDocument(AccountableDocument* aDocument)
	{
		accountableDocument = aDocument;
	}

	void AccountableUnionDocument::SetAccountableEntryVector(std::vector<AccountableEntry>* aEntryVector)
	{
		entryVec = aEntryVector;
	}

	void AccountableUnionDocument::SetAccountablePaymentVector(std::vector<AccountablePaymentRelation>* aPaymentRelationVector)
	{
		paymentVec = aPaymentRelationVector;
	}

	void AccountableUnionDocument::SetAccountableWithdrawalVector(std::vector<AccountableWithdrawalRelation>* aWithdrawalRelationVector)
	{
		withdrawalVec = aWithdrawalRelationVector;
	}

	void AccountableUnionDocument::SetAccountableTransaction(AccountableTransaction* aWithdrawalTransaction)
	{
		accountableTransaction = aWithdrawalTransaction;
	}

	bool AccountableUnionDocument::CreateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, AccountableDocument* aDocument,
		AccountableTransaction* aTransaction, std::vector<AccountableApprovement>* aApproveVec,
		std::vector<AccountableDocumentListRelation>* aDocListVec, std::vector<AccountableEntry>* aEntryVec,
		std::vector<AccountablePaymentRelation>* aPaymentVec, std::vector<AccountableWithdrawalRelation>* aWithdrawalVec,
		std::vector<ExpenseDocument>* aExpenseVec, std::string& errorMessage)
	{

		//if (IsDuplicate(globalVar, ormasDal, eID, aInformation, errorMessage))
		//	return false;
		std::map<std::string, int> statusMap = Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		
		accountableDocument = aDocument;
		accountableTransaction = aTransaction;
		approveVec = aApproveVec;
		docListVec = aDocListVec;
		entryVec = aEntryVec;
		paymentVec = aPaymentVec;
		withdrawalVec = aWithdrawalVec;
		expenseVec = aExpenseVec;

		if (accountableDocument->GetStatusID() == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->CreateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				accountableTransaction->SetAccountableDocumentID(accountableDocument->GetID());
				if (accountableTransaction->CreateAccountableTransaction(globalVar, ormasDal, errorMessage))
				{
					if (approveVec->size() > 0)
					{
						for each (auto appr in *approveVec)
						{
							appr.SetAccountableDocumentID(accountableDocument->GetID());
							if (!appr.CreateAccountableApprovement(globalVar, ormasDal, errorMessage))
								return false;
						}
						if (entryVec->size() > 0)
						{
							for each (auto aEnt in *entryVec)
							{
								aEnt.SetAccountableDocumentID(accountableDocument->GetID());
								if (!aEnt.CreateAccountableEntry(globalVar, ormasDal, errorMessage))
									return false;
							}
							if (paymentVec->size() > 0)
							{
								for each (auto aPmt in *paymentVec)
								{
									aPmt.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aPmt.CreateAccountablePaymentRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (withdrawalVec->size() > 0)
							{
								for each (auto aWtd in *withdrawalVec)
								{
									aWtd.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aWtd.CreateAccountableWithdrawalRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (expenseVec->size() > 0)
							{
								AccountableDocumentListRelation adListVec;
								for each (auto aEdoc in *expenseVec)
								{
									if (!aEdoc.CreateExpenseDocument(globalVar, ormasDal, errorMessage))
										return false;
									adListVec.SetAccountableDocumentID(accountableDocument->GetID());
									adListVec.SetExpenseDocumentID(aEdoc.GetID());
									if (!adListVec.CreateAccountableDocumentListRelation(globalVar, ormasDal, errorMessage))
										return false;

								}
								return true;
							}
							else
							{
								return false;
							}
						}
						
					}
				}
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			if (accountableDocument->CreateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				accountableTransaction->SetAccountableDocumentID(accountableDocument->GetID());
				if (accountableTransaction->CreateAccountableTransaction(globalVar, ormasDal, errorMessage))
				{
					if (approveVec->size() > 0)
					{
						for each (auto appr in *approveVec)
						{
							appr.SetAccountableDocumentID(accountableDocument->GetID());
							if (!appr.CreateAccountableApprovement(globalVar, ormasDal, errorMessage))
								return false;
						}
						if (entryVec->size() > 0)
						{
							for each (auto aEnt in *entryVec)
							{
								aEnt.SetAccountableDocumentID(accountableDocument->GetID());
								if (!aEnt.CreateAccountableEntry(globalVar, ormasDal, errorMessage))
									return false;
								if (!aEnt.ExecuteEntry(globalVar, ormasDal, errorMessage))
									return false;
							}
							if (paymentVec->size() > 0)
							{
								for each (auto aPmt in *paymentVec)
								{
									aPmt.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aPmt.CreateAccountablePaymentRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (withdrawalVec->size() > 0)
							{
								for each (auto aWtd in *withdrawalVec)
								{
									aWtd.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aWtd.CreateAccountableWithdrawalRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (expenseVec->size() > 0)
							{
								AccountableDocumentListRelation adListVec;
								for each (auto aEdoc in *expenseVec)
								{
									if (!aEdoc.CreateExpenseDocument(globalVar, ormasDal, errorMessage))
										return false;
									adListVec.SetAccountableDocumentID(accountableDocument->GetID());
									adListVec.SetExpenseDocumentID(aEdoc.GetID());
									if (!adListVec.CreateAccountableDocumentListRelation(globalVar, ormasDal, errorMessage))
										return false;

								}
								return true;
							}
							else
							{
								return false;
							}
						}
					}
				}
			}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableUnionDocument::CreateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		std::map<std::string, int> statusMap = Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;
		//if (IsDuplicate(globalVar, ormasDal, errorMessage))
		//	return false;
		if (accountableDocument->GetStatusID() == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->CreateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				accountableTransaction->SetAccountableDocumentID(accountableDocument->GetID());
				if (accountableTransaction->CreateAccountableTransaction(globalVar, ormasDal, errorMessage))
				{
					if (approveVec->size() > 0)
					{
						for each (auto appr in *approveVec)
						{
							appr.SetAccountableDocumentID(accountableDocument->GetID());
							if (!appr.CreateAccountableApprovement(globalVar, ormasDal, errorMessage))
								return false;
						}
						if (entryVec->size() > 0)
						{
							for each (auto aEnt in *entryVec)
							{
								aEnt.SetAccountableDocumentID(accountableDocument->GetID());
								if (!aEnt.CreateAccountableEntry(globalVar, ormasDal, errorMessage))
									return false;
							}
							if (paymentVec->size() > 0)
							{
								for each (auto aPmt in *paymentVec)
								{
									aPmt.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aPmt.CreateAccountablePaymentRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (withdrawalVec->size() > 0)
							{
								for each (auto aWtd in *withdrawalVec)
								{
									aWtd.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aWtd.CreateAccountableWithdrawalRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (expenseVec->size() > 0)
							{
								AccountableDocumentListRelation adListVec;
								for each (auto aEdoc in *expenseVec)
								{
									if (!aEdoc.CreateExpenseDocument(globalVar, ormasDal, errorMessage))
										return false;
									adListVec.SetAccountableDocumentID(accountableDocument->GetID());
									adListVec.SetExpenseDocumentID(aEdoc.GetID());
									if (!adListVec.CreateAccountableDocumentListRelation(globalVar, ormasDal, errorMessage))
										return false;

								}
								return true;
							}
							else
							{
								return true;
							}
						}

					}
				}
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			if (accountableDocument->CreateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				accountableTransaction->SetAccountableDocumentID(accountableDocument->GetID());
				if (accountableTransaction->CreateAccountableTransaction(globalVar, ormasDal, errorMessage))
				{
					if (approveVec->size() > 0)
					{
						for each (auto appr in *approveVec)
						{
							appr.SetAccountableDocumentID(accountableDocument->GetID());
							if (!appr.CreateAccountableApprovement(globalVar, ormasDal, errorMessage))
								return false;
						}
						if (entryVec->size() > 0)
						{
							for each (auto aEnt in *entryVec)
							{
								aEnt.SetAccountableDocumentID(accountableDocument->GetID());
								if (!aEnt.CreateAccountableEntry(globalVar, ormasDal, errorMessage))
									return false;
								if (!aEnt.ExecuteEntry(globalVar, ormasDal, errorMessage))
									return false;
							}
							if (paymentVec->size() > 0)
							{
								for each (auto aPmt in *paymentVec)
								{
									aPmt.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aPmt.CreateAccountablePaymentRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (withdrawalVec->size() > 0)
							{
								for each (auto aWtd in *withdrawalVec)
								{
									aWtd.SetAccountableDocumentID(accountableDocument->GetID());
									if (!aWtd.CreateAccountableWithdrawalRelation(globalVar, ormasDal, errorMessage))
										return false;
								}
							}
							if (expenseVec->size() > 0)
							{
								AccountableDocumentListRelation adListVec;
								for each (auto aEdoc in *expenseVec)
								{
									if (!aEdoc.CreateExpenseDocument(globalVar, ormasDal, errorMessage))
										return false;
									adListVec.SetAccountableDocumentID(accountableDocument->GetID());
									adListVec.SetExpenseDocumentID(aEdoc.GetID());
									if (!adListVec.CreateAccountableDocumentListRelation(globalVar, ormasDal, errorMessage))
										return false;

								}
								return true;
							}

						}

					}
				}
			}
		}
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}
	bool AccountableUnionDocument::DeleteAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		//ormasDal.StartTransaction(errorMessage);
		if (!errorMessage.empty())
			return false;
		
		std::map<std::string, int> statusMap = Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;

		if (accountableDocument->GetStatusID() == statusMap.find("EXECUTED")->second)
		{
			errorMessage = "Cannot delete document with \"EXECUTED\" status!";
			return false;
		}
		if (accountableDocument->GetStatusID() == statusMap.find("ERROR")->second)
		{
			errorMessage = "Cannot delete document with \"ERROR\" status!";
			return false;
		}

		ExpenseDocument expense;
		AccountableDocumentListRelation adList;
		adList.SetAccountableDocumentID(accountableDocument->GetID());
		std::string filterList = adList.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableDocumentListCollection> accountableListVector = ormasDal.GetAccountableDocumentList(errorMessage, filterList);
		if (accountableListVector.size() > 0)
		{
			for each (auto dlist in accountableListVector)
			{
				expense.Clear();
				expense.SetID(std::get<2>(dlist));
				if (!expense.DeleteExpenseDocument(globalVar, ormasDal, errorMessage))
					return false;
			}
		}
		AccountableTransaction aTransaction;
		aTransaction.SetAccountableDocumentID(accountableDocument->GetID());
		if (!aTransaction.DeleteAccountableTransactionByDocumentID(globalVar, ormasDal, errorMessage))
			return false;
		AccountableApprovement aApprove;
		aApprove.SetAccountableDocumentID(accountableDocument->GetID());
		if (!aApprove.DeleteAccountableApprovementByDocumentID(globalVar, ormasDal, errorMessage))
			return false;
		AccountableDocumentListRelation aList;
		aList.SetAccountableDocumentID(accountableDocument->GetID());
		if (!aList.DeleteAccountableDocumentListRelationByDocumentID(globalVar, ormasDal, errorMessage))
			return false;
		AccountableEntry aEntry;
		aEntry.SetAccountableDocumentID(accountableDocument->GetID());
		if (!aEntry.DeleteAccountableEntryByDocumentID(globalVar, ormasDal, errorMessage))
			return false;
		AccountablePaymentRelation aPay;
		aPay.SetAccountableDocumentID(accountableDocument->GetID());
		if (!aPay.DeleteAccountablePaymentRelationByDocumentID(globalVar, ormasDal, errorMessage))
			return false;
		AccountableWithdrawalRelation aWith;
		aWith.SetAccountableDocumentID(accountableDocument->GetID());
		if (!aWith.DeleteAccountableWithdrawalRelationByDocumentID(globalVar, ormasDal, errorMessage))
			return false;
		if (accountableDocument->DeleteAccountableDocument(globalVar, ormasDal, errorMessage))
		{
			return true;
		}
		
		//ormasDal.CancelTransaction(errorMessage);
		return false;
	}

	bool AccountableUnionDocument::UpdateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, AccountableDocument* aDocument, 
		AccountableTransaction* aTransaction, std::vector<AccountableApprovement>* aApproveVec,
		std::vector<AccountableDocumentListRelation>* aDocListVec, std::vector<AccountableEntry>* aEntryVec,
		std::vector<AccountablePaymentRelation>* aPaymentVec, std::vector<AccountableWithdrawalRelation>* aWithdrawalVec,
		std::vector<ExpenseDocument>* aExpenseVec, std::string& errorMessage)
	{
		accountableDocument = aDocument;
		accountableTransaction = aTransaction;
		approveVec = aApproveVec;
		docListVec = aDocListVec;
		entryVec = aEntryVec;
		paymentVec = aPaymentVec;
		withdrawalVec = aWithdrawalVec;
		expenseVec = aExpenseVec;

		std::map<std::string, int> statusMap = Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;

		AccountablePaymentRelation apRel;
		AccountableWithdrawalRelation awRel;
		AccountableTransaction tran;
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, accountableDocument->GetID(), errorMessage);
		if (accountableDocument->GetStatusID() == statusMap.find("OPEN")->second && previousStatusID == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				if (approveVec->size() > 0)
				{
					for each (auto appr in *approveVec)
					{
						if (!appr.UpdateAccountableApprovement(globalVar, ormasDal, errorMessage))
							return false;
					}
				}
				return true;
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("EXECUTED")->second && previousStatusID == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				if (entryVec->size() > 0)
				{
					for each (auto ent in *entryVec)
					{
						if (!ent.ExecuteEntry(globalVar, ormasDal, errorMessage))
							return false;
					}
					return true;
				}
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("ERROR")->second && previousStatusID == statusMap.find("EXECUTED")->second)
		{
			AccountableDocument aDoc;
			aDoc.SetID(accountableDocument->GetID());
			std::string filter = aDoc.GenerateFilterFieldBiggerThen(ormasDal);
			std::vector<DataLayer::accountableDocumentCollection> aDocVector = ormasDal.GetAccountableDocument(errorMessage, filter);
			if (aDocVector.size() > 0)
				return false;
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				if (entryVec->size() > 0)
				{
					for each (auto ent in *entryVec)
					{
						if (!ent.ExecuteEntryReverse(globalVar, ormasDal, errorMessage))
							return false;
					}
					apRel.Clear();
					apRel.SetAccountableDocumentID(accountableDocument->GetID());
					if (!apRel.DeleteAccountablePaymentRelationByDocumentID(globalVar, ormasDal, errorMessage))
						return false;
					awRel.Clear();
					awRel.SetAccountableDocumentID(accountableDocument->GetID());
					if (!awRel.DeleteAccountableWithdrawalRelationByDocumentID(globalVar, ormasDal, errorMessage))
						return false;
					tran.Clear();
					tran.SetAccountableDocumentID(accountableDocument->GetID());
					if (!tran.DeleteAccountableTransactionByDocumentID(globalVar, ormasDal, errorMessage))
						return false;
					return true;
				}
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("ERROR")->second && previousStatusID == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				return true;
			}
		}
		return false;
	}
	bool AccountableUnionDocument::UpdateAccountableUnionDocument(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{

		std::map<std::string, int> statusMap = Status::GetStatusesAsMap(globalVar, ormasDal, errorMessage);
		if (0 == statusMap.size())
			return false;

		AccountablePaymentRelation apRel;
		AccountableWithdrawalRelation awRel;
		AccountableTransaction tran;
		previousStatusID = GetCurrentStatusID(globalVar, ormasDal, accountableDocument->GetID(), errorMessage);
		if (accountableDocument->GetStatusID() == statusMap.find("OPEN")->second && previousStatusID == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				if (approveVec->size() > 0)
				{
					for each (auto appr in *approveVec)
					{
						if (!appr.UpdateAccountableApprovement(globalVar, ormasDal, errorMessage))
							return false;
					}
				}
				return true;
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("EXECUTED")->second && previousStatusID == statusMap.find("OPEN")->second)
		{
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				if (entryVec->size() > 0)
				{
					for each (auto ent in *entryVec)
					{
						if (!ent.ExecuteEntry(globalVar, ormasDal, errorMessage))
							return false;
					}
					return true;
				}
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("ERROR")->second && previousStatusID == statusMap.find("EXECUTED")->second)
		{
			AccountableDocument aDoc;
			aDoc.SetID(accountableDocument->GetID());
			std::string filter = aDoc.GenerateFilterFieldBiggerThen(ormasDal);
			std::vector<DataLayer::accountableDocumentCollection> aDocVector = ormasDal.GetAccountableDocument(errorMessage, filter);
			if (aDocVector.size() > 0)
				return false;
			if (accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				if (entryVec->size() > 0)
				{
					for each (auto ent in *entryVec)
					{
						if (!ent.ExecuteEntryReverse(globalVar, ormasDal, errorMessage))
							return false;
					}
					apRel.Clear();
					apRel.SetAccountableDocumentID(accountableDocument->GetID());
					if (!apRel.DeleteAccountablePaymentRelationByDocumentID(globalVar, ormasDal, errorMessage))
						return false;
					awRel.Clear();
					awRel.SetAccountableDocumentID(accountableDocument->GetID());
					if (!awRel.DeleteAccountableWithdrawalRelationByDocumentID(globalVar, ormasDal, errorMessage))
						return false;
					tran.Clear();
					tran.SetAccountableDocumentID(accountableDocument->GetID());
					if (!tran.DeleteAccountableTransactionByDocumentID(globalVar, ormasDal, errorMessage))
						return false;
					return true;
				}
			}
		}
		if (accountableDocument->GetStatusID() == statusMap.find("ERROR")->second && previousStatusID == statusMap.find("OPEN")->second)
		{
			if (!accountableDocument->UpdateAccountableDocument(globalVar, ormasDal, errorMessage))
			{
				return true;
			}
		}
		return false;
	}

	std::string AccountableUnionDocument::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		/*if (0 != id || 0 != directorID || 0 != accountantID || 0 != accountableDocumentID || !approveDate.empty())
		{
			return ormasDal.GetFilterForAccountableApprovement(id, approveDate, directorID, accountantID, accountableDocumentID);
		}*/
		return "";
	}

	/*bool AccountableUnionDocument::GetAccountableApprovementByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int aID, std::string& errorMessage)
	{
		if (aID <= 0)
			return false;
		id = aID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (0 != accountableApprovementVector.size())
		{
			id = std::get<0>(accountableApprovementVector.at(0));
			approveDate = std::get<1>(accountableApprovementVector.at(0));
			directorID = std::get<2>(accountableApprovementVector.at(0));
			accountantID = std::get<3>(accountableApprovementVector.at(0));
			accountableDocumentID = std::get<4>(accountableApprovementVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Accountable Approvement with this id";
		}
		return false;
	}*/

	bool AccountableUnionDocument::IsEmpty()
	{
		if (accountableDocument->IsEmpty() && accountableTransaction->IsEmpty() && approveVec->size() == 0 && docListVec->size() == 0 && entryVec->size() == 0
			&& paymentVec->size() == 0 && withdrawalVec->size() == 0 && expenseVec->size() == 0)
			return true;
		return false;
	}

	void AccountableUnionDocument::Clear()
	{
		accountableDocument->Clear();
		accountableTransaction->Clear();
		approveVec->clear();
		docListVec->clear();
		entryVec->clear();
		paymentVec->clear();
		withdrawalVec->clear();
		expenseVec->clear();
	}

	/*bool AccountableUnionDocument::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string aDate, int aDocumentID, std::string& errorMessage)
	{
		AccountableUnionDocument accountableApprovement;
		accountableApprovement.Clear();
		errorMessage.clear();
		accountableApprovement.SetApproveDate(aDate);
		accountableApprovement.SetAccountableDocumentID(aDocumentID);

		std::string filter = accountableApprovement.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableApprovementVector.size())
		{
			return false;
		}
		errorMessage = "Accountable approvement with this parameters are already exist! Please avoid the duplication!";
		return true;
	}*/

	/*bool AccountableUnionDocument::IsDuplicate(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		AccountableUnionDocument accountableApprovement;
		accountableApprovement.Clear();
		errorMessage.clear();
		accountableApprovement.SetApproveDate(approveDate);
		accountableApprovement.SetAccountableDocumentID(accountableDocumentID);

		std::string filter = accountableApprovement.GenerateFilter(ormasDal);
		std::vector<DataLayer::accountableApprovementCollection> accountableApprovementVector = ormasDal.GetAccountableApprovement(errorMessage, filter);
		if (!errorMessage.empty())
			return true;
		if (0 == accountableApprovementVector.size())
		{
			return false;
		}
		errorMessage = "Accountable approvement with this parameters are already exist! Please avoid the duplication!";
		return true;
	}*/

	int AccountableUnionDocument::GetCurrentStatusID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int oID, std::string& errorMessage)
	{
		AccountableDocument accDoc;
		if (accDoc.GetAccountableDocumentByID(globalVar, ormasDal, oID, errorMessage))
			return accDoc.GetStatusID();
		return 0;
	}
}