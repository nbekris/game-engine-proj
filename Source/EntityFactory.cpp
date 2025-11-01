//------------------------------------------------------------------------------
//
// File Name:	EntityFactorye.cpp
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
#include "EntityFactory.h"
#include "Stream.h"
#include "Entity.h"
#include "EntityContainer.h"

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
	EntityContainer EntityFactory::archetypes;
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	EntityFactory::EntityFactory(void)
	{
	}

	//--------------------------------------------------------------------------

	EntityFactory::~EntityFactory(void)
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

	Entity* EntityFactory::Build(std::string_view entityName)
	{
		Entity* entity = archetypes.FindByName(entityName);
		std::string filePath;

		if (!entity)
		{
			filePath.append("./Data/Archetypes/");
			filePath.append(entityName);
			filePath.append(".json");

			Stream stream(filePath);
			if (stream.IsValid() && stream.Contains("Entity"))
			{
				entity = new Entity();
				entity->Read(stream);
				archetypes.Add(entity);
			}
		}

		if (entity) 
		{
			return new Entity(entity);
		}

		return nullptr;
	}

	void EntityFactory::DeleteAll()
	{
		archetypes.DeleteAll();
	}

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace