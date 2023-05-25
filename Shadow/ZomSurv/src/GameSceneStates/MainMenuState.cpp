#include "sdpch.h"
#include "MainMenuState.h"

#include "Input/InputManager.h"
#include "Graphics/TextureManager.h"

#include "ZomSurv/src/GameManager.h"

void MainMenuState::OnStateEnter()
{
	Shadow::SceneManager::Instance()->SetActiveScene(m_pScene);

	glm::vec2 position = { 100, 50 };
	m_buttons[0] = Shadow::Button(0, position, 50, "Play", Color(Black), Color(Blue));

	position = { 100, 125 };
	m_buttons[1] = Shadow::Button(1, position, 50, "Quit", Color(Black), Color(Blue));

	Shadow::Audio::Instance()->PlayMusic(GameManager::Instance()->GetMusicId());
}

void MainMenuState::Update()
{
	bool mousePressed = Shadow::InputManager::Instance()->IsMouseDown(Shadow::BUTTON_LEFT);
	glm::vec2 mousePosition = Shadow::InputManager::Instance()->GetMousePosition();

	for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
		if (it->second.Update(mousePosition, mousePressed))
		{
			ButtonPressed(it->second.GetButtonId());
			return;
		}
}

void MainMenuState::OnStateExit()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); it++)
		it->second.DestroyButton();

	m_buttons.clear();

	Shadow::Audio::Instance()->PauseMusic();

}

void MainMenuState::ButtonPressed(short buttonId)
{
	switch (buttonId)
	{
	case 0:
		PlayPressed();
		break;
	case 1:
		QuitPressed();
		break;
	default:
		Shadow::Log::Instance()->Warning("Button pressed in Main Menu that was not handled.");
		break;
	}
}

void MainMenuState::PlayPressed()
{
	GameManager::Instance()->ChangeSceneState(GameSceneState::LOADING);
}

void MainMenuState::QuitPressed()
{
	GameManager::Instance()->ChangeSceneState(GameSceneState::QUIT);
}