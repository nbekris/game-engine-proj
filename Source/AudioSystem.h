//------------------------------------------------------------------------------
//
// File Name:	AudioSystem.h
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new system.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "System.h"
#include <fmod.hpp>

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
	class AudioSystem : public System
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		AudioSystem(void);

		// All systems need a virtual destructor to have their destructor called 
		~AudioSystem(void) override;

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:
		// Windows message event handler.
		//virtual bool HandleMessage(const Message& message) = 0;

		// Private Functions:
	private:
		// @brief Initialize the system.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the system each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override {};

		// @brief Render the system each frame.
		void Render() const override {};

		void LoadSound(const std::string& filename);

		void StreamMusic(const std::string& filename, bool isLooped);

		void PlaySFX();
		void PlayMusic();

		// Private Static Constants:
	private:

		// Private Static Variables:
	private:
		static AudioSystem* instance;
		FMOD_RESULT result;
		FMOD::System* system;
		FMOD::Sound* sfx;
		FMOD::Sound* music;
		FMOD::Channel* musicChannel;
		FMOD::Channel* sfxChannel;

		// Private Variables:
	private:
	};

}	// namespace