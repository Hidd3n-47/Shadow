#pragma once

#include "Component/SpriteRenderer.h"

#include "Ammo/Ammo.h"

class Gun;

class GunManager
{
public:
	inline static GunManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new GunManager() : m_pInstance; }

	Gun* LoadGun(const std::string& filePath);

	void Update();
	void Render();

private:
	GunManager();
	~GunManager();

	static GunManager* m_pInstance;

	Shadow::GameObject* m_pFlashGameObject = nullptr;
	Shadow::SpriteRenderer* m_pSpriteRenderer = nullptr;

	bool m_render = false;

	const glm::vec2 FLASH_DIMENSIONS = glm::vec2(10, 10);
	const int GUN_PIXEL_OFFSET = 18;
	const int RADIUS = TILE_WIDTH * 0.5f;
	const float FLASH_TIME = 0.1f;
	float m_timer = 0.0f;

	void UpdateFlashPosition();
	bool AmmoTypeFromString(AmmoType& ammoType, const std::string& str);

};

