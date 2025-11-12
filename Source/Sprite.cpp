//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
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
#include "Sprite.h"
#include "Transform.h"
#include "Entity.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Stream.h"
#include "MeshLibrary.h"
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

	Sprite::Sprite(void)
	{
	}

	Sprite::Sprite(const Sprite* other)
	{
		this->alpha = other->alpha;
		this->tintColor = other->tintColor;
		this->frameIndex = other->frameIndex;
		this->spriteSource = other->spriteSource;
		this->mesh = other->mesh;
		this->text = other->text;
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
	void Sprite::Render() const
	{
		Transform* transform = Parent()->Get<Transform>();
		if (transform)
		{
			if (spriteSource)
			{
				DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
				spriteSource->UseTexture();
				spriteSource->SetTextureOffset(frameIndex);
			}
			else
			{
				DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
			}

			DGL_Graphics_SetCB_Alpha(alpha);
			DGL_Graphics_SetCB_TintColor(&tintColor);
			if (text == "")
			{
				DGL_Graphics_SetCB_TransformMatrix(&transform->GetMatrix());
				if (mesh)
				{
					mesh->Render();
				}
			}
			else
			{
				Matrix2D matrix = transform->GetMatrix();
				Matrix2D offset;

				offset.Translate(transform->Scale().x, 0.0f);
				for (char c : text)
				{
					if (spriteSource)
					{
						unsigned charIndex = c - ' ';
						spriteSource->SetTextureOffset(charIndex);
						DGL_Graphics_SetCB_TransformMatrix(&matrix);
						if (mesh)
						{
							mesh->Render();
						}
						matrix = offset * matrix;
					}
				}
			}
		}
	}

	void Sprite::Read(Stream& stream)
	{
		DRAGON_ASSERT(stream.Contains("Sprite"), "Sprite::Read: Failed to find required key: Sprite");

		std::string meshName;
		stream.PushNode("Sprite");
		stream.Read("Alpha", alpha);
		stream.Read("FrameIndex", frameIndex);
		stream.Read("Mesh", meshName);
		stream.PopNode();

		if (meshName != "")
		{
			mesh = MeshLibrary::Build(meshName);
		}
		std::string spriteSourceName;
		stream.PushNode("Sprite");
		stream.Read("SpriteSource", spriteSourceName);
		if (spriteSourceName != "")
		{
			spriteSource = SpriteSourceLibrary::Build(spriteSourceName);
		}
		stream.PopNode();
	}

	void Sprite::SetFrame(unsigned frame)
	{
		LoggingSystem::Verbose("Sprite::SetFrame: frame index = {}", frame);
		if (spriteSource)
		{
			if (frame < spriteSource->GetFrameCount())
			{
				frameIndex = frame;
			}
		}
	}

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace