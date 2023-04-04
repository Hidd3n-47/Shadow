#pragma once

#include "IComponent.h"
#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

class BoxCollider2D : public IComponent
{
public:
	BoxCollider2D(GameObject* pOwner, glm::vec2 position, glm::vec2 dimensions);
	~BoxCollider2D() override { }

	virtual void OnComponentAdd() override;

	virtual void Update() override;

	virtual void Render(glm::vec3 worldPosition) override;

	virtual void OnComponentRemove() override;

	// Accessor.
	//SDL_Rect GetBoxCollider() const { return m_boxCollider; }
	inline glm::vec2 GetDimension() const { return m_dimensions; }
private:
	GameObject* m_pOwner;
	glm::vec2 m_dimensions;
	//SDL_Rect m_boxCollider;
};

SHADOW_NAMESPACE_END