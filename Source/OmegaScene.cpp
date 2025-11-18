//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.cpp
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

#include "OmegaScene.h"
#include "Scene.h"
#include "SceneSystem.h"

#include "EntityFactory.h"
#include "MeshLibrary.h"
#include "Mesh.h"
#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"
#include "ScoreSystem.h"
#include "SpriteSourceLibrary.h"

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

	OmegaScene::OmegaScene()
		: Scene("OmegaScene")
	{
		OmegaSpawnCount = OmegaSpawnInitial;
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

	void OmegaScene::Load()
	{
		ScoreSystem::Instance().NewGame();
	}

	bool OmegaScene::Initialize()
	{
		Entity* arenaEntity = EntityFactory::Build("Arena");
		if (arenaEntity)
		{
			this->AddEntity(arenaEntity);
		}
		Entity* spaceshipEntity = EntityFactory::Build("SpaceshipOmega");

		if (spaceshipEntity)
		{
			this->AddEntity(spaceshipEntity);
		}

		DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		Entity* scoreEntity = EntityFactory::Build("OmegaScore");
		Entity* highScoreEntity = EntityFactory::Build("OmegaHighScore");
		Entity* OmegaWaveEntity = EntityFactory::Build("OmegaWaveCount");

		this->AddEntity(scoreEntity);
		this->AddEntity(highScoreEntity);
		this->AddEntity(OmegaWaveEntity);

		ScoreSystem::Instance().Reset();
		OmegaSpawnCount = OmegaSpawnInitial;

		return true;
	}

	void OmegaScene::Update(float dt)
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

	void OmegaScene::Render() const
	{
		RenderEntities();
	}

	void OmegaScene::Shutdown()
	{
		DeleteEntities();
		EntityFactory::DeleteAll();
	}

	void OmegaScene::Unload()
	{
		MeshLibrary::DeleteAll();
		SpriteSourceLibrary::DeleteAll();
	}

	void OmegaScene::SpawnWave()
	{
		ScoreSystem::Instance().IncreaseWave();
		for (unsigned int i = 0; i < OmegaSpawnCount; ++i)
		{
			SpawnAsteroid();
		}

		OmegaSpawnCount = OmegaSpawnCount != OmegaSpawnMaximum ? ++OmegaSpawnCount : OmegaSpawnMaximum;
	}

	void OmegaScene::SpawnAsteroid()
	{
		Entity* entity = EntityFactory::Build("Asteroid");
		if (entity)
		{
			AddEntity(entity);
			entity->Get<Transform>()->Translation({ 0.0f, 0.0f });
		}
	}

#pragma endregion Private Functions

}	// namespace