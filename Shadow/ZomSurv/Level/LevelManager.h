#pragma once

#include "Scene/Scene.h"

#include "ZomSurv/Level/PerkMachineTrigger.h"
#include "ZomSurv/Level/PowerTrigger.h"
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

	inline void AddPerkMachineTrigger(Shadow::Scene* pScene, int perkId, const glm::vec2& worldPosition) { m_perkTriggers[perkId].push_back(new PerkMachineTrigger(pScene, perkId, worldPosition)); }
	inline void AddPowerTrigger(Shadow::Scene* pScene, const glm::vec2& worldPosition) { m_powerTriggers.push_back(new PowerTrigger(pScene, worldPosition)); }

	bool BuyPerk(int perkId);
	void DeletePowerTriggers();

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

	std::vector<PowerTrigger*> m_powerTriggers;
	std::unordered_map<int, std::vector<PerkMachineTrigger*>> m_perkTriggers;
	
	std::vector<AmmoTrigger*> m_ammoTriggers;
};