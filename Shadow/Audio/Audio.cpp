#include "sdpch.h"
#include "Audio.h"

SHADOW_NAMESPACE_BEGIN

Audio* Audio::m_pInstance = nullptr;

Audio::Audio()
{
	// Empty.
}

void Audio::Init()
{
	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0)
		Log::Instance()->FatalError("Failed to initialize SDL Mixer.\nSDL_Error: ", ERR_CODE::SDL_MIXER_FAILED_TO_INIT, true);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

void Audio::Destroy()
{
	for (auto it = m_music.begin(); it != m_music.end(); ++it)
		Mix_FreeMusic(it->second);

	for (auto it = m_sounds.begin(); it != m_sounds.end(); ++it)
		Mix_FreeChunk(it->second);

	Mix_Quit();

	delete m_pInstance;
}

Uint16 Audio::LoadSound(const std::string& filePath)
{
	m_sounds[m_soundId] = Mix_LoadWAV(filePath.c_str());

	if (m_sounds[m_soundId] == nullptr)
		Log::Instance()->FatalError("Failed to load WAV file at: " + filePath, ERR_CODE::CANNOT_CREATE_MUSIC, true);

	return m_soundId++;
}

Uint16 Audio::LoadSound(const std::string& filePath, int volume)
{
	Uint16 id = LoadSound(filePath);

	m_sounds[id]->volume = volume;
	return id;
}

Uint16 Audio::LoadMusic(const std::string& filePath)
{
	m_music[m_musicId] = Mix_LoadMUS(filePath.c_str());

	if (m_music[m_musicId] == nullptr)
		Log::Instance()->FatalError("Failed to load Mp3 file at: " + filePath, ERR_CODE::CANNOT_CREATE_MUSIC, true);

	return m_musicId++;
}

Uint16 Audio::LoadMusic(const std::string& filePath, int volume)
{
	Uint16 id = LoadMusic(filePath);

	SetMusicVolume(id, volume);
	return id;
}

void Audio::PlaySound(Uint16 soundId)
{
	if (Mix_PlayChannel(-1, m_sounds[soundId], 0) == -1)
		Log::Instance()->FatalError("Failed to play sound effect with ID: " + std::to_string(soundId), ERR_CODE::FAILED_TO_PLAY_SOUND, true);
}

void Audio::PlayMusic(Uint16 musicId)
{
	if(!Mix_PlayingMusic())
		if (Mix_PlayMusic(m_music[musicId], -1) == -1)
			Log::Instance()->FatalError("Failed to play music with ID: " + std::to_string(musicId), ERR_CODE::FAILED_TO_PLAY_MUSIC, true);
	else if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}

void Audio::DestroySound(Uint16 soundId)
{
	Mix_FreeChunk(m_sounds[soundId]);

	m_sounds.erase(soundId);
}

void Audio::DestroyMusic(Uint16 musicId)
{
	Mix_FreeMusic(m_music[musicId]);

	m_music.erase(musicId);
}

SHADOW_NAMESPACE_END