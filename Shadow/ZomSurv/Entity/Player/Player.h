#pragma once

#include "Scene/Scene.h"
#include "Graphics/FontManager.h"
#include "Component/Animation.h"

#include "ZomSurv/Entity/IEntity.h"
#include "ZomSurv/Weapons/Gun.h"
#include "ZomSurv/Entity/Player/Hud.h"


enum class PlayerState
{
	PLAYING,
	RELOADING
};

enum class PlayerMovingState
{
	MOVING,
	STANDING
};

class Player : public IEntity
{
public:
	Player(Shadow::Scene* pScene, const glm::vec3& startingPosition);
	~Player();

	void Init();

	void Update(const glm::vec3& moveDirection);

	bool Damage(uint16_t damage);
	bool PurchaseItem(unsigned int cost);
	void Shoot();

	void ResetPerkStats();

	inline void Reload() { m_state = PlayerState::RELOADING; Hud::Instance()->DisplayReloading(true); Hud::Instance()->DisplayReloadPrompt(); }
	inline void ApplyJugPerk() { m_maxHealth = 200; }
	inline void ApplySpeedColaPerk() { m_speed = 250.0f; }

	// Accessors.
	inline unsigned int GetScore() const { return m_score; }
	inline unsigned short GetAmmoInClip() const { return m_pGun->GetNumInClip(); }
	inline unsigned short GetAmmoForType() const { return Ammo::Instance()->GetAmmo(m_pGun->GetAmmoType()); }
	inline PlayerState GetState() const { return m_state; }
	inline float GetRotation() const { return *m_pRotation; }

	// Mutators.
	inline void SetPosition(const glm::vec3& position) { *m_position = position; }
	inline void AddScore(unsigned int score) { m_score += score; Hud::Instance()->UpdatePlayerScore(m_score); }
	inline void SetGun(Gun* pGun) { m_pGun = pGun; }
	inline void SetState(PlayerState state) { m_state = state; }
private:
	Shadow::Scene* m_pScene = nullptr;
	Shadow::Animation* m_pAnimationComponent = nullptr;

	float* m_pRotation = nullptr;

	PlayerState m_state = PlayerState::PLAYING;
	PlayerMovingState m_movingState = PlayerMovingState::STANDING;
	float m_maxHealth = 150.0f;
	unsigned int m_score;
	const float HEALTH_REGEN_DELAY = 2.0f;
	float m_healthRegenTimer = HEALTH_REGEN_DELAY;
	float m_healthRegenPerSecond = 20.0f;

	bool m_indestructable = false;
	const float INDESTRUCTABLE_TIME = 2.0f;
	float m_indestructableTimer = INDESTRUCTABLE_TIME;

	Gun* m_pGun = nullptr;

	float m_halfWidth, m_halfHeight;

	void CreateGameObject(Shadow::Scene* pScene);
	void UpdateMovingState(const glm::vec3& moveDirection);
	void UpdateRotation();
	void UpdateRegenTimer(float dt);
	void ReloadUpdate();
};

