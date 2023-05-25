#include "sdpch.h"
#include "BulletManager.h"

#include "Graphics/TextureManager.h"

BulletManager* BulletManager::m_pInstance = nullptr;

BulletManager::BulletManager()
{
	// Empty.
}

BulletManager::~BulletManager()
{
	delete m_pInstance;
}

void BulletManager::CreateBullet(const glm::vec2& pos, const glm::vec2& dir, float damage)
{
	if (m_pScene == nullptr)
		m_pScene = Shadow::SceneManager::Instance()->GetActiveScene();

	m_bullets.push_back(new Bullet(m_pScene, pos, dir, damage));
}

void BulletManager::Update()
{
	for (Bullet* bullet : m_bullets)
		bullet->Update();
}

float BulletManager::DestroyBullet(Shadow::GameObject* gameObject)
{
	float damage = 0;
	for(int i = 0; i < m_bullets.size(); i++)
		if (m_bullets[i]->GetGameObject() == gameObject)
		{
			if(!InQueueAlready(i))
				m_bulletsToBeDeletedIndex.push_back(i);
			return m_bullets[i]->GetDamage();
		}

	return damage;
}

void BulletManager::DestroyBulletsInQueue()
{
	for (int i = m_bulletsToBeDeletedIndex.size() - 1; i >= 0; i--)
	{
		delete m_bullets[m_bulletsToBeDeletedIndex[i]];
		m_bullets[m_bulletsToBeDeletedIndex[i]] = m_bullets.back();
		m_bullets.pop_back();
	}

	m_bulletsToBeDeletedIndex.clear();
}

bool BulletManager::InQueueAlready(int index)
{
	for (int i : m_bulletsToBeDeletedIndex)
		if (i == index)
			return true;

	return false;
}