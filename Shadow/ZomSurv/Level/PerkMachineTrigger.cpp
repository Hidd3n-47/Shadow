#include "sdpch.h"
#include "PerkMachineTrigger.h"

#include "Input/InputManager.h"
#include "Graphics/FontManager.h"
#include "Component/BoxCollider2D.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Level/LevelManager.h"
#include "ZomSurv/Entity/Player/Hud.h"

PerkMachineTrigger::PerkMachineTrigger(Shadow::Scene* pScene, int perkId, const glm::vec2& worldPosition) :
	m_pScene(pScene),
	m_perkId(perkId)
{
	PerkNameFromId(perkId);

	m_pGameObject = m_pScene->CreateEmptyGameObject("Perk Trigger: " + m_perkName);

	Shadow::BoxCollider2D* box = new Shadow::BoxCollider2D(m_pGameObject, glm::vec2(TILE_WIDTH >> 1), true);
	box->SetTriggerFunction(this);
	m_pGameObject->AddComponent(box);

	m_pGameObject->GetTransform()->position = { worldPosition.x, worldPosition.y, 0.0f };
}

PerkMachineTrigger::~PerkMachineTrigger()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_pScene->RemoveGameObject(m_pGameObject);
}

void PerkMachineTrigger::OnTriggerEnter(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
{
	if (otherCollider->GetName() != "Player")
		return;

	std::string prompt;

	if (!GameManager::Instance()->GetPowerOn())
		prompt = "You need to turn the power on.";
	else
	{
		prompt = "Press 'E' to purchase " + m_perkName + " [Cost: " + std::to_string(PERK_COST) + "]";
		m_power = true;
	}


	glm::vec2 playerPosition = GameManager::Instance()->GetPlayerPosition();
	Shadow::Camera* camera = GameManager::Instance()->GetScene()->GetCamera();
	float width, height;
	camera->GetWidthAndHeight(width, height);
	glm::vec2 cameraPosition = camera->GetPosition();
	glm::vec2 position = glm::vec2(floor(playerPosition.x + 32 + width * 0.5f), floor(playerPosition.y - 16 + height * 0.5f)) - cameraPosition;
	m_popupId = Shadow::FontManager::Instance()->CreateFont("Assets/Fonts/Louis George Cafe Bold.ttf", 18, prompt, Color(Black), position);
}

void PerkMachineTrigger::OnTriggerStay(Shadow::GameObject* thisCollider, Shadow::GameObject* otherCollider)
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

	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_e) && m_power)
		BuyPerk();
}

void PerkMachineTrigger::OnTriggerExit()
{
	if (m_popupId != -1)
		Shadow::FontManager::Instance()->DeleteFont(m_popupId);

	m_popupId = -1;
}

void PerkMachineTrigger::PerkNameFromId(int perkId)
{
	switch (perkId)
	{
	case 100:
		m_perkName = "Quick Revive";
		break;
	case 101:
		m_perkName = "Speed Cola";
		break;
	case 102:
		m_perkName = "Double Tap";
		break;
	case 103:
		m_perkName = "Juggernog";
		break;
	default:
		Shadow::Log::Instance()->Warning("Perk machine id not processed into a name string. PerkId: " + std::to_string(perkId));
		break;
	}
}

void PerkMachineTrigger::BuyPerk()
{
	if (!LevelManager::Instance()->BuyPerk(m_perkId))
		return;

	switch (m_perkId)
	{
	case 100:
		Hud::Instance()->SetQuickReviveActive(true);
		break;
	case 101:
		Hud::Instance()->SetSpeedColaActive(true);
		break;
	case 102:
		Hud::Instance()->SetDoubleTapActive(true);
		break;
	case 103:
		Hud::Instance()->SetJugActive(true);
		break;
	}

	Shadow::DLOG("Room with trigger of " + std::to_string(m_perkId) + " purchased");
}