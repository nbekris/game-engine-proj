//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.cpp
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
	ScoreSystem* ScoreSystem::instance = nullptr;
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

	//--------------------------------------------------------------------------

	ScoreSystem::ScoreSystem(void)
		: System("ScoreSystem")
	{
		instance = this;
	}

	ScoreSystem::~ScoreSystem(void)
	{
		instance = nullptr;
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

	void ScoreSystem::NewGame()
	{
		score = 0;
		highScore = 0;
		waveCount = 0;
	}

	void ScoreSystem::Reset()
	{
		highScore = std::max(score, highScore);
		score = 0;
		waveCount = 0;
	}

	unsigned ScoreSystem::GetValue(ScoreSystemId id) const
	{
		switch (id) 
		{
			case (SsiScore):
				return score;
				break;
			case (SsiHighScore):
				return highScore;
				break;
			case (SsiWaveCount):
				return waveCount;
				break;
		}

		return 0;
	}

	void ScoreSystem::IncreaseScore(unsigned amount)
	{
 		score += amount;
	}

	void ScoreSystem::IncreaseWave(void)
	{
		++waveCount;
	}

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace