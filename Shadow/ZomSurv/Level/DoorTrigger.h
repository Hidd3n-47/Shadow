#pragma once

#include "Component/ITrigger.h"

class DoorTrigger : public Shadow::ITrigger
{
public:
	DoorTrigger(int doorId, int nextDoorId, int currentRoomId, const glm::vec2& worldPosition, Shadow::Scene* pScene);
	virtual ~DoorTrigger();

	virtual void OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider) override;
	virtual void OnTriggerExit() override;

private:
	Shadow::Scene* m_pScene = nullptr;
	Shadow::GameObject* m_pGameObject = nullptr;

	int m_doorId = -1;
	int m_nextRoomId = -1;
	int m_currentRoomId = -1;

	int m_popupId = -1;

	void BuyRoom();
};