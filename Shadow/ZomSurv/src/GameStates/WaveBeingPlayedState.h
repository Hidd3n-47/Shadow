#pragma once

#include "IGameState.h"

class WaveBeingPlayedState : public IGameState
{
public:
	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;
};

