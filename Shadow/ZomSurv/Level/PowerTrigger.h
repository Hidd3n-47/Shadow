#pragma once

#include "Component/ITrigger.h"


class PowerTrigger : public Shadow::ITrigger
{
public:
	PowerTrigger(Shadow::Scene* pScene, const glm::vec2& worldPosition);
	virtual ~PowerTrigger();

	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerExit() override;

private:
	Shadow::Scene* m_pScene = nullptr;
	Shadow::GameObject* m_pGameObject = nullptr;

	int m_popupId = -1;

	void TurnPowerOn();
};