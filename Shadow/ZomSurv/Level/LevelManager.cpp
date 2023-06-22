#include "sdpch.h"
#include "LevelManager.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/src/ZombieManager.h"
#include "../Graphics/TextureManager.h"
#include "../Camera/Camera.h"
#include "LevelParser.h"


LevelManager* LevelManager::m_pInstance = nullptr;

LevelManager::LevelManager() :
	m_mapLoaded(false),
	m_pLevelData(nullptr)
{
	m_levelFilePathMap[Level::MAP1] = "Assets/Levels/map1";
}

LevelManager::~LevelManager()
{
	for (int i = 0; i < m_ammoTriggers.size(); i++)
		delete m_ammoTriggers[i];
	m_ammoTriggers.clear();

	delete m_pLevelData;

	delete m_pInstance;
}

void LevelManager::LoadMap(const Level& level, Shadow::Scene* pScene)
{
	delete m_pLevelData;

	m_pLevelData = new LevelData();

	LevelParser::Instance()->ParseLevel(m_pLevelData, m_levelFilePathMap[level], pScene);
	m_mapLoaded = true;
}

void LevelManager::UnloadMap()
{
	delete m_pLevelData;
	m_pLevelData = nullptr;
	m_mapLoaded = false;
}

void LevelManager::BuyPerk(int perkId)
{
	if (!GameManager::Instance()->PlayerPurchase(PERK_COST))
	{
		Shadow::DLOG("You cannot afford that perk!")
		return;
	}

	GameManager::Instance()->PlayPurchasSound();

	switch (perkId)
	{
	case 100:
		// Quick Revive.
		GameManager::Instance()->ActivateQuickRevive();
		break;
	case 101:
		// Speed Cola.
		GameManager::Instance()->PurchaseSpeedCola();
		break;
	case 102:
		// Double tap.
		ZombieManager::Instance()->ActivateDoubleTap();
		break;
	case 103:
		// Jug
		GameManager::Instance()->PurchaseJug();
		break;
	default:
		Shadow::Log::Instance()->Warning("Perk machine purchased and not processed. Perk ID: " + std::to_string(perkId));
		break;
	}

	// Delete the perks.
	for (int i = 0; i < m_perkTriggers[perkId].size(); i++)
		delete m_perkTriggers[perkId][i];

	m_perkTriggers[perkId].clear();
}

void LevelManager::DeletePowerTriggers()
{
	for (int i = 0; i < m_powerTriggers.size(); i++)
		delete m_powerTriggers[i];

	m_powerTriggers.clear();
}