#pragma once

#include <glm/glm.hpp>
#include "ZomSurv/Level/Door.h"

class DoorTrigger;

class RoomManager
{
public:
	inline static RoomManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new RoomManager() : m_pInstance; }

	void AddDoor(const glm::vec2& position, int roomId, Shadow::Scene* pScene);
	void AddDoorObject(const glm::vec2& position, int value, Shadow::Scene* pScene);
	void BuyRoom(int roomId, int nextRoomId);

	glm::vec2 GetRandomSpawnLocation();

	static const int DOOR_WIDTH = 2;

	inline void InitZombieSpawnLocation() { AddToZombieSpawns(1); }

	// Accesors.
	inline const std::vector<glm::vec2>& GetZombieSpawns() { return m_zombieSpawns; }
	inline glm::vec2 GetZombieSpawnAtIndex(int index) { return m_zombieSpawns[index]; }
private:
	RoomManager();
	~RoomManager();

	static RoomManager* m_pInstance;

	uint16_t m_textureId = 0;

	std::vector<glm::vec2> m_zombieSpawns;
	//std::unordered_map<int, CollisionBox* [DOOR_WIDTH]> m_doors;
	std::unordered_map<int, Door*> m_doors;
	//std::unordered_map<DoorObject*, std::vector<CollisionBox*> > m_doorTriggers;

	//std::unordered_map<int, std::vector<std::pair<DoorTrigger*, CollisionBox*>>> m_doorTriggers;
	std::unordered_map<int, std::vector<DoorTrigger*>> m_doorTriggers;

	void AddToZombieSpawns(int roomToAddId);
};
