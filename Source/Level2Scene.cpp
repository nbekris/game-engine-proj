//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.cpp
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <Windows.h>

#include "Level2Scene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Stream.h"
#include "SandboxScene.h"
#include "Level1Scene.h"
#include "DemoScene.h"

#include "Sprite.h"
#include "Mesh.h"
#include "Transform.h"
#include "Physics.h"

#include "Entity.h"
#include "EntityFactory.h"
#include <iostream>

#include "MeshLibrary.h"

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
	static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
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

	Level2Scene::Level2Scene()
		: Scene("Level2Scene")
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

	void Level2Scene::Load()
	{
		meshSpaceship = new Mesh();
		meshSpaceship->BuildSpaceship();
	}

	bool Level2Scene::Initialize()
	{
		entitySpaceship = EntityFactory::Build("SpaceshipHoming");
		Vector2D startPos(0.0f, 0.0f);

		if (entitySpaceship)
		{
			Sprite* sprite = entitySpaceship->Get<Sprite>();
			Physics* physics = entitySpaceship->Get<Physics>();
			if (sprite)
			{
				sprite->SetMesh(meshSpaceship);
			}

			DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
			DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
			entitySpaceship->Get<Transform>()->Translation(startPos);
		}
		return true;
	}

	void Level2Scene::Update(float dt)
	{
		if (entitySpaceship)
		{
			MovementController(entitySpaceship);
			entitySpaceship->Update(dt);

			Sprite* sprite = entitySpaceship->Get<Sprite>();
			if (DGL_Input_KeyTriggered('Z'))
			{
				sprite->Alpha(0.5f);
			}
			else if (DGL_Input_KeyTriggered('X'))
			{
				sprite->Alpha(1.0f);
			}

		}
		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		//SceneSystem::EndScene();
	}

	void Level2Scene::Render() const
	{
		if (entitySpaceship)
		{
			entitySpaceship->Render();
		}
	}

	void Level2Scene::Shutdown()
	{
		if (entitySpaceship)
		{
			delete entitySpaceship;
			entitySpaceship = nullptr;
		}
	}

	void Level2Scene::Unload()
	{
		if (meshSpaceship)
		{
			delete meshSpaceship;
			meshSpaceship = nullptr;
		}
	}

	void Level2Scene::MovementController(Entity* entity)
	{
		Transform* transform = entity->Get<Transform>();
		Physics* physics = entity->Get<Physics>();
		if (transform && physics)
		{
			DGL_Vec2 mousePos = DGL_Input_GetMousePosition();
			DGL_Vec2 mouseCords = DGL_Camera_ScreenCoordToWorld(&mousePos);

			Vector2D mouseCordsV2D(mouseCords.x, mouseCords.y);

			// calculate direction vector to mouse position
			Vector2D direction = mouseCordsV2D;
			direction.Sub(transform->Translation());
			direction.Normalize();

			transform->Rotation(direction.ToAngleRad());

			Vector2D scaledDirection = direction;
			scaledDirection.Scale(spaceshipSpeed);
			physics->Velocity(scaledDirection);
		}
	}

#pragma endregion Private Functions

}	// namespace