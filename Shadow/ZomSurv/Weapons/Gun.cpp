#include "sdpch.h"
#include "Gun.h"

#include <glm/gtx/vector_angle.hpp>

#include "Graphics/TextureManager.h"
#include "Input/InputManager.h"
#include "Audio/Audio.h"
#include "Time/Time.h"

#include "ZomSurv/src/GameManager.h"
#include "Bullet/BulletManager.h"
#include "GunManager.h"

Gun::Gun(const std::string& name, bool automatic, float damage, float fireRate, AmmoType ammoType, unsigned short clipSize, float timeToReload) :
	m_name(name),
	m_automatic(automatic),
	m_damage(damage),
	m_fireRate(fireRate),
	m_ammoType(ammoType),
	m_clipSize(clipSize),
	m_numInClip(m_clipSize),
	m_timeToReload(timeToReload),
	m_reloadTimer(m_timeToReload),
	m_textureId(-1)
{
	ReloadSuccessful();

	Shadow::SceneManager::Instance()->GetActiveScene()->GetCamera()->GetWidthAndHeight(m_halfWidth, m_halfHeight);

	m_halfWidth *= 0.5f;
	m_halfHeight *= 0.5f;

	m_sound = new Shadow::SoundEffect("Assets/Weapons/Audio/pistolShot.wav", 5);
	m_reloadSound = new Shadow::SoundEffect("Assets/Weapons/Audio/reloadPistol.wav", 5);
}

Gun::~Gun()
{
	delete m_sound;
}


void Gun::Shoot()
{
	const float BULLET_DISTANCE_FROM_CENTER = 18;

	if (m_shot)
	{
		m_timer += Shadow::Time::Instance()->TimerStop() / 1000.0f;

		if (m_timer < m_fireRate)
		{
			Shadow::Time::Instance()->TimerStart();
			return;
		}
	}

	m_sound->Play();

	short directionMultiplierX = 1;
	short directionMultiplierY = -1;

	glm::vec2 playerPosition = GameManager::Instance()->GetPlayerPosition();

	glm::vec2 mouseCoords = Shadow::InputManager::Instance()->GetMousePosition();
	glm::vec2 dir = glm::normalize(mouseCoords - glm::vec2(m_halfWidth + 16, m_halfHeight + 16));

	float angle = glm::angle(dir, glm::vec2(1.0f, 0.0f));

	if (dir.y < 0)
		angle = 2 * PI - angle;
	else
		directionMultiplierY = 0;

	if (dir.x < 0)
		directionMultiplierX = -1;
	
	glm::vec2 bulletPos = { playerPosition.x + TILE_WIDTH * 0.5f + BULLET_DISTANCE_FROM_CENTER * cos(angle) + directionMultiplierX * 5.5f, 
								playerPosition.y + TILE_WIDTH * 0.5f + BULLET_DISTANCE_FROM_CENTER * sin(angle) + directionMultiplierY * 5.5f };

	BulletManager::Instance()->CreateBullet(bulletPos, dir, m_damage);

	GunManager::Instance()->Render();

	m_numInClip--;
	m_timer = 0.0f;
	m_shot = true;
	Shadow::Time::Instance()->TimerStart();

	Hud::Instance()->UpdateAmmo();
}

bool Gun::Reload()
{
	if (Shadow::InputManager::Instance()->IsMouseDown(Shadow::BUTTON_LEFT) && m_numInClip != 0)
	{
		CancelReload();
		return true;
	}

	if (m_numInClip == m_clipSize || Ammo::Instance()->GetAmmo(m_ammoType) == 0)
		return true;

	ReloadAudio();

	m_reloadTimer -= GameManager::Instance()->GetReloadMultiplier() * Shadow::Time::Instance()->GetDeltaTime();

	if (m_reloadTimer <= 0.0f)
	{
		ReloadSuccessful();
		Hud::Instance()->UpdateAmmo();
		return true;
	}

	return false;
}

void Gun::ReloadAudio()
{
	if (!m_playReloadAudio)
		return;
	
	m_reloadSound->Play();
	m_playReloadAudio = false;
}

void Gun::CancelReload()
{
	m_reloadTimer = m_timeToReload;
	m_playReloadAudio = true;
}

void Gun::Update()
{
	// Empty.
}

void Gun::ReloadSuccessful()
{
	unsigned short clipUsed = m_clipSize - m_numInClip;

	short totalAmmo = Ammo::Instance()->GetAmmo(m_ammoType);

	short amountAfterReload = totalAmmo - clipUsed;

	if (amountAfterReload <= 0)
	{
		m_numInClip = totalAmmo;
		Ammo::Instance()->ReduceAmmo(m_ammoType, totalAmmo);
	}
	else
	{
		m_numInClip = m_clipSize;
		Ammo::Instance()->ReduceAmmo(m_ammoType, clipUsed);
	}

	m_reloadTimer = m_timeToReload;
	m_playReloadAudio = true;

}