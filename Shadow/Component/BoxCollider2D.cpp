#include "sdpch.h"
#include "BoxCollider2D.h"

#include "Window/WindowManager.h"
#include "Graphics/TextureManager.h"
#include "Collision/CollisionHandler.h"
#include "RigidBody2D.h"

SHADOW_NAMESPACE_BEGIN

BoxCollider2D::BoxCollider2D(GameObject* pOwner, glm::vec2 halfExtent, bool trigger) :
	m_pOwner(pOwner),
	m_size(halfExtent),
	m_trigger(trigger)
{
	SetComponentType(ComponentType::BoxCollider2D);
}

BoxCollider2D::BoxCollider2D(GameObject* pOwner, bool trigger) :
	m_pOwner(pOwner),
	m_trigger(trigger)
{
	SetComponentType(ComponentType::BoxCollider2D);
}

BoxCollider2D::BoxCollider2D(GameObject* pOwner, glm::vec2 halfExtent) :
	m_pOwner(pOwner),
	m_size(halfExtent)
{
	SetComponentType(ComponentType::BoxCollider2D);
}

BoxCollider2D::BoxCollider2D(GameObject* pOwner) :
	m_pOwner(pOwner)
{
	SetComponentType(ComponentType::BoxCollider2D);
}

//BoxCollider2D::BoxCollider2D(GameObject* pOwner, glm::vec2 dimensions, bool trigger) :
//	m_pOwner(pOwner),
//	m_trigger(trigger)
//{
//	/*m_boxCollider.x = position.x;
//	m_boxCollider.y = position.y;
//	m_boxCollider.w = dimensions.x;
//	m_boxCollider.h = dimensions.y;*/
//	m_pOwner->dim = dimensions;
//
//}

void BoxCollider2D::OnComponentAdd()
{
	// BUG: There is a bug with this as a person can remove the rigid body after box collider created meaning it will try remove it from static not dynamic.
	// add to the collsion handler network.
	if (!m_pOwner->HasComponent(ComponentType::RigidBody2D))
	{
		CollisionHandler::Instance()->AddBoxToStatic(m_pOwner);
		m_static = true;
	}
	else
	{
		RigidBody2D* rb = (RigidBody2D*)m_pOwner->GetComponent(ComponentType::RigidBody2D);
		if (rb->GetBodyType() == RigidBody2D::BodyType::Static)
		{
			CollisionHandler::Instance()->AddBoxToStatic(m_pOwner);
			m_static = true;
		}
		else
			CollisionHandler::Instance()->AddBoxToDynamic(m_pOwner);
	}

	m_lastFramePosition = m_pOwner->GetTransform()->position;

	DLOG("Box Collider 2D added to '" + m_pOwner->GetName() + "'.");
}

void BoxCollider2D::Update()
{
	if (m_lastFramePosition == m_pOwner->GetTransform()->position)
		return;

	CollisionHandler::Instance()->AddBoxToDynamicQueue(m_pOwner);
	m_lastFramePosition = m_pOwner->GetTransform()->position;
}

void BoxCollider2D::PhysicsUpdate()
{
	if (!m_calledThisFrame && m_triggered)
		OnTriggerExit();
	else
		m_calledThisFrame = false;
}

void BoxCollider2D::Render(glm::vec3 worldPosition)
{
	SDL_Renderer* pRenderer = m_pOwner->GetSceneParent()->GetWindow()->GetRenderer();
	Camera* pCamera = m_pOwner->GetSceneParent()->GetCamera();

#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(worldPosition.x, worldPosition.y, 0.0f), m_size, Color(Blue));
#endif
}

void BoxCollider2D::Trigger()
{
	m_calledThisFrame = true;

	if (!m_triggered)
		OnTriggerEnter();
	else
		OnTriggerStay();
}

void BoxCollider2D::OnTriggerEnter()
{
	m_triggered = true;
}

void BoxCollider2D::OnTriggerStay()
{
	

}

void BoxCollider2D::OnTriggerExit()
{
	m_triggered = false;

}

void BoxCollider2D::OnComponentRemove()
{
	if (m_static)
		CollisionHandler::Instance()->RemoveFromBoxStatic(m_pOwner);
	else
		CollisionHandler::Instance()->RemoveFromBoxDynamic(m_pOwner);

	DLOG("Box Collider 2D removed from '" + m_pOwner->GetName() + "'.");
}

SHADOW_NAMESPACE_END