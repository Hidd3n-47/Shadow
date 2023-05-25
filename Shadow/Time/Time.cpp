#include "sdpch.h"
#include "Time.h"

SHADOW_NAMESPACE_BEGIN

Time* Time::m_pInstance = nullptr;

Time::Time() :
	m_maxFps(60.0f),
	m_targetFrameTime(1.0f / m_maxFps),
	m_deltaTime(0.0f)
{
	// Empty.
}

Time::~Time()
{
	delete m_pInstance;
}

void Time::StartTick()
{
	m_start = SDL_GetPerformanceCounter();
}

void Time::EndTick()
{
	Uint64 now = SDL_GetPerformanceCounter();
	m_deltaTime = (now - m_start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	if (m_targetFrameTime > m_deltaTime)
		SDL_Delay(m_targetFrameTime - m_deltaTime);

	m_deltaTime /= 1000.0f;
}

void Time::Tick()
{
	m_deltaTime = (SDL_GetTicks() - m_lastTime) / 1000.0f;

	if (m_targetFrameTime > m_deltaTime)
		SDL_Delay((m_targetFrameTime - m_deltaTime) * 1000.0f);

	m_lastTime = SDL_GetTicks();
}

SHADOW_NAMESPACE_END