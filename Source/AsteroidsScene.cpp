//------------------------------------------------------------------------------
//
// File Name:	AsteroidsScene.cpp
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

#include "AsteroidsScene.h"
#include "Scene.h"
#include "SceneSystem.h"

#include "EntityFactory.h"
#include "MeshLibrary.h"
#include "Mesh.h"
#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"

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

	AsteroidsScene::AsteroidsScene()
		: Scene("AsteroidsScene")
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

	void AsteroidsScene::Load()
	{
		asteroidSpawnCount = asteroidSpawnInitial;
	}

	bool AsteroidsScene::Initialize()
	{
		Entity* entity = EntityFactory::Build("Spaceship");
		if (entity)
		{
			AddEntity(entity);
			entity->Get<Transform>()->Translation({ 0.0f, 0.0f }); // set spaceship to start position
		}

		DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		return true;
	}

	void AsteroidsScene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);

		if (!FindEntity("Asteroid"))
		{
			SpawnWave();
		}

		UpdateEntities(dt);

		CheckCollisions();
		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
	}

	void AsteroidsScene::Render() const
	{
		RenderEntities();
	}

	void AsteroidsScene::Shutdown()
	{
		DeleteEntities();
		EntityFactory::DeleteAll();
	}

	void AsteroidsScene::Unload()
	{
		MeshLibrary::DeleteAll();
	}

	void AsteroidsScene::SpawnWave()
	{
		while (asteroidSpawnCount < asteroidSpawnMaximum) // this probably needs to be changed
		{
			SpawnAsteroid();
			++asteroidSpawnCount;
		}
	}

	void AsteroidsScene::SpawnAsteroid()
	{
		Entity* entity = EntityFactory::Build("Asteroid");
		if (entity) //should add spawn entity function
		{
			AddEntity(entity);
			entity->Get<Transform>()->Translation({ 0.0f, 0.0f });
		}
	}

#pragma endregion Private Functions

}	// namespace