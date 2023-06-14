#include "sdpch.h"
#include "Ammo.h"

Ammo* Ammo::m_pInstance = nullptr;

Ammo::Ammo()
{
	m_ammoCount[AmmoType::LIGHT] = MAX_LIGHT;
	m_ammoCount[AmmoType::MEDIUM] = MAX_MEDIUM;
	m_ammoCount[AmmoType::HEAVY] = MAX_HEAVY;
	m_ammoCount[AmmoType::SPECIAL] = MAX_SPECIAL;
}

Ammo::~Ammo()
{
	delete m_pInstance;
}

void Ammo::AddAmmo(AmmoType ammoType, unsigned short amount)
{
	unsigned short max = 0;

	switch (ammoType)
	{
	case AmmoType::LIGHT:
		max = MAX_LIGHT;
		break;
	case AmmoType::MEDIUM:
		max = MAX_MEDIUM;
		break;
	case AmmoType::HEAVY:
		max = MAX_HEAVY;
		break;
	case AmmoType::SPECIAL:
		max = MAX_SPECIAL;
		break;
	default:
		Shadow::Log::Instance()->Warning("Different Ammo Type passed into AddAmmo method.");
		break;
	}

	ClampTop(m_ammoCount[ammoType], amount, max);
}

void Ammo::ReduceAmmo(AmmoType ammoType, unsigned short amount)
{
	if (m_ammoCount[ammoType] < amount)
		m_ammoCount[ammoType] = 0;
	else
		m_ammoCount[ammoType] -= amount;
}

void Ammo::ClampTop(unsigned short& value, unsigned short addition, unsigned int max)
{
	unsigned short total = value + addition;
	value = total > max ? max : total;
}

void Ammo::MaxAmmo()
{
	m_ammoCount[AmmoType::LIGHT]	= MAX_LIGHT;
	m_ammoCount[AmmoType::MEDIUM]	= MAX_MEDIUM;
	m_ammoCount[AmmoType::HEAVY]	= MAX_HEAVY;
	m_ammoCount[AmmoType::SPECIAL]	= MAX_SPECIAL;
}

bool Ammo::IsMaxAmmo()
{
	if (m_ammoCount[AmmoType::LIGHT] != MAX_LIGHT)
		return false;

	if (m_ammoCount[AmmoType::MEDIUM] != MAX_MEDIUM)
		return false;

	if (m_ammoCount[AmmoType::HEAVY] != MAX_HEAVY)
		return false;

	if (m_ammoCount[AmmoType::SPECIAL] != MAX_SPECIAL)
		return false;

	return true;
}