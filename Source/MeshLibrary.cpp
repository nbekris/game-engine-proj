//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.cpp
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
#include "MeshLibrary.h"
#include "Stream.h"
#include "Mesh.h"

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
	std::unordered_map<std::string, const Mesh*> CS529::MeshLibrary::meshes;
	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	MeshLibrary::MeshLibrary(void)
	{
	}

	//--------------------------------------------------------------------------

	MeshLibrary::~MeshLibrary(void)
	{
		DeleteAll();
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

	const Mesh* MeshLibrary::Build(const std::string& meshName)
	{
		if (auto search = meshes.find(meshName); search != meshes.end())
		{
			return search->second;
		}

		std::string filePath = "./Data/Meshes/" + meshName + ".json";
		Stream stream(filePath);
		if (stream.IsValid() && stream.Contains("Mesh"))
		{
			Mesh* mesh = new Mesh();
			mesh->Read(stream);
			meshes.insert({ meshName, mesh });

			return mesh;
		}

		return nullptr;
	}

	const Mesh* MeshLibrary::Find(const std::string meshName)
	{
		if (auto search = meshes.find(meshName); search != meshes.end()) return search->second;
		return nullptr;
	}

	void MeshLibrary::DeleteAll()
	{
		for (auto& pair : meshes)
		{
			delete pair.second;
			pair.second = nullptr;
		}
		meshes.clear();
	}
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