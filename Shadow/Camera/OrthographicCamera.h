#pragma once

#include <glm/glm.hpp>

SHADOW_NAMESPACE_BEGIN

class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);

	// Accessors.
	inline const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
	inline const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
	inline const glm::vec3& GetPosition() const { return m_position; }
	inline float GetRotation() const { return m_rotation; }

	// Mutators.
	inline void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
	inline void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }
private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_viewProjectionMatrix;

	glm::vec3 m_position;
	float m_rotation = 0.0f; // Rotation along the z-axis.

	void RecalculateViewMatrix();
};

SHADOW_NAMESPACE_END