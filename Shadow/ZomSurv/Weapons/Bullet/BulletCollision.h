#pragma once

#include "Component/ICollisionMethods.h"

class BulletCollision : public Shadow::ICollisionMethods
{
	virtual void OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject) override;
};

