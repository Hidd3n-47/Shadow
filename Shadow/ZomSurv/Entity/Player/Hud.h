#pragma once

#include "Component/SpriteRenderer.h"

class Hud
{
public:
	inline static Hud* Instance() { return m_pInstance == nullptr ? m_pInstance = new Hud() : m_pInstance; }

	void Init(uint8_t wave, unsigned int score);
	void Destroy();

	void UpdateWave(uint8_t wave);
	void UpdatePlayerScore(unsigned int score);
	void UpdateAmmo();
	void UpdateHealthBar(float health, float maxHealth);

	void ResetPerks();

	inline void DisplayReloadPrompt(bool display = false) { DisplayReloadingUpdate(m_reloadPrompt, display, m_reloadPromptDimentions); }
	inline void DisplayReloading(bool display = false) { DisplayReloadingUpdate(m_reloading, display, m_reloadingDimentions); }

	inline void SetInstaKillActive(bool active) { if(m_pInstaKill) m_pInstaKill->SetIsActive(active); }
	inline void SetDoublePointsActive(bool active) { if (m_pDoublePoints) m_pDoublePoints->SetIsActive(active); }
	inline void SetQuickReviveActive(bool active) { m_pQuickRevive->SetIsActive(active); }
	inline void SetDoubleTapActive(bool active) { m_pDoubleTap->SetIsActive(active); }
	inline void SetSpeedColaActive(bool active) { m_pSpeedCola->SetIsActive(active); }
	inline void SetJugActive(bool active) { m_pJug->SetIsActive(active); }

	inline bool GetQuickReviveActive() const { return m_pQuickRevive->GetIsActive(); }
private:
	Hud();
	~Hud() { }

	static Hud* m_pInstance;

	// Health Bar.
	Shadow::GameObject* m_pHealthBar = nullptr;
	Shadow::GameObject* m_pHealth = nullptr;
	Shadow::SpriteRenderer* m_pHealthSpriteRenderer = nullptr;

	// Perk Game Objects.
	Shadow::GameObject* m_pQuickRevive	= nullptr;
	Shadow::GameObject* m_pDoubleTap	= nullptr;
	Shadow::GameObject* m_pSpeedCola	= nullptr;
	Shadow::GameObject* m_pJug	= nullptr;

	// Pick Up Game Objects.
	Shadow::GameObject* m_pInstaKill	= nullptr;
	Shadow::GameObject* m_pDoublePoints	= nullptr;

	// Font id's.
	uint16_t m_waveFont			= 0;
	uint16_t m_playerScoreFont	= 0;
	uint16_t m_ammoFont			= 0;
	uint16_t m_reloadPrompt		= 0;
	uint16_t m_reloading		= 0;
	
	bool m_ammoFontCreated = false;

	// Constants.
	const glm::vec2 WAVE_POS	= {	 30, 700 };
	const glm::vec2 SCORE_POS	= { 930, 650 };
	const glm::vec2 AMMO_POS	= { 900, 700 };


	const glm::vec2 HEALTH_BAR_DIMENTIONS	= { 320.0f, 50.0f };
	const glm::vec2 RELOAD_OFFSET			= {   0.0f, 50.0f };
	const glm::vec2 PERK_PROMPT				= {  50.0f, 50.0f };
	glm::vec2 m_reloadPromptDimentions		= {   0.0f,  0.0f };
	glm::vec2 m_reloadingDimentions			= {   0.0f,  0.0f };   
	glm::vec2 m_cameraExtentDimentions		= {   0.0f,  0.0f };

	const short WAVE_FONT_SIZE		= 50;
	const short SCORE_FONT_SIZE		= 30;
	const short AMMO_FONT_SIZE		= 30;
	const short RELOAD_FONT_SIZE	= 16;

	void DisplayReloadingUpdate(uint16_t fontId, bool display, const glm::vec2& offset);
};

