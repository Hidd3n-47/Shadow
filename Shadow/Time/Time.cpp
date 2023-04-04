#include "sdpch.h"
#include "Time.h"

Time* Time::m_pInstance = nullptr;

Time::Time() :
	m_maxFps(60.0f),
	m_targetFrameTime(1000.0f / m_maxFps),
	m_lastTime(0),
	m_deltaTime(0.0f)
{
	// Empty.
}

Time::~Time()
{
	delete m_pInstance;
}

void Time::Tick()
{
	Uint32 now = SDL_GetTicks();
	m_deltaTime = (now - m_lastTime) / 1000.0f;
	m_lastTime = now;

	if (m_targetFrameTime > m_deltaTime)
		SDL_Delay(m_targetFrameTime - m_deltaTime);
}