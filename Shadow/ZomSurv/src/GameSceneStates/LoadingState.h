#pragma once

#include <future>

#include "ZomSurv/src/GameStates/IGameState.h"

class LoadingState : public IGameState
{
public:
	LoadingState(Shadow::Window* window, Shadow::Camera* camera, Shadow::Scene* playingScene);
	~LoadingState() { Shadow::SceneManager::Instance()->DestroyScene(m_pScene); }

	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;

private:
	Shadow::Scene* m_pScene = nullptr;
	static Shadow::Scene* m_pPlayingScene;

	uint16_t m_loading = 0;
	//uint16_t m_loading2 = 0;
	//uint16_t m_loading3 = 0;

	static bool m_loaded;

	const float MAX_TIME = 1.0f;
	float m_timer = 0.0f;
	short m_animationIndex = 0;
	std::string m_text[3] = { "Loading.", "Loading..", "Loading..." };

	//std::future<void> m_future;
	//std::thread m_loadingThread;

	static void Loading();
	glm::vec2 position;
};

