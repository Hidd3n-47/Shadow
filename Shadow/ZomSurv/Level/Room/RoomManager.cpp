#include "sdpch.h"
#include "RoomManager.h"

#include "Graphics/TextureManager.h"
#include "Random/Random.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Level/DoorTrigger.h"
#include "ZomSurv/Level/LevelManager.h"

RoomManager* RoomManager::m_pInstance = nullptr;

RoomManager::RoomManager()
{
	m_textureId = Shadow::TextureManager::Instance()->Load("Assets/Environment/door.png", Shadow::SceneManager::Instance()->GetActiveScene()->GetWindow()->GetRenderer());

	std::vector<glm::vec2> roomSpawnLocations = LevelManager::Instance()->GetSpawnLocations(1);

	for (glm::vec2 location : roomSpawnLocations)
		m_zombieSpawns.push_back(location);
}

RoomManager::~RoomManager()
{
	delete m_pInstance;
}

void RoomManager::AddDoor(const glm::vec2& position, int roomId, Shadow::Scene* pScene)
{
	auto it = m_doors.find(roomId);
	if (it == m_doors.end())
		m_doors[roomId] = new Door(roomId);

	m_doors[roomId]->AddDoorSection({ position.x * TILE_WIDTH, position.y * TILE_WIDTH }, pScene, m_textureId);
}

void RoomManager::AddDoorObject(const glm::vec2& position, int value, Shadow::Scene* pScene)
{
	int doorId = floor(value / 100.0f);
	int nextRoomId = floor(value / 10.0f) - 10 * doorId;
	int currentRoomId = value - nextRoomId * 10 - doorId * 100;
	
	m_doorTriggers[doorId].push_back(new DoorTrigger(doorId, nextRoomId, currentRoomId, glm::vec2(position.x * TILE_WIDTH, position.y * TILE_WIDTH), pScene));
}

void RoomManager::BuyRoom(int roomId, int nextRoomId)
{
	if (!GameManager::Instance()->PlayerPurchase(m_doors[roomId]->GetCost()))
	{
		Shadow::DLOG("You cannot afford that room!")
		return;
	}

	// Delete the doors.
	delete m_doors[roomId];
	m_doors.erase(roomId);

	// Delete the door triggers.
	for (int i = 0; i < m_doorTriggers[roomId].size(); i++)
		delete m_doorTriggers[roomId][i];

	m_doorTriggers[roomId].clear();
	m_doorTriggers.erase(roomId);

	// Add the zombie spawners of the new room.
	AddToZombieSpawns(nextRoomId);
}

glm::vec2 RoomManager::GetRandomSpawnLocation()
{
	int index = Shadow::Random::GetRandomIntBetween(0, m_zombieSpawns.size());

	return m_zombieSpawns[index];
}

void RoomManager::AddToZombieSpawns(int roomToAddId)
{
	std::vector<glm::vec2> roomSpawnLocations = LevelManager::Instance()->GetSpawnLocations(roomToAddId);

	for (glm::vec2 location : roomSpawnLocations)
		m_zombieSpawns.push_back(location);
}