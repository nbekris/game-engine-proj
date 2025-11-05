//------------------------------------------------------------------------------
//
// File Name:	ObjectFactory.cpp
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
#include "ObjectFactory.h"
#include "LoggingSystem.h"

#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Animation.h"
#include "Behavior.h"
#include "BehaviorSpaceship.h"
#include "BehaviorBullet.h"
#include "BehaviorTeleporter.h"
#include "BehaviorAsteroid.h"

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

	ObjectFactory::ObjectFactory(void)
	{
		Register("Transform", []() -> Object* { return new Transform(); });
		Register("Sprite", []() -> Object* { return new Sprite(); });
		Register("Physics", []() -> Object* { return new Physics(); });
		Register("Animation", []() -> Object* { return new Animation(); });
		Register("BehaviorSpaceship", []() -> Object* { return new BehaviorSpaceship(); });
		Register("BehaviorBullet", []() -> Object* { return new BehaviorBullet(); });
		Register("BehaviorTeleporter", []() -> Object* { return new BehaviorTeleporter(); });
		Register("BehaviorAsteroid", []() -> Object* { return new BehaviorAsteroid(); });
	}

	//--------------------------------------------------------------------------

	ObjectFactory::~ObjectFactory(void)
	{
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

#pragma region Public Functions

	bool ObjectFactory::Register(const std::string& objectName, objectConstructor constructor)
	{
		if (registry.contains(objectName))
		{
			LoggingSystem::Verbose("ObjectFactory::Register: Attempted to register duplicate object name: {}", objectName);
			return false;
		}

		registry.insert({ objectName, constructor });
		return true;
	}

	Object* ObjectFactory::Create(const std::string& objectName) const
	{
		if (auto search = registry.find(objectName); search != registry.end())
		{
			return search->second();
		}
		return nullptr;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace