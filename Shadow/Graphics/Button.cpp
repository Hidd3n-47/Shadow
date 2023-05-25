#include "sdpch.h"
#include "Button.h"

#include "Graphics/FontManager.h"

SHADOW_NAMESPACE_BEGIN

Button::Button(short buttonId, const glm::vec2& position, int size, const std::string& text, Color mainColor, Color hoverColor, const std::string& filePath) :
	m_buttonId(buttonId),
	m_position(position),
	m_mainColor(mainColor),
	m_hoverColor(hoverColor)
{
	m_fontId = Shadow::FontManager::Instance()->CreateFont(filePath, size, text, m_mainColor, position);
	Shadow::FontManager::Instance()->GetWidthAndHeightOfFont(m_fontId, m_width, m_height);
}

bool Button::Update(const glm::vec2& mousePosition, bool mousePressed)
{
	if (m_position.x <= mousePosition.x && mousePosition.x <= m_position.x + m_width && 
			m_position.y <= mousePosition.y && mousePosition.y <= m_position.y + m_height)
	{
		if (mousePressed)
		{
			Shadow::FontManager::Instance()->UpdateFont(m_fontId, m_hoverColor);
			return true;
		}
		else if (!m_hovering)
		{
			Shadow::FontManager::Instance()->UpdateFont(m_fontId, m_hoverColor);
			m_hovering = true;
		}
	}
	else if (m_hovering)
	{
		Shadow::FontManager::Instance()->UpdateFont(m_fontId, m_mainColor);
		m_hovering = false;
	}

	return false;
}

void Button::DestroyButton()
{
	Shadow::FontManager::Instance()->DeleteFont(m_fontId);
}


SHADOW_NAMESPACE_END