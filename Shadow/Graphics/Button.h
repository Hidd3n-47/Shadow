#pragma once

SHADOW_NAMESPACE_BEGIN

class Button
{
public:
	Button() { }
	Button(short buttonId, const glm::vec2& position, int size, const std::string& text, Color mainColor, Color hoverColor, const std::string& filePath = "Assets/Fonts/Louis George Cafe Bold.ttf");
	
	bool Update(const glm::vec2& mousePosition, bool mousePressed);
	void DestroyButton();

	// Accessors.
	inline short GetButtonId() const { return m_buttonId; }
	inline glm::vec2 GetPosition() const { return m_position; }
	inline uint16_t GetFontId() const { return m_fontId; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline bool GetHovering() const { return m_hovering; }

	// Mutators.
	inline void SetHovering(bool hover) { m_hovering = hover; }
private:
	short m_buttonId = 0;
	glm::vec2 m_position = glm::vec2(0.0f);
	uint16_t m_fontId = 0;
	int m_width = 0;
	int m_height = 0;
	bool m_hovering = false;

	Color m_mainColor = Color(Black);
	Color m_hoverColor = Color(Black);
};

SHADOW_NAMESPACE_END