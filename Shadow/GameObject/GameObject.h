#include "sdpch.h"
#pragma once

#include "Component/IComponent.h"
#include "Physics/Transform.h"

#include "Scene/Scene.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
GAME_OBJECT:
	Game Object interface.
=========================================================================================
*/
class GameObject
{
	friend class Scene;
	friend class GameObjectManager;
public:
	void AddComponent(IComponent* component);
	void RemoveComponent(ComponentType component);
	void RemoveAllComponents();

	bool HasComponent(ComponentType component);

	// Accessors.
	inline Scene* GetSceneParent() const { return m_pOwner; }
	inline Transform* GetTransform() const { return m_pTransform; }
	inline std::string GetName() const { return m_name; }
	IComponent* GetComponent(ComponentType component);

	// tmp
	glm::vec2 dim;
private:
	GameObject(Scene* pOwner, const std::string& name);
	~GameObject();

	Scene* m_pOwner = nullptr;
	std::string m_name;
	Transform* m_pTransform;
	
	std::list<IComponent*> m_components;

	void Update();
	void Render();
};

SHADOW_NAMESPACE_END