//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
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
#include "Animation.h"
#include "Stream.h"
#include "Sprite.h"
#include "Entity.h"
#include "Component.h"

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

	Animation::Animation(void)
	{
	}

	Animation::Animation(const Animation* other)
	{
		if (!other) return;
		this->frameIndex = other->frameIndex;
		this->frameCount = other->frameCount;
		this->frameDelay = other->frameDelay;
		this->frameDuration = other->frameDuration;
		this->isRunning = other->isRunning;
		this->isLooping = other->isLooping;
		this->isDone = other->isDone;
	}

	//--------------------------------------------------------------------------
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

	void Animation::Play(unsigned frameCount, float frameDuration, bool isLooping)
	{
		Sprite* sprite = Parent()->Get<Sprite>();
		if (!sprite) return;

		this->frameCount = frameCount;
		this->frameDuration = frameDuration;
		this->isLooping = isLooping;

		this->isRunning = true;
		this->isDone = false;
		this->frameIndex = 0;
		this->frameDelay = frameDuration;

		// Sprite set frame
		sprite->SetFrame(frameIndex);
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

	void Animation::Update(float dt)
	{
		if (!this) return;

		isDone = false;
		if (isRunning)
		{
			frameDelay -= dt;
			if (frameDelay <= 0.0f)
			{
				AdvanceFrame();
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}
	}

	void Animation::AdvanceFrame()
	{
		Entity* parent = Parent();
		if (!parent) return;

		Sprite* sprite = parent->Get<Sprite>();
		if (!sprite) return;

		++frameIndex;
		if (frameIndex >= frameCount)
		{
			if (isLooping)
			{
				frameIndex = 0;
			}
			else
			{
				frameIndex = frameCount - 1;
				isRunning = false;
			}

			isDone = true;
		}

		if (isRunning) 
		{
			//Update sprite frame
			Sprite* sprite = Parent()->Get<Sprite>();
			sprite->SetFrame(frameIndex);
			frameDelay += frameDuration;
		}
		else
		{
			frameDelay = 0;
		}
	}

	void Animation::Read(Stream& stream)
	{
		if (!&stream) return;

		DRAGON_ASSERT(stream.Contains("Animation"), "Animation::Read: Failed to find required key: Animation");

		stream.PushNode("Animation");
		stream.Read("FrameIndex", frameIndex);
		stream.Read("FrameCount", frameCount);
		stream.Read("FrameDelay", frameDelay);
		stream.Read("FrameDuration", frameDuration);
		stream.Read("IsRunning", isRunning);
		stream.Read("IsLooping", isLooping);
		stream.Read("IsDone", isDone);
		stream.PopNode();
	}

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace