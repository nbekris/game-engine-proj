//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
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
#include "SpriteSource.h"
#include "Vector2D.h"

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

	SpriteSource::SpriteSource(void)
	{
	}

	//--------------------------------------------------------------------------

	SpriteSource::~SpriteSource(void)
	{
		if (textureResource)
		{
			DGL_Graphics_FreeTexture(const_cast<DGL_Texture**>(&textureResource));
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
	void SpriteSource::LoadTexture(unsigned numCols, unsigned numRows, std::string_view textureName)
	{
		this->numCols = numCols;
		this->numRows = numRows;

		textureResource = DGL_Graphics_LoadTexture(textureName.data());
	}

	unsigned SpriteSource::GetFrameCount() const
	{
		return numCols * numRows;
	}

	void SpriteSource::UseTexture() const
	{
		if (textureResource)
		{
			DGL_Graphics_SetTexture(textureResource);
		}
	}

	// @brief Calculates the UV offset for the specified frame.
	// @brief [HINT: Refer to the "Sprite Sources" slide deck for implementation details.]
	//
	// @param frameIndex = The index of the frame within a spritesheet to be displayed.
	// @param uv = A structure to be filled with the calculated UV values.
	void SpriteSource::CalculateTextureOffset(unsigned frameIndex, Vector2D& uv) const
	{
		float uSize = 1.0f / numCols;
		float vSize = 1.0f / numRows;

		float uOffset = uSize * (frameIndex % numCols);
		float vOffset = vSize * (frameIndex / numCols);

		uv.Set(uOffset, vOffset);
	}

	// @brief Calculates the UV offset for the specified frame and passes it to the DGL.
	// @brief Specific Steps:
	// @brief   Create a Vector2D variable called 'uv'.
	// @brief   Call CalculateTextureOffset
	// @brief   Call DGL_Graphics_SetCB_TextureOffset
	//
	// @param frameIndex = The index of the frame within a spritesheet to be displayed.
	void SpriteSource::SetTextureOffset(unsigned frameIndex) const
	{
		Vector2D uv;
		CalculateTextureOffset(frameIndex, uv);
		DGL_Graphics_SetCB_TextureOffset(&uv);
	}
#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace