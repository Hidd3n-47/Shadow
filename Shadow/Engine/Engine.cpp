#include "sdpch.h"
#include "Engine.h"

#include "Input/InputManager.h"
#include "Window/WindowManager.h"
#include "Scene/SceneManager.h"
#include "Graphics/FontManager.h"
#include "GameObject/GameObjectManager.h"
#include "Collision/CollisionHandler.h"
#include "Time/Time.h"
#include "Graphics/TextureManager.h"
#include "Audio/Audio.h"
#include "ParticleSystem/ParticleManager.h"

#include "ZomSurv/src/GameManager.h"

SHADOW_NAMESPACE_BEGIN

Engine* Engine::m_pInstance = nullptr;

void Engine::InitEngine()
{
	// TODO need to implement where the engine load textures that are used for the engine, example, debugging textures such as arrows for rigid body as well as the "No texture" texture.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		Log::Instance()->FatalError("Failed to initialize SDL.\nSDL_Error: ", ERR_CODE::SDL_FAILED_TO_INIT, true);

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		Log::Instance()->FatalError("Failed to initialize SDL Image.\nSDL_Error: ", ERR_CODE::SDL_IMG_FAILED_TO_INIT, true);

	FontManager::Instance()->Init();

	Audio::Instance()->Init();

	int width = 1024;
	int height = 768;
	Window* pMainWindow = WindowManager::Instance()->CreateWindow("Main Window", width, height);
	m_pMainCamera = new Camera(glm::vec3(0.0f, 0.0f, -10.0f), width, height);

	Time::Instance()->SetMaxFps(144);

	m_pMainScene = SceneManager::Instance()->CreateEmptyScene("MainScene", pMainWindow, m_pMainCamera);

	GameManager::Instance()->InitGame(m_pMainScene);

	DLOG("Engine Initialized!");
}

void Engine::Run()
{
	while (m_running)
	{
		Time::Instance()->Tick();
		//Time::Instance()->StartTick();
		InputManager::Instance()->Listen();
		Update();
		PhysicsUpdate();
		Render();
		//Time::Instance()->EndTick();

	}
}

void Engine::DestroyEngine()
{
	GameManager::Instance()->DestroyGame();

	SceneManager::Instance()->DestroyAllScenes();

	WindowManager::Instance()->Destroy();

	InputManager::Instance()->Destory();

	FontManager::Instance()->Destroy();

	Audio::Instance()->Destroy();

	delete m_pMainCamera;
	m_pMainCamera = nullptr;

	IMG_Quit();

	SDL_Quit();

	//system("PAUSE");

	// Delete the instance of the engine. THIS MUST BE THE LAST THING DESTROYED.
	delete m_pInstance;
	m_pInstance = nullptr;
}

void Engine::Update()
{
	SceneManager::Instance()->UpdateActiveScene();
	GameManager::Instance()->Update();
	ParticleManager::Instance()->Update();
}

void Engine::PhysicsUpdate()
{
	SceneManager::Instance()->PhysicsUpdateActiveScene();

	CollisionHandler::Instance()->Update();
}

void Engine::Render()
{
	SDL_Renderer* pRen = WindowManager::Instance()->GetMainWindow()->GetRenderer();
	SDL_SetRenderDrawColor(pRen, BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);

	SDL_RenderClear(pRen);

	ParticleManager::Instance()->Render();
	SceneManager::Instance()->RenderActiveScene();
	FontManager::Instance()->RenderFonts();

	SDL_RenderPresent(pRen);
}

SHADOW_NAMESPACE_END