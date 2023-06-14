#include "sdpch.h"
#include "Bullet.h"

#include "Time/Time.h"
#include "Component/SpriteRenderer.h"
#include "Component/CircleCollider2D.h"

#include "BulletManager.h"
#include "BulletCollision.h"

Bullet::Bullet(Shadow::Scene* pScene, const glm::vec2& pos, const glm::vec2& dir, float dam) :
	m_pScene(pScene),
	m_direction({dir.x, dir.y, 0.0f}),
	m_damage(dam)
{
	const float RADIUS = 11;

	m_pGameObject = m_pScene->CreateEmptyGameObject("Bullet");
	m_pGameObject->SetTag("Bullet");

	Shadow::CircleCollider2D* cc = new Shadow::CircleCollider2D(m_pGameObject, RADIUS * 0.5f);
	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(m_pGameObject, "Assets/Weapons/bullet.png", glm::vec2(RADIUS));
	cc->SetCollisionMethods(new BulletCollision());

	m_pGameObject->AddComponent(cc);
	m_pGameObject->AddComponent(sr);

	m_position = &m_pGameObject->GetTransform()->position;
	*m_position = glm::vec3(pos.x, pos.y, 0.0f);
}

Bullet::~Bullet()
{
	m_pScene->RemoveGameObject(m_pGameObject);
}

void Bullet::Update()
{
	float dt = Shadow::Time::Instance()->GetDeltaTime();

	*m_position += m_direction * dt * BulletManager::Instance()->GetVelocity();
}