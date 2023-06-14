#include "sdpch.h"
#include "ParticleManager.h"

#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

ParticleManager* ParticleManager::m_pInstance = nullptr;

ParticleManager::~ParticleManager()
{
	for (auto it = m_particleEffects.begin(); it != m_particleEffects.end(); ++it)
		DestroyParticleEffect(it->first);
}

void ParticleManager::CreateParticleEffect(Scene* pScene, const std::string& spriteFilePath, const glm::vec2& spriteDimensions, const glm::vec2& position, const glm::vec2& direction, 
	float velocity, float friction, float lifeTime, short numParticles)
{
	numParticles = NumParticlesFree(numParticles);

	if (numParticles == 0)
		return;

	m_numParticlesAlive += numParticles;

	m_particleEffects[m_id++] = new ParticleEffect(pScene, spriteFilePath, spriteDimensions, position, direction, velocity, friction, lifeTime, numParticles);
}

void ParticleManager::Update()
{
	std::vector<uint16_t> toDelete;

	for (auto pe : m_particleEffects)
		if (pe.second->Update())
			toDelete.push_back(pe.first);

	for (auto id : toDelete)
		DestroyParticleEffect(id);
}

void ParticleManager::Render()
{
	for (auto pe : m_particleEffects)
		pe.second->Render();
}

void ParticleManager::DestroyParticleEffect(uint16_t id)
{
	m_numParticlesAlive -= m_particleEffects[id]->GetNumParticles();
	delete m_particleEffects[id];

	m_particleEffects.erase(id);
}

void ParticleManager::DestroyParticleEffects()
{
	for (auto it = m_particleEffects.begin(); it != m_particleEffects.end(); ++it)
		delete it->second;

	m_particleEffects.clear();
}

short ParticleManager::NumParticlesFree(short desiredNumParticles)
{
	short remainingParticle = MAX_PARTICLES - m_numParticlesAlive;

	if (remainingParticle < desiredNumParticles)
		if (remainingParticle > 0)
			desiredNumParticles = remainingParticle;
		else
			desiredNumParticles = 0;

	return desiredNumParticles;
}

SHADOW_NAMESPACE_END