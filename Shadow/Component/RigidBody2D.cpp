#include "sdpch.h"
#include "RigidBody2D.h"

#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

RigidBody2D::RigidBody2D(GameObject* pOwner, bool affectedByGravity) : 
	m_pOwner(pOwner), 
	m_netForce(glm::vec3(0.0f)),
	m_acceleration(glm::vec3(0.0f)),
	m_velocity(glm::vec3(0.0f)),
	m_affectedByGravity(affectedByGravity)
{
	SetComponentType(ComponentType::RigidBody2D);
}

void RigidBody2D::OnComponentAdd()
{
	if (m_affectedByGravity)
		m_netForce = glm::vec3(0, 9.8f, 0.0f);

	DLOG("Rigid Body 2D added to '" + m_pOwner->GetName() + "'.");

}

void RigidBody2D::Update()
{
	float dt = Time::Instance()->GetDeltaTime();

	m_acceleration = m_netForce / m_mass;

	m_velocity += m_acceleration * dt;
	m_pOwner->GetTransform()->position += m_velocity * dt;
}

void RigidBody2D::OnComponentRemove()
{
	DLOG("Rigid Body 2D removed from '" + m_pOwner->GetName() + "'.");
}

SHADOW_NAMESPACE_END