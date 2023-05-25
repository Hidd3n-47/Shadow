#pragma once
#include "src/sdpch.h"

#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

class ICollisionMethods
{
public:
	virtual ~ICollisionMethods() { }

	virtual void OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject) = 0;
	//virtual void OnCollisionStay(Shadow::GameObject* otherGameObject) = 0; //< Not sure if this is needed or if I should add this.
	//virtual void OnCollisionExit() = 0; // TODO: Implement later.
};

SHADOW_NAMESPACE_END