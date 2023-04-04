#include "sdpch.h"
#include "Camera.h"

SHADOW_NAMESPACE_BEGIN

Camera::Camera(glm::vec3 position, float width, float height) :
	m_position(position),
	m_width(width),
	m_height(height)
{
	// Empty.
}

Camera::~Camera()
{
	// Empty.
}

void Camera::Update()
{
	if (m_pTargetCenter != nullptr)
		m_position = *m_pTargetCenter;
}

SHADOW_NAMESPACE_END