#include "sdpch.h"
#include "DoorTrigger.h"

#include "Input/InputManager.h"
#include "Graphics/FontManager.h"
#include "Component/BoxCollider2D.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Level/Room/RoomManager.h"

DoorTrigger::DoorTrigger(int doorId, int nextRoorId, int currentRoomId, const glm::vec2& worldPosition, Shadow::Scene* pScene) :
	m_pScene(pScene),
	m_doorId(doorId),
	m_nextRoomId(nextRoorId),
	m_currentRoomId(currentRoomId)
{
	m_pGameObject = m_pScene->CreateEmptyGameObject("Door Trigger: " + std::to_string(doorId));

	Shadow::BoxCollider2D* box = new Shadow::BoxCollider2D(m_pGameObject, glm::vec2(TILE_WIDTH >> 1), true);
	box->SetTriggerFunction(this);
	m_pGameObject->AddComponent(box);

	m_pGameObject->GetTransform()->position = { worldPosition.x, worldPosition.y, 0.0f };
}

DoorTrigger::~DoorTrigger()
{
	if(m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_pScene->RemoveGameObject(m_pGameObject);
}

void DoorTrigger::OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
{
	if (otherCollider->GetName() != "Player")
		return;

	glm::vec2 playerPosition = GameManager::Instance()->GetPlayerPosition();
	Shadow::Camera* camera = GameManager::Instance()->GetScene()->GetCamera();
	float width, height;
	camera->GetWidthAndHeight(width, height);
	glm::vec2 cameraPosition = camera->GetPosition();
	glm::vec2 position = glm::vec2(floor(playerPosition.x + 32 + width * 0.5f), floor(playerPosition.y - 16 + height * 0.5f)) - cameraPosition;
	m_popupId = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 18, "Press 'E' to open door. [Cost: 1000]", Color(Black), position);
}

void DoorTrigger::OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
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
		BuyRoom();
}

void DoorTrigger::OnTriggerExit()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_popupId = -1;
}

void DoorTrigger::BuyRoom()
{
	Shadow::DLOG("Room with trigger of " + std::to_string(m_doorId) + " purchased");

	RoomManager::Instance()->BuyRoom(m_doorId, m_nextRoomId);
}