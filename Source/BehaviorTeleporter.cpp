//------------------------------------------------------------------------------
//
// File Name:	BehaviorTeleporter.cpp
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
#include "BehaviorTeleporter.h"
#include "Stream.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Physics.h"
#include <iostream>

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

	BehaviorTeleporter::BehaviorTeleporter(void)
		: Behavior()
	{
	}

	BehaviorTeleporter::BehaviorTeleporter(const BehaviorTeleporter* other)
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

	void BehaviorTeleporter::Read(Stream& stream)
	{
		stream.PushNode("BehaviorTeleporter");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorTeleporter::onInit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorTeleporter::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}

		CheckPosition();
	}

	void BehaviorTeleporter::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorTeleporter::CheckPosition()
	{
		// Get dimensions of window, then scale to get window half size to test against
		DGL_Vec2 windowSize = DGL_Window_GetSize();
		Vector2D wHalfSize(windowSize.x, windowSize.y);
		wHalfSize.Scale(0.5f);

		Transform* transform = Parent()->Get<Transform>();
		Physics* physics = Parent()->Get<Physics>();

		Vector2D velocity(physics->Velocity());
		Vector2D pos(transform->Translation());

		// Check if entity has reached screen boundaries, top, left, bottom, right
		if (pos.x < -wHalfSize.x)
		{
			Teleport(pos, transform);
		}
		else if (pos.x > wHalfSize.x)
		{
			Teleport(pos, transform);
		}
		else if (pos.y < -wHalfSize.y) 
		{
			Teleport(pos, transform);
		}
		else if (pos.y > wHalfSize.y)
		{
			Teleport(pos, transform);
		}
	}

	void BehaviorTeleporter::Teleport(Vector2D pos, Transform* transform)
	{
		pos.Scale(-1);
		transform->Translation(pos);
	}

#pragma endregion Private Functions

}	// namespace