#include "sdpch.h"
#include "CircleCollider2D.h"

#include "Collision/CollisionHandler.h"
#include "Graphics/TextureManager.h"
#include "Window/Window.h"
#include "RigidBody2D.h"

SHADOW_NAMESPACE_BEGIN

CircleCollider2D::CircleCollider2D(GameObject* pOwner, float radius) :
	m_pOwner(pOwner),
	m_radius(radius)
{
	SetComponentType(ComponentType::CircleCollider2D);
}

void CircleCollider2D::OnComponentAdd()
{
	if (!m_pOwner->HasComponent(ComponentType::RigidBody2D))
	{
		CollisionHandler::Instance()->AddCircleToStatic(m_pOwner);
		m_static = true;
	}
	else
	{
		RigidBody2D* rb = (RigidBody2D*)m_pOwner->GetComponent(ComponentType::RigidBody2D);
		if (rb->GetBodyType() == RigidBody2D::BodyType::Static)
		{
			CollisionHandler::Instance()->AddCircleToStatic(m_pOwner);
			m_static = true;
		}
		else
			CollisionHandler::Instance()->AddCircleToDynamic(m_pOwner);
	}

	m_lastFramePosition = m_pOwner->GetTransform()->position;

	DLOG("Circle Collider 2D added to '" + m_pOwner->GetName() + "'.");
}

void CircleCollider2D::Update()
{
	if (m_lastFramePosition == m_pOwner->GetTransform()->position)
		return;

	CollisionHandler::Instance()->AddCircleToDynamicQueue(m_pOwner);
}

void CircleCollider2D::PhysicsUpdate()
{
	// Empty.
}

void CircleCollider2D::Render(glm::vec3 worldPosition)
{
	SDL_Renderer* pRenderer = m_pOwner->GetSceneParent()->GetWindow()->GetRenderer();
	Camera* pCamera = m_pOwner->GetSceneParent()->GetCamera();
	
#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(worldPosition.x, worldPosition.y, 0.0f), glm::vec2(m_radius, m_radius), Color(Blue));
#endif
}

void CircleCollider2D::OnComponentRemove()
{
	if (m_static)
		CollisionHandler::Instance()->RemoveFromCircleStatic(m_pOwner);
	else
		CollisionHandler::Instance()->RemoveFromCircleDynamic(m_pOwner);
	
	DLOG("Circle Collider 2D removed from '" + m_pOwner->GetName() + "'.");
}

SHADOW_NAMESPACE_END