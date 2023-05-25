#pragma once

#include "Mix/SDL_mixer.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
Audio:
	Deals with playing any audio sound effect or music.
=========================================================================================
*/
class Audio
{
public:
	inline static Audio* Instance() { return m_pInstance == nullptr ? m_pInstance = new Audio() : m_pInstance; }

	void Init();
	void Destroy();

	Uint16 LoadSound(const std::string& filePath);
	Uint16 LoadSound(const std::string& filePath, int volume);
	Uint16 LoadMusic(const std::string& filePath);
	Uint16 LoadMusic(const std::string& filePath, int volume);

	void PlaySound(Uint16 soundId);
	void PlayMusic(Uint16 musicId);

	void DestroySound(Uint16 soundId);
	void DestroyMusic(Uint16 musicId);

	inline void PauseMusic() { Mix_PauseMusic(); }

	inline void SetSoundVolume(Uint16 soundId, int volume) { m_sounds[soundId]->volume = volume; }
	inline void SetMusicVolume(Uint16 musicId, int volume) { Mix_VolumeMusic(volume); }
private:
	Audio();
	~Audio() { }

	static Audio* m_pInstance;

	Uint16 m_soundId = 0;
	Uint16 m_musicId = 0;

	std::unordered_map<Uint16, Mix_Chunk*> m_sounds;
	std::unordered_map<Uint16, Mix_Music*> m_music;
};

SHADOW_NAMESPACE_END