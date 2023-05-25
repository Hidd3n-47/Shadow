#include "sdpch.h"
#include "Hud.h"

#include "Graphics/FontManager.h"

#include "ZomSurv/src/GameManager.h"

Hud* Hud::m_pInstance = nullptr;

Hud::Hud()
{
	// Empty.
}

void Hud::Init(uint8_t wave, unsigned int score)
{
	m_waveFont = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", WAVE_FONT_SIZE, std::to_string(wave), Color(White), WAVE_POS);
	m_playerScoreFont = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", SCORE_FONT_SIZE, std::to_string(score), Color(Red), SCORE_POS);
	m_reloadPrompt = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", RELOAD_FONT_SIZE, "Press 'R' to reload", Color(Black), glm::vec2(-100.0f));
	m_reloading = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", RELOAD_FONT_SIZE, "Reloading", Color(Black), glm::vec2(-100.0f));

	int width, height;
	Shadow::FontManager::Instance()->GetWidthAndHeightOfFont(m_reloadPrompt, width, height);
	m_reloadingDimentions = glm::vec2(width * 0.5f - 16, height * 0.5f);
	Shadow::FontManager::Instance()->GetWidthAndHeightOfFont(m_reloading, width, height);
	m_reloadingDimentions = glm::vec2(width * 0.5f - 16, height * 0.5f);

	float w, h;
	Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetWidthAndHeight(w, h);
	m_cameraExtentDimentions = glm::vec2(w * 0.5f, h * 0.5f);

	UpdateAmmo();
}

void Hud::Destroy()
{
	Shadow::FontManager::Instance()->DeleteFont(m_waveFont);
	Shadow::FontManager::Instance()->DeleteFont(m_playerScoreFont);
	Shadow::FontManager::Instance()->DeleteFont(m_ammoFont);

	delete m_pInstance;
}

void Hud::UpdateWave(uint8_t wave)
{
	Shadow::FontManager::Instance()->DeleteFont(m_waveFont);
	m_waveFont = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", WAVE_FONT_SIZE, std::to_string(wave), Color(White), WAVE_POS);
}

void Hud::UpdatePlayerScore(unsigned int score)
{
	Shadow::FontManager::Instance()->DeleteFont(m_playerScoreFont);
	m_playerScoreFont = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", SCORE_FONT_SIZE, std::to_string(score), Color(Red), SCORE_POS);
}

void Hud::UpdateAmmo()
{
	std::string ammoStr = "";

	std::pair<unsigned short, unsigned short> ammo = GameManager::Instance()->GetGunAmmo();

	ammoStr += std::to_string(ammo.first) + "/" + std::to_string(ammo.second);

	if(m_ammoFontCreated)
		Shadow::FontManager::Instance()->DeleteFont(m_ammoFont);

	m_ammoFont = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", AMMO_FONT_SIZE, ammoStr, Color(Red), AMMO_POS);

	m_ammoFontCreated = true;
}

void Hud::DisplayReloadingUpdate(uint16_t fontId, bool display, const glm::vec2& offset)
{
	if (!display)
	{
		Shadow::FontManager::Instance()->UpdateFont(fontId, glm::vec2(-100.0f));
		return;
	}

	glm::vec2 camPosition = Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetPosition();
	Shadow::FontManager::Instance()->UpdateFont(fontId,  m_cameraExtentDimentions + RELOAD_OFFSET - offset);
}