//------------------------------------------------------------------------------
//
// File Name:	Entity.cpp
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
#include "Entity.h"
#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Stream.h"
#include "Animation.h"
#include "ObjectFactory.h"

#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

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

	Entity::Entity(void)
	{
	}

	//--------------------------------------------------------------------------

	Entity::Entity(const Entity* other)
	{
		name = other->name;
		isDestroyed = other->isDestroyed;
		for (Component* component : other->components)
		{
			this->Add(component->Clone());
		}
	}

	Entity::~Entity(void)
	{
		for (Component* component : components)
		{
			delete component;
		}
		components.clear();
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

	bool Entity::Initialize()
	{
		// Only return true if all components initialize successfully
		for (Component* component : components)
		{
			if (!component->Initialize())
			{
				return false;
			}
		}
		return true;
	}

	void Entity::Update(float dt)
	{
		for (Component* component : components)
		{
			component->Update(dt);
		}
	}

	void Entity::Render() const
	{
		for (const Component* component : components)
		{
			component->Render();
		}
	}

	void Entity::Add(Component* component)
	{
		if (component)
		{
			components.push_back(component);
			component->Parent(this);
		}
	}

	void Entity::Read(Stream& stream)
	{
		auto lambda = [this, &stream](const std::string& key) 
			{
				ObjectFactory& objectFactory = ObjectFactory::GetInstance();
				Object* object = objectFactory.Create(key);

				if (!object)
				{
					LoggingSystem::Debug("Entity::Read: Failed to create component of type '{}'", key);
					return;
				}

				Component* component = static_cast<Component*>(object);
				if (component)
				{
					component->Read(stream);
					Add(component);
				}
				else
				{
					delete object;
				}

			};
		if (stream.IsValid())
		{
			stream.PushNode("Entity");
			stream.Read("Name", name);
			if (stream.Contains("Components"))
			{
				stream.ReadObject("Components", lambda);
			}
			stream.PopNode();
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