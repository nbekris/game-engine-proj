//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.cpp
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"

#include "LoggingSystem.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Public Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	EntityContainer::EntityContainer()
	{
		entities.reserve(100);
	}

	//--------------------------------------------------------------------------

	EntityContainer::~EntityContainer()
	{
		DeleteAll();
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

	void EntityContainer::Update(float dt) 
	{
		for (Entity* entity : entities)
		{
			entity->Update(dt);
		}

		for (int i = 0; i < entities.size(); ++i)
		{
			Entity* entity = entities[i];
			if (entity->IsDestroyed())
			{
				delete entity;
				entity = nullptr;

				entities.erase(entities.begin() + i);
			}
		}
	}

	void EntityContainer::Render() const
	{
		for (Entity* entity : entities)
		{
			entity->Render();
		}
	}

	void EntityContainer::Add(Entity* entity)
	{
		if (entity && entity->Initialize())
		{
			entities.push_back(entity);
		}
		else if (entity)
		{
			LoggingSystem::Verbose("Add Entity failed initialization : {}", entity->Name());
		}
		else
		{
			LoggingSystem::Verbose("Add Entity failed: Entity is NULL");
		}

	}

	Entity* EntityContainer::FindByName(std::string_view findName) const
	{
		for (Entity* entity : entities)
		{
			std::string_view name = findName;
			if (entity->IsNamed(findName))
			{
				return entity;
			}
		}
		return nullptr;
	}

	void EntityContainer::CheckCollisions() const
	{
		Collider* colliderA;
		Collider* colliderB;
		for (int i = 0; i < entities.size(); ++i)
		{
			if (entities[i]->Name() == "Arena")
			{
				colliderA = entities[i]->Get<ColliderLine>();
			}
			else 
			{
				colliderA = entities[i]->Get<ColliderCircle>();
			}

			if (colliderA)
			{
				for (int j = i + 1; j < entities.size(); ++j)
				{
					if (entities[i]->Name() == "Arena")
					{
						colliderB = entities[j]->Get<ColliderCircle>();
					}
					else
					{
						colliderB = entities[j]->Get<ColliderCircle>();
					}

					if (colliderB)
					{
						colliderA->CheckCollision(colliderB);
					}
				}
			}
		}
	}

	void EntityContainer::DeleteAll()
	{
		for (Entity* entity : entities)
		{
			delete entity;
			entity = nullptr;
		}
		entities.clear();
	}
#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace