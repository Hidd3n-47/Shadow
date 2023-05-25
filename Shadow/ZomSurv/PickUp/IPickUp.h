#pragma once

#include "GameObject/GameObject.h"

#include "PickupTriggers.h"

enum class PickUpType
{
	MAX_AMMO = 0,
	NUKE,
	INSTA_KILL,
	DOUBLE_POINTS,
	Count // Used to find the total number of Pick ups.
};

class IPickUp
{
public:
	virtual ~IPickUp() {  }

	bool Update();

	// Accessors.
	inline Shadow::GameObject* GetGameObject() const { return m_pGameObject; }
protected:
	Shadow::GameObject* m_pGameObject = nullptr;

	const float MAX_TIME = 5.0f;
	float m_timer = 0;

	void Init(Shadow::Scene* pScene, const glm::vec2& position, const std::string& name, uint16_t textureId, Shadow::ITrigger* triggerMethods);
};

class MaxAmmo : public IPickUp
{
public:
	MaxAmmo(Shadow::Scene* pScene, const glm::vec2& position, uint16_t textureId)
	{
		Init(pScene, position, "MaxAmmo", textureId, new MaxAmmoTrigger());
	}
};

class Nuke : public IPickUp
{
public:
	Nuke(Shadow::Scene* pScene, const glm::vec2& position, uint16_t textureId)
	{
		Init(pScene, position, "Nuke", textureId, new NukeTrigger());
	}
};

class InstaKill : public IPickUp
{
public:
	InstaKill(Shadow::Scene* pScene, const glm::vec2& position, uint16_t textureId)
	{
		Init(pScene, position, "InstaKill", textureId, new InstaKillTrigger());
	}
};

class DoublePoints : public IPickUp
{
public:
	DoublePoints(Shadow::Scene* pScene, const glm::vec2& position, uint16_t textureId)
	{
		Init(pScene, position, "DoublePoints", textureId, new DoublePointsTrigger());
	}
};
