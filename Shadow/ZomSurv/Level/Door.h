#pragma once
#include "sdpch.h"

#include <glm/glm.hpp>
#include "Component/SpriteRenderer.h"
#include "Component/BoxCollider2D.h"
#include "Scene/Scene.h"

class Door
{
public:
	Door(int doorId);

	~Door();

	void AddDoorSection(glm::vec2 worldPosition, Shadow::Scene* pScene, uint16_t textureId);

	// Accessors.
	inline unsigned int GetCost() const { return m_cost; }
private:
	int m_doorId = -1;
	unsigned int m_cost = 0;

	Shadow::GameObject* m_gameObject[2] = { nullptr, nullptr };
	Shadow::Scene* m_pScene = nullptr;

	void SetCostOfDoor();
};