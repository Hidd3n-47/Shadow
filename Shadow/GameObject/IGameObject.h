#include "sdpch.h"
#pragma once

#include "Vec2.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
IGAME_OBJECT:
	Game Object interface.
=========================================================================================
*/
class IGameObject
{
public:
	virtual void Update() = 0;
	// void add comp
	// void remove comp
private:
	vec2 m_position;
	// List of components.
};

SHADOW_NAMESPACE_END