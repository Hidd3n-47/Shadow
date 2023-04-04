#include "sdpch.h"
#include "Engine.h"

#include "Input/InputManager.h"
#include "Window/WindowManager.h"

#include "Scene/SceneManager.h"
#include "GameObject/GameObjectManager.h"
#include "Collision/CollisionHandler.h"
#include "Physics/Transform.h"
#include "Component/SpriteRenderer.h"
#include "Component/RigidBody2D.h"
#include "Component/BoxCollider2D.h"
#include "Time/Time.h"

SHADOW_NAMESPACE_BEGIN

Engine* Engine::m_pInstance = nullptr;

void Engine::InitEngine()
{
	// TODO need to implement where the engine load textures that are used for the engine, example, debugging textures such as arrows for rigid body as well as the "No texture" texture.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		Log::Instance()->FatalError("Failed to initialize SDL.\nSDL_Error: ", ERR_CODE::SDL_FAILED_TO_INIT, true);

	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		Log::Instance()->FatalError("Failed to initialize SDL Image.\nSDL_Error: ", ERR_CODE::SDL_IMG_FAILED_TO_INIT, true);

	int width = 1024;
	int height = 768;
	Window* pMainWindow = WindowManager::Instance()->CreateWindow("Main Window", width, height);
	Camera* pMainCamera = new Camera(glm::vec3(0.0f, 0.0f, -10.0f), width, height);

	DLOG("Engine Initialized!")

	Time::Instance()->SetMaxFps(144);

	m_pMainScene = SceneManager::Instance()->CreateEmptyScene("MainScene", pMainWindow, pMainCamera);

	/// --- Test -> Debugging
	gm = m_pMainScene->CreateEmptyGameObject("test");
	pMainCamera->SetTargetPosition(gm->GetTransform()->position);
	col = m_pMainScene->CreateEmptyGameObject("Collider");

	SpriteRenderer* sr = new SpriteRenderer(gm, "Assets/circle.png");
	gm->AddComponent(sr);
	RigidBody2D* rb = new RigidBody2D(gm, true);
	gm->AddComponent(rb);
	BoxCollider2D* b = new BoxCollider2D(gm, { }, { 32.0f, 32.0f});
	gm->AddComponent(b);


	col->GetTransform()->position = glm::vec3(0.0f, 500.0f, 0.0f);
	BoxCollider2D* bc = new BoxCollider2D(col, {0.0f, 0.0f }, { 200.0f, 50.0f });
	col->AddComponent(bc);
}

void Engine::Run()
{
	while (m_running)
	{
		InputManager::Instance()->Listen();
		Update();
		Render();

		Time::Instance()->Tick();
	}
}

void Engine::DestroyEngine()
{
	SceneManager::Instance()->DestroyAllScenes();

	WindowManager::Instance()->Destroy();

	InputManager::Instance()->Destory();

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

	CollisionHandler::Instance()->Update();
}

void Engine::Render()
{
	SDL_Renderer* pRen = WindowManager::Instance()->GetMainWindow()->GetRenderer();
	SDL_SetRenderDrawColor(pRen,BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);

	SDL_RenderClear(pRen);

	SceneManager::Instance()->RenderActiveScene();

	SDL_RenderPresent(pRen);
}

SHADOW_NAMESPACE_END