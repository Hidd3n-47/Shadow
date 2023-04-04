#pragma once

#include <SDL/SDL.h>

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

	void Tick();

	// Accessors.
	inline float GetDeltaTime() const { return m_deltaTime; }

	// Mutators.
	inline void SetMaxFps(const float& maxFps) { m_maxFps = maxFps; m_targetFrameTime = 1000.0f / maxFps; }
private:
	Time();
	~Time();

	static Time* m_pInstance;

	// Private variables.
	float m_maxFps;
	float m_targetFrameTime;
	Uint32 m_lastTime;
	float m_deltaTime;
};

