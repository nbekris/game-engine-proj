//------------------------------------------------------------------------------
//
// File Name:	Physics.cpp
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
#include "Physics.h"
#include "Transform.h"
#include "Entity.h"
#include "Stream.h"

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

	Physics::Physics(void)
	{
	}

	Physics::Physics(const Physics* other)
	{
		velocity = other->velocity;
		oldTranslation = other->oldTranslation;
		acceleration = other->acceleration;
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
	
	bool Physics::Initialize()
	{
		Transform* transform = Parent()->Get<Transform>();
		if (transform)
		{
			oldTranslation = transform->Translation();
			return true;
		}
		return false;
	}

	void Physics::Update(float dt)
	{
		Transform* transform = Parent()->Get<Transform>();
		if (transform)
		{
			Vector2D translation = transform->Translation();
			float rotation = transform->Rotation();
			oldTranslation = translation;

			velocity.ScaleAdd(dt, acceleration);

			velocity.Scale(drag);

			translation.ScaleAdd(dt, velocity);

			rotation += rotationalVelocity * dt;



			transform->Rotation(rotation);
			transform->Translation(translation);
		}
	}

	void Physics::Read(Stream& stream)
	{
		DRAGON_ASSERT(stream.Contains("Physics"), "Physics::Read: Failed to find required key: Physics");

		stream.PushNode("Physics");
		stream.ReadVector2D("Velocity", velocity);
		stream.ReadVector2D("Acceleration", acceleration);
		stream.PopNode();
	}

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace