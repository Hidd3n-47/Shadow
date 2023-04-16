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

// Global Functions.
// Question: is this the incorrect place/bad practice?
// Template function to find the next unique name in the given template.
// Note that the template class needs to have a GetName() method.
template <typename T>
void FindNextUniqueName(const std::vector<T>& vec, std::string& name)
{
	std::string original = name;
	int counter = 0;
	bool nameTaken = false;

	 do
	 {
		for (T a : vec)
			if (a->GetName() == name)
			{
				nameTaken = true;
			}
			else
			{
				nameTaken = false;
			}

		if (nameTaken)
		{
			counter++;
			name = original + " (" + std::to_string(counter) + ")";
		}
	 } while (nameTaken);
}

//Log::Instance()->DebugLog("x: " + std::to_string(p.x) + " | y: " + std::to_string(p.y) + " | z: " + std::to_string(p.z));