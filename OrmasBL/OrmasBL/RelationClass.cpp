#include "stdafx.h"
#include "RelationClass.h"

namespace BusinessLayer{
	Relation::Relation(DataLayer::relationsCollection rCollection)
	{
		id = std::get<0>(rCollection);
		user1ID = std::get<1>(rCollection);
		user2ID = std::get<2>(rCollection);
		relationTypeID = std::get<3>(rCollection);
	}
	Relation::Relation()
	{
		user1ID = 0;
		user2ID = 0;
		relationTypeID = 0;
	}
	int Relation::GetID()
	{
		return id;
	}

	int Relation::GetUser1ID()
	{
		return user1ID;
	}

	int Relation::GetUser2ID()
	{
		return user2ID;
	}

	int Relation::GetRelationTypeID()
	{
		return relationTypeID;
	}

	void Relation::SetID(int rID)
	{
		id = rID;
	}
	void Relation::SetUser1ID(int u1ID)
	{
		user1ID = u1ID;
	}
	void Relation::SetUser2ID(int u2ID)
	{
		user2ID = u2ID;
	}
	void Relation::SetRelationTypeID(int rtID)
	{
		relationTypeID = rtID;
	}

	bool Relation::CreateRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int u1ID, int u2ID, int rtID, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		user1ID = u1ID;
		user2ID = u2ID;
		relationTypeID = rtID;

		if (0 != id && ormasDal.CreateRelation(id, user1ID, user2ID, relationTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Relation::CreateRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		id = ormasDal.GenerateID();
		if (0 != id && ormasDal.CreateRelation(id, user1ID, user2ID, relationTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Relation::DeleteRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (ormasDal.DeleteRelation(id, errorMessage))
		{
			Clear();
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Unexpected error. Please contact with application provider.";
		}
		return false;
	}

	bool Relation::UpdateRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int u1ID, int u2ID, int rtID, std::string& errorMessage)
	{
		user1ID = u1ID;
		user2ID = u2ID;
		relationTypeID = rtID;
		if (0 != id && ormasDal.UpdateRelation(id, user1ID, user2ID, relationTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}
	bool Relation::UpdateRelation(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, std::string& errorMessage)
	{
		if (0 != id && ormasDal.UpdateRelation(id, user1ID, user2ID, relationTypeID, errorMessage))
		{
			return true;
		}
		if (errorMessage.empty())
		{
			errorMessage = "Warning! ID is 0, or some unexpected error. Please contact with provider.";
		}
		return false;
	}

	std::string Relation::GenerateFilter(DataLayer::OrmasDal& ormasDal)
	{
		if (0 != id || 0 != user1ID || 0 != user2ID || 0 != relationTypeID)
		{
			return ormasDal.GetFilterForRelation(id, user1ID, user2ID, relationTypeID);
		}
		return "";
	}

	bool Relation::GetRelationByID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int bID, std::string& errorMessage)
	{
		if (bID <= 0)
			return false;
		id = bID;
		std::string filter = GenerateFilter(ormasDal);
		std::vector<DataLayer::relationsViewCollection> relationVector = ormasDal.GetRelations(errorMessage, filter);
		if (0 != relationVector.size())
		{
			id = std::get<0>(relationVector.at(0));
			user1ID = std::get<8>(relationVector.at(0));
			user2ID = std::get<9>(relationVector.at(0));
			relationTypeID = std::get<10>(relationVector.at(0));
			return true;
		}
		else
		{
			errorMessage = "Cannot find Relation with this id";
		}
		return false;
	}

	std::vector<int> Relation::GetUser2IDByUser1ID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int u1ID, std::string& errorMessage)
	{
		std::vector<int> user2IDVector;
		Relation relation;
		relation.SetUser1ID(u1ID);
		relation.SetUser2ID(0);
		std::string filter = relation.GenerateFilter(ormasDal);
		std::vector<DataLayer::relationsViewCollection> relVector = ormasDal.GetRelations(errorMessage, filter);
		if (0 != relVector.size())
		{
			for each (auto item in relVector)
			{
				user2IDVector.push_back(std::get<9>(item));
			}
		}
		return user2IDVector;
	}

	std::vector<int> Relation::GetUser1IDByUser2ID(GlobalVariable* globalVar, DataLayer::OrmasDal &ormasDal, int u2ID, std::string& errorMessage)
	{
		std::vector<int> user1IDVector;
		Relation relation;
		relation.SetUser1ID(0);
		relation.SetUser2ID(u2ID);
		std::string filter = relation.GenerateFilter(ormasDal);
		std::vector<DataLayer::relationsViewCollection> relVector = ormasDal.GetRelations(errorMessage, filter);
		if (0 != relVector.size())
		{
			for each (auto item in relVector)
			{
				user1IDVector.push_back(std::get<8>(item));
			}
		}
		return user1IDVector;
	}

	bool Relation::IsEmpty()
	{
		if (0 == id && 0 == user1ID && 0 == user2ID && 0 == relationTypeID)
			return true;
		return false;
	}

	void Relation::Clear()
	{
		id = 0;
		user1ID = 0;
		user2ID = 0;
		relationTypeID = 0;
	}
}