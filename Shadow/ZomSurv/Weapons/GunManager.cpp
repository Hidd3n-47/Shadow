#include "sdpch.h"
#include "GunManager.h"

#include "Gun.h"
#include "FileIO/IOManager.h"

GunManager* GunManager::m_pInstance = nullptr;

GunManager::GunManager()
{
	// Empty.
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