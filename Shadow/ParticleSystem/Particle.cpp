#include "sdpch.h"
#include "Particle.h"

#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

Particle::Particle(const glm::vec2& position, const glm::vec2& direction, const glm::vec2& scale, float velocity, float friction) :
	m_position(position),
	m_direction(direction),
	m_scale(scale),
	m_velocity(velocity),
	m_friction(friction)
{
	// Empty
}

void Particle::Update()
{
	m_position += m_direction * m_velocity * Time::Instance()->GetDeltaTime();

	m_velocity = m_velocity < m_friction ? 0.0f : m_velocity - m_friction * Time::Instance()->GetDeltaTime();
}

SHADOW_NAMESPACE_END