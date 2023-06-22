#pragma once

#include <ttf/SDL_ttf.h>

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
FONT:
	A class to hold information relating to a font.
=========================================================================================
*/
struct Font
{
	Font() { }
	Font(SDL_Texture* texture, int w, int h, int size, const glm::vec2& fontPosition, const std::string& filePath, const std::string& text, Color color) : 
		pTexture(texture), width(w), height(h), fontSize(size), position(fontPosition), filePath(filePath), text(text), color(color) { }
	~Font() { SDL_DestroyTexture(pTexture); }

	SDL_Texture* pTexture = nullptr;
	int width = 0;
	int height = 0;
	int fontSize = 12;
	glm::vec2 position = glm::vec2(0.0f);
	const std::string filePath;
	std::string text = "";
	Color color = Color(Black);
};

/***
=========================================================================================
FONT_MANAGER:
	Font manager is a singleton that deals with the loading, updating, rendering and
	destroying of the fonts.
=========================================================================================
*/
class FontManager
{
public:
	inline static FontManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new FontManager() : m_pInstance; }

	void Init();
	void Destroy();

	uint16_t CreateFont(const std::string& fontFilepath, int fontSize, const std::string& text, Color textColor, const glm::vec2& position = glm::vec2(0.0f));
	/*uint16_t CreatePopupText(const std::string& fontFilepath, int fontSize, const std::string& text, Color textColor, const glm::vec2& worldPosition = glm::vec2(0.0f));
	void DisablePopupText(uint16_t popupId);*/ // THIS IS FOR A TIMER.

	void UpdateFont(uint16_t fontId, std::string text);
	void UpdateFont(uint16_t fontId, const std::string& text, int size);
	void UpdateFont(uint16_t fontId, const std::string& text, Color color);
	void UpdateFont(uint16_t fontId, const std::string& text, int size, Color color);
	void UpdateFont(uint16_t fontId, int size);
	void UpdateFont(uint16_t fontId, int size, Color color);
	void UpdateFont(uint16_t fontId, Color color);

	inline void UpdateFont(uint16_t fontId, const glm::vec2& position) { m_fonts[fontId]->position = position; }
	inline void TranslateFont(uint16_t fontId, const glm::vec2& translation) { m_fonts[fontId]->position += translation; }

	void RenderFonts();

	void DeleteFont(uint16_t fontId);
	void DeleteAllFonts();
	
	// Accessors.
	inline void GetWidthAndHeightOfFont(uint16_t fontId, int& width, int& height) { width = m_fonts[fontId]->width; height = m_fonts[fontId]->height; }
private:
	FontManager() { }
	~FontManager() { }

	static FontManager* m_pInstance;

	std::unordered_map<uint16_t, Font*> m_fonts;
	std::list<uint16_t> m_popupText;

	TTF_Font* m_pFont = nullptr;
	uint16_t m_fontId = 0;

	bool FontIdInMap(uint16_t id);
	void LoadFont(uint16_t fontId, const std::string& fontFilepath, int fontSize, const std::string& text, Color textColor, const glm::vec2& position = glm::vec2(0.0f));
};

SHADOW_NAMESPACE_END