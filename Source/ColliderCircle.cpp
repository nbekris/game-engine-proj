//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
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
#include "ColliderCircle.h"
#include "Transform.h"
#include "Entity.h"
#include "Physics.h"
#include "Stream.h"

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

	ColliderCircle::ColliderCircle(void)
	{
	}

	ColliderCircle::ColliderCircle(const ColliderCircle* other)
	{
		radius = other->radius;
	}

	//--------------------------------------------------------------------------

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------
	
	void ColliderCircle::Read(Stream& stream)
	{
		if (&stream)
		{
			stream.PushNode("ColliderCircle");
			stream.Read("Radius", radius);
			stream.PopNode();
		}
	}

	bool ColliderCircle::IsColliding(const Collider* other) const
	{
		// maybe use static cast here instead, its more efficient but not safe?
		// reason: dynamic cast will actually set variable to null pointer if cast fails
		// trade off: greater memory overhead since we are storing type info pointers,
		// also performing a runtime type check which can slow things down in loops that 
		// run many times.
		const ColliderCircle* colliderCircle = dynamic_cast<const ColliderCircle*>(other);
		if (colliderCircle)
		{
			Vector2D translation = this->Parent()->Get<Transform>()->Translation();
			Vector2D otherTranslation = other->Parent()->Get<Transform>()->Translation();

			float distance = translation.SquareDistance(otherTranslation);
			float sqCheck = std::powf(this->Radius() + colliderCircle->Radius(), 2.0f);
			if (distance <= sqCheck)
			{
				return true;
			}
		}
		return false;
	}

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace