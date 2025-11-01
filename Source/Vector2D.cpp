//------------------------------------------------------------------------------
//
// File Name:	Vector2D.cpp
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

	Vector2D::Vector2D(void)
	{
		x = 0;
		y = 0;
	}

	Vector2D::Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2D::Vector2D(const Vector2D& other)
	{
		this->x = other.x;
		this->y = other.y;
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

	void Vector2D::Zero()
	{
		x = 0;
		y = 0;
	}

	void Vector2D::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Vector2D::Negate()
	{
		this->x = -x;
		this->y = -y;
	}

	void Vector2D::Add(const Vector2D& offset)
	{
		this->x += offset.x;
		this->y += offset.y;
	}

	void Vector2D::Sub(const Vector2D& offset)
	{
		this->x -= offset.x;
		this->y -= offset.y;
	}

	void Vector2D::Normalize()
	{
		float mag = Length();;
		this->x = this->x / mag;
		this->y = this->y / mag;
	}

	void Vector2D::Scale(float scale)
	{
		this->x = x * scale;
		this->y = y * scale;
	}

	void Vector2D::ScaleAdd(float scale, const Vector2D& offset)
	{
		this->x += offset.x * scale;
		this->y += offset.y * scale;
	}

	void Vector2D::ScaleSub(float scale, const Vector2D& offset)
	{
		this->x -= offset.x * scale;
		this->y -= offset.y * scale;
	}

	float Vector2D::Length() const
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y));
	}

	float Vector2D::SquareLength() const
	{
		return (this->x * this->x) + (this->y * this->y);
	}

	float Vector2D::Distance(const Vector2D& point2) const
	{
		float distanceX = point2.x - this->x;
		float distanceY = point2.y - this->y;

		return std::sqrt((distanceX * distanceX) + (distanceY * distanceY));
	}

	float Vector2D::SquareDistance(const Vector2D& point2) const
	{
		float distanceX = point2.x - this->x;
		float distanceY = point2.y - this->y;

		return (distanceX * distanceX) + (distanceY * distanceY);
	}

	float Vector2D::DotProduct(const Vector2D& vector2) const
	{
		return (this->x * vector2.x) + (this->y * vector2.y);
	}

	void Vector2D::FromAngleDeg(float angle)
	{
		float radians = static_cast<float>(angle * std::numbers::pi) / 180.0f;
		this->x = std::cos(radians);
		this->y = std::sin(radians);
	}

	void Vector2D::FromAngleRad(float angle)
	{
		this->x = std::cosf(angle);
		this->y = std::sinf(angle);
	}

	float Vector2D::ToAngleRad() const
	{
		return std::atan2f(this->y, this->x);
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace