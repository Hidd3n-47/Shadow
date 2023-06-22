#include "sdpch.h"
#pragma once

#include "Audio/Audio.h"

SHADOW_NAMESPACE_BEGIN

/***
=========================================================================================
SOUND_EFFECT:
	Class representing a sound effect. Loads a sound effect from file path and handles
	volume, loading and destruction.
=========================================================================================
*/
class SoundEffect
{
public:
	SoundEffect(const std::string& filePath) { m_soundId = Audio::Instance()->LoadSound(filePath); }
	SoundEffect(const std::string& filePath, int volume) : m_volume(volume) { m_soundId = Audio::Instance()->LoadSound(filePath, volume); }

	~SoundEffect() { Audio::Instance()->DestroySound(m_soundId); }

	inline void Play() { Audio::Instance()->PlaySound(m_soundId); }

	// Accessors.
	inline int GetVolume() const { return m_volume; }

	// Mutators.
	inline void SetVolume(int volume) { m_volume = volume; Audio::Instance()->SetSoundVolume(m_soundId, m_volume); }
private:
	Uint16 m_soundId = 0;
	int m_volume = 100;
};

SHADOW_NAMESPACE_END