#pragma once

#include <random>
#include <ctime>

SHADOW_NAMESPACE_BEGIN

class Random
{
public:
	//inline static Random* Instance() { return m_pInstance == nullptr ? m_pInstance = new Random() : m_pInstance; }

	static int GetRandomIntBetween(int lowerBound, int upperBound);

	inline static int GetRandomInt() { return (*m_randomEngine)(); }

private:
	/*Random();*/
	~Random();

	static std::mt19937* m_randomEngine ;

	static int mod(int value, int mod);
};

SHADOW_NAMESPACE_END