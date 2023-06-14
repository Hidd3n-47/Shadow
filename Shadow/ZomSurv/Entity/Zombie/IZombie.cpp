#include "sdpch.h"
#include "IZombie.h"

#include <glm/gtx/vector_angle.hpp>

#include "Time/Time.h"
#include "Component/IComponent.h"
#include "Component/SpriteRenderer.h"
#include "Component/Animation.h"
#include "Component/CircleCollider2D.h"

#include "ZombieCollision.h"

IZombie::IZombie(Shadow::Scene* pScene, const glm::vec2& spawnLocation, uint16_t health, uint16_t textureId) : 
	m_pScene(pScene)
{
	m_health = health;

	CreateZombie(pScene, spawnLocation, textureId);
}

IZombie::IZombie(Shadow::Scene* pScene, const glm::vec2& spawnLocation, uint16_t health, uint16_t textureId, ZombieType type) :
	m_pScene(pScene),
	m_type(type)
{
	m_health = health;

	CreateZombie(pScene, spawnLocation, textureId);
}

IZombie::~IZombie()
{
	m_pScene->RemoveGameObject(m_gameObject);
}

void IZombie::Update(const glm::vec3& playerPosition)
{
	glm::vec3 direction = glm::normalize(playerPosition - *m_position);

	*m_position += direction * m_speed * Shadow::Time::Instance()->GetDeltaTime();

	float angle = glm::angle(glm::vec2(direction), glm::vec2(1.0f, 0.0f)) / PI * 180.0f;

	if (direction.y < 0)
		angle = 450 - angle;
	else
		angle += 90;

	if (angle > 360)
		angle -= 360;

	m_gameObject->GetTransform()->rotation.z = angle;
}

bool IZombie::Damage(uint16_t damage)
{
	if (m_health <= damage)
		return false;

	m_health -= damage;
	return true;
}

void IZombie::CreateZombie(Shadow::Scene* pScene, const glm::vec2& spawnLocation, uint16_t textureId)
{
	CreateGameObject(pScene);
	InitZombieByType(textureId);

	m_position = &m_gameObject->GetTransform()->position;

	*m_position = { spawnLocation.x, spawnLocation.y, 0.0f };
}

void IZombie::CreateGameObject(Shadow::Scene* pScene)
{
	m_gameObject = pScene->CreateEmptyGameObject("Zombie");
	m_gameObject->SetTag("Zombie");
	Shadow::CircleCollider2D* circ = new Shadow::CircleCollider2D(m_gameObject, TILE_WIDTH >> 1);
	circ->SetCollisionMethods(new ZombieCollision());
	m_gameObject->AddComponent(circ);
}

void IZombie::InitZombieByType(uint16_t textureId)
{
	Shadow::Animation* a = nullptr;

	switch (m_type)
	{
	default:
		Shadow::Log::Instance()->Warning("Zombie type passed in that is not set.");

	case ZombieType::WALKER:
		InitZombie(50, 50.0f);
		a = new Shadow::Animation(m_gameObject, "Assets/zombieAnimation.png", 7, glm::vec2(32.0f), 0.075f);
		break;
	case ZombieType::SPRINTER:
		InitZombie(50, 100.0f);
		a = new Shadow::Animation(m_gameObject, "Assets/zombieAnimation.png", 7, glm::vec2(32.0f), 0.075f);
		break;
	}

	//m_gameObject->AddComponent(sr);
	m_gameObject->AddComponent(a);
}

void IZombie::InitZombie(uint8_t damage, float speed)
{
	m_damage = damage;
	m_speed = speed;
}

float IZombie::GetCollisionRadius()
{
	Shadow::CircleCollider2D* comp = (Shadow::CircleCollider2D*)(m_gameObject->GetComponent(Shadow::ComponentType::CircleCollider2D));

	return comp->GetRadius();
}