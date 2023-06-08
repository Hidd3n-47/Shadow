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

	// Game Object Creation.
	Shadow::Scene* pScene = Shadow::SceneManager::Instance()->GetActiveScene();

	m_pHealthBar	= pScene->CreateEmptyGameObject("HealthBar");
	m_pHealth		= pScene->CreateEmptyGameObject("Health");
	m_pInstaKill	= pScene->CreateEmptyGameObject("InstaKillShield");
	m_pDoublePoints	= pScene->CreateEmptyGameObject("DoublePointsShield");
	m_pQuickRevive	= pScene->CreateEmptyGameObject("QuickRevive");
	m_pDoubleTap	= pScene->CreateEmptyGameObject("DoubleTap");
	m_pSpeedCola	= pScene->CreateEmptyGameObject("SpeedCola");
	m_pJug			= pScene->CreateEmptyGameObject("Jug");

	// Adding Sprite Renderers.
	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(m_pHealthBar, "Assets/healthBar.png", HEALTH_BAR_DIMENTIONS, glm::vec2(-HEALTH_BAR_DIMENTIONS.x * 0.5f, m_cameraExtentDimentions.y - 60.0f), true);
	m_pHealthBar->AddComponent(sr);

	m_pHealthSpriteRenderer = new Shadow::SpriteRenderer(m_pHealth, "Assets/health.png", HEALTH_BAR_DIMENTIONS, glm::vec2(-HEALTH_BAR_DIMENTIONS.x * 0.5f, m_cameraExtentDimentions.y - 60.0f), true);
	m_pHealth->AddComponent(m_pHealthSpriteRenderer);

	sr = new Shadow::SpriteRenderer(m_pInstaKill, "Assets/Environment/PerkMachines/instaKillShield.png", PERK_PROMPT, glm::vec2(-PERK_PROMPT.x - 5.0f, -m_cameraExtentDimentions.y + 5.0f), true);
	m_pInstaKill->AddComponent(sr);

	sr = new Shadow::SpriteRenderer(m_pDoublePoints, "Assets/Environment/PerkMachines/doublePointsShield.png", PERK_PROMPT, glm::vec2(5.0f, -m_cameraExtentDimentions.y + 5.0f), true);
	m_pDoublePoints->AddComponent(sr);

	sr = new Shadow::SpriteRenderer(m_pQuickRevive, "Assets/Environment/PerkMachines/quickReviveSym.png", PERK_PROMPT, glm::vec2(-(PERK_PROMPT.x + 5.0f) * 2.0f, m_cameraExtentDimentions.y - 110.0f), true);
	m_pQuickRevive->AddComponent(sr);

	sr = new Shadow::SpriteRenderer(m_pDoubleTap, "Assets/Environment/PerkMachines/doubleTapSym.png", PERK_PROMPT, glm::vec2(-PERK_PROMPT.x - 5.0f, m_cameraExtentDimentions.y - 110.0f), true);
	m_pDoubleTap->AddComponent(sr);

	sr = new Shadow::SpriteRenderer(m_pSpeedCola, "Assets/Environment/PerkMachines/speedColaSym.png", PERK_PROMPT, glm::vec2(5.0f, m_cameraExtentDimentions.y - 110.0f), true);
	m_pSpeedCola->AddComponent(sr);

	sr = new Shadow::SpriteRenderer(m_pJug, "Assets/Environment/PerkMachines/jugSym.png", PERK_PROMPT, glm::vec2(10.0f + PERK_PROMPT.x, m_cameraExtentDimentions.y - 110.0f), true);
	m_pJug->AddComponent(sr);

	m_pInstaKill->SetIsActive(false);
	m_pDoublePoints->SetIsActive(false);
	m_pQuickRevive->SetIsActive(false);
	m_pDoubleTap->SetIsActive(false);
	m_pSpeedCola->SetIsActive(false);
	m_pJug->SetIsActive(false);

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

void Hud::UpdateHealthBar(float health, float maxHealth)
{
	const glm::vec2 healthBarDims = { 160.0f, 50.0f };

	float percent = health / maxHealth;

	int width = (int)(healthBarDims.x * percent);

	m_pHealthSpriteRenderer->SetDimensions({ width, healthBarDims.y });
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