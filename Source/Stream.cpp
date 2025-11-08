//------------------------------------------------------------------------------
//
// File Name:	Stream.cpp
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
#include "Stream.h"
#include <fstream>
#include <iostream>
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

	Stream::Stream(std::string_view filePath)
	{
		Open(filePath);
	}

	//--------------------------------------------------------------------------

	Stream::~Stream(void)
	{
	}

	bool Stream::Contains(std::string_view key)
	{
		return dataNode->contains(key);
	}

	void Stream::ReadArray(std::string_view key, std::function<void()> lambda)
	{
		if (Contains(key))
		{
			PushNode(key);
			for (auto& item : dataNode->items())
			{
				dataStack.push_back(dataNode);
				dataNode = &item.value();
				lambda();
				PopNode();
			}
			PopNode();
			
		}
	}

	void Stream::ReadObject(std::string_view key, std::function<void(const std::string& key)> lambda)
	{
		if (Contains(key))
		{
			PushNode(key);
			for (auto& [componentKey, componentValue] : dataNode->items())
			{
				lambda(componentKey);
			}
			PopNode();
		}
	}

	void Stream::PushNode(std::string_view key)
	{
		if (Contains(key))
		{
			dataStack.push_back(dataNode);
			dataNode = &dataNode->at(key);
		}
	}

	void Stream::PopNode()
	{
		if (!dataStack.empty())
		{
			dataNode = dataStack.back();
			dataStack.pop_back();
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

#pragma region Public Functions

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------
	bool Stream::Open(std::string_view filePath)
	{
		isValid = false;

		// Open the JSON file.
		std::ifstream file(filePath.data());
		if (!file.is_open())
		{
			LoggingSystem::Error("Stream: Failed to open file {}", filePath);
			return isValid;
		}


		try
		{
			file >> jsonData;
		}
		catch (const json::parse_error& exception)
		{
			LoggingSystem::Error("Stream: JSON parsing error reading {}: ", filePath, exception.what());
			return isValid;
		}

		// Set the current data node to the root of the JSON data.
		dataNode = &jsonData;

		// The JSON file has been read and parsed successfully.
		isValid = true;
		return isValid;
	}
#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace