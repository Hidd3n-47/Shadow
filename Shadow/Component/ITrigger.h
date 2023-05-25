#pragma once
#include "src/sdpch.h"

SHADOW_NAMESPACE_BEGIN

class ITrigger
{
public:
	virtual ~ITrigger() { }

	virtual void OnTriggerEnter(GameObject* thisCollider, GameObject* otherCollider) = 0;
	virtual void OnTriggerStay(GameObject* thisCollider, GameObject* otherCollider) = 0;
	virtual void OnTriggerExit() = 0;
};

SHADOW_NAMESPACE_END