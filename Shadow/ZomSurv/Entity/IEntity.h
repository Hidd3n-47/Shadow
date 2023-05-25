#pragma once



class IEntity
{
public:
	virtual ~IEntity() { }

	// Accessors.
	inline float GetHealth() const { return m_health; }
	inline uint8_t GetDamage() const { return m_damage; }
	inline glm::vec3 GetPosition() const { return *m_position; }
	inline float GetSpeed() const { return m_speed; }

	// Mutators.
	inline void SetHealth(float health) { m_health = health; }
	inline void SetSpeed(float speed) { m_speed = speed; }
protected:
	Shadow::GameObject* m_gameObject = nullptr;

	float m_health = 0.0f;
	uint8_t m_damage = 0;
	glm::vec3* m_position = nullptr;
	float m_speed = 1.0f;
};