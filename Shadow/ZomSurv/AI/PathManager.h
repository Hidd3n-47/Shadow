#pragma once

#include "Path.h"

class PathManager
{
public:
	inline static PathManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new PathManager() : m_pInstance; }

	void LoadNode(short id, const glm::vec2& nodePosition);

	void RoomPurchased(short roomId);

	void FindPath(Path* path, const glm::vec2& startingPosition, const glm::vec2& targetPosition);

private:
	PathManager();
	~PathManager() { delete m_pInstance; }

	static PathManager* m_pInstance;

	std::unordered_map<short, Node> m_nodeIdMap;
	std::unordered_map<short, std::vector<short>> m_nodesPerRoomId;
	std::unordered_map<short, std::vector<short>> m_nodeConnections;

	std::vector<Node*> m_nodes;
};

