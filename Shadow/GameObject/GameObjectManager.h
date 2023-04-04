//#pragma once
//
//#include "GameObject.h"
//
//SHADOW_NAMESPACE_BEGIN
//
//class GameObjectManager
//{
//public:
//	inline static GameObjectManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new GameObjectManager() : m_pInstance; }
//
//	GameObject* CreateEmptyGameObject(const std::string& name);
//	bool RemoveGameObject(GameObject* gameObject);
//
//	void Update();
//	void Render();
//private:
//	GameObjectManager() { }
//	~GameObjectManager() { }
//
//	static GameObjectManager* m_pInstance;
//	
//	std::vector<GameObject*> m_gameObjects;
//};
//
//
//SHADOW_NAMESPACE_END