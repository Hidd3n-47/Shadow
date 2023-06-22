#pragma once

#include <future>

#include "Scene/SceneManager.h"
#include "LevelData.h"

class LevelParser
{
public:
	inline static LevelParser* Instance() { return m_pInstance == nullptr ? m_pInstance = new LevelParser() : m_pInstance; }

	void ParseLevel(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
private:
	LevelParser() { }
	~LevelParser();

	static LevelParser* m_pInstance;

	void ProcessLevelWalls(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
	void TileHandler(LevelData* pLevelData, int tileID, int x, int y, Shadow::Scene* pScene);

	void ProcessLevelDoors(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
	void DoorIdHandler(int value, int x, int y, Shadow::Scene* pScene);

	void ProcessEnvironment(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
	void EnvironmentHandler(LevelData* pLevelData, int value, int x, int y, Shadow::Scene* pScene);
	std::string PerkMachineFilePath(int key, int*& pTextureId);

	void CreateSolidWallGameObject(const std::string& gameObjectName, const std::string& filePath, const glm::vec2& position, Shadow::Scene* pScene, int& textureId);
	void CreateFloorGameObject(const std::string& gameObjectName, const std::string& filePath, const glm::vec2& position, Shadow::Scene* pScene, int& textureId);

	void LoadNavMesh(LevelData* pLevelData, const std::string& filePath);

	void LoadFromTextFile(std::vector<std::string>& levelFile, const std::string& filePath);

	// Texture id's
	int m_wallId		= -1;
	int m_darkWallId	= -1;
	int m_powerWallId	= -1;
	int m_spawnerId		= -1;
	int m_quickRevId	= -1;
	int m_doubleTapId	= -1;
	int m_speedColaId	= -1;
	int m_jugId			= -1;
	int m_ammoId		= -1;
};

