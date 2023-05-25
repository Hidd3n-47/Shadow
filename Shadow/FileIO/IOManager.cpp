#include "sdpch.h"
#include "FileIO/IOManager.h"

SHADOW_NAMESPACE_BEGIN

IOManager* IOManager::m_pInstance = nullptr;

IOManager::~IOManager()
{
	delete m_pInstance;
}

void IOManager::LoadTextFile(std::vector<std::string>& fileContents, const std::string& filePath)
{
	m_fileReadOnly.open(filePath.c_str(), std::ios::in);

	if (m_fileReadOnly.fail())
		Log::Instance()->FatalError("Failed to open file.\nFile Path: " + filePath, ERR_CODE::FAILED_TO_OPEN_FILE);

	std::string line;

	while (std::getline(m_fileReadOnly, line, '\n'))
		fileContents.push_back(line);

	m_fileReadOnly.close();
}

SHADOW_NAMESPACE_END