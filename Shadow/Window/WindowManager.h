#include "sdpch.h"
#pragma once

#include "Window.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
WINDOW_MANAGER:
	WindowManager is a class to manage the engines different engine.
	The main window will be the first element in the windows list.
	Use Destroy method to manually destroy the instance of the singleton.
=========================================================================================
*/
class WindowManager
{
public:
	inline static WindowManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new WindowManager : m_pInstance; }
	
	Window* CreateWindow(const std::string& title, int width, int height);

	void DestroyWindow(Window* pWindow);
	void DestoryWindow(uint8_t winId);

	void Destroy();

	inline Window* GetMainWindow() const { return m_windows.front(); }
private:
	WindowManager() {}
	~WindowManager() { }

	static WindowManager* m_pInstance;

	uint8_t m_id = 0;
	std::list<Window*> m_windows;
};

SHADOW_NAMESPACE_END