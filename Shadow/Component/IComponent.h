#include "sdpch.h"
#pragma once

#include <glm/glm.hpp>

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
COMPONENT_TYPE:
	The different types of comonents the engine has.
=========================================================================================
*/
enum class ComponentType 
{
	Undefined,
	SpriteRenderer,
	BoxCollider2D,
	CircleCollider2D,
	RigidBody2D
};

/***
=========================================================================================
ICOMPONENT:
	An interface for the components.
=========================================================================================
*/
class IComponent
{
public:
	virtual ~IComponent() { }

	/*
		\brief Method called when the component is created and added to a Game Object.
	*/
	virtual void OnComponentAdd() = 0;
	/*
		\brief Method called on each update frame.
	*/
	virtual void Update() = 0;
	/*
		\brief Method called to Render something to the screen.
	*/
	virtual void Render(glm::vec3 worldPosition) = 0;
	/*
		\brief Method called when the component is destroyed and removed from a Game Object.
	*/
	virtual void OnComponentRemove() = 0;

	// Accessors.
	/*
		\brief Method called to get the type of the component.
	*/
	ComponentType GetComponentType() const { return m_componentType; }
protected:
	// Mutators.
	/*
		\brief Method called to set the type of the componet.
	*/
	void SetComponentType(ComponentType component) { m_componentType = component; }
private:
	ComponentType m_componentType = ComponentType::Undefined;
};

SHADOW_NAMESPACE_END