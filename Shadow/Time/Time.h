#pragma once

#include <SDL/SDL.h>

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
TIME:
	Time is a class to deal with the time of the engine.
=========================================================================================
*/
class Time
{
public:
	inline static Time* Instance() { return m_pInstance == nullptr ? m_pInstance = new Time() : m_pInstance; }

	void StartTick();
	void EndTick();
	void Tick();

	inline void TimerStart() { m_timerStart = SDL_GetTicks(); }
	inline Uint32 TimerStop() { return SDL_GetTicks() - m_timerStart; }

	// Accessors.
	inline float GetDeltaTime() const { return m_deltaTime; }

	// Mutators.
	inline void SetMaxFps(float maxFps) { m_maxFps = maxFps; m_targetFrameTime = 1.0f / maxFps; }
private:
	Time();
	~Time();

	static Time* m_pInstance;

	// Private variables.
	float m_maxFps;
	float m_targetFrameTime;
	float m_deltaTime;
	Uint32 m_lastTime; 
	Uint64 m_start;

	Uint32 m_timerStart;
};

SHADOW_NAMESPACE_END