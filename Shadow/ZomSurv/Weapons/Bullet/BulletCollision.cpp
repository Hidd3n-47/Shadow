#include "sdpch.h"
#include "BulletCollision.h"

#include "ParticleSystem/ParticleManager.h"

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
	//glm::vec3 bulletPos = otherGameObject->GetTransform()->position + glm::vec3(TILE_WIDTH * 0.5f);
	glm::vec3 bulletPos = GameManager::Instance()->GetPlayerPosition();

	ZombieManager::Instance()->DamageZombie(otherGameObject, damage);
	glm::vec2 dir = thisGameObject->GetTransform()->position - bulletPos;
	glm::normalize(dir);

	Shadow::ParticleManager::Instance()->CreateParticleEffect(Shadow::SceneManager::Instance()->GetActiveScene(), "Assets/blood.png", glm::vec2(11), thisGameObject->GetTransform()->position, dir, 700, 7.5f, 5, 10);
}
