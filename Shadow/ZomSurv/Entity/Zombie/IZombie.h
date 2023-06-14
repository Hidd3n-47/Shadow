#pragma once

#include "Scene/Scene.h"
#include "GameObject/GameObject.h"
#include "ZomSurv/Entity/IEntity.h"

enum class ZombieType
{
	WALKER,
	SPRINTER,
	count // Used to represent the number of Zombie Types.
};

class IZombie : public IEntity
{
public:
	IZombie(Shadow::Scene* pScene, const glm::vec2& spawnLocation, uint16_t health, uint16_t textureId);
	IZombie(Shadow::Scene* pScene, const glm::vec2& spawnLocation, uint16_t health, uint16_t textureId, ZombieType type);
	virtual ~IZombie();

	void Update(const glm::vec3& playerPosition);

	bool Damage(uint16_t damage);

	float GetCollisionRadius();

	// Accessors.
	inline const Shadow::GameObject* GetGameObject() const { return m_gameObject; }
private:
	Shadow::Scene* m_pScene = nullptr;
	ZombieType m_type = ZombieType::WALKER;

	void CreateZombie(Shadow::Scene* pScene, const glm::vec2& spawnLocation, uint16_t textureId);
	void CreateGameObject(Shadow::Scene* pScene);
	void InitZombieByType(uint16_t textureId);

	void InitZombie(uint8_t damage, float speed);
};