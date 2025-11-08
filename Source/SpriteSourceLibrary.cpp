//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.cpp
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
#include "SpriteSourceLibrary.h"
#include "Stream.h"
#include "SpriteSource.h"

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
	std::unordered_map<std::string, const SpriteSource*> SpriteSourceLibrary::spriteSources;
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	SpriteSourceLibrary::SpriteSourceLibrary(void)
	{
	}

	//--------------------------------------------------------------------------

	SpriteSourceLibrary::~SpriteSourceLibrary(void)
	{
		DeleteAll();
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------
	void SpriteSourceLibrary::DeleteAll()
	{
		for (auto& pair : spriteSources)
		{
			delete pair.second;
			pair.second = nullptr;
		}
		spriteSources.clear();
	}

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

	const SpriteSource* SpriteSourceLibrary::Build(const std::string& spriteSourceName)
	{
		const SpriteSource* existingSpriteSource = Find(spriteSourceName);
		if (existingSpriteSource)
		{
			return existingSpriteSource;
		}

		std::string filePath = "./Data/SpriteSources/" + spriteSourceName + ".json";
		Stream stream(filePath);
		if (stream.IsValid() && stream.Contains("SpriteSource"))
		{
			SpriteSource* spriteSource = new SpriteSource();
			spriteSource->Read(stream);
			spriteSources.insert({ spriteSourceName, spriteSource });

			return spriteSource;
		}

		return nullptr;
	}

	const SpriteSource* SpriteSourceLibrary::Find(const std::string spriteSourceName)
	{
		if (auto search = spriteSources.find(spriteSourceName); search != spriteSources.end()) return search->second;
		return nullptr;
	}

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace