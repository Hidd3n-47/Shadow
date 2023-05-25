#include "sdpch.h"
#include "PlayingState.h"

#include "Input/InputManager.h"
#include "Time/Time.h"

#include "ZomSurv/src/GameStates/GameStateManager.h"
#include "ZomSurv/Weapons/Bullet/BulletManager.h"
#include "ZomSurv/src/ZombieManager.h"
#include "ZomSurv/PickUp/PickUpManager.h"

PlayingState::PlayingState(Shadow::Window* window, Shadow::Camera* camera, Shadow::Scene* pScene) :
	m_pScene(pScene)
{
	// Empty.
}

void PlayingState::OnStateEnter()
{
	Shadow::SceneManager::Instance()->SetActiveScene(m_pScene);

	m_pPlayer = new Player(m_pScene, m_playerStartingPosition);
	m_pPlayer->Init();
}

void PlayingState::Update()
{
	//LevelManager::Instance()->LoadMap(Level::MAP1, m_pGameScene);
	static unsigned int playerScoreLastFrame = m_pPlayer->GetScore();
	unsigned int score = m_pPlayer->GetScore();
	if (score != playerScoreLastFrame)
		playerScoreLastFrame = score;

	Input();

	UpdatePlayer();

	BulletManager::Instance()->Update();

	UpdateZombies();

	GameStateManager::Instance()->Update();

	PickUpManager::Instance()->Update();

	AfterUpdate();
}

void PlayingState::AfterUpdate()
{
	BulletManager::Instance()->DestroyBulletsInQueue();

	ZombieManager::Instance()->DestroyZombiesInQueue();
}

void PlayingState::OnStateExit()
{
	delete m_pPlayer;

	Hud::Instance()->Destroy();
}

void PlayingState::AddZombieToHitCooldown(Shadow::GameObject* pZombie)
{
	std::list<ZombieHitCooldown>::iterator it;
	for (it = m_zombieHitCooldownList.begin(); it != m_zombieHitCooldownList.end(); it++)
		if (it->pZombie == pZombie)
			return;

	if (!m_pPlayer->Damage(50))
		GameManager::Instance()->ChangeSceneState(GameSceneState::DEAD);

	m_zombieHitCooldownList.emplace_back(pZombie);
}

void PlayingState::Input()
{
	glm::vec3 moveDirection = glm::vec3(0.0f);

	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_w))
		moveDirection += glm::vec3(0.0f, -1.0f, 0.0f);
	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_s))
		moveDirection += glm::vec3(0.0f, 1.0f, 0.0f);
	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_a))
		moveDirection += glm::vec3(-1.0f, 0.0f, 0.0f);
	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_d))
		moveDirection += glm::vec3(1.0f, 0.0f, 0.0f);
	if (Shadow::InputManager::Instance()->IsKeyDown(Shadow::KEYCODE_r))
		m_pPlayer->Reload();
	if (Shadow::InputManager::Instance()->IsMouseDown(Shadow::BUTTON_LEFT))
		m_pPlayer->Shoot();

	if (moveDirection != glm::vec3(0.0f))
		moveDirection = glm::normalize(moveDirection);

	m_pPlayer->Update(moveDirection);
}

void PlayingState::UpdatePlayer()
{
	// Update the zombie cooldowns.
	float dt = Shadow::Time::Instance()->GetDeltaTime();
	std::vector<std::list<ZombieHitCooldown>::iterator> toRemove;

	std::list<ZombieHitCooldown>::iterator it;
	for (it = m_zombieHitCooldownList.begin(); it != m_zombieHitCooldownList.end(); it++)
	{
		it->timer -= dt;
		if (it->timer <= 0)
			toRemove.push_back(it);
	}

	for (auto i : toRemove)
		m_zombieHitCooldownList.erase(i);
}

void PlayingState::UpdateZombies()
{
	ZombieManager::Instance()->Update(m_pPlayer->GetPosition());
}

std::pair<unsigned short, unsigned short> PlayingState::GetGunAmmo()
{
	std::pair<unsigned short, unsigned short> ammo;

	ammo.first = m_pPlayer->GetAmmoInClip();
	ammo.second = m_pPlayer->GetAmmoForType();

	return ammo;
}