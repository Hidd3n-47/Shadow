#include "sdpch.h"
#include "DeathState.h"

#include "Audio/Audio.h"
#include "Component/SpriteRenderer.h"
#include "Graphics/FontManager.h"

void DeathState::OnStateEnter()
{
	Shadow::SceneManager::Instance()->SetActiveScene(m_pScene);
	Shadow::FontManager::Instance()->DeleteAllFonts();
	
	m_musicId = Shadow::Audio::Instance()->LoadMusic("Assets/Music/death.mp3", 75);

	InitBackground();
}

void DeathState::Update()
{
	static bool playing = false;

	if (playing)
		return;

	Shadow::Audio::Instance()->PlayMusic(m_musicId);
	playing = true;
}

void DeathState::OnStateExit()
{
	Shadow::Audio::Instance()->DestroyMusic(m_musicId);
}

void DeathState::InitBackground()
{
	float width, height;
	m_pScene->GetCamera()->GetWidthAndHeight(width, height);

	m_pBg = m_pScene->CreateEmptyGameObject("deathBg");
	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(m_pBg, "Assets/deathScreen.png", glm::vec2(width, height), glm::vec2(-width * 0.5f, -height * 0.5f), true);
	m_pBg->AddComponent(sr);
}