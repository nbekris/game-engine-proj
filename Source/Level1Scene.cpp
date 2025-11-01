//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.cpp
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

#include "Level1Scene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Stream.h"
#include "Level2Scene.h"
#include "DemoScene.h"
#include "SandboxScene.h"

#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"
#include "Entity.h"
#include "EntityFactory.h"

#include "Animation.h"

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
	static const float groundHeight = -150.0f;
	static const float moveVelocity = 500.0f;
	static const float jumpVelocity = 1000.0f;
	static const Vector2D gravityNormal = { 0.0f, -1500.0f };
	static const Vector2D gravityNone = { 0.0f, 0.0f };

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------
	static const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
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

	Level1Scene::Level1Scene()
		: Scene("Level1Scene")
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

	void Level1Scene::Load()
	{
		int num;
		numLives = 0;

		mesh1x1 = new Mesh();
		mesh3x3 = new Mesh();
		mesh16x8 = new Mesh();

		spriteSourceMonkeyIdle = new SpriteSource();
		spriteSourceMonkeyJump = new SpriteSource();
		spriteSourceMonkeyWalk = new SpriteSource();
		spriteSourceFontSheet = new SpriteSource();
		spriteSourcePlanet = new SpriteSource();

		Stream stream("Data/Level1.json");

		if (stream.IsValid())
		{
			stream.Read("NumLives", num);
			numLives = num;
			LoggingSystem::Verbose("{}: Lives: {}", Scene::Name(), numLives);
		}

		mesh1x1->BuildQuad(1.0f, 1.0f, "Mesh1x1");
		mesh3x3->BuildQuad(1.0f / 3, 1.0f / 3, "Mesh3x3");
		mesh16x8->BuildQuad(1.0f / 16, 1.0f / 8, "Mesh16x8");

		spriteSourceMonkeyIdle->LoadTexture(1, 1, "Assets/MonkeyIdle.png");
		spriteSourceMonkeyJump->LoadTexture(1, 1, "Assets/MonkeyJump.png");
		spriteSourceMonkeyWalk->LoadTexture(3, 3, "Assets/MonkeyWalk.png");

		// instructions say create sprite source with a 16x8 sprite sheet, could be incorrect
		spriteSourceFontSheet->LoadTexture(16, 8, "Assets/Roboto_Mono_black.png");

		spriteSourcePlanet->LoadTexture(1, 1, "Assets/PlanetTexture.png");
	}

	bool Level1Scene::Initialize()
	{
		entityPlanet = EntityFactory::Build("PlanetBounce"); // was planetJump
		entityMonkey = EntityFactory::Build("Monkey");
		entityLives = EntityFactory::Build("MonkeyLivesText");

		if (entityPlanet)
		{
			Sprite* spritePlanetBounce = entityPlanet->Get<Sprite>();
			if (spritePlanetBounce)
			{
				spritePlanetBounce->SetMesh(mesh1x1);
				spritePlanetBounce->SetSpriteSource(spriteSourcePlanet);
			}
		}

		if (entityMonkey)
		{
			monkeyState = Invalid;
			SetMonkeyState(entityMonkey, Idle);
		}

		if (entityLives)
		{
			Sprite* spriteLives = entityLives->Get<Sprite>();
			if (spriteLives)
			{
				spriteLives->SetMesh(mesh16x8);
				spriteLives->SetSpriteSource(spriteSourceFontSheet);
				spriteLives->SetText(std::format("Lives: {}", numLives));
			}
		}

		DGL_Graphics_SetBackgroundColor(&DGL_Color_White);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		return true;
	}

	void Level1Scene::Update(float dt)
	{
		if (entityMonkey)
		{
			entityMonkey->Update(dt);
			MovementController(entityMonkey);
		}

		if (entityPlanet)
		{
			entityPlanet->Update(dt);
			BounceController(entityPlanet);
		}

		if (entityLives)
		{
			entityLives->Update(dt);
		}

		if (isColliding(entityMonkey, entityPlanet))
		{
			if (entityLives)
			{
				Sprite* spriteLives = entityLives->Get<Sprite>();
				if (spriteLives)
				{
					spriteLives->SetText(std::format("Lives: {}", numLives));
					--numLives;
					if (numLives <= 0)
					{
						SceneSystem::SetPendingScene<Level2Scene>();
					}
					else
					{
						Restart();
					}
				}
			}
		}

		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		//SceneSystem::EndScene();
	}

	void Level1Scene::Render() const
	{
		if (entityPlanet)
		{
			entityPlanet->Render();
		}

		if (entityMonkey)
		{
			entityMonkey->Render();
		}

		if (entityLives)
		{
			entityLives->Render();
		}
	}

	void Level1Scene::Shutdown()
	{
		delete entityPlanet;
		entityPlanet = nullptr;

		delete entityMonkey;
		entityMonkey = nullptr;

		delete entityLives;
		entityLives = nullptr;
	}

	void Level1Scene::Unload()
	{
		delete spriteSourcePlanet;
		spriteSourcePlanet = nullptr;

		delete mesh1x1;
		mesh1x1 = nullptr;

		delete mesh3x3;
		mesh3x3 = nullptr;

		delete mesh16x8;
		mesh16x8 = nullptr;

		delete spriteSourceMonkeyIdle;
		spriteSourceMonkeyIdle = nullptr;

		delete spriteSourceMonkeyWalk;
		spriteSourceMonkeyIdle = nullptr;

		delete spriteSourceMonkeyJump;
		spriteSourceMonkeyJump = nullptr;

		delete spriteSourceFontSheet;
		spriteSourceFontSheet = nullptr;
	}

	void Level1Scene::MovementController(Entity* entity)
	{
		Physics* physics = entity->Get<Physics>();
		Transform* transform = entity->Get<Transform>();
		if (physics && transform)
		{
			Vector2D velocity = physics->Velocity();
			if (DGL_Input_KeyDown(VK_LEFT))
			{
				velocity.x = -moveVelocity;
				if (monkeyState != Jump)
				{
					SetMonkeyState(entity, Walk);
				}
			}
			else if (DGL_Input_KeyDown(VK_RIGHT))
			{
				velocity.x = moveVelocity;
				if (monkeyState != Jump)
				{
					SetMonkeyState(entity, Walk);
				}
			}
			else
			{
				velocity.x = 0.0f;
				if (monkeyState != Jump)
				{
					SetMonkeyState(entity, Idle);
				}
			}

			if (DGL_Input_KeyTriggered(VK_UP)) 
			{
				velocity.y = jumpVelocity;
				physics->Acceleration(gravityNormal);
				SetMonkeyState(entity, Jump);
			}

			Vector2D translation = transform->Translation();
			if (translation.y < groundHeight)
			{
				translation.y = groundHeight;
				transform->Translation(translation);

				velocity.y = 0.0f;
				physics->Acceleration(gravityNone);
				SetMonkeyState(entity, Idle);
			}
			physics->Velocity(velocity);
		}
	}

	void Level1Scene::BounceController(Entity* entity) const
	{
		Transform* transform = entity->Get<Transform>();
		Physics* physics = entity->Get<Physics>();
		if (transform && physics)
		{
			Vector2D translation = transform->Translation();
			Vector2D velocity = physics->Velocity();
			if (translation.x < -wallDistance)
			{
				translation.x = -wallDistance;
				velocity.x = -velocity.x;
			}
			if (translation.x > wallDistance)
			{
				translation.x = wallDistance;
				velocity.x = -velocity.x;
			}
			if (translation.y <= groundHeight)
			{
				translation.y = groundHeight + (groundHeight - translation.y);
				velocity.y = -velocity.y;
			}

			transform->Translation(translation);
			physics->Velocity(velocity);
		}
	}

	void Level1Scene::SetMonkeyState(Entity* entity, MonkeyStates state)
	{
		if (monkeyState != state)
		{
			Sprite* sprite = entity->Get<Sprite>();
			Animation* animation = entity->Get<Animation>();
			if (sprite && animation)
			{
				switch (state)
				{
				case Idle:
					sprite->SetMesh(mesh1x1);
					sprite->SetSpriteSource(spriteSourceMonkeyIdle);
					animation->Play(1, 0.0f, false);
					break;
				case Jump:
					sprite->SetMesh(mesh1x1);
					sprite->SetSpriteSource(spriteSourceMonkeyJump);
					animation->Play(1, 0.0f, false);
					break;
				case Walk:
					sprite->SetMesh(mesh3x3);
					sprite->SetSpriteSource(spriteSourceMonkeyWalk);
					animation->Play(8, 0.05f, true);
					break;
				default:
					break;
				}
				monkeyState = state;
			}
		}
	}

	bool Level1Scene::isColliding(const Entity* entityA, const Entity* entityB) const
	{
		if (entityA && entityB)
		{
			Transform* transformA = entityA->Get<Transform>();
			Transform* transformB = entityB->Get<Transform>();
			if (transformA && transformB)
			{
				Vector2D posA = transformA->Translation();
				Vector2D posB = transformB->Translation();

				float distanceSquared = posA.SquareDistance(posB);
				if (distanceSquared <= CheckSquareDistance)
				{
					return true;
				}
			}
		}
		return false;
	}

#pragma endregion Private Functions

}	// namespace