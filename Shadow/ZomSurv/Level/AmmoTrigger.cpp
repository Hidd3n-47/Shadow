#include "sdpch.h"
#include "AmmoTrigger.h"

#include "Input/InputManager.h"
#include "Graphics/FontManager.h"
#include "Component/BoxCollider2D.h"

#include "ZomSurv/src/GameManager.h"

AmmoTrigger::AmmoTrigger(Shadow::Scene* pScene, const glm::vec2& worldPosition) :
	m_pScene(pScene)
{
	m_pGameObject = m_pScene->CreateEmptyGameObject("Ammo Station Trigger");

	Shadow::BoxCollider2D* box = new Shadow::BoxCollider2D(m_pGameObject, glm::vec2(TILE_WIDTH >> 1), true);
	box->SetTriggerFunction(this);
	m_pGameObject->AddComponent(box);

	m_pGameObject->GetTransform()->position = { worldPosition.x, worldPosition.y, 0.0f };
}

AmmoTrigger::~AmmoTrigger()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_pScene->RemoveGameObject(m_pGameObject);
}

void AmmoTrigger::OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
{
	if (otherCollider->GetName() != "Player")
		return;

	glm::vec2 playerPosition = GameManager::Instance()->GetPlayerPosition();
	Shadow::Camera* camera = GameManager::Instance()->GetScene()->GetCamera();
	float width, height;
	camera->GetWidthAndHeight(width, height);
	glm::vec2 cameraPosition = camera->GetPosition();
	glm::vec2 position = glm::vec2(floor(playerPosition.x + 32 + width * 0.5f), floor(playerPosition.y - 16 + height * 0.5f)) - cameraPosition;
	m_popupId = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 18, "Press 'E' to purchase ammo [Cost: " + std::to_string(AMMO_COST) + "]", Color(Black), position);
}

void AmmoTrigger::OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
{
	if (otherCollider->GetName() != "Player")
		return;

	if (m_popupId != -1)
	{
		glm::vec2 playerPosition = GameManager::Instance()->GetPlayerPosition();
		Shadow::Camera* camera = GameManager::Instance()->GetScene()->GetCamera();
		float width, height;
		camera->GetWidthAndHeight(width, height);
		glm::vec2 cameraPosition = camera->GetPosition();
		glm::vec2 position = glm::vec2(floor(playerPosition.x + 32 + width * 0.5f), floor(playerPosition.y - 16 + height * 0.5f)) - cameraPosition;

		Shadow::FontManager::Instance()->UpdateFont(m_popupId, position);
	}

	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_e))
		BuyAmmo();
}

void AmmoTrigger::OnTriggerExit()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_popupId = -1;
}

void AmmoTrigger::BuyAmmo()
{
	if (!GameManager::Instance()->PlayerPurchase(AMMO_COST))
		return;

	Ammo::Instance()->MaxAmmo();
	Hud::Instance()->UpdateAmmo();
}