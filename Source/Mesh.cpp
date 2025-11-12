//------------------------------------------------------------------------------
//
// File Name:	Mesh.cpp
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
#include "Mesh.h"
#include "Stream.h"

#include "DGL.h"

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
	// DGL_Vec2 Constants:
	static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f, 0.5f };
	static const DGL_Vec2 Vertex_Pos_Trc = { 0.5f, 0.5f };
	static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };
	static const DGL_Vec2 Vertex_Pos_Brc = { 0.5f, -0.5f };
	static const DGL_Vec2 Vertex_Pos_Zero = { 0.0f, 0.0f };
	static const DGL_Vec2 Vertex_Pos_Right = { 0.5f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Zero = { 0.0f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Tlc = { 0.0f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Trc = { 1.0f, 0.0f };
	static const DGL_Vec2 Vertex_UV_Blc = { 0.0f, 1.0f };
	static const DGL_Vec2 Vertex_UV_Brc = { 1.0f, 1.0f };

	// DGL_Color constants:
	static const DGL_Color DGL_Color_Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_White = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	static const DGL_Color DGL_Color_Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
	static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

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

	Mesh::Mesh(void)
	{
		name = "UnNamed Mesh";
	}

	//--------------------------------------------------------------------------

	Mesh::~Mesh(void)
	{
		if (meshResource)
		{
			DGL_Graphics_FreeMesh(const_cast<DGL_Mesh**>(&meshResource));
		}
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------
	
	void Mesh::BuildQuad(float uSize, float vSize, std::string_view name)
	{
		DGL_Graphics_StartMesh();

		DGL_Vec2 const adjustedUV_Trc = { uSize, 0.0f };
		DGL_Vec2 const adjustedUV_Brc = { uSize, vSize };
		DGL_Vec2 const adjustedUV_Blc = { 0.0f, vSize };

		// triangle 1, top right, bottom left, bottom right
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &adjustedUV_Blc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &adjustedUV_Trc,
			&Vertex_Pos_Brc, &DGL_Color_Black, &adjustedUV_Brc);

		// triangle 2, bottom left, top left, top right
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &adjustedUV_Blc,
			&Vertex_Pos_Tlc, &DGL_Color_Black, &Vertex_UV_Tlc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &adjustedUV_Trc);

		meshResource = DGL_Graphics_EndMesh();
		//this->drawMode = DGL_DM_TRIANGLELIST();

		assert(meshResource && "Failed to create mesh!");

		this->name = name;
	}

	void Mesh::BuildSpaceship()
	{
		// build a triangular, colored mesh space ship
		DGL_Graphics_StartMesh();
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Right, &DGL_Color_Yellow, &Vertex_UV_Zero,
			&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
			&Vertex_Pos_Tlc, &DGL_Color_Red, &Vertex_UV_Zero);
		meshResource = DGL_Graphics_EndMesh();

		assert(meshResource && "Failed to create mesh!");
	}

	void Mesh::Render() const
	{
		if (meshResource)
		{
			DGL_Graphics_DrawMesh(meshResource, drawMode);
		}
	}

	void Mesh::Read(Stream& stream)
	{
		if (stream.IsValid())
		{
			stream.PushNode("Mesh");
			stream.Read("Name", this->name);
			if (name == "MeshSpaceship")
			{
				BuildSpaceship();
			}
			else if (stream.Contains("Vertices"))
			{
				auto lambda = [&stream]() 
					{
						Vector2D position;
						Vector2D uvOffsets;
						std::vector<float> color(4);
						stream.ReadVector2D("Position", position);
						stream.ReadVector2D("UV", uvOffsets);
						stream.Read("Color", color);
						const DGL_Color dglColor = { color[0], color[1], color[2], 1.0 };
						DGL_Graphics_AddVertex(&position, &dglColor, &uvOffsets);
					};
				DGL_Graphics_StartMesh();
				stream.ReadArray("Vertices", lambda);
				meshResource = DGL_Graphics_EndMesh();

				assert(meshResource && "Failed to create mesh!");
			}
			else if (stream.Contains("Quad"))
			{
				unsigned int numCols;
				unsigned int numRows;
				stream.Read("NumCols", numCols);
				stream.Read("NumRows", numRows);
				BuildQuad(1.0f / numCols, 1.0f / numRows, "name");
			}
			else
			{
				LoggingSystem::Warning("No Mesh found in json.");
			}
			stream.PopNode();
		}
	}

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

#pragma endregion Private Functions

}	// namespace