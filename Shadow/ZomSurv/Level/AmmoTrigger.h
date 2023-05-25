#pragma once

#include "Component/ITrigger.h"

#define AMMO_COST 500

class AmmoTrigger : public Shadow::ITrigger
{
public:
	AmmoTrigger(Shadow::Scene* pScene, const glm::vec2& worldPosition);
	virtual ~AmmoTrigger();

	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerExit() override;

private:
	Shadow::Scene* m_pScene = nullptr;
	Shadow::GameObject* m_pGameObject = nullptr;
	
	int m_popupId = -1;

	void BuyAmmo();
};

