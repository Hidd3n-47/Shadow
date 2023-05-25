#include "sdpch.h"
#include "PreWaveState.h"

#include "GameStateManager.h"
#include "Time/Time.h"

void PreWaveState::OnStateEnter()
{
	m_timeUntilNextWave = m_timeBetweenWaves;
}

void PreWaveState::Update()
{
	m_timeUntilNextWave -= Shadow::Time::Instance()->GetDeltaTime();

	if (m_timeUntilNextWave <= 0.0f)
		GameStateManager::Instance()->NextState();
}

void PreWaveState::OnStateExit()
{
	// Empty.
}
