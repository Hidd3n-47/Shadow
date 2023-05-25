#pragma once

#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

class GameObject;

class SpriteRenderer : public IComponent
{
public:
	SpriteRenderer(GameObject* pOwner, std::string filePath);
	SpriteRenderer(GameObject* pOwner, uint16_t textureId);
	~SpriteRenderer() override;

	virtual void OnComponentAdd() override;
	virtual void Update() override;
	virtual void PhysicsUpdate() override { }
	virtual void Render(glm::vec3 worldPosition) override;
	virtual void OnComponentRemove() override;

	// Accessor.
	inline uint16_t GetTextureId() const { return m_textureId; }
private:
	GameObject* m_pOwner = nullptr;
	std::string m_filePath = "";
	uint16_t m_textureId = 0;
	bool m_loadTexture = true;
};

SHADOW_NAMESPACE_END