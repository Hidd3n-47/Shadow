#include "sdpch.h"
#include "LoadingState.h"

#include <thread>

#include "Time/Time.h"
#include "Graphics/FontManager.h"

#include "ZomSurv/Level/LevelManager.h"
#include "ZomSurv/src/GameManager.h"

Shadow::Scene* LoadingState::m_pPlayingScene = nullptr;
bool LoadingState::m_loaded = false;

LoadingState::LoadingState(Shadow::Window* window, Shadow::Camera* camera, Shadow::Scene* playingScene)
{
	m_pPlayingScene = playingScene;

	m_pScene = Shadow::SceneManager::Instance()->CreateEmptyScene("Loading", window, camera);
}

void LoadingState::OnStateEnter()
{
	Shadow::SceneManager::Instance()->SetActiveScene(m_pScene);

	int width = Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetWidth();
	int height = Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetHeight();
	position = { width >> 1, height >> 1 };

	m_loading = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 50, "Loading.", Color(White), position);

	int w, h;
	Shadow::FontManager::Instance()->GetWidthAndHeightOfFont(m_loading, w, h);
	position += glm::vec2(-w >> 1, -h >> 1);
	Shadow::FontManager::Instance()->UpdateFont(m_loading, position);


	//m_loading2 = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 50, "Loading..", Color(White), position);
	//m_loading3 = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 50, "Loading...", Color(White), position);

	m_timer = MAX_TIME;

	LevelManager::Instance()->LoadMap(Level::MAP1, m_pPlayingScene);
	m_loaded = true;

	/*std::future<void> future = std::async(std::launch::async, Loading);
	m_future = std::move(future);*/
	//std::thread m_loadingThread(Loading);
}

void LoadingState::Update()
{
	GameManager::Instance()->ChangeSceneState(GameSceneState::PLAYING);

	/*if (m_future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		Shadow::DLOG("Test")
		GameManager::Instance()->ChangeSceneState(GameSceneState::PLAYING);
		return;
	}*/

	////m_loading = false;
	////auto future = std::async(std::launch::async, Loading);
	//while (!m_loaded)
	//{

		/*m_timer -= Shadow::Time::Instance()->GetDeltaTime();

		if (m_timer <= 0)
		{
			m_animationIndex = (m_animationIndex + 1) % 3;
			Shadow::FontManager::Instance()->DeleteFont(m_loading);
			m_loading = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 50, m_text[m_animationIndex], Color(White), position);
			Shadow::FontManager::Instance()->UpdateFont(m_loading, m_text[m_animationIndex]);

			m_timer = MAX_TIME;
		}*/

	//}
}

void LoadingState::OnStateExit()
{
	Shadow::FontManager::Instance()->DeleteFont(m_loading);
}

void LoadingState::Loading()
{
	LevelManager::Instance()->LoadMap(Level::MAP1, m_pPlayingScene);
	m_loaded = true;

	//m_timer -= Shadow::Time::Instance()->GetDeltaTime();

	//if (m_timer <= 0)
	//{
	//	m_animationIndex = (m_animationIndex + 1) % 3;
	//	Shadow::FontManager::Instance()->DeleteFont(m_loading);
	//	m_loading = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 50, m_text[m_animationIndex], Color(White), position);
	//	//Shadow::FontManager::Instance()->UpdateFont(m_loading, m_text[m_animationIndex]);

	//	m_timer = MAX_TIME;
	//}
}