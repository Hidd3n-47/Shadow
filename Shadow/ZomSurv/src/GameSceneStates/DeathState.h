#pragma once

#include "ZomSurv/src/GameStates/IGameState.h"

class DeathState : public IGameState
{
public:
	DeathState(Shadow::Window* window, Shadow::Camera* camera) { m_pScene = Shadow::SceneManager::Instance()->CreateEmptyScene("Death", window, camera); }

	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;

private:
	Shadow::Scene* m_pScene = nullptr;
	uint16_t m_fontId = 0;
};

