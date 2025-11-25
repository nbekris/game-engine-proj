//------------------------------------------------------------------------------
//
// File Name:	AudioSystem.cpp
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template class for a new system.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <cassert>

#include "AudioSystem.h"
#include "System.h"
#include <fmod.hpp>
#include <fmod_errors.h>

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

	//------------------------------------------------------------------------------
	// Private Static Variables:
	//------------------------------------------------------------------------------

	AudioSystem* AudioSystem::instance = nullptr;

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	AudioSystem::AudioSystem(void)
		: System("AudioSystem")
	{
		result = FMOD_OK;
		system = NULL;

		// Raise an assert if this system has already been created.
		assert(instance == nullptr);

		// Store this system's instance for use by static functions.
		instance = this;
	}

	//--------------------------------------------------------------------------

	AudioSystem::~AudioSystem(void)
	{
		// Clear the static instance pointer.
		instance = nullptr;
		
		if (system)
		{
			system->close();
			system->release();
		}
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

	bool AudioSystem::Initialize()
	{
		result = FMOD::System_Create(&system);      // Create the main system object.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}

		result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
		// Add system-specific initialization code here.

		// Return true if the initialization completed successfully.
		return true;
	}

	void AudioSystem::LoadSound(const std::string& filename)
	{
		result = system->createSound(filename.c_str(), FMOD_NONBLOCKING, 0, &sfx);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

	void AudioSystem::StreamMusic(const std::string& filename, bool isLooped)
	{
		FMOD_MODE mode = isLooped ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		result = system->createStream(filename.c_str(), mode, 0, &music);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

	void AudioSystem::PlaySFX()
	{
		// replace 'sound' with the actual FMOD::Sound* you want to play
		result = system->playSound(sfx, 0, false, &sfxChannel);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

	void AudioSystem::PlayMusic()
	{
		result = system->playSound(sfx, 0, false, &musicChannel);
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			exit(-1);
		}
	}

#pragma endregion Private Functions

}	// namespace