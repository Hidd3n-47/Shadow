#pragma once

#include "GameObject/GameObject.h"
#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

class RigidBody2D : public IComponent
{
public:
	RigidBody2D(GameObject* pOwner, bool affectedByGravity = false);
	~RigidBody2D() override { }

	virtual void OnComponentAdd() override;

	virtual void Update() override;

	virtual void Render(glm::vec3 worldPosition) override { } // ADDITION could use this to render the directions in debug mode

	virtual void OnComponentRemove() override;

	inline void AddForce(glm::vec3 force) { m_netForce += force; }
	inline void ResetAll() { m_netForce = { 0.0f, 0.0f, 0.0f }; m_velocity = { 0.0f, 0.0f, 0.0f }; }
private:
	GameObject* m_pOwner = nullptr;

	glm::vec3 m_netForce;
	glm::vec3 m_acceleration;
	glm::vec3 m_velocity;

	bool m_affectedByGravity = false;
	float m_mass = 0.1f;
};

SHADOW_NAMESPACE_END