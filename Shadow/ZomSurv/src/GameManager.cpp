#include "sdpch.h"
#include "GameManager.h"

#include "Time/Time.h"
#include "Engine/Engine.h"
#include "GameObject/GameObject.h"
#include "Component/CircleCollider2D.h"
#include "Component/SpriteRenderer.h"
#include "Input/InputManager.h"
#include "Graphics/TextureManager.h"

#include "ZomSurv/Level/LevelManager.h"
#include "GameStates/GameStateManager.h"
#include "ZombieManager.h"

GameManager* GameManager::m_pInstance = nullptr;

GameManager::GameManager()
{
	// Empty.
}

GameManager::~GameManager()
{
	delete m_pDeathState;
	delete m_pPlayingState;
	delete m_pLoadingState;
	delete m_pMainMenuState;

	delete m_pInstance;
}

void GameManager::InitGame(Shadow::Scene* pScene)
{
	m_pGameScene = pScene;

	Shadow::Window* win = pScene->GetWindow();
	Shadow::Camera* cam = pScene->GetCamera();

	m_pMainMenuState = new MainMenuState(win, cam);
	m_pLoadingState = new LoadingState(win, cam, pScene);
	m_pPlayingState = new PlayingState(win, cam, pScene);
	m_pDeathState = new DeathState(win, cam);
	m_pMainMenuState->OnStateEnter();
	m_pCurrentState = m_pMainMenuState;

	m_startingRoundAudio = Shadow::Audio::Instance()->LoadSound("Assets/Audio/roundStart.mp3", 50);
	m_maxAmmoAudio = Shadow::Audio::Instance()->LoadSound("Assets/Pickups/maxAmmo.mp3", 20);
	m_nukeAudio = Shadow::Audio::Instance()->LoadSound("Assets/Pickups/nuke.mp3", 20);
	m_instaKillAudio = Shadow::Audio::Instance()->LoadSound("Assets/Pickups/instaKill.mp3", 20);
	m_doublePointsAudio = Shadow::Audio::Instance()->LoadSound("Assets/Pickups/doublePoints.mp3", 20);
	m_powerAudio = Shadow::Audio::Instance()->LoadSound("Assets/Audio/power.mp3", 75);
	m_purchasAudio = Shadow::Audio::Instance()->LoadSound("Assets/Audio/purchas.mp3", 20);
}

void GameManager::Update()
{
	m_pCurrentState->Update();

	// If the state is not the playing state, no need to update double points.
	if (m_pCurrentState != m_pPlayingState)
		return;

	PlayStartingRoundAudio();

	if (m_doublePointsTimer == DOUBLE_POINTS_TIMER_DEFAULT)
		return;

	float dt = Shadow::Time::Instance()->GetDeltaTime();

	m_doublePointsTimer -= dt;
	if (m_doublePointsTimer > 0)
		return;

	m_doublePointsTimer = DOUBLE_POINTS_TIMER_DEFAULT;
	m_scoreMultiplier = 1.0f;
	Hud::Instance()->SetDoublePointsActive(false);
}

void GameManager::DestroyGame()
{
	//~GameManager();
}

void GameManager::ChangeSceneState(GameSceneState state)
{
	m_pCurrentState->OnStateExit();

	m_state = state;
	switch (m_state)
	{
	case GameSceneState::MAIN_MENU:
		m_pCurrentState = m_pMainMenuState;
		break;
	case GameSceneState::LOADING:
		m_pCurrentState = m_pLoadingState;
		break;
	case GameSceneState::PLAYING:
		m_pCurrentState = m_pPlayingState;
		break;
	case GameSceneState::DEAD:
		m_pCurrentState = m_pDeathState;
		break;
	case GameSceneState::QUIT:
		Shadow::Engine::Instance()->StopRunning();
		break;
	default:
		Shadow::Log::Instance()->Warning("Unprocessed state in the Game Manger NextState method.");
		break;
	}

	m_pCurrentState->OnStateEnter();
}

void GameManager::PlayStartingRoundAudio()
{
	static bool played = false;
	static bool deleted = false;
	static float timer = 15.0f;

	if (deleted)
		return;

	if (played)
	{

		timer -= Shadow::Time::Instance()->GetDeltaTime();
		if (timer <= 0.0f)
		{
			Shadow::Audio::Instance()->DestroySound(m_startingRoundAudio);
			deleted = true;
		}

		return;
	}

	Shadow::Audio::Instance()->PlaySound(m_startingRoundAudio);
	played = true;
}

void GameManager::TurnPowerOn()
{
	m_powerOn = true;

	Shadow::Audio::Instance()->PlaySound(m_powerAudio);
}