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
#include "Transform.h"
#include "Physics.h"
#include "ColliderCircle.h"
#include "ScoreSystem.h"

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
		origin = cAsteroidOriginTlc;
	}

	BehaviorAsteroid::BehaviorAsteroid(const BehaviorAsteroid* other)
		: Behavior(other),
		  origin(other ? other->origin : cAsteroidOriginTlc),
		  asteroidSpeedMin(other ? other->asteroidSpeedMin : 50.0f),
		  asteroidSpeedMax(other ? other->asteroidSpeedMax : 100.0f)
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
		Vector2D wSize(DGL_Window_GetSize());
		wSize.Scale(0.5f);

		Transform* transform = Parent()->Get<Transform>();
		switch (origin)
		{
		case cAsteroidOriginTrc:
			transform->Translation(wSize);
			break;
		case cAsteroidOriginBlc:
			transform->Translation({ -wSize.x, -wSize.y });
			break;
		case cAsteroidOriginBrc:
			transform->Translation({ wSize.x, -wSize.y });
			break;
		case cAsteroidOriginTlc:
			transform->Translation({ -wSize.x, wSize.y });
			break;
		}
	}

	void BehaviorAsteroid::SetVelocity()
	{
		Physics* physics = Parent()->Get<Physics>();
		float angle = 0;
		switch (origin)
		{
		case cAsteroidOriginTrc:
			angle = Random::Range(-80.0f, -10.0f);
			break;
		case cAsteroidOriginBlc:
			angle = Random::Range(-170.0f, -100.0f);
			break;
		case cAsteroidOriginBrc:
			angle = Random::Range(10.0f, 80.0f);
			break;
		case cAsteroidOriginTlc:
			angle = Random::Range(100.0f, 170.0f);
			break;
		}
		Vector2D dirVec;
		float speed = Random::Range(asteroidSpeedMin, asteroidSpeedMax);

		dirVec.FromAngleDeg(angle);
		dirVec.Scale(speed);

		physics->Velocity(dirVec);
	}

	void BehaviorAsteroid::onInit()
	{
		origin = static_cast<AsteroidOrigin>(Random::Range(0, 3));
		SetPosition();
		SetVelocity();

		ColliderCircle* colliderCircle = Parent()->Get<ColliderCircle>();
		if (colliderCircle)
		{
			colliderCircle->RegisterHandler(CollisionHandler);
		}
	}

	void BehaviorAsteroid::onUpdate(float dt)
	{
	}

	void BehaviorAsteroid::onExit()
	{
	}

	void BehaviorAsteroid::CollisionHandler(Entity* entityA, const Entity* entityB)
	{
		if (entityA && entityB)
		{
			if (entityB->IsNamed("Bullet") || entityB->IsNamed("Spaceship"))
			{
				ScoreSystem::Instance().IncreaseScore(asteroidScore);
				entityA->Destroy();
			}
		}
	}

#pragma endregion Private Functions

}	// namespace