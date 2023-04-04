#pragma once

SHADOW_NAMESPACE_BEGIN

class GameObject;
class Window;
class Camera;

class Scene
{
	friend class SceneManager;
public:
	GameObject* CreateEmptyGameObject(std::string name);
	bool RemoveGameObject(GameObject* gameObject);

	void Update();

	void Render();

	// Accessors.
	inline std::string GetName() const { return m_name; }
	inline Window* GetWindow() const { return m_pWindow; }
	inline Camera* GetCamera() const { return m_pCamera; }
private:
	Scene(const std::string& name, Window* pWindow, Camera* pCamera);
	~Scene();

	std::string m_name;
	Window* m_pWindow = nullptr;
	Camera* m_pCamera = nullptr;

	std::vector<GameObject*> m_gameObjects;

	void FindNextUniqueName(std::string& name);
	bool GameObjectNameTaken(const std::string& name);
};

SHADOW_NAMESPACE_END