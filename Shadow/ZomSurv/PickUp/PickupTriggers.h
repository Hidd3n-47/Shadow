#pragma once

#include "Component/ITrigger.h"

#include "ZomSurv/Weapons/Ammo/Ammo.h"
#include "ZomSurv/src/ZombieManager.h"
#include "ZomSurv/src/GameManager.h"

class MaxAmmoTrigger : public Shadow::ITrigger
{
public:
	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override
	{
		if (otherCollider->GetTag() != "Player")
			return;
		
		GameManager::Instance()->PlayMaxAmmoSound();

		Ammo::Instance()->MaxAmmo();
		Hud::Instance()->UpdateAmmo();

		thisCollider->RemoveAllComponents();
	}

	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override { }
	virtual void OnTriggerExit() override { }
};

class NukeTrigger : public Shadow::ITrigger
{
public:
	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override
	{
		if (otherCollider->GetTag() != "Player")
			return;

		GameManager::Instance()->PlayNukeSound();

		ZombieManager::Instance()->Nuke();
		GameManager::Instance()->AddPlayerScore(500);

		thisCollider->RemoveAllComponents();
	}

	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override { }
	virtual void OnTriggerExit() override { }
};

class InstaKillTrigger : public Shadow::ITrigger
{
public:
	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override
	{
		if (otherCollider->GetTag() != "Player")
			return;

		Hud::Instance()->SetInstaKillActive(true);

		GameManager::Instance()->PlayInstaKillSound();

		ZombieManager::Instance()->ActivateInstaKill();

		thisCollider->RemoveAllComponents();
	}

	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override { }

	virtual void OnTriggerExit() override { }
};

class DoublePointsTrigger : public Shadow::ITrigger
{
public:
	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override
	{
		if (otherCollider->GetTag() != "Player")
			return;

		Hud::Instance()->SetDoublePointsActive(true);

		GameManager::Instance()->PlayDoublePointsSound();

		GameManager::Instance()->ActivateDoublePoints();

		thisCollider->RemoveAllComponents();
	}

	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override { }
	virtual void OnTriggerExit() override { }
};