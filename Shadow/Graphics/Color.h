#include "src/sdpch.h"
#pragma once

enum BasicColors
{
	Black,
	White,
	Blue,
	Red,
	Pink,
	Purple,
	Orange,
	Green,
	Yellow,
	Brown
};

struct Color
{
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) { }
	Color(BasicColors color)
	{
		switch (color)
		{
		case Black:
			*this = Color(0, 0, 0, 255);
			break;
		case White:
			*this = Color(255, 255, 255, 255);
			break;
		case Blue:
			*this = Color(7, 120, 176, 255);
			break;
		case Red:
			*this = Color(255, 0, 0, 255);
			break;
		case Pink:
			*this = Color(217, 46, 200, 255);
			break;
		case Purple:
			*this = Color(65, 6, 184, 255);
			break;
		case Orange:
			*this = Color(219, 100, 9, 255);
			break;
		case Green:
			*this = Color(0, 255, 0, 255);
			break;
		case Yellow:
			*this = Color(230, 226, 14, 255);
			break;
		case Brown:
			*this = Color(82, 49, 2, 255);
			break;
		}
	}

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 0;
};