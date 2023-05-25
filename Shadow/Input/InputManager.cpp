#include "sdpch.h"
#include "InputManager.h"

#include "Engine/Engine.h"

SHADOW_NAMESPACE_BEGIN

InputManager* InputManager::m_pInstance = nullptr;

void InputManager::Listen()
{
	m_leftMouseReleased = false;
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Engine::Instance()->StopRunning();
			break;
		case SDL_KEYDOWN:
			KeyDown(e.key.keysym.sym);
			break;
		case SDL_KEYUP:
			KeyUp(e.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			KeyDown(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			KeyUp(e.button.button);

			if (e.button.button == BUTTON_LEFT)
				m_leftMouseReleased = true;
			break;
		default:
			break;
		}
	}
}

bool InputManager::IsKeyDown(uint16_t keyId)
{
	auto it = m_keyMap.find(keyId);
	if (it != m_keyMap.end())
		return it->second;
	return false;
}

bool InputManager::IsMouseDown(uint8_t buttonId)
{
	auto it = m_keyMap.find(buttonId);
	if (it != m_keyMap.end())
		return it->second;
	return false;
}

glm::vec2 InputManager::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return { x, y };
}

void InputManager::KeyDown(uint16_t keyId)
{
	m_keyMap[keyId] = true;
}

void InputManager::KeyUp(uint16_t keyId)
{
	m_keyMap[keyId] = false;

	m_keyMap.erase(keyId);
}

void InputManager::MouseDown(uint8_t buttonId)
{
	m_keyMap[buttonId] = true;
}

void InputManager::MouseUp(uint8_t buttonId)
{
	m_keyMap[buttonId] = false;

	m_keyMap.erase(buttonId);
}

SHADOW_NAMESPACE_END