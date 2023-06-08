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
	for (int i = 0; i < m_components.size(); i++)
	{
		if (m_components[i]->GetComponentType() != component)
			continue;

		delete m_components[i];
		m_components[i] = m_components.back();
		m_components.pop_back();
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
	for (int i = 0; i < m_components.size(); i++)
		if (m_components[i]->GetComponentType() == component)
			return m_components[i];

	return nullptr;
}

void GameObject::Update()
{
	if (!m_isActive)
		return;

	for (IComponent* comp : m_components)
		comp->Update();
}

void GameObject::PhysicsUpdate()
{
	if (!m_isActive)
		return;

	for (IComponent* comp : m_components)
		comp->PhysicsUpdate();
}

void GameObject::Render()
{
	if (!m_isActive)
		return;

	for (IComponent* comp : m_components)
		comp->Render(m_pTransform->position);
}

SHADOW_NAMESPACE_END