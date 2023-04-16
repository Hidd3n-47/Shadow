#pragma once

#include <box2d/b2_world.h>

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
	void PhysicsUpdate();
	void Render();

	// Accessors.
	inline std::string GetName() const { return m_name; }
	inline Window* GetWindow() const { return m_pWindow; }
	inline Camera* GetCamera() const { return m_pCamera; }
	inline b2World* GetPhysicsWorld() const { return m_pPhysicsWorld; }
private:
	Scene(const std::string& name, Window* pWindow, Camera* pCamera);
	~Scene();

	std::string m_name;
	Window* m_pWindow = nullptr;
	Camera* m_pCamera = nullptr;

	std::vector<GameObject*> m_gameObjects;

	b2World* m_pPhysicsWorld = nullptr;

	const int32 m_velocityIterations = 6;
	const int32 m_positionIterations = 2;
};

SHADOW_NAMESPACE_END