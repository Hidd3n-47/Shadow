#include "sdpch.h"
#pragma once

SHADOW_NAMESPACE_BEGIN

// Engines custom keycodes.
typedef enum
{
	KEYCODE_UNKNOWN = 0,
	KEYCODE_RETURN = '\r',
	KEYCODE_ESCAPE = '\x1B',
	KEYCODE_BACKSPACE = '\b',
	KEYCODE_TAB = '\t',
	KEYCODE_SPACE = ' ',
	KEYCODE_EXCLAIM = '!',
	KEYCODE_QUOTEDBL = '"',
	KEYCODE_HASH = '#',
	KEYCODE_PERCENT = '%',
	KEYCODE_DOLLAR = '$',
	KEYCODE_AMPERSAND = '&',
	KEYCODE_QUOTE = '\'',
	KEYCODE_LEFTPAREN = '(',
	KEYCODE_RIGHTPAREN = ')',
	KEYCODE_ASTERISK = '*',
	KEYCODE_PLUS = '+',
	KEYCODE_COMMA = ',',
	KEYCODE_MINUS = '-',
	KEYCODE_PERIOD = '.',
	KEYCODE_SLASH = '/',
	KEYCODE_0 = '0',
	KEYCODE_1 = '1',
	KEYCODE_2 = '2',
	KEYCODE_3 = '3',
	KEYCODE_4 = '4',
	KEYCODE_5 = '5',
	KEYCODE_6 = '6',
	KEYCODE_7 = '7',
	KEYCODE_8 = '8',
	KEYCODE_9 = '9',
	KEYCODE_COLON = ':',
	KEYCODE_SEMICOLON = ';',
	KEYCODE_LESS = '<',
	KEYCODE_EQUALS = '=',
	KEYCODE_GREATER = '>',
	KEYCODE_QUESTION = '?',
	KEYCODE_AT = '@',
	KEYCODE_LEFTBRACKET = '[',
	KEYCODE_BACKSLASH = '\\',
	KEYCODE_RIGHTBRACKET = ']',
	KEYCODE_CARET = '^',
	KEYCODE_UNDERSCORE = '_',
	KEYCODE_BACKQUOTE = '`',
	KEYCODE_a = 'a',
	KEYCODE_b = 'b',
	KEYCODE_c = 'c',
	KEYCODE_d = 'd',
	KEYCODE_e = 'e',
	KEYCODE_f = 'f',
	KEYCODE_g = 'g',
	KEYCODE_h = 'h',
	KEYCODE_i = 'i',
	KEYCODE_j = 'j',
	KEYCODE_k = 'k',
	KEYCODE_l = 'l',
	KEYCODE_m = 'm',
	KEYCODE_n = 'n',
	KEYCODE_o = 'o',
	KEYCODE_p = 'p',
	KEYCODE_q = 'q',
	KEYCODE_r = 'r',
	KEYCODE_s = 's',
	KEYCODE_t = 't',
	KEYCODE_u = 'u',
	KEYCODE_v = 'v',
	KEYCODE_w = 'w',
	KEYCODE_x = 'x',
	KEYCODE_y = 'y',
	KEYCODE_z = 'z',
};

/***
=========================================================================================
INPUT_MANAGER:
	InputManager is a class to manage the engines input system.
	Use Listen() to poll for input. Can inquire if a key is down with IsKeyDown().
	Use Destroy method to manually destroy the instance of the singleton.
=========================================================================================
*/
class InputManager
{
public:
	inline static InputManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new InputManager() : m_pInstance; }

	void Listen();
	bool IsKeyDown(uint16_t keyId);

	inline void Destory() { delete m_pInstance; m_pInstance = nullptr; }
private:
	InputManager() { }
	~InputManager() { }

	static InputManager* m_pInstance;

	// Private methods.
	void KeyDown(uint16_t keyId);
	void KeyUp(uint16_t keyId);
	uint16_t a = SDLK_1;

	// Private variables.
	std::unordered_map<uint16_t, bool> m_keyMap;
};

SHADOW_NAMESPACE_END