#include "sdpch.h"
#include "BoxCollider2D.h"

#include "Window/WindowManager.h"
#include "Graphics/TextureManager.h"
#include "Collision/CollisionHandler.h"

SHADOW_NAMESPACE_BEGIN

BoxCollider2D::BoxCollider2D(GameObject* pOwner, glm::vec2 position, glm::vec2 dimensions) :
	m_pOwner(pOwner),
	m_dimensions(dimensions)
{
	/*m_boxCollider.x = position.x;
	m_boxCollider.y = position.y;
	m_boxCollider.w = dimensions.x;
	m_boxCollider.h = dimensions.y;*/
	m_pOwner->dim = dimensions;
}

void BoxCollider2D::OnComponentAdd()
{
	// add to the collsion handler network.
	if (m_pOwner->HasComponent(ComponentType::RigidBody2D))
		CollisionHandler::Instance()->AddToDynamic(m_pOwner);
	else
		CollisionHandler::Instance()->AddToStatic(m_pOwner);

	DLOG("Box Collider 2D added to '" + m_pOwner->GetName() + "'.");
}

void BoxCollider2D::Update()
{
	/*m_boxCollider.x = m_pOwner->GetTransform()->position.x;
	m_boxCollider.y = m_pOwner->GetTransform()->position.y;*/
}

void BoxCollider2D::Render(glm::vec3 worldPosition)
{
	SDL_Renderer* pRenderer = m_pOwner->GetSceneParent()->GetWindow()->GetRenderer();
	Camera* pCamera = m_pOwner->GetSceneParent()->GetCamera();

#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(worldPosition.x, worldPosition.y, 0.0f), m_dimensions, Color(Blue));
#endif
}

void BoxCollider2D::OnComponentRemove()
{
	// remove from the collision handler check.

	DLOG("Box Collider 2D removed from '" + m_pOwner->GetName() + "'.");
}

SHADOW_NAMESPACE_END