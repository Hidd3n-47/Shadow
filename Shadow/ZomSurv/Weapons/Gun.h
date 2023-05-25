#pragma once

#include "Ammo/Ammo.h"
#include "Audio/SoundEffect.h"

class Gun
{
public:
	Gun(const std::string& name, bool automatic,  float damage,  float fireRate, AmmoType ammoType, unsigned short clipSize,  float timeToReload);
	~Gun();

	void Shoot();
	bool Reload();
	void ReloadAudio();
	void CancelReload();
	void Update(); // This update function could be used to update the position and direction of the gun sprite.

	// Accessors.
	inline float GetDamage() const { return m_damage; }
	inline unsigned short GetNumInClip() const { return m_numInClip; }
	inline AmmoType GetAmmoType() const { return m_ammoType; }

	// Mutators.
	inline void SetClipSize(unsigned short max) { m_clipSize = max; }
	inline void SetTimerToMax() { m_timer = m_fireRate; }
private:
	// Private variables.
	std::string m_name;
	bool m_automatic;
	float m_damage;
	float m_fireRate;
	AmmoType m_ammoType;
	unsigned short m_clipSize;
	unsigned short m_numInClip;
	float m_timeToReload;
	float m_reloadTimer;
	int m_textureId;
	glm::vec2 m_position;
	glm::vec2 m_direction;
	float m_halfWidth;
	float m_halfHeight;

	float m_timer = 0.0f;
	bool m_shot = false;
	bool m_playReloadAudio = true;

	Shadow::SoundEffect* m_sound = nullptr;
	Shadow::SoundEffect* m_reloadSound = nullptr;

	// Private methods.
	void ReloadSuccessful();
};

