//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.cpp
// Author(s):	bekri
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <Windows.h>

#include "SandboxScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "LoggingSystem.h"
#include "Stream.h"
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

	SandboxScene::SandboxScene()
		: Scene("SandboxScene")
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

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	void SandboxScene::Load()
	{
	}

	bool SandboxScene::Initialize()
	{
		return true;
	}

	void SandboxScene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);

		Stream stream("Data/VectorTests.json");

		if (stream.IsValid())
		{
			Vector2D v;

			v.Zero();
			LogVector("Zero", v);

			v.Set(1.5, 1.0);
			LogVector("Set", v);

			v.Negate();
			LogVector("Negate", v);

			v.Add(v);
			LogVector("Add",  v);

			v.Sub(v);
			LogVector("Sub", v);

			stream.ReadVector2D("v", v);
			LogVector("StreamReadVector2D", v);

			v.Normalize();
			LogVector("Normalize", v);

			float scale;
			stream.Read("scale", scale);
			LogFloat("StreamReadFloat", scale);

			v.Scale(scale);
			LogVector("Vector2DScale", v);

			v.ScaleAdd(scale, v);
			LogVector("Vector2DScaleAdd", v);

			v.ScaleSub(scale, v);
			LogVector("Vector2DScaleSub", v);

			float length;
			length = v.Length();
			LogFloat("Vector2DLength", length);

			length = v.SquareLength();
			LogFloat("Vector2DSquareLength", length);

			Vector2D p1;
			Vector2D p2;
			stream.ReadVector2D("p1", p1);
			stream.ReadVector2D("p2", p2);
			LogVector("StreamReadVector2D", p1);
			LogVector("StreamReadVector2D", p2);

			LogFloat("Distance", p1.Distance(p2));
			LogFloat("SquareDistance", p1.SquareDistance(p2));

			float result = p1.DotProduct(p2);
			LogFloat("Vector2DDotProduct", result);

			float angle;
			stream.Read("degrees", angle);
			LogFloat("StreamReadFloat", angle);

			Vector2D p3;

			p3.FromAngleDeg(angle);
			LogVector("Vector2DFromAngleDeg", p3);

			stream.Read("radians", angle);
			LogFloat("StreamReadFloat", angle);

			p3.FromAngleRad(angle);
			LogVector("Vector2DFromAngleRad", p3);

			LogFloat("Vector2DToAngleRad", p3.ToAngleRad());
		}

		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		SceneSystem::EndScene();
	}

	void SandboxScene::Render() const
	{
	}

	void SandboxScene::Shutdown()
	{
	}

	void SandboxScene::Unload()
	{
	}

	void SandboxScene::LogFloat(const char* text, float f)
	{
		LoggingSystem::Verbose("Vector Test: {} = {}", text, f);
	}

	void SandboxScene::LogVector(const char* text, const Vector2D& v)
	{
		LoggingSystem::Verbose("Vector Test: {} = [{}, {}]", text, v.x, v.y);
	}

#pragma endregion Private Functions

}	// namespace