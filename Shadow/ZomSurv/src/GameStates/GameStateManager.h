#pragma once

#include "WaveDisplayState.h"
#include "PreWaveState.h"
#include "SpawningZombiesState.h"
#include "WaveBeingPlayedState.h"

enum class GameState
{
	WAVE_DISPLAY = 0,
	PRE_WAVE,
	SPAWNING_ZOMBIES,
	WAVE_BEING_PLAYED
	// WAVE_COMPLETED, // < DONT THINK i NEED THIS STATE.
};

class GameStateManager
{
public:
	inline static GameStateManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new GameStateManager() : m_pInstance; }
	
	inline void Update() { m_state->Update(); }

	void NextState();
private:
	GameStateManager();
	~GameStateManager();

	static GameStateManager* m_pInstance;

	GameState m_gameState = GameState::WAVE_DISPLAY;
	IGameState* m_state = nullptr;

	// State Instances.
	WaveDisplayState* m_waveDisplayState = nullptr;
	PreWaveState* m_preWaveState = nullptr;
	SpawningZombiesState* m_spawningZombiesState = nullptr;
	WaveBeingPlayedState* m_waveBeingPlayedState = nullptr;
	
	void ChangeState(IGameState* newState);
};

