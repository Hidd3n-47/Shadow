#pragma once

#include "IComponent.h"

SHADOW_NAMESPACE_BEGIN

class GameObject;

class SpriteRenderer : public IComponent
{
public:
	SpriteRenderer(GameObject* pOwner, std::string filePath);
	SpriteRenderer(GameObject* pOwner, uint16_t textureId);
	SpriteRenderer(GameObject* pOwner, const std::string& filePath, const glm::vec2& dimentions, const glm::vec2& screenPosition = glm::vec2(0.0f), bool staticSprite = false);
	~SpriteRenderer() override;

	virtual void OnComponentAdd() override;
	virtual void Update() override;
	virtual void PhysicsUpdate() override { }
	virtual void Render(glm::vec3 worldPosition) override;
	virtual void OnComponentRemove() override;

	// Accessor.
	inline uint16_t GetTextureId() const { return m_textureId; }

	// Mutator.
	inline void SetDimensions(const glm::vec2& dims) { m_dimensions = dims; }
private:
	GameObject* m_pOwner = nullptr;

	uint16_t m_textureId = 0;
	bool m_loadTexture = true;
	bool m_staticSprite = false;
	glm::vec2 m_dimensions = glm::vec2(TILE_WIDTH);
	glm::vec2 m_screenPosition = glm::vec2(0.0f);
};

SHADOW_NAMESPACE_END