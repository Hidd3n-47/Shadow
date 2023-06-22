#pragma once

#include "IComponent.h"
#include "ICollisionMethods.h"
#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
CIRCLE_COLLIDER2D_COMPONENT:
	A component that can be attached to a GameObject.
	This component is responsible for creating a circle shape that will have collision.
	Circle collisions are not abstract, i.e. no circle triggers.

	For custom collision methods (events that occure when there is a collision is
	triggered, then can create a pointer to the collision methods.
=========================================================================================
*/
class CircleCollider2D : public IComponent
{
public:
	CircleCollider2D(GameObject* pOwner, float radius = 0.5f);
	~CircleCollider2D();

	virtual void OnComponentAdd() override;

	virtual void Update() override;
	virtual void PhysicsUpdate() override;

	virtual void Render(glm::vec3 worldPosition) override;

	virtual void OnComponentRemove() override;

	void OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject);

	// Accessors.
	inline float GetRadius() const { return m_radius; }

	// Mutators.
	inline void SetLastFramePosition(const glm::vec3& position) { m_lastFramePosition = position; }
	inline void SetCollisionMethods(ICollisionMethods* collisionMethods) { m_pCollisionMethods = collisionMethods; }
private:
	GameObject* m_pOwner = nullptr;
	ICollisionMethods* m_pCollisionMethods = nullptr;
	bool m_collisionEntered = false;
	bool m_static = false;
	float m_radius = 0.0f;
	glm::vec3 m_lastFramePosition = glm::vec3(0.0f);
};

SHADOW_NAMESPACE_END