#pragma once

class Hud
{
public:
	inline static Hud* Instance() { return m_pInstance == nullptr ? m_pInstance = new Hud() : m_pInstance; }

	void Init(uint8_t wave, unsigned int score);
	void Destroy();

	void UpdateWave(uint8_t wave);
	void UpdatePlayerScore(unsigned int score);
	void UpdateAmmo();

	inline void DisplayReloadPrompt(bool display = false) { DisplayReloadingUpdate(m_reloadPrompt, display, m_reloadPromptDimentions); }
	inline void DisplayReloading(bool display = false) { DisplayReloadingUpdate(m_reloading, display, m_reloadingDimentions); }
private:
	Hud();
	~Hud() { }

	static Hud* m_pInstance;

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

	const glm::vec2 RELOAD_OFFSET		= { 0.0f, 50.0f };
	glm::vec2 m_reloadPromptDimentions	= { 0.0f,  0.0f };
	glm::vec2 m_reloadingDimentions		= { 0.0f,  0.0f };
	glm::vec2 m_cameraExtentDimentions	= { 0.0f,  0.0f };

	const short WAVE_FONT_SIZE		= 50;
	const short SCORE_FONT_SIZE		= 30;
	const short AMMO_FONT_SIZE		= 30;
	const short RELOAD_FONT_SIZE	= 16;

	void DisplayReloadingUpdate(uint16_t fontId, bool display, const glm::vec2& offset);
};

