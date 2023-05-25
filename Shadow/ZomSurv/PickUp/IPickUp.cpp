#include "sdpch.h"
#include "IPickUp.h"

#include "Time/Time.h"
#include "Component/SpriteRenderer.h"
#include "Component/BoxCollider2D.h"

#include "PickUpManager.h"

void IPickUp::Init(Shadow::Scene* pScene, const glm::vec2& position, const std::string& name, uint16_t textureId, Shadow::ITrigger* triggerMethods)
{
	m_pGameObject = pScene->CreateEmptyGameObject("Pickup " + name);

	m_pGameObject->GetTransform()->position = { position.x, position.y, 0.0f };

	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(m_pGameObject, textureId);
	Shadow::BoxCollider2D* bc = new Shadow::BoxCollider2D(m_pGameObject, true);
	bc->SetTriggerFunction(triggerMethods);

	m_pGameObject->AddComponent(sr);
	m_pGameObject->AddComponent(bc);


	m_timer = MAX_TIME;
}

bool IPickUp::Update()
{
	m_timer -= Shadow::Time::Instance()->GetDeltaTime();

	if (m_timer > 0)
		return false;

	return true;
}