#include "sdpch.h"
#include "SpawningZombiesState.h"

#include "Time/Time.h"
#include "GameStateManager.h"
#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/src/ZombieManager.h"

void SpawningZombiesState::OnStateEnter()
{
	m_timeUntilNextZombieSpawn = m_timeBewtweenZombieSpawns;

	m_waveMaxZombies = GameManager::Instance()->GetWave();
	m_waveCurrentZombies = 0;

	const int maxWaves = 30;
	const int maxZombies = 200;
	const int numStartingZombies = 10;
	unsigned int x = GameManager::Instance()->GetWave();
	m_waveMaxZombies = -maxZombies / (4 * pow(maxWaves, 3)) * pow(x, 3) + 3 * maxZombies / (4 * pow(maxWaves, 2)) * pow(x, 2) + numStartingZombies;
}

void SpawningZombiesState::Update()
{
	m_timeUntilNextZombieSpawn -= Shadow::Time::Instance()->GetDeltaTime();

	if (m_timeUntilNextZombieSpawn <= 0.0f)
	{
		m_timeUntilNextZombieSpawn = m_timeBewtweenZombieSpawns;

		ZombieManager::Instance()->SpawnZombie();
		m_waveCurrentZombies++;

		if (m_waveCurrentZombies == m_waveMaxZombies)
			GameStateManager::Instance()->NextState();
	}
}

void SpawningZombiesState::OnStateExit()
{
	// Empty.
}