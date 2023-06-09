#pragma once

#include "IComponent.h"
#include "ITrigger.h"
#include "ICollisionMethods.h"
#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
BOX_COLLIDER2D_COMPONENT:
	A component that can be attached to a GameObject. 
	This component is responsible for creating a boxed shape that will have collision.
	Collision can either be abstract (such as triggers) or simulations such as 
	collision between other GameObjects with a Collision Component.

	For custom trigger or collision methods (events that occure when there is a 
	collision or a trigger is triggered, then can create a pointer to the collision or
	trigger methods.
=========================================================================================
*/
class BoxCollider2D : public IComponent
{
public:
	BoxCollider2D(GameObject* pOwner, glm::vec2 halfExtent, bool trigger);
	BoxCollider2D(GameObject* pOwner, bool trigger);
	BoxCollider2D(GameObject* pOwner, glm::vec2 halfExtent);
	BoxCollider2D(GameObject* pOwner);
	~BoxCollider2D() override;

	virtual void OnComponentAdd() override;

	virtual void Update() override;
	virtual void PhysicsUpdate() override;

	virtual void Render(glm::vec3 worldPosition) override;

	void Trigger(GameObject* thisCollider, GameObject* otherCollider);

	void OnTriggerEnter(GameObject* thisCollider, GameObject* otherCollider);
	void OnTriggerStay(GameObject* thisCollider, GameObject* otherCollider);
	void OnTriggerExit();
	void OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject);

	virtual void OnComponentRemove() override;

	// Accessor.
	inline glm::vec2 GetSize() const { return m_size; }
	inline bool GetIsTrigger() const { return m_trigger; }

	// Mutators.
	inline void SetLastFramePosition(const glm::vec3& position) { m_lastFramePosition = position; }
	inline void SetTriggerFunction(ITrigger* triggerFunctions) { m_pTriggerFunction = triggerFunctions; }
	inline void SetCollisionMethods(ICollisionMethods* collisionMethods) { m_pCollisionMethods = collisionMethods; }
private:
	GameObject* m_pOwner = nullptr;
	ITrigger* m_pTriggerFunction = nullptr;
	ICollisionMethods* m_pCollisionMethods = nullptr;
	glm::vec2 m_offset = glm::vec2(0.0f);
	glm::vec2 m_size = glm::vec2({ 0.5f, 0.5f });
	bool m_static = false;
	bool m_trigger = false;
	bool m_triggered = false;
	bool m_calledThisFrame = false;
	bool m_collisionEntered = false;
	glm::vec3 m_lastFramePosition;
};

SHADOW_NAMESPACE_END