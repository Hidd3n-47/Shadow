#include "sdpch.h"
#include "CollisionHandler.h"

#include <glm/gtx/vector_angle.hpp>

#include "Component/BoxCollider2D.h"
#include "Component/CircleCollider2D.h"
#include "Component/RigidBody2D.h"

#include "Window/WindowManager.h"
#include "Scene/SceneManager.h"
#include "Camera/Camera.h"

SHADOW_NAMESPACE_BEGIN

CollisionHandler* CollisionHandler::m_pInstance = nullptr;

void CollisionHandler::Update()
{
	// Dynamic Circles check.
	for (int i = 0; i < m_dynamicCircle2d.size(); i++)
	{
		for (int j = 0; j < m_dynamicCircle2d.size(); j++)
		{
			if (i == j)
				continue;

			CheckCollisionBetweenCircles(m_dynamicCircle2d[i], m_dynamicCircle2d[j]);
		}

		for (int x = 0; x < m_staticCircle2d.size(); x++)
			CheckCollisionBetweenCircles(m_dynamicCircle2d[i], m_staticCircle2d[x], false);

		for (int y = 0; y < m_dynamicBox2d.size(); y++)
			CheckCollisionBetweenBoxCircle(m_dynamicBox2d[y], m_dynamicCircle2d[i], true);

		for (int z = 0; z = m_staticBox2d.size(); z++)
			CheckCollisionBetweenBoxCircle(m_staticBox2d[z], m_dynamicCircle2d[i], false, true);
	}

	// Static Circles check.
	for (int i = 0; i < m_staticCircle2d.size(); i++)
	{
		for (int j = 0; j < m_staticCircle2d.size(); j++)
		{
			if (i == j)
				continue;

			CheckCollisionBetweenCircles(m_staticCircle2d[i], m_staticCircle2d[j]);
		}

		for (int y = 0; y < m_dynamicBox2d.size(); y++)
			CheckCollisionBetweenBoxCircle(m_dynamicBox2d[y], m_staticCircle2d[i], true);

		for (int z = 0; z < m_staticBox2d.size(); z++)
			CheckCollisionBetweenBoxCircle(m_staticBox2d[z], m_staticCircle2d[i], false, true);
	}

	// Dynamic Boxes check.
	for (int i = 0; i < m_dynamicBox2d.size(); i++)
	{
		for (int j = 0; j < m_dynamicBox2d.size(); j++)
		{
			if (i == j)
				continue;

			CheckCollisionBetweenBoxes(m_dynamicBox2d[i], m_dynamicBox2d[j]);
		}

		for (int z = 0; z < m_staticBox2d.size(); z++)
			CheckCollisionBetweenBoxes(m_dynamicBox2d[i], m_staticBox2d[z], false);
	}
}

void CollisionHandler::CheckCollisionBetweenBoxes(GameObject* b1, GameObject* b2, bool pushBoth)
{
	glm::vec3 b1Position = b1->GetTransform()->position;
	BoxCollider2D* b1Collider = (BoxCollider2D*)b1->GetComponent(ComponentType::BoxCollider2D);
	bool isTrigger = b1Collider->GetIsTrigger();
	glm::vec2 boxDimensions = b1Collider->GetSize();

	glm::vec3 b2Position = b2->GetTransform()->position;
	BoxCollider2D* staticBc = (BoxCollider2D*)b2->GetComponent(ComponentType::BoxCollider2D);
	glm::vec2 staticDimensions = staticBc->GetSize();

	//>>> Because we are using 2D engine, ignore z for now. <<<//

	if (b1Position.x >= b2Position.x + 2.0f * staticDimensions.x)
		return;

	if (b1Position.x + 2.0f * boxDimensions.x <= b2Position.x)
		return;

	if (b1Position.y >= b2Position.y + 2.0f * staticDimensions.y)
		return;

	if (b1Position.y + 2.0f * boxDimensions.y <= b2Position.y)
		return;

	if (b1Collider->GetIsTrigger())
	{
		b1Collider->Trigger(b1, b2);
		return;
	}
	else if (staticBc->GetIsTrigger())
	{
		staticBc->Trigger(b2, b1);
		return;
	}

	glm::vec2 b1Center(b1Position.x + boxDimensions.x, b1Position.y + boxDimensions.y);
	glm::vec2 b2Center(b2Position.x + staticDimensions.x, b2Position.y + staticDimensions.y);

	float dx = b1Center.x - b2Center.x;
	float dy = b1Center.y - b2Center.y;
	glm::vec2 minDistance(boxDimensions.x + staticDimensions.x, boxDimensions.y + staticDimensions.y);

	if (abs(dx) >= minDistance.x || abs(dy) >= minDistance.y)
		return;

	float overlapX = minDistance.x - abs(dx);
	float overlapY = minDistance.y - abs(dy);


	if (overlapX < overlapY)
	{
		if (pushBoth)
		{
			float halfOverlap = -0.5f * SignOfFloat(dx) * overlapX;
			b1->GetTransform()->position.x -= halfOverlap;
			b2->GetTransform()->position.x += halfOverlap;
			return;
		}
		b1->GetTransform()->position.x -= SignOfFloat(dx) * overlapX;
	}
	else
	{
		if (pushBoth)
		{
			float halfOverlap = -0.5f * SignOfFloat(dy) * overlapY;
			b1->GetTransform()->position.y -= halfOverlap;
			b2->GetTransform()->position.y += halfOverlap;
			return;
		}
		b1->GetTransform()->position.y -= SignOfFloat(dy) * overlapY;
	}

	b1Collider->OnCollisionEnter(b1, b2);
	staticBc->OnCollisionEnter(b2, b1);
}

void CollisionHandler::CheckCollisionBetweenCircles(GameObject* c1, GameObject* c2, bool pushBoth)
{
	CircleCollider2D* c1Circle = (CircleCollider2D*)c1->GetComponent(ComponentType::CircleCollider2D);
	CircleCollider2D* c2Circle = (CircleCollider2D*)c2->GetComponent(ComponentType::CircleCollider2D);

	float r1 = c1Circle->GetRadius();
	float r2 = c2Circle->GetRadius();

	glm::vec3 c1Center = c1->GetTransform()->position + glm::vec3(r1, r1, 0.0f);
	glm::vec3 c2Center = c2->GetTransform()->position + glm::vec3(r2, r2, 0.0f);

	float minDistance = r1 + r2;

	glm::vec3 distanceVector = c1Center - c2Center;
	float distance = glm::length(distanceVector);
	float overlap = minDistance - distance;

	if (overlap < 0.0f)
		return;


	glm::vec3 overlapPush = glm::normalize(distanceVector) * overlap;

	if (pushBoth)
	{
		glm::vec3 halfOverlapPush = 0.5f * overlapPush;
		c1->GetTransform()->position += halfOverlapPush;
		c2->GetTransform()->position -= halfOverlapPush;
	}
	else
		c1->GetTransform()->position += overlapPush;

	c1Circle->OnCollisionEnter(c1, c2);
	c2Circle->OnCollisionEnter(c2, c1);
}

void CollisionHandler::CheckCollisionBetweenBoxCircle(GameObject* box, GameObject* circle, bool pushBoth, bool pushCircle)
{
	BoxCollider2D* bc = (BoxCollider2D*)box->GetComponent(ComponentType::BoxCollider2D);
	CircleCollider2D* cc = (CircleCollider2D*)circle->GetComponent(ComponentType::CircleCollider2D);

	glm::vec3 position = circle->GetTransform()->position;
	float w = bc->GetSize().x;
	float h = bc->GetSize().y;
	float r = cc->GetRadius();

	glm::vec3 boxCenter = box->GetTransform()->position + glm::vec3(w, h, 0.0f);
	glm::vec3 circleCenter = position + glm::vec3(r, r, 0.0f);
			
	float dx = circleCenter.x - boxCenter.x;
	float dy = circleCenter.y - boxCenter.y;
	if (abs(dx) > w + r || abs(dy) > h + r)
		return;

	if (bc->GetIsTrigger())
	{
		bc->Trigger(box, circle);
		return;
	}

	bc->OnCollisionEnter(box, circle);
	cc->OnCollisionEnter(circle, box);

	if (BetweenAngleInclusive(boxCenter.x - w, circleCenter.x, boxCenter.x + w))
	{
		float overlap = abs(dy) - (h + r);
			
		if (dy > 0)
			circle->GetTransform()->position.y -= overlap;
		else 
			circle->GetTransform()->position.y += overlap;

		return;
	}
	else if (BetweenAngleInclusive(boxCenter.y - h, circleCenter.y, boxCenter.y + h))
	{
		float overlap = abs(dx) - (w + r);

		if (dx < 0)
			circle->GetTransform()->position.x += overlap;
		else
			circle->GetTransform()->position.x -= overlap;

		return;
	}

	bool topCorner = circleCenter.y > boxCenter.y;
	glm::vec3 cornerPosition;

	if (circleCenter.x < boxCenter.x)
		if (topCorner)
			cornerPosition = boxCenter + glm::vec3(-w, +h, 0.0f);
		else
			cornerPosition = boxCenter + glm::vec3(-w, -h, 0.0f);
	else
		if (topCorner)
			cornerPosition = boxCenter + glm::vec3(+w, +h, 0.0f);
		else
			cornerPosition = boxCenter + glm::vec3(+w, -h, 0.0f);

	glm::vec3 direction = circleCenter - cornerPosition;
	float distance = glm::length(direction);

	float overlap = distance - r;

	if (overlap > 0)
		return;

	direction = glm::normalize(direction);

	if (pushBoth)
	{
		float halfOverlap = 0.5f * overlap;

		circle->GetTransform()->position -= halfOverlap * direction;
		box->GetTransform()->position += halfOverlap * direction;
		
		return;
	}

	if (pushCircle)
		circle->GetTransform()->position -= overlap * direction;
	else
		box->GetTransform()->position += overlap * direction;
}	

void CollisionHandler::RemoveFromBoxDynamic(GameObject* go)
{
	for (int i = 0; i < m_dynamicBox2d.size(); i++)
	{
		if (m_dynamicBox2d[i] != go)
			continue;

		m_dynamicBox2d[i] = m_dynamicBox2d.back();
		m_dynamicBox2d.pop_back();
		return;
	}
}

void CollisionHandler::RemoveFromBoxStatic(GameObject* go)
{
	for (int i = 0; i < m_staticBox2d.size(); i++)
	{
		if (m_staticBox2d[i] != go)
			continue;

		m_staticBox2d[i] = m_staticBox2d.back();
		m_staticBox2d.pop_back();
		return;
	}
}

void CollisionHandler::RemoveFromCircleDynamic(GameObject* go)
{
	for (int i = 0; i < m_dynamicCircle2d.size(); i++)
	{
		if (m_dynamicCircle2d[i] != go)
			continue;

		m_dynamicCircle2d[i] = m_dynamicCircle2d.back();
		m_dynamicCircle2d.pop_back();
		return;
	}
}

void CollisionHandler::RemoveFromCircleStatic(GameObject* go)
{
	for (int i = 0; i < m_staticCircle2d.size(); i++)
	{
		if (m_staticCircle2d[i] != go)
			continue;

		m_staticCircle2d[i] = m_staticCircle2d.back();
		m_staticCircle2d.pop_back();
		return;
	}
}

float CollisionHandler::SignOfFloat(float f)
{
	if (f < 0.0f)
		return -1.0f;

	return 1.0f;
}

bool CollisionHandler::BetweenAngleInclusive(float amin, float angle, float amax)
{
	if (amin <= angle && angle <= amax)
		return true;
	return false;
}

SHADOW_NAMESPACE_END