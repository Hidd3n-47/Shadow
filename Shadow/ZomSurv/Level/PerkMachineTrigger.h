#pragma once

#include "Component/ITrigger.h"

#define PERK_COST 1250

class PerkMachineTrigger : public Shadow::ITrigger
{
public:
	PerkMachineTrigger(Shadow::Scene* pScene, int perkId, const glm::vec2& worldPosition);
	virtual ~PerkMachineTrigger();

	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerExit() override;

private:
	Shadow::Scene* m_pScene = nullptr;
	Shadow::GameObject* m_pGameObject = nullptr;
	std::string m_perkName = "";

	int m_perkId = -1;

	int m_popupId = -1;

	void PerkNameFromId(int perkId);
	void BuyPerk();
};

