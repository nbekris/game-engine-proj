//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.cpp
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
#include "CheatSystem.h"

#include "SceneSystem.h"
#include "DemoScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "AsteroidsScene.h"

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

	CheatSystem::CheatSystem(void) : System("CheatSystem")
	{
	}

	//--------------------------------------------------------------------------

	CheatSystem::~CheatSystem(void)
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
#ifdef DEBUG
	void CheatSystem::Update(float dt)
	{
		if (DGL_Input_KeyTriggered('0'))
		{
			SceneSystem::SetPendingScene<DemoScene>();
		}
		else if (DGL_Input_KeyTriggered('1'))
		{
			SceneSystem::SetPendingScene<Level1Scene>();
		}
		else if (DGL_Input_KeyTriggered('2'))
		{
			SceneSystem::SetPendingScene<Level2Scene>();
		}
		else if (DGL_Input_KeyTriggered('3'))
		{
			SceneSystem::SetPendingScene<AsteroidsScene>();
		}
		else if (DGL_Input_KeyTriggered('9'))
		{
			SceneSystem::SetPendingScene<SandboxScene>();
		}
	}
#endif
#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace