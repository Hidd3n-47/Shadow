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

	void PlayStartingRoundAudio();
	void TurnPowerOn();

	inline bool PlayerPurchase(unsigned int cost) { return m_pPlayingState->PlayerPurchase(cost); }

	inline void AddZombieToHitCooldown(Shadow::GameObject* pZombie) { m_pPlayingState->AddZombieToHitCooldown(pZombie); }

	inline std::pair<unsigned short, unsigned short> GetGunAmmo() { return m_pPlayingState->GetGunAmmo(); }

	inline void IncrementWave() { m_wave++; Hud::Instance()->UpdateWave(m_wave); }
	inline void ActivateDoublePoints() { m_scoreMultiplier = 2.0f; m_doublePointsTimer = DOUBLE_POINTS_TIMER; }
	inline void PurchaseJug() { m_pPlayingState->PurchaseJug(); }
	inline void PurchaseSpeedCola() { m_speedCola = true; }
	inline float GetReloadMultiplier() { if (m_speedCola) return 2.0f; else return 1.0f; }
	inline void ResetPerkStats() { m_speedCola = false; m_quickRevive = false; }

	// Inline Sound effects.
	inline void PlayMaxAmmoSound()		{ Shadow::Audio::Instance()->PlaySound(m_maxAmmoAudio); }
	inline void PlayNukeSound()			{ Shadow::Audio::Instance()->PlaySound(m_nukeAudio); }
	inline void PlayInstaKillSound()	{ Shadow::Audio::Instance()->PlaySound(m_instaKillAudio); }
	inline void PlayDoublePointsSound() { Shadow::Audio::Instance()->PlaySound(m_doublePointsAudio); }
	inline void PlayPurchasSound()		{ Shadow::Audio::Instance()->PlaySound(m_purchasAudio); }

	// Accessors.
	inline uint8_t GetWave() const { return m_wave; }
	inline Shadow::Scene* GetScene() const { return m_pGameScene; }
	inline unsigned int GetPlayerScore() const { return m_pPlayingState->GetPlayerScore(); }
	inline glm::vec3 GetPlayerPosition() const { return m_pPlayingState->GetPlayerPosition(); }
	inline float GetPlayerRotation() const { return m_pPlayingState->GetPlayerRotation(); }
	inline Shadow::Scene* GetGameScene() const { return m_pGameScene; }
	inline bool GetPowerOn() const { return m_powerOn; }
	inline bool GetQuickRevive() const { return m_quickRevive; }

	// Mutators.
	inline void SetPlayerStartingPos(const glm::vec2& position) { m_pPlayingState->SetPlayerStartingPos(glm::vec3(position.x, position.y, 0.0f)); }
	inline void AddPlayerScore(unsigned int score) { m_pPlayingState->AddPlayerScore(m_scoreMultiplier * score); }
	inline void ActivateQuickRevive() { m_quickRevive = true; }
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
	
	bool m_powerOn = false;
	bool m_speedCola = false;
	bool m_quickRevive = false;

	// Audio ID's.
	uint16_t m_startingRoundAudio = 0;
	uint16_t m_maxAmmoAudio = 0;
	uint16_t m_nukeAudio = 0;
	uint16_t m_instaKillAudio = 0;
	uint16_t m_doublePointsAudio = 0;
	uint16_t m_powerAudio = 0;
	uint16_t m_purchasAudio = 0;
};

