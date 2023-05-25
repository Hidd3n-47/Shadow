#pragma once

#include "IGameState.h"

class SpawningZombiesState : public IGameState
{
	friend class GameManager;
public:
	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;

private:
	uint8_t m_waveMaxZombies = 0;
	uint8_t m_waveCurrentZombies = 0;
	const float m_timeBewtweenZombieSpawns = 0.75f;
	float m_timeUntilNextZombieSpawn = 0.0f;
};

