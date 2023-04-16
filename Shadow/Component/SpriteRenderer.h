#pragma once

#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

class GameObject;

class SpriteRenderer : public IComponent
{
public:
	SpriteRenderer(GameObject* pOwner, std::string filePath);
	~SpriteRenderer() override;

	virtual void OnComponentAdd() override;
	virtual void Update() override;
	virtual void PhysicsUpdate() override { }
	virtual void Render(glm::vec3 worldPosition) override;
	virtual void OnComponentRemove() override;
private:
	GameObject* m_pOwner = nullptr;
	std::string m_filePath = "";
	uint16_t m_textureId = -1;
};

SHADOW_NAMESPACE_END