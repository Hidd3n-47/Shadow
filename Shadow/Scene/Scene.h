#pragma once

#include "Window/Window.h"
#include "Camera/Camera.h"
#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

class GameObject;

class Scene
{
	friend class SceneManager;
public:
	GameObject* CreateEmptyGameObject(std::string name);
	bool RemoveGameObject(GameObject* gameObject);

	void Update();
	void PhysicsUpdate();
	void Render();

	// Accessors.
	inline uint8_t GetSceneIndex() const { return m_index; }
	inline std::string GetName() const { return m_name; }
	inline Window* GetWindow() const { return m_pWindow; }
	inline Camera* GetCamera() const { return m_pCamera; }
private:
	Scene(uint8_t sceneIndex, const std::string& name, Window* pWindow, Camera* pCamera);
	~Scene();

	uint8_t m_index = 0;
	std::string m_name = "none";
	Window* m_pWindow = nullptr;
	Camera* m_pCamera = nullptr;

	std::vector<GameObject*> m_gameObjects;
	std::unordered_map<std::string, unsigned int> m_gameObjectNames;
};

SHADOW_NAMESPACE_END