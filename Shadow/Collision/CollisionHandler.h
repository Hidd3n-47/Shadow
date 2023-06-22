#pragma once

#include "GameObject/GameObject.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
COLLISION_HANDLER:
	Handles the collision of the engine. Specifically 2D collision.
	Collision checks are between Squares, Circles, and Squares v. Circles.
	Dynamic objects are ones that will have movement and behaviour.
	Static objects are ones that will be rigid and not have movement.

	Note: Collision Handler is not the collision components, the collision
		  components will deal with adding and removing objects to the handler.
=========================================================================================
*/
class CollisionHandler
{
public:
	inline static CollisionHandler* Instance() { return m_pInstance == nullptr ? m_pInstance = new CollisionHandler() : m_pInstance; }

	void Update();

	inline void AddBoxToDynamic(GameObject* go) { m_dynamicBox2d.push_back(go); }
	inline void AddBoxToStatic(GameObject* go) { m_staticBox2d.push_back(go); }
	inline void AddCircleToDynamic(GameObject* go) { m_dynamicCircle2d.push_back(go); }
	inline void AddCircleToStatic(GameObject* go) { m_staticCircle2d.push_back(go); }

	void RemoveFromBoxDynamic(GameObject* go);
	void RemoveFromBoxStatic(GameObject* go);
	void RemoveFromCircleDynamic(GameObject* go);
	void RemoveFromCircleStatic(GameObject* go);

	void AddToBeDeleted(GameObject* go) { m_toBeDeleted.push_back(go); }
private:
	CollisionHandler() { }
	~CollisionHandler() { delete m_pInstance; }

	static CollisionHandler* m_pInstance;

	std::vector<GameObject*> m_dynamicBox2d;
	std::vector<GameObject*> m_staticBox2d;
	std::vector<GameObject*> m_dynamicCircle2d;
	std::vector<GameObject*> m_staticCircle2d;
	std::vector<GameObject*> m_toBeDeleted;

	void CheckCollisionBetweenBoxes(GameObject* b1, GameObject* b2, bool pushBoth = true);
	void CheckCollisionBetweenCircles(GameObject* c1, GameObject* c2, bool pushBoth = true);
	void CheckCollisionBetweenBoxCircle(GameObject* box, GameObject* circle, bool pushBoth = true, bool pushCircle = false);

	float SignOfFloat(float f);
	bool BetweenAngleInclusive(float amin, float angle, float amax);
};

SHADOW_NAMESPACE_END