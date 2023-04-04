#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define SHADOW_NAMESPACE_BEGIN namespace Shadow {
#define SHADOW_NAMESPACE_END }

#include "Logger/Log.h"
#include "Graphics/Color.h"

// Debugging definitions.
#define RENDER_DEBUG

// Engine Defaults.
const Color BG_COLOR = Color(10, 10, 15, 255);

// Defines.
#define TILE_WIDTH 32

// Macros.
#define DLOG(...) Log::Instance()->DebugLog(__VA_ARGS__);

//Log::Instance()->DebugLog("x: " + std::to_string(p.x) + " | y: " + std::to_string(p.y) + " | z: " + std::to_string(p.z));