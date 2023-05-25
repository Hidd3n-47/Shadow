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

	static void ProcessLevelWalls(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
	static void TileHandler(LevelData* pLevelData, int tileID, int x, int y, Shadow::Scene* pScene);

	static void ProcessLevelDoors(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
	static void DoorIdHandler(int value, int x, int y, Shadow::Scene* pScene);

	static void ProcessEnvironment(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene);
	static void EnvironmentHandler(LevelData* pLevelData, int value, int x, int y, Shadow::Scene* pScene);
	static std::string PerkMachineFilePath(int key, int*& pTextureId);

	static void CreateSolidWallGameObject(const std::string& gameObjectName, const std::string& filePath, const glm::vec2& position, Shadow::Scene* pScene, int& textureId);
	static void CreateFloorGameObject(const std::string& gameObjectName, const std::string& filePath, const glm::vec2& position, Shadow::Scene* pScene);

	static void LoadNavMesh(LevelData* pLevelData, const std::string& filePath);

	static void LoadFromTextFile(std::vector<std::string>& levelFile, const std::string& filePath);

	/*template<typename Arg1, typename... Args>
	static void ProcessTextFromFile(std::vector<std::string>& levelFile, void* function(Arg1, Args&&... Args));

	static void Test(int x, int y, int z);*/

	// Texture id's
	static int m_wallId;
	static int m_spawnerId;
	static int m_quickRevId;
	static int m_doubleTapId;
	static int m_speedColaId;
	static int m_jugId;
	static int m_ammoId;
};

