#pragma once
#include "sdpch.h"

#include "ZomSurv/AI/NavMesh.h"

struct LevelData
{
	static const int LEVEL_WIDTH = 142;
	static const int LEVEL_HEIGHT = 110;

	std::map<int, std::vector<glm::vec2>> mapTiles;
	std::unordered_map<int, std::vector<glm::vec2>> spawnPoints;
	NavMesh* pNavMesh = nullptr;
};