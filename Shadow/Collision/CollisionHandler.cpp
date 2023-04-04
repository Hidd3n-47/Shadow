#include "sdpch.h"
#include "CollisionHandler.h"

#include "Component/RigidBody2D.h"

SHADOW_NAMESPACE_BEGIN

CollisionHandler* CollisionHandler::m_pInstance = nullptr;

void CollisionHandler::Update()
{
	/*for (GameObject* go : m_dynamicQueue)
	{

	}

	m_dynamicQueue.clear();*/

	for (GameObject* dy : m_dynamicObjects)
	{
		CheckCollisionAgainstStatic(dy);
	}
}

void CollisionHandler::CheckCollisionAgainstStatic(GameObject* go)
{
	for (GameObject* st : m_staticObjects)
	{
		SDL_Rect d = { go->GetTransform()->position.x, go->GetTransform()->position.y, go->dim.x, go->dim.y };
		SDL_Rect s = { st->GetTransform()->position.x, st->GetTransform()->position.y, st->dim.x, st->dim.y };
		
		SDL_Rect res;
		if (SDL_IntersectRect(&d, &s, &res))
		{
			RigidBody2D* rb = (RigidBody2D*)go->GetComponent(ComponentType::RigidBody2D);
			rb->ResetAll();
		}

	}
}

SHADOW_NAMESPACE_END