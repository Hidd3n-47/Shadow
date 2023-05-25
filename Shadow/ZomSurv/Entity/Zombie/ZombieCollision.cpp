#include "sdpch.h"
#include "ZombieCollision.h"

#include "ZomSurv/src/GameManager.h"

void ZombieCollision::OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject)
{
	if (otherGameObject->GetTag() == "Player")
		GameManager::Instance()->AddZombieToHitCooldown(thisGameObject);
}
