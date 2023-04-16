#include "sdpch.h"
#include "Physics2D.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "Graphics/TextureManager.h"
#include "Window/Window.h"

SHADOW_NAMESPACE_BEGIN

Physics2D::Physics2D(GameObject* pOwner, b2World* pWorld, glm::vec2 halfExtents, bool a) : 
	m_pOwner(pOwner),
	m_pWorld(pWorld),
	m_halfExtents(halfExtents),
	b(a)
{
	SetComponentType(ComponentType::Physics2D);
}

void Physics2D::OnComponentAdd()
{
	b2BodyDef bodyDef;
	if (b)
		bodyDef.type = b2_dynamicBody;
	else
		bodyDef.type = b2_staticBody;
	bodyDef.position.Set(m_pOwner->GetTransform()->position.x, m_pOwner->GetTransform()->position.y);
	m_pBody = m_pWorld->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(m_halfExtents.x, m_halfExtents.y);

	b2FixtureDef fixDef;
	fixDef.shape = &box;
	fixDef.density = m_density;
	fixDef.friction = m_friction;
	fixDef.restitution = m_restitution;
	fixDef.restitutionThreshold = m_restitutionThreshold;

	m_pBody->CreateFixture(&fixDef);

	DLOG("Physics 2D added to '" + m_pOwner->GetName() + "'.")
}

void Physics2D::PhysicsUpdate()
{
	b2Vec2 position = m_pBody->GetPosition();
	m_pOwner->GetTransform()->position.x = position.x;
	m_pOwner->GetTransform()->position.y = position.y;
}

void Physics2D::Render(glm::vec3 worldPosition)
{
	SDL_Renderer* pRenderer = m_pOwner->GetSceneParent()->GetWindow()->GetRenderer();
	Camera* pCamera = m_pOwner->GetSceneParent()->GetCamera();

#ifdef RENDER_DEBUG
	TextureManager::Instance()->DebugRender(pCamera, pRenderer, Square, glm::vec3(m_pOwner->GetTransform()->position.x, m_pOwner->GetTransform()->position.y, 0.0f), m_halfExtents, Color(Blue));
#endif
}

void Physics2D::OnComponentRemove()
{
	DLOG("Physics 2D removed from '" + m_pOwner->GetName() + "'.");
}

SHADOW_NAMESPACE_END