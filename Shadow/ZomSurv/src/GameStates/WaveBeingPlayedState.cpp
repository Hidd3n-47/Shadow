#include "sdpch.h"
#include "WaveBeingPlayedState.h"

#include "GameStateManager.h"
#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/src/ZombieManager.h"

void WaveBeingPlayedState::OnStateEnter()
{
	// Empty.
}

void WaveBeingPlayedState::Update()
{
	if(ZombieManager::Instance()->GetNumZombies() <= 0)
		GameStateManager::Instance()->NextState();
}

void WaveBeingPlayedState::OnStateExit()
{
	GameManager::Instance()->IncrementWave();
}