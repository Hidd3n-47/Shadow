#include "sdpch.h"
#include "Random.h"

SHADOW_NAMESPACE_BEGIN

std::mt19937* Random::m_randomEngine = new std::mt19937(time(nullptr));

Random::~Random()
{
	delete m_randomEngine;
}

int Random::GetRandomIntBetween(int lowerBound, int upperBound)
{
	int rand = GetRandomInt();

	if (rand < 0)
		rand *= -1;

	return lowerBound + mod(rand, upperBound - lowerBound);
}

int Random::mod(int value, int mod)
{
	int ans = value % mod;

	if (ans < 0)
		return ans + mod;

	return ans;
}

SHADOW_NAMESPACE_END