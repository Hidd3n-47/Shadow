#include "sdpch.h"
#include "Door.h"

#include "Logger/Log.h"

Door::Door(int doorId) :
	m_doorId(doorId)
{
	SetCostOfDoor();
}

Door::~Door() 
{
	for (Shadow::GameObject* go : m_gameObject)
		m_pScene->RemoveGameObject(go);
}

void Door::AddDoorSection(glm::vec2 worldPosition, Shadow::Scene* pScene, uint16_t textureId)
{
	m_pScene = pScene;

	int it = 0;
	std::string name = "DoorFirstPiece (" + std::to_string(m_doorId) + ")";

	if (m_gameObject[0] != nullptr)
	{
		name = "DoorSecondPiece (" + std::to_string(m_doorId) + ")";
		it = 1;
	}

	m_gameObject[it] = pScene->CreateEmptyGameObject(name);
	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(m_gameObject[it], textureId);
	Shadow::BoxCollider2D* box = new Shadow::BoxCollider2D(m_gameObject[it], glm::vec2(TILE_WIDTH >> 1));
	m_gameObject[it]->AddComponent(sr);
	m_gameObject[it]->AddComponent(box);
	m_gameObject[it]->GetTransform()->position = { worldPosition.x, worldPosition.y, 0.0f };
}

void Door::SetCostOfDoor()
{
	switch (m_doorId)
	{
	case 1:
		m_cost = 1000;
		break;
	case 2:
		m_cost = 1000;
		break;
	case 3:
		m_cost = 1000;
		break;
	case 4:
		m_cost = 1000;
		break;
	case 5:
		m_cost = 1000;
		break;
	case 6:
		m_cost = 1000;
		break;
	case 7:
		m_cost = 1000;
		break;
	case 8:
		m_cost = 1000;
		break;
	case 9:
		m_cost = 1000;
		break;
	default:
		Shadow::Log::Instance()->Warning("Door ID that is not processed has been entered.");
		break;
	}
}