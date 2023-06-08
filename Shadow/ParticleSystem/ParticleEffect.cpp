#include "sdpch.h"
#include "ParticleEffect.h"

#include <glm/gtx/vector_angle.hpp>

#include "Graphics/TextureManager.h"
#include "Time/Time.h"
#include "Random/Random.h"

SHADOW_NAMESPACE_BEGIN

ParticleEffect::ParticleEffect(Scene* pScene, const std::string& spriteFilePath, const glm::vec2& spriteDimensions, const glm::vec2& position, const glm::vec2& direction,
	float velocity, float friction, float lifeTime, short numParticles) :
	m_pScene(pScene),
	m_textureDimensions(spriteDimensions),
	m_position(position),
	m_maxLifeSpan(lifeTime),
	m_lifeTime(lifeTime)
{
	m_textureId = TextureManager::Instance()->Load(spriteFilePath, pScene->GetWindow()->GetRenderer(), spriteDimensions.x, spriteDimensions.y);

	const short RAND_ANGLE_OFFSET = 3;
	const float VELOCITY_PERCENT_OFFSET = 0.1f;
	const short SCALE_BOUND_X = 75;
	const short SCALE_BOUND_Y = 175;

	for (int i = 0; i < numParticles; i++)
	{
		glm::vec2 dir(1.0f);
		float randAngle = Random::GetRandomIntBetween(-RAND_ANGLE_OFFSET, RAND_ANGLE_OFFSET);
		float angle = glm::angle(direction, glm::vec2(1.0f, 0.0f)) + randAngle / (2 * PI);

		dir.x *= glm::cos(angle);
		dir.y *= glm::sin(angle);

		float velocityOffset = VELOCITY_PERCENT_OFFSET * velocity;
		float v = Random::GetRandomIntBetween(velocity - velocityOffset, velocity + velocityOffset);

		float scale = Random::GetRandomIntBetween(SCALE_BOUND_X, SCALE_BOUND_Y) / 100.0f;

		m_particles.push_back(new Particle(m_position, dir, glm::vec2(scale), v, friction));
	}
}

ParticleEffect::~ParticleEffect()
{
	TextureManager::Instance()->RemoveTexture(m_textureId);

	for (int i = 0; i < m_particles.size(); i++)
		delete m_particles[i];
}

bool ParticleEffect::Update()
{
	m_lifeTime -= Time::Instance()->GetDeltaTime();

	if (m_lifeTime <= 0.0f)
		return true;

	for (auto p : m_particles)
		p->Update();

	TextureManager::Instance()->SetTextureAlpha(m_textureId, m_lifeTime / m_maxLifeSpan);
	
	return false;
}

void ParticleEffect::Render()
{
	for (auto particle : m_particles)
	{
		TextureManager::Instance()->RenderSingle(m_pScene->GetCamera(), m_pScene->GetWindow()->GetRenderer(), m_textureId, particle->m_position, particle->m_scale, m_textureDimensions);
	}
}

SHADOW_NAMESPACE_END