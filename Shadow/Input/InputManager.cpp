#include "sdpch.h"
#include "InputManager.h"

#include "Engine/Engine.h"

SHADOW_NAMESPACE_BEGIN

InputManager* InputManager::m_pInstance = nullptr;

void InputManager::Listen()
{
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

void InputManager::KeyDown(uint16_t keyId)
{
	m_keyMap[keyId] = true;
}

void InputManager::KeyUp(uint16_t keyId)
{
	m_keyMap[keyId] = false;

	m_keyMap.erase(keyId);
}

SHADOW_NAMESPACE_END