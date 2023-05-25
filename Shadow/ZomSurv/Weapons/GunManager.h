#pragma once

#include "Ammo/Ammo.h"

class Gun;

class GunManager
{
public:
	inline static GunManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new GunManager() : m_pInstance; }

	Gun* LoadGun(const std::string& filePath);

private:
	GunManager();
	~GunManager();

	static GunManager* m_pInstance;

	bool AmmoTypeFromString(AmmoType& ammoType, const std::string& str);
};

