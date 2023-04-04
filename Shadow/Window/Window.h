#include "sdpch.h"
#pragma once

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
WINDOW:
	Class to hold engines own window. 
	Window class contains a pointer to the Window as well as the dimensions of the window.
	Only the Window Manager can change the window.
=========================================================================================
*/
class Window
{
	friend class WindowManager;
public:
	/* 
		\brief Get the renderer associated with the window.
	*/
	inline SDL_Renderer* GetRenderer() { return m_pRenderer; }
	/*
		\brief Get the ID of the window.
	*/
	inline uint8_t GetId() const { return m_id; }
private:
	Window() { }
	Window(const std::string& name, int width, int height) : m_name(name), m_width(width), m_height(height) { /* Empty. */ }
	~Window() { }

	// Window Properties.
	std::string m_name = "";
	int m_width = 0;
	int m_height = 0;
	uint8_t m_id = -1;

	// The SDL window and renderer.
	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	/*
		\brief Sets up the window properties.
		\param name: name of the window.
		\param width: width of the window.
		\param height: height of the window.
	*/
	inline void SetWindowProperties(const std::string& name, int width, int height) { m_name = name; m_width = width, m_height = height; }

	/*
		\brief Sets up the windows dimensions.
		\param width: width of the window.
		\param height: height of the window.
	*/
	inline void SetWindowDimensions(int width, int height) { m_width = width; m_height = height; }
};

SHADOW_NAMESPACE_END