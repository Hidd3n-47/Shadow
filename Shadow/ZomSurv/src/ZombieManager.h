#pragma once

#include "Scene/Scene.h"
#include "ZomSurv/Entity/Zombie/IZombie.h"

#define INSTA_KILL_TIMER_DEFAULT -69.47

class ZombieManager
{
public:
	inline static ZombieManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new ZombieManager() : m_pInstance; }

	void Update(const glm::vec3& playerPosition);

	void SpawnZombie();

	void DamageZombie(Shadow::GameObject* gameObject, float damage);
	
	void Nuke();

	void DestroyZombiesInQueue();

	inline void ActivateDoubleTap() { m_doubleTapMultiplier = 2.0f; }
	inline void ActivateInstaKill() { m_damageMultiplier = 20000.0f; m_instaKillTimer = INTA_KILL_TIMER; }

	// Accesors.
	inline uint16_t GetNumZombies() const { return m_numZombies; }
private:
	ZombieManager();
	~ZombieManager();

	static ZombieManager* m_pInstance;

	Shadow::Scene* m_pScene;

	std::vector<IZombie*> m_zombies;
	std::vector<int> m_zombiesToBeDeletedIndex;

	int m_textureId = -1;
	uint16_t m_numZombies = 0;

	float m_doubleTapMultiplier = 1.0f;

	const float INTA_KILL_TIMER = 10.0f;
	short m_damageMultiplier = 1.0f;
	float m_instaKillTimer = INSTA_KILL_TIMER_DEFAULT;

	bool InQueueAlready(int index);
};

