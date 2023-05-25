#pragma once

#include "IGameState.h"

class WaveDisplayState : public IGameState
{
public:
	virtual void OnStateEnter() override;
	virtual void Update() override;
	virtual void OnStateExit() override;
private:
	const float TIME_TO_DISPLAY = 5.0f;
	const float SPEED = 0.6f;
	float m_timer = 0.0f;
	uint16_t m_fontId = 0;
};

