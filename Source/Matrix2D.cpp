//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.cpp
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
#include "Matrix2D.h"
#include "Vector2D.h"
#include <numbers>

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
	const Matrix2D Matrix2D::identity = Matrix2D();
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

	// @brief Creates an instance of a 2D transformation matrix.
	// @brief [NOTE: Ideally, the matrix is initialized as an identity matrix.]
	// @brief [HINT: This can be done using "DGL_Mat4{}" in the initializer list.]
	// @brief [HINT: The body of the constructor should be empty.]
	Matrix2D::Matrix2D(void) : 
		DGL_Mat4{ 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f }
	{
	}

	//--------------------------------------------------------------------------

	Matrix2D::~Matrix2D(void)
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
	
	void Matrix2D::Identity()
	{
		*this = identity;
	}

	void Matrix2D::Translate(const Vector2D& v)
	{
		Translate(v.x, v.y);
	}

	void Matrix2D::Translate(float x, float y)
	{
		*this = identity;
		this->m[0][3] = x;
		this->m[1][3] = y;
	}

	void Matrix2D::Scale(const Vector2D& v)
	{
		Scale(v.x, v.y);
	}

	void Matrix2D::Scale(float x, float y)
	{
		*this = identity;
		this->m[0][0] = x;
		this->m[1][1] = y;
	}

	void Matrix2D::RotationDeg(float angle)
	{
		float radians = static_cast<float>(angle * std::numbers::pi) / 180.0f;
		RotationRad(radians);
	}

	void Matrix2D::RotationRad(float angle)
	{
		*this = identity;
		this->m[0][0] = std::cos(angle);
		this->m[0][1] = -std::sin(angle);
		this->m[1][0] = std::sin(angle);
		this->m[1][1] = std::cos(angle);
	}

	Matrix2D Matrix2D::operator*(const Matrix2D& other) const
	{
		Matrix2D result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column) 
			{
				result.m[row][column] = this->m[row][0] * other.m[0][column] +
					this->m[row][1] * other.m[1][column] +
					this->m[row][2] * other.m[2][column] +
					this->m[row][3] * other.m[3][column];
			}
		}
		return result;
	}

	Vector2D Matrix2D::operator*(const Vector2D& v) const
	{
		Vector2D result;
		result.x = 
			this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][3] * 1.0f;
		result.y = 
			this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][3] * 1.0f;
		return result;
	}
#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace