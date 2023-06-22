#pragma once
#include "src/sdpch.h"

#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
COLLISION_METHODS_INTERFACE:
	An interface for handling custom collision events.
	Add to an object if there are custom outcomes due to collision.
=========================================================================================
*/
class ICollisionMethods
{
public:
	virtual ~ICollisionMethods() { }

	virtual void OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject) = 0;
	//virtual void OnCollisionStay(Shadow::GameObject* otherGameObject) = 0; //< TODO: Could be implmented later if needed.
	//virtual void OnCollisionExit() = 0; // TODO: Implement later if needed.
};

SHADOW_NAMESPACE_END