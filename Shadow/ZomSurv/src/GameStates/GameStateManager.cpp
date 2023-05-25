#include "sdpch.h"
#include "GameStateManager.h"

GameStateManager* GameStateManager::m_pInstance = nullptr;

GameStateManager::GameStateManager() :
	m_waveDisplayState(new WaveDisplayState()),
	m_preWaveState(new PreWaveState()),
	m_spawningZombiesState(new SpawningZombiesState()),
	m_waveBeingPlayedState(new WaveBeingPlayedState())
{
	m_state = m_waveDisplayState;

	m_state->OnStateEnter();
}

GameStateManager::~GameStateManager()
{
	// Delete the states.
	delete m_waveBeingPlayedState;
	delete m_spawningZombiesState;
	delete m_preWaveState;
	delete m_waveDisplayState;

	// Delete the instance of the manager.
	delete m_pInstance;
}

void GameStateManager::NextState()
{
	switch (m_gameState)
	{
	case GameState::WAVE_DISPLAY:
		m_gameState = GameState::PRE_WAVE;
		ChangeState(m_preWaveState);
		break;
	case GameState::PRE_WAVE:
		m_gameState = GameState::SPAWNING_ZOMBIES;
		ChangeState(m_spawningZombiesState);
		break;
	case GameState::SPAWNING_ZOMBIES:
		m_gameState = GameState::WAVE_BEING_PLAYED;
		ChangeState(m_waveBeingPlayedState);
		break;
	case GameState::WAVE_BEING_PLAYED:
		m_gameState = GameState::WAVE_DISPLAY;
		ChangeState(m_waveDisplayState);
		break;
	}
}

void GameStateManager::ChangeState(IGameState* newState)
{
	m_state->OnStateExit();
	m_state = newState;
	m_state->OnStateEnter();
}