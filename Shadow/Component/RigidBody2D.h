#pragma once

#include "GameObject/GameObject.h"
#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
RIGID_BODY2D_COMPONENT:
	A component that can be attached to a GameObject.
	This component is responsible for creating a game object that has a 2D rigid
	body. This means that the object is affected by physics.

	(A full force based system needs to be implemented).
=========================================================================================
*/
class RigidBody2D : public IComponent
{
public:
	enum class BodyType { Static = 0, Dynamic, Kinematic };

public:
	RigidBody2D(GameObject* pOwner, BodyType bodyType);
	~RigidBody2D() override {  }

	virtual void OnComponentAdd() override;

	virtual void Update() override { }
	virtual void PhysicsUpdate() override;

	virtual void Render(glm::vec3 worldPosition) override { } //< ADDITION could use this to render the directions in debug mode.

	virtual void OnComponentRemove() override;

	void Translate(glm::vec3 direction);

	/*inline void AddForce(glm::vec3 force) { m_netForce += force; }
	inline void ResetAll() { m_netForce = { 0.0f, 0.0f, 0.0f }; m_velocity = { 0.0f, 0.0f, 0.0f }; }*/

	// Accessors.
	inline BodyType GetBodyType() { return m_type; }
	/*inline glm::vec3 GetNetForce() { return m_netForce; }
	inline bool GetFixedRotation() { return m_fixedRotation; }*/
private:
	GameObject* m_pOwner = nullptr;
	BodyType m_type = BodyType::Static;

	/*glm::vec3 m_netForce = glm::vec3(0.0f);
	glm::vec3 m_acceleration = glm::vec3(0.0f);
	glm::vec3 m_velocity = glm::vec3(0.0f);*/

	float m_mass = 0.50f;
};

SHADOW_NAMESPACE_END