#include "sdpch.h"
#pragma once

#include "Component/IComponent.h"
#include "Physics/Transform.h"

#include "Scene/Scene.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
GAME_OBJECT:
	A game object is any object that is placed in a Scene and can have components added.
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
	inline std::string GetTag() const { return m_tag; }
	inline bool GetIsActive() const { return m_isActive; }

	// Mutators.
	inline void SetTag(const std::string& tag) { m_tag = tag; }
	inline void SetIsActive(bool activity) { m_isActive = activity; }
private:
	GameObject(Scene* pOwner, const std::string& name);
	~GameObject();

	Scene* m_pOwner = nullptr;
	std::string m_name;
	Transform* m_pTransform;

	std::string m_tag = "";

	bool m_isActive = true;
	
	//std::list<IComponent*> m_components;
	std::vector<IComponent*> m_components;

	void Update();
	void PhysicsUpdate();
	void Render();
};

SHADOW_NAMESPACE_END