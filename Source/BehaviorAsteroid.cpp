//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.cpp
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "template" entity.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"

#include "Entity.h"
#include "Behavior.h"
#include "BehaviorAsteroid.h"
#include "Stream.h"
#include "Random.h"

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

	BehaviorAsteroid::BehaviorAsteroid(void)
		: Behavior()
	{
	}

	BehaviorAsteroid::BehaviorAsteroid(const BehaviorAsteroid* other)
		: Behavior(other)
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

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	void BehaviorAsteroid::Read(Stream& stream)
	{
		stream.PushNode("BehaviorAsteroid");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorAsteroid::SetPosition()
	{
	}

	void BehaviorAsteroid::SetVelocity()
	{
	}

	void BehaviorAsteroid::onInit()
	{
		origin = static_cast<AsteroidOrigin>(Random::Range(0, 3));
		SetPosition();
		SetVelocity();
		//switch (stateCurr)
		//{
		//case cIdle:
		//	break;

		//default:
		//	break;
		//}
	}

	void BehaviorAsteroid::onUpdate(float dt)
	{
		//switch (stateCurr)
		//{
		//case cIdle:
		//	break;

		//default:
		//	break;
		//}
	}

	void BehaviorAsteroid::onExit()
	{
		//switch (stateCurr)
		//{
		//case cIdle:
		//	break;

		//default:
		//	break;
		//}
	}

#pragma endregion Private Functions

}	// namespace