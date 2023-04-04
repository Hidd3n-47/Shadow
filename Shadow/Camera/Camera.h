#pragma once

#include <glm/glm.hpp>

SHADOW_NAMESPACE_BEGIN

class Camera
{
public:
	Camera(glm::vec3 position, float width, float height);
	~Camera();

	void Update();

	// Accessors.
	inline glm::vec3 GetPostion() const { return m_position; }
	inline float GetWidth() const { return m_width; }
	inline float GetHeight() const { return m_height; }
	inline void GetWidthAndHeight(float& width, float& height) const { width = m_width; height = m_height; }

	// Mutators.
	inline void SetTargetPosition(glm::vec3& pTarget) { m_pTargetCenter = &pTarget; }
private:
	glm::vec3 m_position;
	glm::vec3* m_pTargetCenter = nullptr;
	float m_width;
	float m_height;
};

SHADOW_NAMESPACE_END