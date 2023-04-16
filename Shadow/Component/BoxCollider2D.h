#pragma once

#include "IComponent.h"
#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

class BoxCollider2D : public IComponent
{
public:
	BoxCollider2D(GameObject* pOwner, glm::vec2 halfExtent, bool trigger);
	BoxCollider2D(GameObject* pOwner, bool trigger);
	BoxCollider2D(GameObject* pOwner, glm::vec2 halfExtent);
	BoxCollider2D(GameObject* pOwner);
	~BoxCollider2D() override { }

	virtual void OnComponentAdd() override;

	virtual void Update() override;
	virtual void PhysicsUpdate() override;

	virtual void Render(glm::vec3 worldPosition) override;

	void Trigger();

	void OnTriggerEnter();
	void OnTriggerStay();
	void OnTriggerExit();

	virtual void OnComponentRemove() override;

	// Accessor.
	//SDL_Rect GetBoxCollider() const { return m_boxCollider; }
	inline glm::vec2 GetSize() const { return m_size; }
	inline bool GetIsTrigger() const { return m_trigger; }

	// Mutators.
	inline void SetLastFramePosition(const glm::vec3& position) { m_lastFramePosition = position; }
private:
	GameObject* m_pOwner = nullptr;
	glm::vec2 m_offset = glm::vec2(0.0f);
	glm::vec2 m_size = glm::vec2({ 0.5f, 0.5f });
	bool m_static = false;
	bool m_trigger = false;
	bool m_triggered = false;
	bool m_calledThisFrame = false;
	glm::vec3 m_lastFramePosition;

	/*float m_density = 1.0f;
	float m_friction = 0.5f;
	float m_restitution = 0.0f;
	float m_restitutionThreshold = 0.5f;*/

	//glm::vec2 m_dimensions;
	//SDL_Rect m_boxCollider;
};

SHADOW_NAMESPACE_END