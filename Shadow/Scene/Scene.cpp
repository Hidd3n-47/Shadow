#include "sdpch.h"
#include "Scene.h"

#include "GameObject/GameObject.h"
#include "Window/Window.h"
#include "Camera/Camera.h"

SHADOW_NAMESPACE_BEGIN

Scene::Scene(const std::string& name, Window* pWindow, Camera* pCamera) : 
	m_name(name), 
	m_pWindow(pWindow), 
	m_pCamera(pCamera)
{

}

Scene::~Scene()
{
	for (int i = m_gameObjects.size() - 1; i > -1; i--)
		RemoveGameObject(m_gameObjects[i]);
}

GameObject* Scene::CreateEmptyGameObject(std::string name)
{
	FindNextUniqueName(name);

	GameObject* gameObject = new GameObject(this, name);
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

	for (GameObject* go : m_gameObjects)
	{
		if (go != gameObject)
			continue;

		delete go;
		go = m_gameObjects.back();
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
	for (GameObject* gm : m_gameObjects)
		gm->Update();
}

void Scene::Render()
{
	// Render each of the game objects.
	for (GameObject* gm : m_gameObjects)
		gm->Render();
}

void Scene::FindNextUniqueName(std::string& name)
{
	std::string original = name;
	int counter = 0;

	while (GameObjectNameTaken(name))
	{
		counter++;

		name = original + " (" + std::to_string(counter) + ")";
	}
}

bool Scene::GameObjectNameTaken(const std::string& name)
{
	for (GameObject* go : m_gameObjects)
		if (go->GetName() == name)
			return true;

	return false;
}

SHADOW_NAMESPACE_END