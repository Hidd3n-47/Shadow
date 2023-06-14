#pragma once

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

	uint16_t Load(std::string filePath, SDL_Renderer* pRenderer, int width = TILE_WIDTH, int height = TILE_WIDTH);

	void RenderSingle(Camera* pCamera, SDL_Renderer* pRenderer, uint16_t id, glm::vec2 world, glm::vec2 scale, const glm::vec2& dimensions = glm::vec2(-1.0f), int sheetX = 0, float angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DebugRender(Camera* pCamera, SDL_Renderer* pRenderer, DebugRenderType type, glm::vec3 worldPos, glm::vec2 halfExtents = {TILE_WIDTH * 0.5f, TILE_WIDTH * 0.5f }, Color color = Color(Red));

	void RemoveTexture(uint16_t id);
	void RemoveAllTextures();

	void SetTextureAlpha(int id, float alpha) { SDL_SetTextureAlphaMod(m_textureMap[id], alpha * 255); }
private:
	TextureManager() { }
	~TextureManager();

	static TextureManager* m_pInstance;

	uint16_t m_id = 0;
	std::unordered_map<int, SDL_Texture*> m_textureMap;
};

SHADOW_NAMESPACE_END