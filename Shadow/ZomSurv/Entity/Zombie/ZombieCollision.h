#pragma once

#include "Component/ICollisionMethods.h"

class ZombieCollision : public Shadow::ICollisionMethods
{
public:
	virtual void OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject) override;
};

