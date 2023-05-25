#include "sdpch.h"
#include "PickUpManager.h"

#include "Graphics/TextureManager.h"
#include "Random/Random.h"

PickUpManager* PickUpManager::m_pInstance = nullptr;

PickUpManager::PickUpManager()
{
	m_pScene = Shadow::SceneManager::Instance()->GetActiveScene();

	SDL_Renderer* pRen = m_pScene->GetWindow()->GetRenderer();
	m_maxAmmoTexture = Shadow::TextureManager::Instance()->Load("Assets/Pickups/maxAmmo.png", pRen);
	m_nukeTexture = Shadow::TextureManager::Instance()->Load("Assets/Pickups/nuke.png", pRen);
	m_instaKillTexture = Shadow::TextureManager::Instance()->Load("Assets/Pickups/instaKill.png", pRen);
	m_doublePointsTexture = Shadow::TextureManager::Instance()->Load("Assets/Pickups/doublePoints.png", pRen);
}

void PickUpManager::SpawnPickup(const glm::vec2& position)
{
	int index = (int)PickUpType::Count;

	int rand = Shadow::Random::GetRandomIntBetween(0, 100);

	// 70% chance that no pick up spawns.
	if (rand < 70)
		return;

	index = rand % index;

	switch (index)
	{
	case (int)PickUpType::MAX_AMMO:
		m_pickups.push_back(new MaxAmmo(m_pScene, position, m_maxAmmoTexture));
		break;
	case (int)PickUpType::NUKE:
		m_pickups.push_back(new Nuke(m_pScene, position, m_nukeTexture));
		break;
	case (int)PickUpType::INSTA_KILL:
		m_pickups.push_back(new InstaKill(m_pScene, position, m_instaKillTexture));
		break;
	case (int)PickUpType::DOUBLE_POINTS:
		m_pickups.push_back(new DoublePoints(m_pScene, position, m_doublePointsTexture));
		break;
	}

}

void PickUpManager::Update()
{
	std::vector<int> deleteIndex;
	for (int i = 0; i < m_pickups.size(); i++)
		if (m_pickups[i]->Update())
			deleteIndex.push_back(i);

	for (int i = deleteIndex.size() - 1; i >= 0; i--)
	{
		m_pScene->RemoveGameObject(m_pickups[deleteIndex[i]]->GetGameObject());

		delete m_pickups[deleteIndex[i]];
		m_pickups[deleteIndex[i]] = m_pickups.back();
		m_pickups.pop_back();
	}
}