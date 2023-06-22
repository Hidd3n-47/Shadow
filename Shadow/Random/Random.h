#pragma once

#include <random>
#include <ctime>

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
RANDOM:
	A small static class to generate random numbers. Can generate a random int or 
	an integer between two numbers (lower inclusive and upper exlusive).
=========================================================================================
*/
class Random
{
public:
	static int GetRandomIntBetween(int lowerBound, int upperBound);

	inline static int GetRandomInt() { return (*m_randomEngine)(); }

private:
	~Random();

	static std::mt19937* m_randomEngine ;

	static int mod(int value, int mod);
};

SHADOW_NAMESPACE_END