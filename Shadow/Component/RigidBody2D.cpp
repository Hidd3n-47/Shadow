#include "sdpch.h"
#include "RigidBody2D.h"

#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

RigidBody2D::RigidBody2D(GameObject* pOwner, BodyType bodyType) : 
	m_pOwner(pOwner),
	m_type(bodyType)
{
	SetComponentType(ComponentType::RigidBody2D);
}

void RigidBody2D::OnComponentAdd()
{
	DLOG("Rigid Body 2D added to '" + m_pOwner->GetName() + "'.");
}

void RigidBody2D::PhysicsUpdate()
{
	float dt = Time::Instance()->GetDeltaTime();
	if (m_type == BodyType::Dynamic)
		Translate(glm::vec3(0.0f, 9.8f * 2, 0.0f));

	/*m_acceleration = m_netForce / m_mass;

	m_velocity += m_acceleration * dt;
	m_pOwner->GetTransform()->position += m_velocity * dt;*/
}

void RigidBody2D::OnComponentRemove()
{
	DLOG("Rigid Body 2D removed from '" + m_pOwner->GetName() + "'.");
}

void RigidBody2D::Translate(glm::vec3 direction)
{
	float dt = Time::Instance()->GetDeltaTime();

	m_pOwner->GetTransform()->position += direction * 1.0f / m_mass * dt;
}

SHADOW_NAMESPACE_END