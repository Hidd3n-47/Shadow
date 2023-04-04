#pragma once

#include <glm/glm.hpp>

SHADOW_NAMESPACE_BEGIN

class Camera;

enum DebugRenderType
{
	Square,
	DirectionArrowBlue,
	DirectionArrowPink,
	DirectionArrowGreen
};

/***
=========================================================================================
TEXTURE_MANAGER:
	TextureManager handles the loading and caching of textures.
	
	Use Destroy method to manually destroy the instance of the singleton.
=========================================================================================
*/
class TextureManager
{
public:
	inline static TextureManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new TextureManager() : m_pInstance; }

	void Create();

	uint16_t Load(std::string filePath, SDL_Renderer* pRenderer, int width = TILE_WIDTH, int height = TILE_WIDTH);

	void RenderSingle(Camera* pCamera, SDL_Renderer* pRenderer, uint16_t id, float worldX, float worldY, int sheetX = 0, int sheetY = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DebugRender(Camera* pCamera, SDL_Renderer* pRenderer, DebugRenderType type, glm::vec3 worldPos, glm::vec2 dimensions = {TILE_WIDTH, TILE_WIDTH}, Color color = Color(Red));

	void RemoveTexture(uint16_t id);
	void RemoveAllTextures();

	void Destroy();
private:
	TextureManager() { }
	~TextureManager();

	static TextureManager* m_pInstance;

	uint16_t m_id = 0;
	std::unordered_map<int, SDL_Texture*> m_textureMap;
};

SHADOW_NAMESPACE_END