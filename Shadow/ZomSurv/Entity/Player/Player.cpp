#include "sdpch.h"
#include "Player.h"

#include <glm/gtx/vector_angle.hpp>

#include "Logger/Log.h"
#include "Time/Time.h"
#include "Input/InputManager.h"
#include "Component/CircleCollider2D.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Weapons/GunManager.h"

Player::Player(Shadow::Scene* pScene, const glm::vec3& startingPosition) : 
	m_pScene(pScene)
{
	m_health = m_maxHealth;
	m_damage = 10;
	m_position = nullptr;
	m_speed = 200.0f;
	m_score = 500;

	CreateGameObject(pScene);
	
	m_position = &m_gameObject->GetTransform()->position;
	m_pRotation = &m_gameObject->GetTransform()->rotation.z;

	*m_position -= glm::vec3(TILE_WIDTH >> 1);


	SetPosition(startingPosition);

	pScene->GetCamera()->SetTargetPosition(*m_position);

	SetGun(GunManager::Instance()->LoadGun("Assets/Weapons/Guns/calt45.gun"));

	Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetWidthAndHeight(m_halfWidth, m_halfHeight);
	m_halfWidth *= 0.5f;
	m_halfHeight *= 0.5f;
}

Player::~Player()
{
	delete m_pGun;

	m_pScene->RemoveGameObject(m_gameObject);
}

void Player::Init()
{
	Hud::Instance()->Init(1, m_score);
}

void Player::Update(const glm::vec3& moveDirection)
{
	UpdateMovingState(moveDirection);

	float dt = Shadow::Time::Instance()->GetDeltaTime();

	*m_position += moveDirection * m_speed * dt;

	UpdateRotation();

	UpdateRegenTimer(dt);

	if (m_state == PlayerState::RELOADING)
		ReloadUpdate();
}

bool Player::Damage(uint16_t damage)
{
	if (m_indestructable)
	{
		m_indestructableTimer -= Shadow::Time::Instance()->GetDeltaTime();
		if (m_indestructableTimer <= 0.f)
			m_indestructable = false;
	}

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
	if (m_pGun->GetNumInClip() == 0)
	{
		m_state = PlayerState::RELOADING;
		m_pGun->Reload();
	}
	else
	{
		m_pGun->Shoot();
		if (m_pGun->GetNumInClip() == 0 && m_state == PlayerState::PLAYING)
			Hud::Instance()->DisplayReloadPrompt(true);
	}
}

void Player::ResetPerkStats()
{
	m_maxHealth = 150.0f; 
	m_speed = 200.0f;
	m_health = m_maxHealth; 
	m_indestructable = true;

	Hud::Instance()->UpdateHealthBar(m_health, m_maxHealth);
}

void Player::CreateGameObject(Shadow::Scene* pScene)
{
	m_gameObject = pScene->CreateEmptyGameObject("Player");

	Shadow::CircleCollider2D* circ = new Shadow::CircleCollider2D(m_gameObject, TILE_WIDTH >> 1);
	m_pAnimationComponent = new Shadow::Animation(m_gameObject, "Assets/playerAnimation.png", 7, glm::vec2(32.0f), 0.075f);

	m_gameObject->AddComponent(circ);
	m_gameObject->AddComponent(m_pAnimationComponent);

	m_gameObject->SetTag("Player");
}

void Player::UpdateMovingState(const glm::vec3& moveDirection)
{
	if (moveDirection != glm::vec3(0.0f))
		m_movingState = PlayerMovingState::MOVING;
	else
		m_movingState = PlayerMovingState::STANDING;

	switch (m_movingState)
	{
	case PlayerMovingState::MOVING:
		m_pAnimationComponent->Resume();
		break;
	case PlayerMovingState::STANDING:
		m_pAnimationComponent->Pause();
		m_pAnimationComponent->Reset();
		break;
	default:
		Shadow::Log::Instance()->Warning("Unprocessed state in the Player Moving State method.");
		break;
	}
}

void Player::UpdateRotation()
{
	glm::vec2 mouseCoords = Shadow::InputManager::Instance()->GetMousePosition();
	glm::vec2 direction = glm::normalize(mouseCoords - glm::vec2(m_halfWidth + TILE_WIDTH * 0.5f, m_halfHeight + TILE_WIDTH * 0.5f));

	float angle = glm::angle(direction, glm::vec2(1.0f, 0.0f)) / PI * 180.0f;

	if (direction.y < 0)
		angle = 450 - angle;
	else
		angle += 90;

	if (angle > 360)
		angle -= 360;

	*m_pRotation = angle;
}

void Player::UpdateRegenTimer(float dt)
{
	if (m_health < m_maxHealth)
		if (m_healthRegenTimer > 0)
			m_healthRegenTimer -= dt;
		else
		{
			float health = m_health + m_healthRegenPerSecond * dt;
			m_health = health > m_maxHealth ? m_maxHealth : health;
			Hud::Instance()->UpdateHealthBar(health, m_maxHealth);
		}
	else
		m_healthRegenTimer = HEALTH_REGEN_DELAY;
}

void Player::ReloadUpdate()
{
	if (!m_pGun->Reload())
		return;

	m_state = PlayerState::PLAYING;
	Hud::Instance()->DisplayReloadPrompt();
	Hud::Instance()->DisplayReloading();
}