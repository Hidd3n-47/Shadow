#pragma once
#include "src/sdpch.h"

enum Direction
{
	Left,
	Right,
	Up,
	Down
};

class NavMesh
{
	friend class LevelParser;
public:
	std::vector<Direction> FindPath(const glm::vec2& startPos, glm::vec2 targetPos);

	inline int GetNavMeshData(int x, int y) { return m_navMesh[y][x]; }
private:
	std::vector<std::vector<int>> m_navMesh;

	void ConvertWorldToIndex(glm::vec2& worldPosition);
	Direction FindNextDirection(glm::vec2& position, const glm::vec2& targetPosition);
};