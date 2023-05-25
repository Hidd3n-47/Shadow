#include "sdpch.h"
#include "SceneManager.h"

SHADOW_NAMESPACE_BEGIN

SceneManager* SceneManager::m_pInstance = nullptr;

Scene* SceneManager::CreateEmptyScene(const std::string& name, Window* pWindow, Camera* pCamera)
{
	std::string sceneName = name;
	auto it = m_sceneNames.find(name);
	if (it != m_sceneNames.end())
		sceneName += " (" + std::to_string(m_sceneNames[name]++) + ")";
	else
		m_sceneNames[name] = 0;

	Scene* scene = new Scene(m_scenes.size(), sceneName, pWindow, pCamera);
	m_scenes.push_back(scene);

	DLOG("Scene '" + name + "' created.");
	return scene;
}

bool SceneManager::DestroyScene(Scene* scene)
{
	std::string name = scene->m_name;

	if (scene == m_scenes.back())
	{
		delete m_scenes.back();
		m_scenes.pop_back();

		DLOG("Scene '" + name + "' destroyed.");
		return true;
	}

	for(int i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != scene)
			continue;

		delete m_scenes[i];
		m_scenes[i] = m_scenes.back();
		m_scenes.pop_back();

		DLOG("Scene '" + name + "' destroyed.");
		return true;
	}

	return false;
}

void SceneManager::DestroyAllScenes()
{
	for (int i = m_scenes.size() -1; i > -1; i--)
		DestroyScene(m_scenes[i]);
}

SHADOW_NAMESPACE_END