#pragma once

#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

class CollisionHandler
{
public:
	inline static CollisionHandler* Instance() { return m_pInstance == nullptr ? m_pInstance = new CollisionHandler() : m_pInstance; }

	void Update();

	inline void AddToDynamic(GameObject* go) { m_dynamicObjects.push_back(go); }
	inline void AddToStatic(GameObject* go) { m_staticObjects.push_back(go); }
	inline void AddToQueue(GameObject* go) { m_dynamicQueue.push_back(go); }
private:
	CollisionHandler() { }
	~CollisionHandler() { delete m_pInstance; }

	static CollisionHandler* m_pInstance;

	std::vector<GameObject*> m_dynamicObjects;
	std::vector<GameObject*> m_staticObjects;

	std::vector<GameObject*> m_dynamicQueue;

	void CheckCollisionAgainstStatic(GameObject* go);
};

SHADOW_NAMESPACE_END