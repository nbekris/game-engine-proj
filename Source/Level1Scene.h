//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.h
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Scene.h"
#include "Entity.h"
#include "Mesh.h"
#include "SpriteSource.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	class Level1Scene : public Scene
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Level1Scene(void);

		// All objects need a virtual destructor to have their destructor called 
		~Level1Scene(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Enums and Constants:
	private:
		enum MonkeyStates
		{
			Invalid = -1,
			Idle,
			Walk,
			Jump
		};

		const float wallDistance = 462.0f;
		const float CheckSquareDistance = (75.0f * 75.0f);
	private:
		// Private Variables:
		int numLives = 0;
		Entity* entityPlanet{ nullptr };
		Mesh* mesh1x1{ nullptr };
		SpriteSource* spriteSourcePlanet{ nullptr };

		MonkeyStates monkeyState = Invalid;

		Entity* entityMonkey{ nullptr };
		Entity* entityLives{ nullptr };

		Mesh* mesh3x3{ nullptr };
		Mesh* mesh16x8{ nullptr };

		SpriteSource* spriteSourceMonkeyIdle{ nullptr };
		SpriteSource* spriteSourceMonkeyWalk{ nullptr };
		SpriteSource* spriteSourceMonkeyJump{ nullptr };
		SpriteSource* spriteSourceFontSheet{ nullptr };

		// Private Functions:
	private:
		// @brief Load any large assets required by the scene.
		void Load();

		// @brief Initialize the scene, including constructing the entities.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the scene each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// @brief Render the scene each frame.
		void Render() const override;

		// @brief Shutdown the scene, destroying any remaining entities.
		void Shutdown() override;

		// @brief Unload any large assets loaded for the scene.
		void Unload() override;

		void MovementController(Entity* entity);

		void BounceController(Entity* entity) const;

		void SetMonkeyState(Entity* entity, MonkeyStates state);

		bool isColliding(const Entity* entityA, const Entity* entityB) const;

		// Private Constants:
	private:
		// Private Static Variables:
	private:
	};

}	// namespace