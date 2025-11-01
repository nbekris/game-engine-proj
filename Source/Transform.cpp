//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	dschilling
// Course:		CS529F25
// Project:		Project 2
// Purpose:		This component class stores an entity's position, orientation,
//   and scale within the world space.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <dragon/assert.h>

#include "Component.h"
#include "Stream.h"
#include "Transform.h"
#include "Matrix2D.h"
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

	Transform::Transform(void)
		: Component()
	{
	}

	Transform::Transform(const Transform* other)
	{
		translation = other->translation;
		rotation = other->rotation;
		scale = other->scale;
		matrix = other->matrix;
		isDirty = true;
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

	void Transform::Read(Stream& stream)
	{
		// Check for valid stream (optional).
		DRAGON_ASSERT(stream.Contains("Transform"), "Transform::Read: Failed to find required key: Transform");

		// Traverse down the tree to the "Transform" object (PushNode).
		stream.PushNode("Transform");

		// Read the translation value from the stream.
		stream.ReadVector2D("Translation", translation);

		// Read the rotation value from the stream.
		stream.Read("Rotation", rotation);

		// Read the scale value from the stream.
		stream.ReadVector2D("Scale", scale);

		// Return to the original location in the tree.
		stream.PopNode();
	}

	const Matrix2D& Transform::GetMatrix()
	{
		if (isDirty)
		{
			Matrix2D T, S, R;

			T.Translate(translation);
			S.Scale(scale);
			R.RotationRad(rotation);

			matrix = T * R * S;
			isDirty = false;
		}

		return matrix;
	}

	void Transform::Translation(const Vector2D& translation)
	{
		this->translation = translation;
		isDirty = true;
	}

	void Transform::Scale(const Vector2D& scale)
	{
		this->scale = scale;
		isDirty = true;
	}

	void Transform::Rotation(float rotation)
	{
		this->rotation = rotation;
		isDirty = true;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace