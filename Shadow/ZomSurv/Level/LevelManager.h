#pragma once

#include "Scene/Scene.h"

#include "ZomSurv/Level/PerkMachineTrigger.h"
#include "LevelData.h"
#include "AmmoTrigger.h"

class Camera;

enum class Level
{
	MAP1
};

class LevelManager
{
public:
	inline static LevelManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new LevelManager() : m_pInstance; }

	void LoadMap(const Level& level, Shadow::Scene* pScene);
	void UnloadMap();

	void AddPerkMachineTrigger(Shadow::Scene* pScene, int perkId, const glm::vec2& worldPosition);
	void BuyPerk(int perkId);

	inline void AddAmmoTrigger(Shadow::Scene* pScene, const glm::vec2& worldPosition) { m_ammoTriggers.push_back(new AmmoTrigger(pScene, worldPosition)); }

	// Accessors.
	inline const std::vector<glm::vec2>& GetSpawnLocations(int roomId) { return m_pLevelData->spawnPoints[roomId]; }
private:
	LevelManager();
	~LevelManager();

	static LevelManager* m_pInstance;

	std::map<Level, std::string> m_levelFilePathMap;
	bool m_mapLoaded = false;
	LevelData* m_pLevelData = nullptr;
	int m_tileMapTextureId = -1;

	std::unordered_map<int, std::vector<PerkMachineTrigger*>> m_perkTriggers;
	
	std::vector<AmmoTrigger*> m_ammoTriggers;
};