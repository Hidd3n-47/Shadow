#pragma once

#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
ANIMATION_COMPONENT:
	A component that can be attached to a GameObject. 
	This component is responsible for loading in a sprite sheet and playing the
	animation during run time.

	The animcation can be paused and reset (to the first index).
=========================================================================================
*/
class Animation : public IComponent
{
public:
	Animation(GameObject* pOwner, const std::string& filePath, int numberFrames, const glm::vec2& spriteDimensions, float timeBetween);
	~Animation() { }

	virtual void OnComponentAdd() override;
	virtual void Update() override;
	virtual void PhysicsUpdate() override { }
	virtual void Render(glm::vec3 worldPosition) override;
	virtual void OnComponentRemove() override;

	inline void Pause() { m_paused = true; }
	inline void Resume() { m_paused = false; }
	inline void Reset() { m_textureIndex = 0; }

private:
	GameObject* m_pOwner = nullptr;

	const glm::vec2 SPRITE_DIMENSIONS;
	const float TIME_BETWEEN;

	uint16_t m_textureId = 0;
	int m_textureIndex = 0;
	int m_numTextures = 0;
	float m_timer = 0.0f;
	bool m_paused = false;
};

SHADOW_NAMESPACE_END