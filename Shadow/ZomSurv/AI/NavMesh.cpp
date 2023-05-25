#include "sdpch.h"
#include "NavMesh.h"

std::vector<Direction> NavMesh::FindPath(const glm::vec2& startPos, glm::vec2 targetPos)
{
	std::vector<Direction> directions;
	glm::vec2 position = startPos;

	ConvertWorldToIndex(position);
	ConvertWorldToIndex(targetPos);

	while (position != targetPos)
	{
		directions.push_back(FindNextDirection(position, targetPos));
	}

	return directions;
}

void NavMesh::ConvertWorldToIndex(glm::vec2& worldPosition)
{
	worldPosition /= TILE_WIDTH;

	worldPosition = { floor(worldPosition.x), floor(worldPosition.y) };
}

Direction NavMesh::FindNextDirection(glm::vec2& position, const glm::vec2& targetPosition)
{
	bool moveLeft = false;
	int dy = targetPosition.y - position.y;
	int dx = targetPosition.x - position.x;

	if (abs(dx) >= abs(dy))
	{
		if (dx >= 0)
		{
			if (m_navMesh[position.y][position.x + 1] == -1)
			{
				position.x += 1;
				return Right;
			}
			//else if()
		}/*
		else
		{

		}*/
	}/*
	else if(abs(dx) >= abs(dy) || moveLeft)
	{

	}*/
	return Right;
}