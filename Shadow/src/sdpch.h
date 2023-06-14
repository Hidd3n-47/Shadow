#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <memory>

#include <SDL/SDL.h>
#include <mix/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <glm/glm.hpp>

#define SHADOW_NAMESPACE_BEGIN namespace Shadow {
#define SHADOW_NAMESPACE_END }

#include "Logger/Log.h"
#include "Scene/SceneManager.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Graphics/Color.h"

// Debugging definitions.
#ifdef _DEBUG
#define RENDER_DEBUG
#endif

// Engine Defaults.
const Color BG_COLOR = Color(200, 200, 200, 255);
//const Color BG_COLOR = Color(10, 10, 15, 255);

// Defines.
#define TILE_WIDTH 32
#define PI 3.14159265358979323846264338327950288

// Macros.
#define DLOG(...) Log::Instance()->DebugLog(__VA_ARGS__);


//void* operator new(size_t size)
//{
//	Shadow::DLOG("Allocated " + std::to_string(size) + " bytes of memory.");
//
//	return malloc(size);
//}
//
//void operator delete(void* memory, size_t size)
//{
//	Shadow::DLOG("Freein " + std::to_string(size) + " bytes of memory.");
//
//	free(memory);
//}
//
//struct AllocationMetrics
//{
//	uint32_t totalAllocated = 0;
//	uint32_t totalFreed = 0;
//
//	inline uint32_t CurrentUsage() { return totalAllocated - totalFreed; }
//};

