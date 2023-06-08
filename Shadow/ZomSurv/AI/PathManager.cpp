#include "sdpch.h"
#include "PathManager.h"

PathManager* PathManager::m_pInstance = nullptr;

PathManager::PathManager()
{
	m_nodesPerRoomId[1] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	m_nodesPerRoomId[2] = { 10, 11, 12, 13 };
	m_nodesPerRoomId[3] = { 14, 15, 16, 17, 18, 19, 20, 21 };
	m_nodesPerRoomId[4] = { 22, 23, 24, 25, 26, 27, 28, 29 };
	m_nodesPerRoomId[5] = { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 53, 54 };
	m_nodesPerRoomId[6] = { 45, 46, 47, 48, 49, 50 };
	m_nodesPerRoomId[7] = { 51, 52, 55 };
	m_nodesPerRoomId[8] = { 56, 57, 58, 59, 61 };
	
	m_nodeConnections[1] = { 6, 5, 2, 7, 3 };
	m_nodeConnections[2] = { 4, 1, 5 };
	m_nodeConnections[3] = { 4, 5, 1, 6 };
	m_nodeConnections[4] = { 2, 3, 5 };
	m_nodeConnections[5] = { 1, 2, 3, 4, 9 };
	m_nodeConnections[6] = { 1, 3 };
	m_nodeConnections[7] = { 1, 8, 61 };
	m_nodeConnections[8] = { 7, 9 };
	m_nodeConnections[9] = { 5, 8, 10, 11 };
	m_nodeConnections[10] = { 9, 11, 12 };
	m_nodeConnections[11] = { 9, 10, 12, 13 };
	m_nodeConnections[12] = { 10, 11, 14, 13 };
	m_nodeConnections[13] = { 11, 12 };
	m_nodeConnections[14] = { 12, 15 };
	m_nodeConnections[15] = { 14, 16 };
	m_nodeConnections[16] = { 15, 17 };
	m_nodeConnections[17] = { 16, 18 };
	m_nodeConnections[18] = { 17, 19 };
	m_nodeConnections[19] = { 18, 20, 21 };
	m_nodeConnections[20] = { 19 };
	m_nodeConnections[21] = { 19, 22 };
	m_nodeConnections[22] = { 21, 23, 24 };
	m_nodeConnections[23] = { 22, 24, 25, 27 };
	m_nodeConnections[24] = { 22, 23, 26 };
	m_nodeConnections[25] = { 23, 27 };
	m_nodeConnections[26] = { 24, 28 };
	m_nodeConnections[27] = { 23, 25, 28 };
	m_nodeConnections[28] = { 26, 27, 29 };
	m_nodeConnections[29] = { 28, 30 };
	m_nodeConnections[30] = { 29, 31, 33, 34 };
	m_nodeConnections[31] = { 30, 32, 41, 34 };
	m_nodeConnections[32] = { 31, 33, 41 };
	m_nodeConnections[33] = { 30, 32, 34, 39 };
	m_nodeConnections[34] = { 30, 33, 31, 37, 54 };
	m_nodeConnections[35] = { 37, 36 };
	m_nodeConnections[36] = { 35, 37 };
	m_nodeConnections[37] = { 25, 26, 24, 38, 54 };
	m_nodeConnections[38] = { 37, 54, 39, 42, 43 };
	m_nodeConnections[39] = { 33, 38, 40 };
	m_nodeConnections[40] = { 39, 41, 44 };
	m_nodeConnections[41] = { 31, 32, 40, 44 };
	m_nodeConnections[42] = { 38, 43 };
	m_nodeConnections[43] = { 38, 42, 44 };
	m_nodeConnections[44] = { 40, 41, 43, 45 };
	m_nodeConnections[45] = { 44, 46 };
	m_nodeConnections[46] = { 45, 47 };
	m_nodeConnections[47] = { 46, 48 };
	m_nodeConnections[48] = { 47, 50, 49 };
	m_nodeConnections[49] = { 50, 48 };
	m_nodeConnections[50] = { 51, 53, 55 };
	m_nodeConnections[51] = { 41, 49, 48 };
	m_nodeConnections[52] = { 51, 53, 55 };
	m_nodeConnections[53] = { 52, 54 };
	m_nodeConnections[54] = { 37, 38, 34 };
	m_nodeConnections[55] = { 56, 52, 51 };
	m_nodeConnections[56] = { 55, 57, 60, 58 };
	m_nodeConnections[57] = { 56, 58, 60 };
	m_nodeConnections[58] = { 57, 61, 59 };
	m_nodeConnections[59] = { 58, 60, 61 };
	m_nodeConnections[60] = { 57, 59 };
	m_nodeConnections[61] = { 7, 58, 59 };
}

void PathManager::LoadNode(short id, const glm::vec2& nodePosition)
{
	m_nodeIdMap[id] = Node(id, nodePosition);
}

void PathManager::RoomPurchased(short roomId)
{
	for (short id : m_nodesPerRoomId[roomId])
		m_nodes.push_back(&m_nodeIdMap[id]);
}

void PathManager::FindPath(Path* path, const glm::vec2& startingPosition, const glm::vec2& targetPosition)
{
	glm::vec2 position = startingPosition;

	while (position != targetPosition)
	{

	}
}