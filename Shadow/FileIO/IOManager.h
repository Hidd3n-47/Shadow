#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "Logger/Log.h"

SHADOW_NAMESPACE_BEGIN

class IOManager
{
public:
	inline static IOManager* Instance() { return m_pInstance == nullptr ? m_pInstance = new IOManager() : m_pInstance; }

	void LoadTextFile(std::vector<std::string>& fileContents, const std::string& filePath);

private:
	IOManager() {};
	~IOManager();

	static IOManager* m_pInstance;

	std::ifstream m_fileReadOnly;
};

SHADOW_NAMESPACE_END