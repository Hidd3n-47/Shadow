#pragma once

#include "ZomSurv/src/GameStates/IGameState.h"
#include "ZomSurv/Entity/Player/Player.h"
#include "ZomSurv/Entity/Player/Hud.h"

struct ZombieHitCooldown
{
	ZombieHitCooldown(Shadow::GameObject* zombie) : pZombie(zombie) { }

	float timer = 0.5f;
	Shadow::GameObject* pZombie = nullptr;
};

class PlayingState : public IGameState
{
public:
	PlayingState(Shadow::Window* window, Shadow::Camera* camera, Shadow::Scene* pScene);

	virtual void OnStateEnter() override;
	virtual void Update() override;
	void AfterUpdate();
	virtual void OnStateExit() override;

	void AddZombieToHitCooldown(Shadow::GameObject* pZombie);

	std::pair<unsigned short, unsigned short> GetGunAmmo();

	// Player inline methods.
	inline bool PlayerPurchase(unsigned int cost) { return m_pPlayer->PurchaseItem(cost); }
	inline unsigned int GetPlayerScore() const { return m_pPlayer->GetScore(); }
	inline glm::vec3 GetPlayerPosition() const { return m_pPlayer->GetPosition(); }
	inline void AddPlayerScore(unsigned int score) { m_pPlayer->AddScore(score); }
	inline void SetPlayerStartingPos(const glm::vec3& position) { m_playerStartingPosition = position; }
	inline void PurchaseJug() { m_pPlayer->ApplyJugPerk(); }
private:
	Shadow::Scene* m_pScene = nullptr;
	Player* m_pPlayer = nullptr;

	glm::vec3 m_playerStartingPosition = glm::vec3(0.0f);

	std::list<ZombieHitCooldown> m_zombieHitCooldownList;

	void Input();
	void UpdatePlayer();
	void UpdateZombies();
};

