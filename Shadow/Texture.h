#pragma once

#include <glm/glm.hpp>

SHADOW_NAMESPACE_BEGIN

struct Texture
{
public:
	Texture(uint16_t textureId, const glm::vec2& dimensions) : m_textureId(textureId), m_originalDimensions(dimensions) { }

	// Accessors.
	uint16_t GetTextureId() const { return m_textureId; }
	const glm::vec2& GetDimensions() { return m_originalDimensions; }
private:
	uint16_t m_textureId = 0;
	glm::vec2 m_originalDimensions = glm::vec2(0.0f);
};

SHADOW_NAMESPACE_END