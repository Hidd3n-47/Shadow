#pragma once

#include "Scene.h"

SHADOW_NAMESPACE_BEGIN

class SceneManager
{
public:
	inline static SceneManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new SceneManager() : m_pInstance; }

	Scene* CreateEmptyScene(std::string name, Window* pWindow, Camera* pCamera);
	bool DestroyScene(Scene* scene);
	void DestroyAllScenes();

	inline void UpdateActiveScene() { m_scenes[m_activeSceneIndex]->Update(); }
	inline void RenderActiveScene() { m_scenes[m_activeSceneIndex]->Render(); }
private:
	SceneManager() { }
	~SceneManager() { delete m_pInstance; }
	static SceneManager* m_pInstance;

	//std::unordered_map<std::string, Scene*> m_scenes;
	std::vector<Scene*> m_scenes;
	uint8_t m_activeSceneIndex = 0;

	void FindNextUniqueName(std::string& name);
	bool SceneNameTaken(const std::string& name);
};

SHADOW_NAMESPACE_END