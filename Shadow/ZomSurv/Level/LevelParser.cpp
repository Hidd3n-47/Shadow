#include "sdpch.h"
#include "LevelParser.h"

#include <thread>

#include "Logger/Log.h"
#include "FileIO/IOManager.h"
#include "Component/BoxCollider2D.h"
#include "Component/SpriteRenderer.h"
#include "Graphics/TextureManager.h"

#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/Level/Room/RoomManager.h"
#include "ZomSurv/Level/LevelManager.h"

LevelParser* LevelParser::m_pInstance = nullptr;

int LevelParser::m_wallId		= -1;
int LevelParser::m_powerWallId	= -1;
int LevelParser::m_spawnerId	= -1;
int LevelParser::m_quickRevId	= -1;
int LevelParser::m_doubleTapId	= -1;
int LevelParser::m_speedColaId	= -1;
int LevelParser::m_jugId		= -1;
int LevelParser::m_ammoId		= -1;

LevelParser::~LevelParser()
{
	delete m_pInstance;
}

void LevelParser::ParseLevel(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene)
{
	/*m_futures.push_back(std::async(std::launch::async, ProcessLevelWalls, pLevelData, filePath, pScene));
	m_futures.push_back(std::async(std::launch::async, ProcessLevelDoors, pLevelData, filePath, pScene));
	m_futures.push_back(std::async(std::launch::async, ProcessEnvironment, pLevelData, filePath, pScene));
	m_futures.push_back(std::async(std::launch::async, LoadNavMesh, pLevelData, filePath));*/

	//std::thread t1(ProcessLevelWalls, pLevelData, filePath, pScene);
	ProcessLevelWalls(pLevelData, filePath, pScene);

	//std::thread t2(ProcessLevelDoors, pLevelData, filePath, pScene);
	ProcessLevelDoors(pLevelData, filePath, pScene);

	//std::thread t3(ProcessEnvironment, pLevelData, filePath, pScene);
	ProcessEnvironment(pLevelData, filePath, pScene);

	// ProcessWallGuns();

	//std::thread t4(LoadNavMesh, pLevelData, filePath);
	LoadNavMesh(pLevelData, filePath);

	/*t1.join();
	t2.join();
	t3.join();
	t4.join();*/
}

void LevelParser::ProcessLevelWalls(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene)
{
	std::vector<std::string> levelFile;
	//Shadow::IOManager::Instance()->LoadTextFile(levelFile, filePath + "_Texture.csv");

	LoadFromTextFile(levelFile, filePath + "_Texture.csv");

	const int WIDTH = pLevelData->LEVEL_WIDTH;
	const int HEIGHT = pLevelData->LEVEL_HEIGHT;

	// Check that the size of the file is correct.
	if (levelFile.size() != HEIGHT)
		Shadow::Log::Instance()->FatalError("The passed in level is not the correct size.\nFile path: " + filePath, Shadow::ERR_CODE::LEVEL_FILE_INCORRECT_LENGTH);

	short startPos = 0;
	short pos;
	std::string strVal;
	for (int row = 0; row < HEIGHT; row++)
	{
		startPos = 0;
		pos = levelFile[row].find(",");
		for (int col = 0; col < WIDTH - 1; col++)
		{
			strVal = levelFile[row].substr(startPos, pos - startPos);

			TileHandler(pLevelData, atoi(strVal.c_str()), col, row, pScene);

			startPos = pos + 1;
			pos = levelFile[row].find(",", startPos);
		}
		strVal = levelFile[row].substr(startPos, levelFile[row].length() - startPos);

		TileHandler(pLevelData, atoi(strVal.c_str()), WIDTH - 1, row, pScene);
	}
}

void LevelParser::TileHandler(LevelData* pLevelData, int tileID, int x, int y, Shadow::Scene* pScene)
{
	pLevelData->mapTiles[tileID].push_back(glm::vec2(x, y));

	switch (tileID)
	{
	case -5: // Air
	case -1: // Floor
		break;
	case -3:
		CreateSolidWallGameObject("Power", "Assets/Environment/powerWall.png", { x * TILE_WIDTH, y * TILE_WIDTH }, pScene, m_powerWallId);
		break;
	case -2: // Player.
		GameManager::Instance()->SetPlayerStartingPos(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
		break;
	case 0: // Walls.
		CreateSolidWallGameObject("Wall", "Assets/Environment/wall.png", { x * TILE_WIDTH, y * TILE_WIDTH }, pScene, m_wallId);
		break;
	case 1: // Zombie Spawners.
		CreateSolidWallGameObject("Spawner", "Assets/Environment/spawner.png", { x * TILE_WIDTH, y * TILE_WIDTH }, pScene, m_spawnerId);
		break;
	default:
		Shadow::Log::Instance()->Warning("Tile passed in with different unprocessed ID. ID: " + std::to_string(tileID));
		break;
	}
}

void LevelParser::ProcessLevelDoors(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene)
{
	std::vector<std::string> levelFile;
	//Shadow::IOManager::Instance()->LoadTextFile(levelFile, filePath + "_Doors.csv");

	LoadFromTextFile(levelFile, filePath + "_Doors.csv");

	const int WIDTH = pLevelData->LEVEL_WIDTH;
	const int HEIGHT = pLevelData->LEVEL_HEIGHT;

	int value;
	short startPos = 0;
	short pos;
	std::string strVal;
	for (int row = 0; row < HEIGHT; row++)
	{
		startPos = 0;
		pos = levelFile[row].find(",");
		for (int col = 0; col < WIDTH - 1; col++)
		{
			strVal = levelFile[row].substr(startPos, pos - startPos);

			value = atoi(strVal.c_str());
			DoorIdHandler(value, col, row, pScene);

			startPos = pos + 1;
			pos = levelFile[row].find(",", startPos);
		}
		strVal = levelFile[row].substr(startPos, levelFile[row].length() - startPos);

		value = atoi(strVal.c_str());

		DoorIdHandler(value, WIDTH - 1, row, pScene);
	}
}

void LevelParser::DoorIdHandler(int value, int x, int y, Shadow::Scene* pScene)
{
	if (value == -1)
		return;

	// The door id is only 1 digit, whereas the triggers are 3 digits, therefore check for one digit to pass a door, else trigger.
	if (value < 10)
		RoomManager::Instance()->AddDoor(glm::vec2(x, y), value, pScene);
	else
		RoomManager::Instance()->AddDoorObject(glm::vec2(x, y), value, pScene);
}

void LevelParser::ProcessEnvironment(LevelData* pLevelData, const std::string& filePath, Shadow::Scene* pScene)
{
	std::vector<std::string> levelFile;
	//Shadow::IOManager::Instance()->LoadTextFile(levelFile, filePath + "_Environment.csv");

	LoadFromTextFile(levelFile, filePath + "_Environment.csv");

	const int WIDTH = pLevelData->LEVEL_WIDTH;
	const int HEIGHT = pLevelData->LEVEL_HEIGHT;

	int value;
	short startPos = 0;
	short pos;
	std::string strVal;
	for (int row = 0; row < HEIGHT; row++)
	{
		startPos = 0;
		pos = levelFile[row].find(",");
		for (int col = 0; col < WIDTH - 1; col++)
		{
			strVal = levelFile[row].substr(startPos, pos - startPos);

			value = atoi(strVal.c_str());
			EnvironmentHandler(pLevelData, value, col, row, pScene);

			startPos = pos + 1;
			pos = levelFile[row].find(",", startPos);
		}
		strVal = levelFile[row].substr(startPos, levelFile[row].length() - startPos);

		value = atoi(strVal.c_str());
		EnvironmentHandler(pLevelData, value, WIDTH - 1, row, pScene);
	}

	RoomManager::Instance()->InitZombieSpawnLocation();
}

void LevelParser::EnvironmentHandler(LevelData* pLevelData, int value, int x, int y, Shadow::Scene* pScene)
{
	if (value == -1)
		return;

	if (value == -2)
		LevelManager::Instance()->AddPowerTrigger(GameManager::Instance()->GetGameScene(), glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));

	// Zombie Spawners.
	if (value < 100)
	{
		pLevelData->spawnPoints[value].push_back(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
		return;
	}

	if (value > 1000 && value < 2000)
	{
		int perkMachine = value / 10;

		LevelManager::Instance()->AddPerkMachineTrigger(GameManager::Instance()->GetGameScene(), perkMachine, glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
		return;
	}

	if (value == 2001)
	{
		LevelManager::Instance()->AddAmmoTrigger(GameManager::Instance()->GetGameScene(), glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
		return;
	}

	// This is where the perk machine code must go.
	int* textureId = nullptr;
	std::string filePath = PerkMachineFilePath(value, textureId);
	CreateSolidWallGameObject("Perk Machine " + std::to_string(value), filePath, { x * TILE_WIDTH, y * TILE_WIDTH }, pScene, *textureId);
}

std::string LevelParser::PerkMachineFilePath(int key, int*& pTextureId)
{
	switch (key)
	{
	case 100:
		pTextureId = &m_quickRevId;
		return "Assets/Environment/PerkMachines/quickRevive.png";
		break;
	case 101:
		pTextureId = &m_speedColaId;
		return "Assets/Environment/PerkMachines/speedCola.png";
		break;
	case 102:
		pTextureId = &m_doubleTapId;
		return "Assets/Environment/PerkMachines/doubleTap.png";
		break;
	case 103:
		pTextureId = &m_jugId;
		return "Assets/Environment/PerkMachines/jug.png";
		break;
	case 2000:
		pTextureId = &m_ammoId;
		return "Assets/Environment/ammo.png";
	default:
		Shadow::Log::Instance()->Warning("Perk machine key not processed. Key: " + std::to_string(key));
		return "";
		break;
	}
}

void LevelParser::CreateSolidWallGameObject(const std::string& gameObjectName, const std::string& filePath, const glm::vec2& position, Shadow::Scene* pScene, int& textureId)
{
	Shadow::GameObject* go = pScene->CreateEmptyGameObject(gameObjectName);
	Shadow::BoxCollider2D* box = new Shadow::BoxCollider2D(go, glm::vec2(TILE_WIDTH >> 1, TILE_WIDTH >> 1));
	Shadow::SpriteRenderer* sr = nullptr;

	if (textureId == -1)
	{
		sr = new Shadow::SpriteRenderer(go, filePath);
		textureId = sr->GetTextureId();
	}
	else
		sr = new Shadow::SpriteRenderer(go, textureId);

	go->AddComponent(box);
	go->AddComponent(sr);
	go->GetTransform()->position = glm::vec3(position.x, position.y, 0.0f);
}

void LevelParser::CreateFloorGameObject(const std::string& gameObjectName, const std::string& filePath, const glm::vec2& position, Shadow::Scene* pScene)
{
	Shadow::GameObject* go = pScene->CreateEmptyGameObject(gameObjectName);
	Shadow::SpriteRenderer* sr = new Shadow::SpriteRenderer(go, filePath);
	go->AddComponent(sr);
	go->GetTransform()->position = glm::vec3(position.x, position.y, 0.0f);
}

void LevelParser::LoadNavMesh(LevelData* pLevelData, const std::string& filePath)
{
	NavMesh* navMesh = new NavMesh();
	std::vector<std::string> levelFile;
	//Shadow::IOManager::Instance()->LoadTextFile(levelFile, filePath + "_NavMesh.csv");

	LoadFromTextFile(levelFile, filePath + "_NavMesh.csv");

	const int WIDTH = pLevelData->LEVEL_WIDTH;
	const int HEIGHT = pLevelData->LEVEL_HEIGHT;

	int value;
	short startPos = 0;
	short pos;
	std::string strVal;
	for (int row = 0; row < HEIGHT; row++)
	{
		navMesh->m_navMesh.push_back(std::vector<int>());

		startPos = 0;
		pos = levelFile[row].find(",");
		for (int col = 0; col < WIDTH - 1; col++)
		{
			strVal = levelFile[row].substr(startPos, pos - startPos);

			value = atoi(strVal.c_str());
			navMesh->m_navMesh[row].push_back(value);

			startPos = pos + 1;
			pos = levelFile[row].find(",", startPos);
		}
		strVal = levelFile[row].substr(startPos, levelFile[row].length() - startPos);

		value = atoi(strVal.c_str());
		navMesh->m_navMesh[row].push_back(value);
	}

	delete pLevelData->pNavMesh;

	pLevelData->pNavMesh = navMesh;
}

void LevelParser::LoadFromTextFile(std::vector<std::string>& levelFile, const std::string& filePath)
{
	std::ifstream fin;
	fin.open(filePath.c_str(), std::ios::in);

	if (fin.fail())
		Shadow::Log::Instance()->FatalError("Failed to open file.\nFile Path: " + filePath, Shadow::ERR_CODE::FAILED_TO_OPEN_FILE);

	std::string line;

	while (std::getline(fin, line, '\n'))
		levelFile.push_back(line);

	fin.close();
}
//
//template<typename Arg1, typename... Args>
//void LevelParser::ProcessTextFromFile(std::vector<std::string>& levelFile, void* function(Arg1, Args&&... Args))
//{
//	const int WIDTH = pLevelData->LEVEL_WIDTH;
//	const int HEIGHT = pLevelData->LEVEL_HEIGHT;
//
//	int value;
//	short startPos = 0;
//	short pos;
//	std::string strVal;
//	for (int row = 0; row < HEIGHT; row++)
//	{
//		function(std::vector<int>());
//		navMesh->m_navMesh.push_back(std::vector<int>());
//
//		startPos = 0;
//		pos = levelFile[row].find(",");
//		for (int col = 0; col < WIDTH - 1; col++)
//		{
//			strVal = levelFile[row].substr(startPos, pos - startPos);
//
//			value = atoi(strVal.c_str());
//			function;
//			navMesh->m_navMesh[row].push_back(value);
//
//			startPos = pos + 1;
//			pos = levelFile[row].find(",", startPos);
//		}
//		strVal = levelFile[row].substr(startPos, levelFile[row].length() - startPos);
//
//		value = atoi(strVal.c_str());
//		navMesh->m_navMesh[row].push_back(value);
//	}
//}
//
//void LevelParser::Test(int x, int y, int z)
//{
//
//}