#include "sdpch.h"
//#include "GameObjectManager.h"
//
//SHADOW_NAMESPACE_BEGIN
//
//GameObjectManager* GameObjectManager::m_pInstance = nullptr;
//
//GameObject* GameObjectManager::CreateEmptyGameObject(const std::string& name)
//{
//	GameObject* gameObject = new GameObject(name);
//	m_gameObjects.push_back(gameObject);
//
//	Log::Instance()->DebugLog("Game object " + m_gameObjects.back()->GetName() + " created.");
//
//	return gameObject;
//}
//
//bool GameObjectManager::RemoveGameObject(GameObject* gameObject)
//{
//	if (gameObject == m_gameObjects.back())
//	{
//		Log::Instance()->DebugLog("Game object " + gameObject->m_name + " destroyed.");
//		delete m_gameObjects.back();
//		m_gameObjects.pop_back();
//
//		return true;
//	}
//
//	for (GameObject* go : m_gameObjects)
//	{
//		if (go != gameObject)
//			continue;
//
//		Log::Instance()->DebugLog("Game object " + gameObject->m_name + " destroyed.");
//
//		delete go;
//		go = m_gameObjects.back();
//		m_gameObjects.pop_back();
//
//		return true;
//	}
//
//	return false;
//}
//
//void GameObjectManager::Update()
//{
//	// update each game object.
//	for (GameObject* gm : m_gameObjects)
//		gm->Update();
//}
//
//void GameObjectManager::Render()
//{
//	for (GameObject* gm : m_gameObjects)
//		gm->Render();
//}
//
//SHADOW_NAMESPACE_END