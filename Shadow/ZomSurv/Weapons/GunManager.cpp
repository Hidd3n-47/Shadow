#include "sdpch.h"
#include "GunManager.h"

#include "Time/Time.h"

#include "ZomSurv/src/GameManager.h"
#include "Gun.h"
#include "FileIO/IOManager.h"

GunManager* GunManager::m_pInstance = nullptr;

GunManager::GunManager()
{
	Shadow::Scene* pScene = Shadow::SceneManager::Instance()->GetActiveScene();

	m_pFlashGameObject = pScene->CreateEmptyGameObject("FlashGameObject");

	m_pSpriteRenderer = new Shadow::SpriteRenderer(m_pFlashGameObject, "Assets/gunFlash.png", FLASH_DIMENSIONS);
	m_pFlashGameObject->AddComponent(m_pSpriteRenderer);

	m_pFlashGameObject->SetIsActive(false);
}

GunManager::~GunManager()
{
	delete m_pInstance;
}

Gun* GunManager::LoadGun(const std::string& filePath)
{
	std::vector<std::string> gunInfo;
	Shadow::IOManager::Instance()->LoadTextFile(gunInfo, filePath);
	
	if(gunInfo.size() != 7)
		Shadow::Log::Instance()->FatalError("Gun file has incorrect size.\nFile path:" + filePath, Shadow::ERR_CODE::GUN_FILE_INCORRECT_LENGTH);

	std::string name = gunInfo[0];

	bool automatic;
	if (gunInfo[1] == "false")
		automatic = false;
	else
		automatic = true;

	float damage = std::stof(gunInfo[2]);

	float fireRate = std::stof(gunInfo[3]);

	std::string ammoTypeString = gunInfo[4];
	AmmoType ammoType;

	float clipSize = std::stof(gunInfo[5]);

	float timeToReload = std::stof(gunInfo[6]);

	if (!AmmoTypeFromString(ammoType, ammoTypeString))
		Shadow::Log::Instance()->FatalError("Invalid ammo type: " + ammoTypeString + " passed in gun with name: " + name, Shadow::ERR_CODE::INVALID_AMMOTYPE_IN_GUN_FILE);
	
	return new Gun(name, automatic, damage, fireRate, ammoType, (unsigned int)clipSize, timeToReload);
}

void GunManager::Update()
{
	if (!m_render)
		return;

	UpdateFlashPosition();

	m_timer -= Shadow::Time::Instance()->GetDeltaTime();

	if (m_timer <= 0.0f)
		m_pFlashGameObject->SetIsActive(false);
	else
		return;

	m_render = false;
}

void GunManager::Render()
{
	m_render = true;
	m_pFlashGameObject->SetIsActive(true);
	m_timer = FLASH_TIME;
}

void GunManager::UpdateFlashPosition()
{
	glm::vec2 pos = GameManager::Instance()->GetPlayerPosition();
	float angle = GameManager::Instance()->GetPlayerRotation();

	pos += glm::vec2(RADIUS);

	angle += 180;

	pos += glm::vec2(-glm::sin(angle * PI / 180) * RADIUS - FLASH_DIMENSIONS.x * 0.5f, glm::cos(angle * PI / 180) * RADIUS - FLASH_DIMENSIONS.y * 0.5f);
	m_pFlashGameObject->GetTransform()->position = glm::vec3(pos, 0.0f);
}

bool GunManager::AmmoTypeFromString(AmmoType& ammoType, const std::string& str)
{
	if (str == "LIGHT")
		ammoType = AmmoType::LIGHT;
	else if (str == "MEDIUM")
		ammoType = AmmoType::MEDIUM;
	else if (str == "HEAVY")
		ammoType = AmmoType::HEAVY;
	else if (str == "SPECIAL")
		ammoType = AmmoType::SPECIAL;
	else
		return false;

	return true;
}