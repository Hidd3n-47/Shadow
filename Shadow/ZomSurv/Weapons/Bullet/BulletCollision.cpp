#include "sdpch.h"
#include "BulletCollision.h"

#include "ZomSurv/Weapons/Bullet/BulletManager.h"
#include "ZomSurv/src/GameManager.h"
#include "ZomSurv/src/ZombieManager.h"

void BulletCollision::OnCollisionEnter(Shadow::GameObject* thisGameObject, Shadow::GameObject* otherGameObject)
{
	if (otherGameObject->GetTag() == "Player")
		return;

	float damage = BulletManager::Instance()->DestroyBullet(thisGameObject);

	if (otherGameObject->GetTag() != "Zombie")
		return;

	GameManager::Instance()->AddPlayerScore(10);

	ZombieManager::Instance()->DamageZombie(otherGameObject, damage);
}
