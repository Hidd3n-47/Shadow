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
	inline void PhysicsUpdateActiveScene() { m_scenes[m_activeSceneIndex]->PhysicsUpdate(); }
	inline void RenderActiveScene() { m_scenes[m_activeSceneIndex]->Render(); }

	// Accessors.
	inline Scene* GetActiveScene() { return m_scenes[m_activeSceneIndex]; }
private:
	SceneManager() { }
	~SceneManager() { delete m_pInstance; }
	static SceneManager* m_pInstance;

	//std::unordered_map<std::string, Scene*> m_scenes;
	std::vector<Scene*> m_scenes;
	uint8_t m_activeSceneIndex = 0;
};

SHADOW_NAMESPACE_END