#pragma once

#include "Graphics/Button.h"

#include "ZomSurv/src/GameStates/IGameState.h"

class MainMenuState : public IGameState
{
public:
	inline MainMenuState(Shadow::Window* window, Shadow::Camera* camera) { m_pScene = Shadow::SceneManager::Instance()->CreateEmptyScene("MainMenu", window, camera); }
	inline ~MainMenuState() { Shadow::SceneManager::Instance()->DestroyScene(m_pScene); }

	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;
private:
	Shadow::Scene* m_pScene = nullptr;
	std::unordered_map<short, Shadow::Button> m_buttons;

	uint16_t m_bg;

	void ButtonPressed(short buttonId);
	void PlayPressed();
	void QuitPressed();
};

