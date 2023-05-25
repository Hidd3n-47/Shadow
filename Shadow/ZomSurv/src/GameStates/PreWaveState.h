#pragma once

#include "IGameState.h"

class PreWaveState : public IGameState
{
public:
	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;
private:
	const float m_timeBetweenWaves = 2.0f;
	float m_timeUntilNextWave = 0.0f;
};

