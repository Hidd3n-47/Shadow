#include "sdpch.h"
#include "DeathState.h"

#include "Graphics/FontManager.h"

void DeathState::OnStateEnter()
{
	Shadow::SceneManager::Instance()->SetActiveScene(m_pScene);
	Shadow::FontManager::Instance()->DeleteAllFonts();

	float width, height;
	m_pScene->GetCamera()->GetWidthAndHeight(width, height);

	glm::vec2 position(width * 0.5f, height * 0.5f);

	m_fontId = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 75, "You Died!", Color(Black), position);

	int w, h;

	Shadow::FontManager::Instance()->GetWidthAndHeightOfFont(m_fontId, w, h);

	position -= glm::vec2(w >> 1, h >> 1);

	Shadow::FontManager::Instance()->UpdateFont(m_fontId, position);
}

void DeathState::Update()
{
	// Empty.
}

void DeathState::OnStateExit()
{
	Shadow::FontManager::Instance()->DeleteFont(m_fontId);
}