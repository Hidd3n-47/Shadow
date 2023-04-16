#pragma once

#include "IComponent.h"
#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

class CircleCollider2D : public IComponent
{
public:
	CircleCollider2D(GameObject* pOwner, float radius = 0.5f);

	virtual void OnComponentAdd() override;

	virtual void Update() override;
	virtual void PhysicsUpdate() override;

	virtual void Render(glm::vec3 worldPosition) override;

	virtual void OnComponentRemove() override;

	// Accessors.
	inline float GetRadius() const { return m_radius; }

	// Mutators.
	inline void SetLastFramePosition(const glm::vec3& position) { m_lastFramePosition = position; }
private:
	GameObject* m_pOwner = nullptr;
	bool m_static = false;
	float m_radius = 0.0f;
	glm::vec3 m_lastFramePosition = glm::vec3(0.0f);
};

SHADOW_NAMESPACE_END