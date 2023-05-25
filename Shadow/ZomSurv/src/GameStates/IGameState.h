#pragma once
#include "sdpch.h"

class IGameState
{
public:
	virtual void OnStateEnter() = 0;
	virtual void Update() = 0;
	virtual void OnStateExit() = 0;
};
