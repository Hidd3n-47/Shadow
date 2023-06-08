#pragma once

SHADOW_NAMESPACE_BEGIN

class Particle
{
	friend class ParticleEffect;
public:
	Particle(const glm::vec2& position, const glm::vec2& direction, const glm::vec2& scale, float velocity, float friction);
	~Particle() { }

	void Update();
private:
	glm::vec2 m_position;
	glm::vec2 m_direction;
	glm::vec2 m_scale;
	float m_velocity;
	float m_friction;
};

SHADOW_NAMESPACE_END