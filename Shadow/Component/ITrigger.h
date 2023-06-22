#pragma once
#include "src/sdpch.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
TRIGGER_METHODS_INTERFACE:
	An interface for handling custom trigger events.
	Add to an object if there are custom outcomes due to trigger being activiated.
=========================================================================================
*/
class ITrigger
{
public:
	virtual ~ITrigger() { }

	virtual void OnTriggerEnter(GameObject* thisCollider, GameObject* otherCollider) = 0;
	virtual void OnTriggerStay(GameObject* thisCollider, GameObject* otherCollider) = 0;
	virtual void OnTriggerExit() = 0;
};

SHADOW_NAMESPACE_END