#include "sdpch.h"
#include "ZombieManager.h"

#include "Time/Time.h"
#include "Scene/SceneManager.h"
#include "Graphics/TextureManager.h"

#include "ZomSurv/Level/Room/RoomManager.h"
#include "ZomSurv/PickUp/PickUpManager.h"
#include "GameManager.h"


ZombieManager* ZombieManager::m_pInstance = nullptr;

ZombieManager::ZombieManager()
{
	m_pScene = GameManager::Instance()->GetScene();
	m_textureId = Shadow::TextureManager::Instance()->Load("Assets/Entity/zombie.png", m_pScene->GetWindow()->GetRenderer());
}

ZombieManager::~ZombieManager()
{
	delete m_pInstance;
}

void ZombieManager::Update(const glm::vec3& playerPosition)
{
	// TODO. Could do multi threading here due to the zombies being independant.
	for (IZombie* zom : m_zombies)
		zom->Update(playerPosition);

	if (m_instaKillTimer == INSTA_KILL_TIMER_DEFAULT)
		return;

	float dt = Shadow::Time::Instance()->GetDeltaTime();

	m_instaKillTimer -= dt;
	if (m_instaKillTimer > 0)
		return;

	m_instaKillTimer = INSTA_KILL_TIMER_DEFAULT;
	m_damageMultiplier = 1.0f;
}

void ZombieManager::SpawnZombie()
{
	const int maxWaves = 50;
	const int maxZomHealth = 1000;
	const int zombieStartinHealth = 100;

	unsigned int x = GameManager::Instance()->GetWave();
	unsigned int health = -maxZomHealth / (4 * pow(maxWaves, 3)) * pow(x, 3) + 3 * maxZomHealth / (4 * pow(maxWaves, 2)) * pow(x, 2) + zombieStartinHealth;
	m_zombies.push_back(new IZombie(m_pScene, RoomManager::Instance()->GetRandomSpawnLocation(), health, m_textureId));

	m_numZombies++;
}

void ZombieManager::DamageZombie(Shadow::GameObject* gameObject, float damange)
{
	for(int i = 0; i < m_zombies.size(); i++)
		if(m_zombies[i]->GetGameObject() == gameObject)
			if (!m_zombies[i]->Damage(m_doubleTapMultiplier * m_damageMultiplier * damange))
			{
				if(!InQueueAlready(i))
					m_zombiesToBeDeletedIndex.push_back(i);

				GameManager::Instance()->AddPlayerScore(100);

				return;
			}
}

void ZombieManager::Nuke()
{
	for (int i = 0; i < m_zombies.size(); i++)
		m_zombiesToBeDeletedIndex.push_back(i);
}

void ZombieManager::DestroyZombiesInQueue()
{
	for (int i = m_zombiesToBeDeletedIndex.size() - 1; i >= 0; i--)
	{
		PickUpManager::Instance()->SpawnPickup(m_zombies[m_zombiesToBeDeletedIndex[i]]->GetPosition());
		delete m_zombies[m_zombiesToBeDeletedIndex[i]];
		m_zombies[m_zombiesToBeDeletedIndex[i]] = m_zombies.back();
		m_zombies.pop_back();

		m_numZombies--;
	}

	m_zombiesToBeDeletedIndex.clear();
}

bool ZombieManager::InQueueAlready(int index)
{
	for (int i : m_zombiesToBeDeletedIndex)
		if (i == index)
			return true;

	return false;
}