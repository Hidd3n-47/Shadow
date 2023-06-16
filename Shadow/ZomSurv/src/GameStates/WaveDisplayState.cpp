#include "sdpch.h"
#include "WaveDisplayState.h"

#include "Scene/SceneManager.h"
#include "Graphics/FontManager.h"
#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/src/GameStates/GameStateManager.h"
#include "Time/Time.h"

void WaveDisplayState::OnStateEnter()
{
	int width = Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetWidth();
	int height = Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetHeight();

	int x = width >> 1;
	int y = height >> 1;
	m_fontId = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 75, "Wave " + std::to_string(GameManager::Instance()->GetWave()), Color(Red), {x	, y});
	int w, h;
	Shadow::FontManager::Instance()->GetWidthAndHeightOfFont(m_fontId, w, h);
	m_x = x + (-w >> 1);
	m_y = y + (-h >> 1);
	Shadow::FontManager::Instance()->TranslateFont(m_fontId, glm::vec2{ -w >> 1, - h >> 1 });

	m_timer = 0.0f;
}

void WaveDisplayState::Update()
{
	float dt = Shadow::Time::Instance()->GetDeltaTime();

	Shadow::FontManager::Instance()->UpdateFont(m_fontId, glm::vec2{ m_x,  m_y + 200 * glm::sin(m_timer / 2.5 * PI) });

	m_timer += dt;
	if (m_timer <= TIME_TO_DISPLAY)
		return;

	GameStateManager::Instance()->NextState();
}

void WaveDisplayState::OnStateExit()
{
	Shadow::FontManager::Instance()->DeleteFont(m_fontId);
}