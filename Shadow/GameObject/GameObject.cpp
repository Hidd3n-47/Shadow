#include "sdpch.h"
#include "GameObject.h"

#include "GameObjectManager.h"
#include "Component/SpriteRenderer.h"

SHADOW_NAMESPACE_BEGIN

GameObject::GameObject(Scene* pOwner, const std::string& name) :
	m_pOwner(pOwner),
	m_name(name),
	m_pTransform(new Transform())
{
	// Empty.
}

GameObject::~GameObject()
{
	RemoveAllComponents();

	delete m_pTransform;
}

void GameObject::AddComponent(IComponent* component)
{
	if (HasComponent(component->GetComponentType()))
	{
		Log::Instance()->Warning("'" + m_name + "' Game Object aldready has this component.");
		return;
	}

	m_components.push_back(component);
	m_components.back()->OnComponentAdd();
}

void GameObject::RemoveComponent(ComponentType component)
{
	for (IComponent* comp : m_components)
	{
		if (comp->GetComponentType() != component)
			continue;

		comp->OnComponentRemove();
		delete comp;
		m_components.remove(comp);
		return;
	}

	Log::Instance()->Warning("'" + m_name + "' Game Object does not have this component.");
}

void GameObject::RemoveAllComponents()
{
	for (IComponent* component : m_components)
	{
		component->OnComponentRemove();

		delete component;
	}
	m_components.clear();
}

bool GameObject::HasComponent(ComponentType component)
{
	for (IComponent* comp : m_components)
		if (comp->GetComponentType() == component)
			return true;

	return false;
}

IComponent* GameObject::GetComponent(ComponentType component)
{
	for (IComponent* comp : m_components)
		if (comp->GetComponentType() == component)
			return comp;

	return nullptr;
}

void GameObject::Update()
{
	for (IComponent* comp : m_components)
		comp->Update();
}

void GameObject::Render()
{
	// ADDITION: Could add debugging render to this.

	for (IComponent* comp : m_components)
	{
		comp->Render(m_pTransform->position);
	}
}

SHADOW_NAMESPACE_END