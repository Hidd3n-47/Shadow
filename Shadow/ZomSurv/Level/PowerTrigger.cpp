#include "sdpch.h"
#include "PowerTrigger.h"

#include "Input/InputManager.h"
#include "Graphics/FontManager.h"
#include "Component/BoxCollider2D.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Level/LevelManager.h"

PowerTrigger::PowerTrigger(Shadow::Scene* pScene, const glm::vec2& worldPosition) :
	m_pScene(pScene)
{
	m_pGameObject = m_pScene->CreateEmptyGameObject("Power Trigger");

	Shadow::BoxCollider2D* box = new Shadow::BoxCollider2D(m_pGameObject, glm::vec2(TILE_WIDTH >> 1), true);
	box->SetTriggerFunction(this);
	m_pGameObject->AddComponent(box);

	m_pGameObject->GetTransform()->position = { worldPosition.x, worldPosition.y, 0.0f };
}

PowerTrigger::~PowerTrigger()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_pScene->RemoveGameObject(m_pGameObject);
}

void PowerTrigger::OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
{
	if (otherCollider->GetName() != "Player")
		return;


	glm::vec2 playerPosition = GameManager::Instance()->GetPlayerPosition();
	Shadow::Camera* camera = GameManager::Instance()->GetScene()->GetCamera();
	float width, height;
	camera->GetWidthAndHeight(width, height);
	glm::vec2 cameraPosition = camera->GetPosition();
	glm::vec2 position = glm::vec2(floor(playerPosition.x + 32 + width * 0.5f), floor(playerPosition.y - 16 + height * 0.5f)) - cameraPosition;
	m_popupId = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 18, "Press [E] to switch power on.", Color(Black), position);
}

void PowerTrigger::OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
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
		TurnPowerOn();
}

void PowerTrigger::OnTriggerExit()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_popupId = -1;
}

void PowerTrigger::TurnPowerOn()
{
	GameManager::Instance()->TurnPowerOn();

	LevelManager::Instance()->DeletePowerTriggers();

	Shadow::DLOG("Power turned on.");
}