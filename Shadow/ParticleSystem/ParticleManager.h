#pragma once

#include "ParticleEffect.h"

SHADOW_NAMESPACE_BEGIN

class ParticleManager
{
public:
	inline static ParticleManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new ParticleManager() : m_pInstance; }

	void CreateParticleEffect(Scene* pScene, const std::string& spriteFilePath, const glm::vec2& spriteDimensions, const glm::vec2& position, const glm::vec2& direction, float velocity, float friction, float lifeTime, short numParticles);

	void Update();

	void Render();

	void DestroyParticleEffect(uint16_t id);
	void DestroyParticleEffects();

	static const unsigned short MAX_PARTICLES = 1000;
private:
	ParticleManager() { }
	~ParticleManager();

	static ParticleManager* m_pInstance;

	uint16_t m_id = 0;
	unsigned short m_numParticlesAlive = 0;

	std::unordered_map<uint16_t, ParticleEffect*> m_particleEffects;

	short NumParticlesFree(short desiredNumParticles);
};

SHADOW_NAMESPACE_END