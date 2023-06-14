#pragma once

#include "Particle.h"

SHADOW_NAMESPACE_BEGIN

class ParticleEffect
{
public:
	ParticleEffect(Scene* pScene, const std::string& spriteFilePath, const glm::vec2& spriteDimensions, const glm::vec2& position, const glm::vec2& direction,
		float velocity, float friction, float lifeTime, short numParticles);
	~ParticleEffect();

	bool Update();
	void Render();

	// Accessor.
	inline short GetNumParticles() const { return m_numParticles; }
private:
	Scene* m_pScene = nullptr;

	uint16_t m_textureId;
	glm::vec2 m_textureDimensions;
	glm::vec2 m_position;
	float m_maxLifeSpan;
	float m_lifeTime;
	short m_numParticles;

	std::vector<Particle*> m_particles;
};

SHADOW_NAMESPACE_END