#include "sdpch.h"
#include "Scene.h"

#include "GameObject/GameObject.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

Scene::Scene(uint8_t sceneIndex, const std::string& name, Window* pWindow, Camera* pCamera) :
	m_index(sceneIndex),
	m_name(name), 
	m_pWindow(pWindow), 
	m_pCamera(pCamera)
{
	// Empty.	
}

Scene::~Scene()
{
	for (int i = m_gameObjects.size() - 1; i > -1; i--)
		RemoveGameObject(m_gameObjects[i]);
}

GameObject* Scene::CreateEmptyGameObject(std::string name)
{
	std::string sceneName = name;
	auto it = m_gameObjectNames.find(name);
	if (it != m_gameObjectNames.end())
		sceneName += " (" + std::to_string(m_gameObjectNames[name]++) + ")";
	else
		m_gameObjectNames[name] = 0;

	GameObject* gameObject = new GameObject(this, sceneName);
	m_gameObjects.push_back(gameObject);

	DLOG("Game object '" + name + "' created.");
	return gameObject;
}

bool Scene::RemoveGameObject(GameObject* gameObject)
{
	std::string name = gameObject->GetName();

	if (gameObject == m_gameObjects.back())
	{
		delete m_gameObjects.back();
		m_gameObjects.pop_back();

		DLOG("Game object '" + name + "' destroyed.");
		return true;
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != gameObject)
			continue;

		delete m_gameObjects[i];
		m_gameObjects[i] = m_gameObjects.back();
		m_gameObjects.pop_back();

		DLOG("Game object '" + name + "' destroyed.");
		return true;
	}

	return false;
}

void Scene::Update()
{
	m_pCamera->Update();

	// Update each of the game objects.
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->Update();
}

void Scene::PhysicsUpdate()
{
	// Update each of the game objects physics.
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->PhysicsUpdate();

	float ts = Time::Instance()->GetDeltaTime();
}

void Scene::Render()
{
	// Render each of the game objects.
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->Render();
}

SHADOW_NAMESPACE_END