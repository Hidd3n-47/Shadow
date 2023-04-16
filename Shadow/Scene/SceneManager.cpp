#include "sdpch.h"
#include "SceneManager.h"

SHADOW_NAMESPACE_BEGIN

SceneManager* SceneManager::m_pInstance = nullptr;

Scene* SceneManager::CreateEmptyScene(std::string name, Window* pWindow, Camera* pCamera)
{
	FindNextUniqueName(m_scenes, name);

	Scene* scene = new Scene(name, pWindow, pCamera);
	//m_scenes[name] = scene;
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

	for (Scene* s : m_scenes)
	{
		if (s != scene)
			continue;

		delete s;
		s = m_scenes.back();
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