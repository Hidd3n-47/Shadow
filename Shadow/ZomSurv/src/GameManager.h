#pragma once

#include "Scene/SceneManager.h"
#include "Graphics/FontManager.h"

#include "ZomSurv/Entity/Player/Player.h"
#include "ZomSurv/src/GameSceneStates/MainMenuState.h"
#include "ZomSurv/src/GameSceneStates/LoadingState.h"
#include "ZomSurv/src/GameSceneStates/PlayingState.h"
#include "ZomSurv/src/GameSceneStates/DeathState.h"

#define DOUBLE_POINTS_TIMER_DEFAULT -69.47

enum class GameSceneState 
{
	MAIN_MENU,
	LOADING,
	PLAYING,
	DEAD,
	QUIT
};

class GameManager
{
public:
	inline static GameManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new GameManager() : m_pInstance; }

	void InitGame(Shadow::Scene* pScene);
	void Update();
	void DestroyGame();

	void ChangeSceneState(GameSceneState state);

	inline bool PlayerPurchase(unsigned int cost) { return m_pPlayingState->PlayerPurchase(cost); }

	inline void AddZombieToHitCooldown(Shadow::GameObject* pZombie) { m_pPlayingState->AddZombieToHitCooldown(pZombie); }

	inline std::pair<unsigned short, unsigned short> GetGunAmmo() { return m_pPlayingState->GetGunAmmo(); }

	inline void IncrementWave() { m_wave++; Hud::Instance()->UpdateWave(m_wave); }
	inline void ActivateDoublePoints() { m_scoreMultiplier = 2.0f; m_doublePointsTimer = DOUBLE_POINTS_TIMER; }
	inline void PurchaseJug() { m_pPlayingState->PurchaseJug(); }
	inline void PurchaseSpeedCola() { m_speedCola = true; }
	inline float GetReloadMultiplier() { if (m_speedCola) return 2.0f; else return 1.0f; }

	// Accessors.
	inline uint8_t GetWave() const { return m_wave; }
	inline Shadow::Scene* GetScene() const { return m_pGameScene; }
	inline unsigned int GetPlayerScore() const { return m_pPlayingState->GetPlayerScore(); }
	inline glm::vec3 GetPlayerPosition() const { return m_pPlayingState->GetPlayerPosition(); }
	inline Shadow::Scene* GetGameScene() const { return m_pGameScene; }
	inline Uint16 GetMusicId() const { return m_musicId; }

	// Mutators.
	inline void SetPlayerStartingPos(const glm::vec2& position) { m_pPlayingState->SetPlayerStartingPos(glm::vec3(position.x, position.y, 0.0f)); }
	inline void AddPlayerScore(unsigned int score) { m_pPlayingState->AddPlayerScore(m_scoreMultiplier * score); }
private:
	GameManager();
	~GameManager();

	static GameManager* m_pInstance;

	Shadow::Scene* m_pGameScene = nullptr;

	GameSceneState m_state			= GameSceneState::MAIN_MENU;
	IGameState* m_pCurrentState		= nullptr;
	MainMenuState* m_pMainMenuState = nullptr;
	LoadingState* m_pLoadingState	= nullptr;
	PlayingState* m_pPlayingState	= nullptr;
	DeathState* m_pDeathState		= nullptr;

	uint8_t m_wave = 1;

	glm::vec3 m_playerStartingPosition = glm::vec3(0.0f);

	const float DOUBLE_POINTS_TIMER = 10.0f;
	short m_scoreMultiplier = 1.0f;
	float m_doublePointsTimer = DOUBLE_POINTS_TIMER_DEFAULT;
	
	bool m_speedCola = false;

	Uint16 m_musicId = 0;

	void ResetTimers();
};
