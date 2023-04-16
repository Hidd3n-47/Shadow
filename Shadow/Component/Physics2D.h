#pragma once

#include "GameObject/GameObject.h"
#include <box2d/b2_body.h>

#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

class Physics2D : public IComponent
{
public:
	Physics2D(GameObject* pOwner, b2World* pWorld, glm::vec2 halfExtents = glm::vec2(0.5f, 0.5f), bool a = true);
	~Physics2D() { }

	virtual void OnComponentAdd() override;
	virtual void Update() override { }
	virtual void PhysicsUpdate() override;
	virtual void Render(glm::vec3 worldPosition) override;
	virtual void OnComponentRemove() override;
private:
	GameObject* m_pOwner = nullptr;
	b2Body* m_pBody = nullptr;
	b2World* m_pWorld = nullptr;
	glm::vec2 m_halfExtents;
	
	float m_density = 1.0f;
	float m_friction = 0.5f;
	float m_restitution = 0.0f;
	float m_restitutionThreshold = 0.5f;
	bool m_fixedRoation = false;
	bool b;
};

SHADOW_NAMESPACE_END