#pragma once

SHADOW_NAMESPACE_BEGIN

enum class ERR_CODE {
	DEFAULT = -1,
	SDL_FAILED_TO_INIT = 1,
	SDL_IMG_FAILED_TO_INIT = 2,
	FAILED_TO_OPEN_FILE = 3,
	INVALID_AMMOTYPE_IN_GUN_FILE = 4,
	SDL_IMG_FAILED_TO_LOAD_IMAGE = 5,
	SDL_FAILED_CREATE_TEXTURE_FROM_SURFACE = 6,
	FAILED_TO_RENDER_TEXTURE = 7,
	GUN_FILE_INCORRECT_LENGTH = 8,
	LEVEL_FILE_INCORRECT_LENGTH = 9,
	NO_MAP_LOADED_TO_RENDER = 10
};

/***
=========================================================================================
TEXTURE_MANAGER:
	TextureManager handles the loading and caching of textures.

	Use Destroy method to manually destroy the instance of the singleton.
=========================================================================================
*/
class Log
{
public:
	inline static Log* Instance() { return m_pInstance == nullptr ? m_pInstance = new Log() : m_pInstance; }

	/*
		\brief Logs a message that will only show in debug mode.
		\param msg: the message logged to the console window.
	*/
	void DebugLog(const std::string& msg);
	/*
		\brief Logs a warning message to the console.
		\param warningMsg: the message logged to the console window.
	*/
	void Warning(const std::string& warningMsg);
	/*
		\brief Logs a critical error message to the console. Critical errors does not exit the game.
		\param warningMsg: the message logged to the console window.
		\param errCode: the error code for the specific error.
	*/
	void CriticalError(const std::string& errMsg, ERR_CODE errCode = ERR_CODE::DEFAULT);
	/*
		\brief Logs a fatal error message to the console. Fatal error message closes the game after message prompt.
		\param errMsg: the message logged to the console window.
		\param errCode: the error code for the specific error.
		\param sdlErr: set true if the error is an SDL Error.
	*/
	void FatalError(const std::string& errMsg, ERR_CODE errCode = ERR_CODE::DEFAULT, bool sdlErr = false);
private:
	Log() { }
	~Log(){ }

	static Log* m_pInstance;
};

SHADOW_NAMESPACE_END