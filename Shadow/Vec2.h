#pragma once
#include <math.h>

/***
=========================================================================================
IGAME_OBJECT:
	A structure for 2 dimensional vectors.
=========================================================================================
*/
struct vec2
{
	//vec2() : x(0), y(0) { }
	vec2(const float& x = 0.0f, const float& y = 0.0f) : x(x), y(y) { }

	float x, y;

	float magnitude() { return (float)sqrt(x * x + y * y); }

	void normalise() { float l = magnitude(); if (l != 0) { x /= l; y /= l; } }

	inline vec2 operator + (const vec2& v2) const { return vec2(x + v2.x, y + v2.y); }
	inline vec2 operator - (const vec2& v2) const { return vec2(x - v2.x, y - v2.y); }
	inline vec2 operator * (const float& scalar) const { return vec2(x * scalar, y * scalar); }
	inline void operator += (const vec2& v2) { x += v2.x; y += v2.y; }
	inline void operator -= (const vec2& v2) { x -= v2.x; y -= v2.y; }
	inline void operator *= (const float& scalar) { x *= scalar; y *= scalar; }
	inline bool operator == (const vec2& v1) { if (x == v1.x && y == v1.y) return true; return false; }
};