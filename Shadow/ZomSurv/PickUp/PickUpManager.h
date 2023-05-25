#pragma once

#include "IPickUp.h"

class PickUpManager
{
public:
	inline static PickUpManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new PickUpManager() : m_pInstance; }

	void SpawnPickup(const glm::vec2& position);
	void Update();

private:
	PickUpManager();
	~PickUpManager() { delete m_pInstance; }

	static PickUpManager* m_pInstance;

	Shadow::Scene* m_pScene = nullptr;

	std::vector<IPickUp*> m_pickups;

	// Texture ID's.
	uint16_t m_maxAmmoTexture		= 0;
	uint16_t m_nukeTexture			= 0;
	uint16_t m_instaKillTexture		= 0;
	uint16_t m_doublePointsTexture	= 0;
};

