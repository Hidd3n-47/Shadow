#include "sdpch.h"
#pragma once

#include "Window/Window.h"
#include "GameObject/GameObject.h"
#include "Camera/Camera.h"

SHADOW_NAMESPACE_BEGIN

class Scene;

/***
=========================================================================================
Engine:
	Engine is a class to manage the engine start-up and shut-down.
	All systems that must be loaded for the engine can be loaded in InitEngine().
	The destruction/unloading of systems happens in DestroyEngine().
=========================================================================================
*/
class Engine
{
public:
	static Engine* Instance() { return m_pInstance == nullptr ? m_pInstance = new Engine() : m_pInstance; }

	void InitEngine();
	void Run();
	void DestroyEngine();

	inline void StopRunning() { m_running = false; }
private:
	Engine(){ }
	~Engine() { }

	static Engine* m_pInstance;

	bool m_running = true;

	void Update();
	void PhysicsUpdate();
	void Render();

	Scene* m_pMainScene = nullptr;
	GameObject* gm = nullptr;
	GameObject* gm2 = nullptr;
	GameObject* col = nullptr;
	//Camera m_camera;
};

SHADOW_NAMESPACE_END