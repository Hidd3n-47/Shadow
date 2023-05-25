#include "sdpch.h"
#include "FontManager.h"

#include "Scene/SceneManager.h"
#include "TextureManager.h"

SHADOW_NAMESPACE_BEGIN

FontManager* FontManager::m_pInstance = nullptr;

void FontManager::Init()
{
	if (TTF_Init() == -1)
		Log::Instance()->FatalError("Failed to initialize SDL TTF.\nSDL_Error: ", ERR_CODE::SDL_TTF_FAILED_TO_INIT, true);
}

void FontManager::Destroy()
{
	DeleteAllFonts();

	TTF_Quit();
}

uint16_t FontManager::CreateFont(const std::string& fontFilepath, int fontSize, const std::string& text, Color textColor, const glm::vec2& position)
{
	LoadFont(m_fontId, fontFilepath, fontSize, text, textColor, position);

	return m_fontId++;
}

void FontManager::UpdateFont(uint16_t fontId, std::string text)
{
	m_fonts[fontId]->text = text;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::UpdateFont(uint16_t fontId, const std::string& text, int size)
{
	m_fonts[fontId]->text = text;
	m_fonts[fontId]->fontSize = size;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::UpdateFont(uint16_t fontId, const std::string& text, Color color)
{
	m_fonts[fontId]->text = text;
	m_fonts[fontId]->color = color;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::UpdateFont(uint16_t fontId, const std::string& text, int size, Color color)
{
	m_fonts[fontId]->text = text;
	m_fonts[fontId]->fontSize = size;
	m_fonts[fontId]->color = color;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::UpdateFont(uint16_t fontId, int size)
{
	m_fonts[fontId]->fontSize = size;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::UpdateFont(uint16_t fontId, int size, Color color)
{
	m_fonts[fontId]->fontSize = size;
	m_fonts[fontId]->color = color;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::UpdateFont(uint16_t fontId, Color color)
{
	m_fonts[fontId]->color = color;

	LoadFont(fontId, m_fonts[fontId]->filePath, m_fonts[fontId]->fontSize, m_fonts[fontId]->text, m_fonts[fontId]->color, m_fonts[fontId]->position);
}

void FontManager::RenderFonts()
{
	SDL_Renderer* pRenderer = SceneManager::Instance()->GetActiveScene()->GetWindow()->GetRenderer();

	std::unordered_map<uint16_t, Font*>::iterator it;
	for (it = m_fonts.begin(); it != m_fonts.end(); it++)
	{
		int width = it->second->width;
		int height = it->second->height;
		SDL_Rect srcRect = { 0, 0, width, height };
		SDL_Rect destRect = { it->second->position.x, it->second->position.y, width, height };

		int err = SDL_RenderCopyEx(pRenderer, it->second->pTexture, &srcRect, &destRect, 0, nullptr, SDL_FLIP_NONE);

		if (err < 0)
			Log::Instance()->CriticalError("Failed to render font texuture with ID " + std::to_string(it->first) + ".\nSDL Error : " + (std::string)SDL_GetError(), ERR_CODE::FAILED_TO_RENDER_TEXTURE);

		// Debugging
#ifdef _DEBUG
		SDL_Rect rect = { it->second->position.x, it->second->position.y, it->second->width, it->second->height };
		SDL_SetRenderDrawColor(pRenderer, 255,0, 255, 255);
		SDL_RenderDrawRect(pRenderer, &rect);
#endif
	}
}

void FontManager::DeleteFont(uint16_t fontId)
{
	delete m_fonts[fontId];

	m_fonts.erase(fontId);

	DLOG("Font with id " + std::to_string(fontId) + " deleted.")
}

void FontManager::DeleteAllFonts()
{
	std::unordered_map<uint16_t, Font*>::iterator it;
	for (it = m_fonts.begin(); it != m_fonts.end(); it++)
		delete it->second;

	m_fonts.clear();
}

bool FontManager::FontIdInMap(uint16_t id)
{
	for (auto it = m_fonts.begin(); it != m_fonts.end(); it++)
		if (it->first == id)
			return true;

	return false;
}

void FontManager::LoadFont(uint16_t fontId, const std::string& fontFilepath, int fontSize, const std::string& text, Color textColor, const glm::vec2& position)
{
	int width;
	int height;

	bool inMap = FontIdInMap(fontId);

	m_pFont = TTF_OpenFont(fontFilepath.c_str(), fontSize);
	if (m_pFont == nullptr)
		Log::Instance()->CriticalError("Failed to load font at file path:\n" + fontFilepath + "\nSDL Err: " + (std::string)TTF_GetError(), ERR_CODE::SDL_FAILED_CREATE_TEXTURE_FROM_SURFACE);

	SDL_Surface* surface = TTF_RenderText_Solid(m_pFont, text.c_str(), { textColor.r, textColor.g, textColor.b });
	if (surface == nullptr)
		Log::Instance()->CriticalError("Failed to create image for font.\nSDL Err: " + (std::string)SDL_GetError(), ERR_CODE::SDL_IMG_FAILED_TO_LOAD_IMAGE);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(SceneManager::Instance()->GetActiveScene()->GetWindow()->GetRenderer(), surface);
	if (texture == nullptr)
		Log::Instance()->CriticalError("Failed to create texture from surface for font.\nSDL Err: " + (std::string)SDL_GetError(), ERR_CODE::SDL_FAILED_CREATE_TEXTURE_FROM_SURFACE);

	width = surface->w;
	height = surface->h;

	SDL_FreeSurface(surface);

	TTF_CloseFont(m_pFont);

	if (!inMap)
	{
		m_fonts[fontId] = new Font(texture, width, height, fontSize, position, fontFilepath, text, textColor);

		return;
	}
	
	SDL_DestroyTexture(m_fonts[fontId]->pTexture);

	m_fonts[fontId]->pTexture = texture;
	m_fonts[fontId]->width = width;
	m_fonts[fontId]->height = height;
}

SHADOW_NAMESPACE_END