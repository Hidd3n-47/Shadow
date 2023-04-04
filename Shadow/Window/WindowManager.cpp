#include "sdpch.h"
#include "WindowManager.h"

SHADOW_NAMESPACE_BEGIN

WindowManager* WindowManager::m_pInstance = nullptr;

Window* WindowManager::CreateWindow(const std::string& title, int width, int height)
{
	Window* win = new Window(title, width, height);
	win->m_id = m_id;
	win->m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	win->m_pRenderer = SDL_CreateRenderer(win->m_pWindow, m_id, 0);

	m_windows.push_back(win);

	m_id++;

	return win;
}

void WindowManager::DestroyWindow(Window* pWindow)
{
	DestoryWindow(pWindow->GetId());
}

void WindowManager::DestoryWindow(uint8_t winId)
{
	for (Window* win : m_windows)
	{
		if (win->GetId() != winId)
			continue;

		SDL_DestroyWindow(win->m_pWindow);
		SDL_DestroyRenderer(win->m_pRenderer);

		delete win;

		m_windows.remove(win);
		return;
	}
}

void WindowManager::Destroy()
{
	for (Window* win : m_windows)
	{
		SDL_DestroyRenderer(win->m_pRenderer);
		SDL_DestroyWindow(win->m_pWindow);

		delete win;
	}
	m_windows.clear();

	delete m_pInstance;
	m_pInstance = nullptr;
}

SHADOW_NAMESPACE_END