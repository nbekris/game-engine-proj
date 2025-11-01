//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.cpp
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
#include "BehaviorSpaceship.h"
#include "Stream.h"
#include "SceneSystem.h"
#include "Physics.h"
#include "Transform.h"
#include "EntityFactory.h"

#include <numbers>

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
	static const float spaceshipAcceleration = 150.0f;
	static const float spaceshipSpeedMax = 500.0f;
	static const float spaceshipTurnRateMax = (float)std::numbers::pi / 1.5f;
	static const float spaceshipWeaponCooldownTime = 0.034f;
	static const float spaceshipWeaponBulletSpeed = 750.0f;
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

	BehaviorSpaceship::BehaviorSpaceship(void)
		: Behavior()
	{
	}

	BehaviorSpaceship::BehaviorSpaceship(const BehaviorSpaceship* other)
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

	void BehaviorSpaceship::Read(Stream& stream)
	{
		if (stream.IsValid())
		{
			stream.PushNode("BehaviorSpaceship");

			// Read the base Behavior variables.
			// [HINT: Behavior::Read().]
			Behavior::Read(stream);
			// Read the derived class Behavior variables, if any.

			stream.PopNode();
		}
	}

	void BehaviorSpaceship::onInit()
	{
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorSpaceship::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			UpdateRotation();
			UpdateWeapon(dt);
			if (DGL_Input_KeyDown(VK_UP))
			{
				stateNext = cSpaceshipThrust;
			}
			break;
		case cSpaceshipThrust:
			UpdateRotation();
			UpdateVelocity(dt);
			UpdateWeapon(dt);
			if (!DGL_Input_KeyDown(VK_UP))
			{
				stateNext = cSpaceshipIdle;
			}
			break;
		default:
			break;
		}
	}

	void BehaviorSpaceship::onExit()
	{
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorSpaceship::UpdateRotation() const
	{
		Physics* physics = Parent()->Get<Physics>();
		if (physics)
		{
			if (DGL_Input_KeyDown(VK_LEFT))
			{
				physics->RotationalVelocity(spaceshipTurnRateMax);
			}
			else if (DGL_Input_KeyDown(VK_RIGHT))
			{
				physics->RotationalVelocity(-spaceshipTurnRateMax);
			}
			else
			{
				physics->RotationalVelocity(0.0f);
			}
		}
	}

	void BehaviorSpaceship::UpdateVelocity(float dt) const
	{
		Physics* physics = Parent()->Get<Physics>();
		Transform* transform = Parent()->Get<Transform>();
		if (physics && transform)
		{
			float rotation = transform->Rotation();
			Vector2D rotationDirectionVector;
			rotationDirectionVector.FromAngleRad(rotation);

			Vector2D velocity = physics->Velocity();
			velocity.ScaleAdd(spaceshipAcceleration * dt, rotationDirectionVector);
			float speed = velocity.Length();
			if (speed > spaceshipSpeedMax)
			{
				velocity.ScaleAdd(spaceshipSpeedMax / speed, velocity);
			}

			physics->Velocity(velocity);
		}
	}

	void BehaviorSpaceship::UpdateWeapon(float dt)
	{
		if (timer > 0)
		{
			timer -= dt;
			if (timer < 0)
			{
				timer = 0;
			}
		}
		if (timer <= 0)
		{
			if (DGL_Input_KeyDown(VK_SPACE))
			{
				SpawnBullet();
				timer = spaceshipWeaponCooldownTime;
			}
		}
	}

	void BehaviorSpaceship::SpawnBullet() const
	{
		Entity* bullet = EntityFactory::Build("Bullet");
		if (bullet)
		{
			Transform* shipTransform = Parent()->Get<Transform>();
			Transform* bulletTransform = bullet->Get<Transform>();

			Vector2D shipPosition = shipTransform->Translation();
			float shipRotation = shipTransform->Rotation();
			bulletTransform->Translation(shipPosition);
			bulletTransform->Rotation(shipRotation);

			Vector2D shipDirectionVector;
			shipDirectionVector.FromAngleRad(shipRotation);
			Physics* bulletPhysics = bullet->Get<Physics>();
			if (bulletPhysics)
			{
				Vector2D bulletVelocity = bulletPhysics->Velocity();
				bulletVelocity.ScaleAdd(spaceshipWeaponBulletSpeed, shipDirectionVector);
				bulletPhysics->Velocity(bulletVelocity);
			}
			SceneSystem::AddEntity(bullet);
		}
	}

#pragma endregion Private Functions

}	// namespace