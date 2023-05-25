#include "sdpch.h"
#include "TextureManager.h"

#include "Camera/Camera.h"

SHADOW_NAMESPACE_BEGIN

TextureManager* TextureManager::m_pInstance = nullptr;

TextureManager::~TextureManager()
{
	RemoveAllTextures();

	delete m_pInstance;
}

uint16_t TextureManager::Load(std::string filePath, SDL_Renderer* pRenderer, int width, int height)
{
	if (width != TILE_WIDTH || height != TILE_WIDTH)
		Log::Instance()->Warning("Texture is not 32 x 32 in size.\nFile Path: " + filePath);

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == nullptr)
		Log::Instance()->CriticalError("Failed to load image at path: " + filePath + "\nSDL Err: " + (std::string)SDL_GetError(),
			ERR_CODE::SDL_IMG_FAILED_TO_LOAD_IMAGE);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	if (texture == nullptr)
		Log::Instance()->CriticalError("Failed to create texture from surface.\nSDL Err: " + (std::string)SDL_GetError(),
			ERR_CODE::SDL_FAILED_CREATE_TEXTURE_FROM_SURFACE);

	SDL_FreeSurface(surface);

	m_textureMap[m_id] = texture;

	return m_id++;
}

void TextureManager::RenderSingle(Camera* pCamera, SDL_Renderer* pRenderer, uint16_t id, glm::vec2 world, glm::vec2 scale, int sheetX, int sheetY, SDL_RendererFlip flip)
{
	glm::vec3 camPosition = pCamera->GetPosition();
	float width, height;
	pCamera->GetWidthAndHeight(width, height);

	// This needs to be fixed later.
	//  Need to accomidate the length of the actual object. THis needs to be implemented when texure class. TODO
	if (world.x < camPosition.x - width || world.x > camPosition.x + width || world.y > camPosition.y + height || world.y < camPosition.y - height)
		return;

	SDL_Rect srcRect = { sheetX, sheetY, TILE_WIDTH, TILE_WIDTH };
	SDL_Rect destRect = { floor(world.x - camPosition.x + width * 0.5f), floor(world.y - camPosition.y + height * 0.5f), TILE_WIDTH * scale.x, TILE_WIDTH * scale.y };

	int err = SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);

	if (err < 0)
		Log::Instance()->CriticalError("Failed to render texture with ID " + std::to_string(id) +
			".\nSDL Error : " + (std::string)SDL_GetError(), ERR_CODE::FAILED_TO_RENDER_TEXTURE);
}

void TextureManager::DebugRender(Camera* pCamera, SDL_Renderer* pRenderer, DebugRenderType type, glm::vec3 worldPos, glm::vec2 halfExtents, Color color)
{
	glm::vec3 camPosition = pCamera->GetPosition();
	float width, height;
	pCamera->GetWidthAndHeight(width, height);

	if (worldPos.x < camPosition.x - width || worldPos.x > camPosition.x + width || worldPos.y > camPosition.y + height || worldPos.y < camPosition.y - height)
		return;

	SDL_Rect destRect = { floor(worldPos.x - camPosition.x + width * 0.5f), floor(worldPos.y - camPosition.y + height * 0.5f), halfExtents.x * 2.0f, halfExtents.y * 2.0f };

	SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a);
	switch (type)
	{
	case Square:
		SDL_RenderDrawRect(pRenderer, &destRect);
		break;
	}
}

void TextureManager::RemoveTexture(uint16_t id)
{
	SDL_DestroyTexture(m_textureMap[id]);

	m_textureMap.erase(id);
}

void TextureManager::RemoveAllTextures()
{
	std::unordered_map<int, SDL_Texture*>::iterator it;
	for (it = m_textureMap.begin(); it != m_textureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	m_textureMap.clear();
}

void TextureManager::Destroy()
{
	//Empty.
}

SHADOW_NAMESPACE_END