#pragma once

#include "Bullet.h"

class BulletManager
{
public:
	inline static BulletManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new BulletManager() : m_pInstance; }

	void CreateBullet(const glm::vec2& pos, const glm::vec2& dir, float dam);

	void Update();

	float DestroyBullet(Shadow::GameObject* gameObject);

	void DestroyBulletsInQueue();

	// Accessor.
	inline float GetVelocity() const { return m_bulletVelocity; }
private:
	BulletManager();
	~BulletManager();

	static BulletManager* m_pInstance;

	Shadow::Scene* m_pScene = nullptr;
	int m_textureId = -1;
	float m_bulletVelocity = 12000.0f;

	std::vector<Bullet*> m_bullets;

	std::vector<int> m_bulletsToBeDeletedIndex;

	bool InQueueAlready(int index);
};

