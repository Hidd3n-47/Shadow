#include "sdpch.h"
#include "Player.h"

#include "Logger/Log.h"
#include "Time/Time.h"
#include "Component/SpriteRenderer.h"
#include "Component/CircleCollider2D.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Weapons/GunManager.h"

Player::Player(Shadow::Scene* pScene, const glm::vec3& startingPosition) : 
	m_pScene(pScene)
{
	m_health = m_maxHealth;
	m_damage = 10;
	m_position = nullptr;
	m_speed = 500.0f;
	m_score = 500;

	CreateGameObject(pScene);
	
	m_position = &m_gameObject->GetTransform()->position;

	*m_position -= glm::vec3(TILE_WIDTH >> 1);

	SetPosition(startingPosition);

	pScene->GetCamera()->SetTargetPosition(*m_position);

	SetGun(GunManager::Instance()->LoadGun("Assets/Weapons/Guns/calt45.gun"));
}

Player::~Player()
{
	delete m_pGun[0];
	delete m_pGun[1];

	m_pScene->RemoveGameObject(m_gameObject);
}

void Player::Init()
{
	Hud::Instance()->Init(1, m_score);
}

void Player::Update(const glm::vec3& moveDirection)
{
	float dt = Shadow::Time::Instance()->GetDeltaTime();

	// Update position.
	*m_position += moveDirection * m_speed * dt;

	if (m_health < m_maxHealth)
	{
		if (m_healthRegenTimer > 0)
			m_healthRegenTimer -= dt;
		else
		{
			float health = m_health + m_healthRegenPerSecond * dt;
			m_health = health > m_maxHealth ? m_maxHealth : health;
			Hud::Instance()->UpdateHealthBar(health, m_maxHealth);
		}
	}
	else
	{
		m_healthRegenTimer = HEALTH_REGEN_DELAY;
	}

	if (m_state == PlayerState::RELOADING)
		ReloadUpdate();
}

bool Player::Damage(uint16_t damage)
{
	m_healthRegenTimer = HEALTH_REGEN_DELAY;

	if (m_health <= damage)
		return false;

	m_health -= damage;
	Hud::Instance()->UpdateHealthBar(m_health, m_maxHealth);
	return true;
}

bool Player::PurchaseItem(unsigned int cost)
{
	if (m_score < cost)
		return false;

	m_score -= cost;
	Hud::Instance()->UpdatePlayerScore(m_score);
	return true;
}

void Player::Shoot()
{
	if (m_pGun[m_gunIndex]->GetNumInClip() == 0)
	{
		m_state = PlayerState::RELOADING;
		m_pGun[m_gunIndex]->Reload();
	}
	else
	{
		m_pGun[m_gunIndex]->Shoot();
		if (m_pGun[m_gunIndex]->GetNumInClip() == 0 && m_state == PlayerState::PLAYING)
			Hud::Instance()->DisplayReloadPrompt(true);
	}
}

void Player::CreateGameObject(Shadow::Scene* pScene)
{
	m_gameObject = pScene->CreateEmptyGameObject("Player");
	Shadow::CircleCollider2D* circ = new Shadow::CircleCollider2D(m_gameObject, TILE_WIDTH >> 1);
	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(m_gameObject, "Assets/Entity/player.png");
	m_gameObject->AddComponent(circ);
	m_gameObject->AddComponent(sr);
	m_gameObject->SetTag("Player");
}

void Player::ReloadUpdate()
{
	if (!m_pGun[m_gunIndex]->Reload())
		return;

	m_state = PlayerState::PLAYING;
	Hud::Instance()->DisplayReloadPrompt();
	Hud::Instance()->DisplayReloading();
}